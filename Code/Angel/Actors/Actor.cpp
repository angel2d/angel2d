//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2014, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../Actors/Actor.h"

#include "../Infrastructure/TagCollection.h"
#include "../Infrastructure/Textures.h"
#include "../Infrastructure/TextRendering.h"
#include "../Infrastructure/Log.h"

#include "../Util/StringUtil.h"
#include "../Util/MathUtil.h"
#include "../Messaging/Switchboard.h"
#include "../Infrastructure/World.h"
#include "../Scripting/LuaModule.h"

#include <sstream>

const float Actor::_squareVertices[] = {
	-0.5f,  0.5f,
	-0.5f, -0.5f,
	 0.5f,  0.5f,
	 0.5f, -0.5f,
};

float Actor::_circleVertices[(CIRCLE_DRAW_SECTIONS+2)*2];
float Actor::_circleTextureCoords[(CIRCLE_DRAW_SECTIONS+2)*2];
Actor* Actor::_scriptCreatedActor = NULL;
bool __inittedActorCirclePoints = false;

std::map<String, Actor*> Actor::_nameList;

Actor::Actor()
{
	if (!__inittedActorCirclePoints)
	{
		Actor::_circleVertices[0] = 0.0f;
		Actor::_circleVertices[1] = 0.0f;
		Actor::_circleTextureCoords[0] = 0.5f;
		Actor::_circleTextureCoords[1] = 0.5f;
		for (int i=1; i < CIRCLE_DRAW_SECTIONS+2; i++)
		{
			Actor::_circleVertices[i*2]     = 0.5f * cos((float) MathUtil::TwoPi * i / CIRCLE_DRAW_SECTIONS);
			Actor::_circleVertices[(i*2)+1] = 0.5f * sin((float) MathUtil::TwoPi * i / CIRCLE_DRAW_SECTIONS);
			Actor::_circleTextureCoords[i*2]     = Actor::_circleVertices[i*2]     + 0.5f;
			Actor::_circleTextureCoords[(i*2)+1] = Actor::_circleVertices[(i*2)+1] + 0.5f;
		}
		__inittedActorCirclePoints = true;
	}

	SetColor(1.0f, 1.0f, 1.0f);
	SetAlpha(1.0f);
	SetSize(1.0f);
	SetRotation(0.0f);
	SetPosition(0.0f, 0.0f);
	SetUVs(Vector2(0.f, 0.f), Vector2(1.f, 1.f));
	_name = "";

	_spriteNumFrames = 0;
	_spriteCurrentFrame = 0;
	_spriteTextureReferences[0] = -1; 
	_spriteFrameDelay = 0.0f;
	_displayListIndex = -1;

	_layer = 0;

	_drawShape = ADS_Square;
}

Actor::~Actor()
{
	StringSet::iterator it = _tags.begin();
	while (it != _tags.end())
	{
		String tag = *it;
		it++;
		Untag(tag);
	}

	Actor::_nameList.erase(_name);
}

void Actor::Update(float dt)
{
	UpdateSpriteAnimation(dt);
	
	if (_positionInterval.ShouldStep())
	{
		SetPosition(_positionInterval.Step(dt));
		if (!_positionInterval.ShouldStep())
		{
			if (_positionIntervalMessage != "")
			{
				theSwitchboard.Broadcast(new Message(_positionIntervalMessage, this));
			}
		}
	}
	if (_rotationInterval.ShouldStep())
	{
		SetRotation(_rotationInterval.Step(dt));
		if (!_rotationInterval.ShouldStep())
		{
			if (_rotationIntervalMessage != "")
			{
				theSwitchboard.Broadcast(new Message(_rotationIntervalMessage, this));
			}
		}
	}
	if (_colorInterval.ShouldStep())
	{
		SetColor(_colorInterval.Step(dt));
		if (!_colorInterval.ShouldStep())
		{
			if (_colorIntervalMessage != "")
			{
				theSwitchboard.Broadcast(new Message(_colorIntervalMessage, this));
			}
		}
	}
	if (_sizeInterval.ShouldStep())
	{
		Vector2 newSize = _sizeInterval.Step(dt);
		SetSize(newSize.X, newSize.Y);
		if (!_sizeInterval.ShouldStep())
		{
			if (_sizeIntervalMessage != "")
			{
				theSwitchboard.Broadcast(new Message(_sizeIntervalMessage, this));
			}
		}
	}
}

