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
#include "../Infrastructure/TextRendering.h"

#include "../Infrastructure/Camera.h"
#include "../Infrastructure/VecStructs.h"
#include "../Infrastructure/Log.h"
#include "../Infrastructure/World.h"

#if ANGEL_MOBILE
	#include <ftgl/ftgles.h>
#else
	#include "FTFont.h"
	#include "FTGLTextureFont.h"
#endif


std::map<String, FTFont*> _fontCache;

const bool RegisterFont(const String& filename, int pointSize, const String& nickname)
{
	std::map<String,FTFont*>::iterator it = _fontCache.find(nickname);
	if(it != _fontCache.end())
	{
		UnRegisterFont(nickname);
	}
	
	if (theWorld.IsHighResScreen())
	{
		pointSize = pointSize * 2;
	}

	FTFont *font = new FTGLTextureFont(filename.c_str());
	if(font->Error())
	{
		sysLog.Log("Failed to open font " + filename);
		return false;
	}
	if(!font->FaceSize(pointSize))
	{
		sysLog.Log("Failed to set size.");
		return false;
	}
	font->CharMap(FT_ENCODING_NONE);
	font->UseDisplayList(true);

	_fontCache[nickname] = font;
	return true;
}

const bool IsFontRegistered(const String& nickname)
{
	std::map<String,FTFont*>::iterator it = _fontCache.find(nickname);
	if (it != _fontCache.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool UnRegisterFont(const String& nickname)
{
	std::map<String,FTFont*>::iterator it = _fontCache.find(nickname);
	if (it == _fontCache.end())
	{
		sysLog.Log("No font called \"" + nickname + "\"; un-registration failed.");
		return false;
	}
	delete it->second;
	it->second = NULL; 
	_fontCache.erase(it);
	return true;
}

Vector2 DrawGameText(const String& text, const String& nickname, int pixelX, int pixelY, float angle)
{
	Vector2 forReturn;

	std::map<String,FTFont*>::iterator it = _fontCache.find(nickname);
	if (it == _fontCache.end())
	{
		return forReturn;
	}
	
	Vec2i winDimensions;
	winDimensions.X = theCamera.GetWindowWidth();
	winDimensions.Y = theCamera.GetWindowHeight();
	pixelY = winDimensions.Y - pixelY;

	//set up projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0f, winDimensions.X, 0.0f, winDimensions.Y);

	//set up modelview
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef((GLfloat)pixelX, (GLfloat)pixelY, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	it->second->Render(text.c_str());
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	float llx, lly, llz, urx, ury, urz;
	it->second->BBox(text.c_str(), llx, lly, llz, urx, ury, urz);
	forReturn.X = urx - llx;
	forReturn.Y = ury - lly;	
	return forReturn;
}

Vector2 DrawGameTextRaw(const String& text, const String& nickname, int pixelX, int pixelY, float angle)
{
    Vector2 forReturn;
    
	std::map<String,FTFont*>::iterator it = _fontCache.find(nickname);
	if (it == _fontCache.end())
	{
		return forReturn;
	}
    
    pixelY = theCamera.GetWindowHeight() - pixelY;
    
	//set up modelview
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef((GLfloat)pixelX, (GLfloat)pixelY, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
    
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	it->second->Render(text.c_str());
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
    
	glPopMatrix();
    
	float llx, lly, llz, urx, ury, urz;
	it->second->BBox(text.c_str(), llx, lly, llz, urx, ury, urz);
	forReturn.X = urx - llx;
	forReturn.Y = ury - lly;
	return forReturn;
}

Vector2 GetTextExtents(const String& text, const String& nickname)
{
	Vector2 forReturn;

	std::map<String,FTFont*>::iterator it = _fontCache.find(nickname);
	if (it == _fontCache.end())
	{
		return forReturn;
	}

	float llx, lly, llz, urx, ury, urz;
	it->second->BBox(text.c_str(), llx, lly, llz, urx, ury, urz);
	forReturn.X = urx - llx;
	forReturn.Y = ury - lly;
		
	return forReturn;
}

float GetTextAscenderHeight(const String& nickname)
{
    std::map<String,FTFont*>::iterator it = _fontCache.find(nickname);
	if (it == _fontCache.end())
	{
		return 0.0f;
	}
    
    return it->second->Ascender();
}
