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
#include "../Actors/TextActor.h"

#include "../Infrastructure/TextRendering.h"
#include "../Infrastructure/Camera.h"
#include "../Util/StringUtil.h"
#include "../Util/MathUtil.h"
#include "../Messaging/Switchboard.h"
#include "../Util/DrawUtil.h"

TextActor::TextActor(const String& fontNickname, const String& displayString, TextAlignment align, int lineSpacing)
{
	SetColor(0.0f, 0.0f, 0.0f); //default text is black
	_fontNickname = fontNickname;
	_alignment = align;
	_lineSpacing = lineSpacing;
	_screenPosition = Vector2::Zero;
	_extents.Min = Vector2::Zero;
	_extents.Max = Vector2::Zero;

	SetDisplayString(displayString);
	
	theSwitchboard.SubscribeTo(this, "CameraChange");
}

void TextActor::Render()
{
	glColor4f(_color.R, _color.G, _color.B, _color.A);
	for(unsigned int i=0; i < _displayStrings.size(); i++)
	{
		DrawGameText(_displayStrings[i]._string, _fontNickname, (int)_displayStrings[i]._position.X, (int)_displayStrings[i]._position.Y, _rotation + theCamera.GetRotation());
	}
}

const String& TextActor::GetFont() const
{
	return _fontNickname;
}

void TextActor::SetFont(const String& newFont)
{
	_fontNickname = newFont;
	CalculatePosition();
}

const String& TextActor::GetDisplayString() const
{
	return _rawString;
}

void TextActor::SetDisplayString(const String& newString)
{
	_rawString = newString;
	_displayStrings.clear();
	StringList strings = SplitString(_rawString, "\n", false);
	StringList::iterator it = strings.begin();
	while(it!= strings.end())
	{
		TextNugget nugget;
		nugget._string = *it;
		_displayStrings.push_back(nugget);
		it++;
	}

	CalculatePosition();
}

const TextAlignment TextActor::GetAlignment()
{
	return _alignment;
}

void TextActor::SetAlignment(TextAlignment newAlignment)
{
	_alignment = newAlignment;
	CalculatePosition();
}

const int TextActor::GetLineSpacing()
{
	return _lineSpacing;
}

void TextActor::SetLineSpacing(int newSpacing)
{
	_lineSpacing = newSpacing;
	CalculatePosition();
}

void TextActor::SetPosition(float x, float y)
{
	Actor::SetPosition(x, y);
	CalculatePosition();
}

void TextActor::SetRotation(float newRotation)
{
	Actor::SetRotation(newRotation);
	CalculatePosition();
}

void TextActor::SetPosition(const Vector2& position)
{
	Actor::SetPosition(position);
	CalculatePosition();
}

void TextActor::ReceiveMessage(Message* m)
{
	if (m->GetMessageName() == "CameraChange")
	{
		CalculatePosition();
	}
}

BoundingBox TextActor::GetBoundingBox() const
{
	return _extents; 
}

void TextActor::CalculatePosition()
{
	Vector2 largest = Vector2::Zero;
	std::vector<TextNugget>::iterator it = _displayStrings.begin();
	while(it != _displayStrings.end())
	{
		(*it)._extents = GetTextExtents((*it)._string, _fontNickname);
		if ((*it)._extents.X > largest.X)
		{
			largest.X = (*it)._extents.X;
		}
		if ((*it)._extents.Y > largest.Y)
		{
			largest.Y = (*it)._extents.Y;
		}

		it++;
	}

	Vector2 startPoint = MathUtil::WorldToScreen(GetPosition());
	Vector2 currentPoint(startPoint.X, startPoint.Y);

	it = _displayStrings.begin();
	while(it != _displayStrings.end())
	{
		Vector2 size;
		switch(_alignment)
		{
			case TXT_Left:
				(*it)._position = currentPoint;
				break;
			case TXT_Center:
				(*it)._position = 
					currentPoint + 
						Vector2::Rotate(Vector2(-(*it)._extents.X * 0.5f, 0.0f), -MathUtil::ToRadians(GetRotation() + theCamera.GetRotation()));
				break;
			case TXT_Right:
				(*it)._position = 
					currentPoint + 
						Vector2::Rotate(Vector2(-(*it)._extents.X, 0.0f), -MathUtil::ToRadians(GetRotation() + theCamera.GetRotation()));
				break;
		}
		
		Vector2 translation(0.0f, largest.Y + _lineSpacing);
		currentPoint += Vector2::Rotate(translation, -MathUtil::ToRadians(GetRotation() + theCamera.GetRotation()));
		it++;
	}
	
	//recalculate extents
	float minX, minY, maxX, maxY; 
	switch(_alignment)
	{
		case TXT_Left:
			minX = _position.X; 
			minY = _position.Y - (MathUtil::PixelsToWorldUnits(largest.Y + _lineSpacing) * (_displayStrings.size() - 1));
			maxX = _position.X + MathUtil::PixelsToWorldUnits(largest.X);
			maxY = _position.Y + MathUtil::PixelsToWorldUnits(largest.Y);
			_extents.Min = Vector2(minX, minY); 
			_extents.Max = Vector2(maxX, maxY); 
			break;
		case TXT_Center:
			minX = _position.X - (MathUtil::PixelsToWorldUnits(largest.X) * 0.5f); 
			minY = _position.Y - (MathUtil::PixelsToWorldUnits(largest.Y + _lineSpacing) * (_displayStrings.size() - 1));
			maxX = _position.X + (MathUtil::PixelsToWorldUnits(largest.X) * 0.5f);
			maxY = _position.Y + MathUtil::PixelsToWorldUnits(largest.Y);
			_extents.Min = Vector2(minX, minY); 
			_extents.Max = Vector2(maxX, maxY); 
			break;
		case TXT_Right:
			minX = _position.X - MathUtil::PixelsToWorldUnits(largest.X); 
			minY = _position.Y - (MathUtil::PixelsToWorldUnits(largest.Y + _lineSpacing) * (_displayStrings.size() - 1));
			maxX = _position.X;
			maxY = _position.Y + MathUtil::PixelsToWorldUnits(largest.Y);
			_extents.Min = Vector2(minX, minY); 
			_extents.Max = Vector2(maxX, maxY); 
			break;
	}
}