void Actor::UpdateSpriteAnimation(float dt)
{
	if (_spriteFrameDelay > 0.0f)
	{
		_spriteCurrentFrameDelay -= dt;

		if (_spriteCurrentFrameDelay < 0.0f)
		{
			while (_spriteCurrentFrameDelay < 0.0f)
			{
				if (_spriteAnimType == SAT_Loop)
				{
					if (_spriteCurrentFrame == _spriteAnimEndFrame)
						_spriteCurrentFrame = _spriteAnimStartFrame;
					else
						++_spriteCurrentFrame;
				}
				else if (_spriteAnimType == SAT_PingPong)
				{
					if (_spriteAnimDirection == 1)
					{
						if (_spriteCurrentFrame == _spriteAnimEndFrame)
						{
							_spriteAnimDirection = -1;
							_spriteCurrentFrame = _spriteAnimEndFrame - 1;
						}
						else
							++_spriteCurrentFrame;

					}
					else
					{
						if (_spriteCurrentFrame == _spriteAnimStartFrame)
						{
							_spriteAnimDirection = 1;
							_spriteCurrentFrame = _spriteAnimStartFrame + 1;
						}
						else 
						{
							--_spriteCurrentFrame; 
						}
					}
				}
				else if (_spriteAnimType == SAT_OneShot)
				{
					// If we're done with our one shot and they set an animName, let them know it's done.
					if (_spriteCurrentFrame == _spriteAnimEndFrame)
					{
						// Needs to get called before callback, in case they start a new animation.
						_spriteAnimType = SAT_None;

						if (_currentAnimName.length() > 0) 
						{
							AnimCallback(_currentAnimName);
						}
					}
					else
					{
						_spriteCurrentFrame += _spriteAnimDirection;
					}
				}

				_spriteCurrentFrameDelay += _spriteFrameDelay;
			}
		}
	}
}

void Actor::SetDrawShape( actorDrawShape drawShape )
{
	_drawShape = drawShape;
}

const actorDrawShape& Actor::GetDrawShape() const
{
	return _drawShape;
}

void Actor::MoveTo(const Vector2& newPosition, float duration, bool smooth, String onCompletionMessage)
{
	_positionInterval = Interval<Vector2>(_position, newPosition, duration, smooth);
	_positionIntervalMessage = onCompletionMessage;
}

void Actor::RotateTo(float newRotation, float duration, bool smooth, String onCompletionMessage)
{
	_rotationInterval = Interval<float>(_rotation, newRotation, duration, smooth);
	_rotationIntervalMessage = onCompletionMessage;
}

void Actor::ChangeColorTo(const Color& newColor, float duration, bool smooth, String onCompletionMessage)
{
	_colorInterval = Interval<Color>(_color, newColor, duration, smooth);
	_colorIntervalMessage = onCompletionMessage;
}

void Actor::ChangeSizeTo(const Vector2& newSize, float duration, bool smooth, String onCompletionMessage)
{
	_sizeInterval = Interval<Vector2>(_size, newSize, duration, smooth);
	_sizeIntervalMessage = onCompletionMessage;
}

void Actor::ChangeSizeTo(float newSize, float duration, bool smooth, String onCompletionMessage)
{
	ChangeSizeTo(Vector2(newSize, newSize), duration, smooth, onCompletionMessage);
}

void Actor::Render()
{
	glPushMatrix();
	glTranslatef(_position.X, _position.Y, 0.0f);
	glRotatef(_rotation, 0, 0, 1);
	glScalef(_size.X, _size.Y, 1.0f);
	glColor4f(_color.R, _color.G, _color.B, _color.A);

	int textureReference = _spriteTextureReferences[_spriteCurrentFrame];
	if (textureReference >= 0)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureReference);
	}
	
	switch( _drawShape )
	{
		default:
		case ADS_Square:
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, _squareVertices);
			glTexCoordPointer(2, GL_FLOAT, 0, _UV);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		break;
		
		case ADS_Circle:
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, _circleVertices);
			glTexCoordPointer(2, GL_FLOAT, 0, _circleTextureCoords);
			glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_DRAW_SECTIONS+2);
		break;

		case ADS_CustomList:
			#if ANGEL_MOBILE
				sysLog.Printf("glCallList is unsupported in OpenGL|ES.");
			#else
				if (_displayListIndex < 0)
				{
					sysLog.Printf("Invalid display list index: %i.", _displayListIndex);
				}
				else
				{
					glCallList(_displayListIndex);
				}
			#endif
		break;
	}

	if (textureReference >= 0)
	{
		glDisable(GL_TEXTURE_2D);
	}

	glPopMatrix();
}

void Actor::SetSize(float x, float y)
{
	float sizeX, sizeY;
	if (x < 0.0f)
		sizeX = 0.0f;
	else
		sizeX = x;
	if (y <= 0.f)
		sizeY = x;
	else
		sizeY = y;
	_size = Vector2(sizeX, sizeY);
}

void Actor::SetSize(const Vector2& newSize)
{
	_size = newSize;
	if (_size.X < 0.0f)
	{
		_size.X = 0.0f;
	}
	if (_size.Y < 0.0f)
	{
		_size.Y = 0.0f;
	}
}

const Vector2& Actor::GetSize() const
{
	return _size;
}

BoundingBox Actor::GetBoundingBox() const
{
	BoundingBox forReturn;
	forReturn.Min = _position - (_size / 2.0f);
	forReturn.Max = _position + (_size / 2.0f);
	return forReturn;
}

void Actor::SetPosition(float x, float y)
{
	_position.X = x;
	_position.Y = y;
}

void Actor::SetPosition(const Vector2& pos)
{
	_position = pos;
}

const Vector2& Actor::GetPosition() const
{
	return _position;
}

void Actor::SetRotation(float rotation)
{
	_rotation = rotation;
}

const float Actor::GetRotation() const
{
	return _rotation;
}

const Color& Actor::GetColor() const
{
	return _color;
}

void Actor::SetColor(float r, float g, float b, float a)
{
	_color = Color(r, g, b, a);
}

void Actor::SetColor(const Color& color)
{
	_color = color;
}

void Actor::SetAlpha(float newAlpha)
{
	_color.A = newAlpha;
}

const float Actor::GetAlpha() const
{
	return _color.A;
}

void Actor::SetSpriteTexture(int texRef, int frame)
{
	frame = MathUtil::Clamp(frame, 0, MAX_SPRITE_FRAMES - 1);

	// Make sure to bump the number of frames if this frame surpasses it.
	if (frame >= _spriteNumFrames)
	{
		_spriteNumFrames = frame + 1;
	}

	_spriteTextureReferences[frame] = texRef;
}

int Actor::GetSpriteTexture(int frame) const
{
	frame = MathUtil::Clamp(frame, 0, _spriteNumFrames - 1);

	return _spriteTextureReferences[frame];
}


// Will load the sprite if it doesn't find it in the texture cache.
// The texture cache caches textures by filename.
bool Actor::SetSprite(const String& filename, int frame, GLint clampmode, GLint filtermode, bool optional)
{
	int textureReference = GetTextureReference(filename, clampmode, filtermode, optional);
	if (textureReference == -1)
		return false;

	SetSpriteTexture(textureReference, frame);
	return true;
}

void Actor::ClearSpriteInfo()
{
	for (int i=0; i<_spriteNumFrames; ++i)
	{
		_spriteTextureReferences[i] = -1;
	}
	_spriteAnimType = SAT_None;
	_spriteFrameDelay = 0.0f;
	_spriteCurrentFrame = 0;
}

void Actor::SetSpriteFrame(int frame)
{
	frame = MathUtil::Clamp(frame, 0, _spriteNumFrames - 1);

	if (_spriteTextureReferences[frame] == -1)
	{
		sysLog.Log("setSpriteFrame() - Warning: frame(" + IntToString(frame) + ") has an invalid texture reference.");
	}

	_spriteCurrentFrame = frame;
}

void Actor::PlaySpriteAnimation(float delay, spriteAnimationType animType, int startFrame, int endFrame, const char* _animName)
{
	startFrame = MathUtil::Clamp(startFrame, 0, _spriteNumFrames-1);
	endFrame = MathUtil::Clamp(endFrame, 0, _spriteNumFrames-1);

	_spriteAnimDirection = startFrame > endFrame ? -1 : 1;

	_spriteCurrentFrameDelay = _spriteFrameDelay = delay;
	_spriteAnimType= animType;
	_spriteAnimStartFrame = _spriteCurrentFrame = startFrame;
	_spriteAnimEndFrame = endFrame;
	if (_animName)
		_currentAnimName = _animName;
}

void Actor::LoadSpriteFrames(const String& firstFilename, GLint clampmode, GLint filtermode)
{
	int extensionLocation = firstFilename.rfind(".");
	int numberSeparator = firstFilename.rfind("_");
	int numDigits = extensionLocation - numberSeparator - 1;

	// Clear out the number of frames we think we have.
	_spriteNumFrames = 0;

	bool bValidNumber = true;
	// So you're saying I've got a chance?
	if (numberSeparator > 0 && numDigits > 0)
	{
		// Now see if all of the digits between _ and . are numbers (i.e. test_001.jpg).
		for (int i=1; i<=numDigits; ++i)
		{
			char digit = firstFilename[numberSeparator+i];
			if (digit < '0' || digit > '9')
			{
				bValidNumber = false;
				break;
			}
		}
	}

	// If these aren't valid, the format is incorrect.
	if (numberSeparator == (int)String::npos || numDigits <= 0 || !bValidNumber)
	{
		sysLog.Log("LoadSpriteFrames() - Bad Format - Expecting somename_###.ext");
		sysLog.Log("Attempting to load single texture: " + firstFilename);

		if (!SetSprite(firstFilename, 0, clampmode, filtermode))
			return;
	}

	// If we got this far, the filename format is correct.
	String numberString;
	// The number string is just the digits between the '_' and the file extension (i.e. 001).
	numberString.append(firstFilename.c_str(), numberSeparator+1, numDigits);

	// Get our starting numberical value.
	int number = atoi(numberString.c_str());

	String baseFilename;
	// The base name is everything up to the '_' before the number (i.e. somefile_).
	baseFilename.append( firstFilename.c_str(), numberSeparator+1);

	String extension;
	// The extension is everything after the number (i.e. .jpg).
	extension.append(firstFilename.c_str(), extensionLocation, firstFilename.length() - extensionLocation);

	// Keep loading until we stop finding images in the sequence.
	while (true)
	{
		// Build up the filename of the current image in the sequence.
		String newFilename = baseFilename + numberString + extension;
		
		// Were we able to load the file for this sprite?
		if (!SetSprite(newFilename, _spriteNumFrames, clampmode, filtermode, true /*optional*/))
		{
			break;
		}

		// Verify we don't go out of range on our hard-coded frame limit per sprite.
		if (_spriteNumFrames >= MAX_SPRITE_FRAMES)
		{
			sysLog.Log("Maximum number of frames reached (" + IntToString(MAX_SPRITE_FRAMES) + "). Bailing out...");
			sysLog.Log("Increment MAX_SPRITE_FRAMES if you need more.");
			break;
		}

		// Bump the number to the next value in the sequence.
		++number;

		// Serialize the numerical value to it so we can retrieve the string equivalent.
		std::stringstream sstr;
		sstr << number;
		String newNumberString = sstr.str();

		// We assume that all the files have as many numerical digits as the first one (or greater) (i.e. 01..999).
		// See if we need to pad with leading zeros.
		int numLeadingZeros = numDigits - (int)newNumberString.length();

		// Do the leading zero padding.
		for (int i=0; i<numLeadingZeros; ++i)
		{
			newNumberString = '0' + newNumberString;
		}

		// Save off the newly formulated number string for the next image in the sequence.
		numberString = newNumberString;
	}
}

void Actor::SetUVs(const Vector2& lowleft, const Vector2& upright)
{
	_UV[0] = lowleft.X;
	_UV[1] = upright.Y;
	_UV[2] = lowleft.X;
	_UV[3] = lowleft.Y;
	_UV[4] = upright.X;
	_UV[5] = upright.Y;
	_UV[6] = upright.X;
	_UV[7] = lowleft.Y;
}

void Actor::GetUVs(Vector2 &lowleft, Vector2 &upright) const
{
	lowleft.X = _UV[2];
	lowleft.Y = _UV[3];
	upright.X = _UV[4];
	upright.Y = _UV[5];
}

const bool Actor::IsTagged(const String& tag)
{
	String searchTag = ToLower(tag);
	StringSet::iterator it = _tags.find(searchTag);
	if (it != _tags.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Actor::Tag(const String& newTag)
{
	StringList tags = SplitString(newTag, ", ");
	for(unsigned int i=0; i < tags.size(); i++)
	{
		tags[i] = ToLower(tags[i]);
		_tags.insert(tags[i]);
		theTagList.AddObjToTagList(this, tags[i]);
	}
}

void Actor::Untag(const String& oldTag)
{
	String delTag = ToLower(oldTag);
	_tags.erase(delTag);
	theTagList.RemoveObjFromTagList(this, delTag);
}

const StringSet& Actor::GetTags() const
{
	return _tags;
}

const String& Actor::SetName(String newName)
{
	//overkill for sure, but who knows how many unique actors we'll need
	static unsigned long long nameIndex = 0;
	
	if(newName.length() == 0)
	{
		newName = GetClassName();
	}
	
	newName[0] = toupper(newName[0]);
	
	const Actor* preNamed = Actor::GetNamed(newName);
	if ((preNamed == NULL) || (preNamed == this))
	{
		_name = newName;
	}
	else
	{
		_name = newName + ULLIntToString(++nameIndex);
	}
	
	Actor::_nameList[_name] = this;
	
	return _name;
}

const String& Actor::GetName() const
{
	return _name;
}

Actor* const Actor::GetNamed(const String& nameLookup)
{
	std::map<String,Actor*>::iterator it = _nameList.find(nameLookup);
	if (it == _nameList.end())
	{
		return NULL;
	}
	else
	{
		return it->second;
	}
}

Actor* Actor::Create(const String& archetype)
{
	lua_State* L = LuaScriptingModule::GetLuaState();
	lua_getglobal(L, "Actor_CreateAndRegister");
	lua_pushstring(L, archetype.c_str());
	if (lua_pcall(L, 1, 0, 0))
	{
		const char* errs = lua_tostring(L, -1);
		sysLog.Printf("ERROR: %s\n", errs);
		// error, will be in the stack trace
		lua_gc(L, LUA_GCCOLLECT, 0); // garbage collect on error
		return NULL;
	}
	else
	{
		return _scriptCreatedActor;
	}
}

void Actor::SetLayer(int layerIndex)
{
	theWorld.UpdateLayer(this, layerIndex);
}

void Actor::SetLayer(const String& layerName)
{
	theWorld.UpdateLayer(this, layerName);
}
