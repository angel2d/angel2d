//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
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

#pragma once

#include "../Util/StringUtil.h"
#include "../Infrastructure/Color.h"

#include "Gwen/Gwen.h"

class GwenRenderer : public Gwen::Renderer::Base
{
public:
	GwenRenderer(const String& texturePath);
	~GwenRenderer();

	virtual void FinishInit();

	virtual void Begin();
	virtual void End();

	virtual void SetDrawColor( Gwen::Color color );

	virtual void DrawFilledRect( Gwen::Rect rect );

	virtual void StartClip();
	virtual void EndClip();

	virtual void LoadTexture( Gwen::Texture* pTexture );
	virtual void FreeTexture( Gwen::Texture* pTexture );
	virtual void DrawTexturedRect( Gwen::Texture* pTexture, Gwen::Rect pTargetRect, float u1=0.0f, float v1=0.0f, float u2=1.0f, float v2=1.0f );
	//virtual void DrawMissingImage( Gwen::Rect pTargetRect );
	virtual Gwen::Color PixelColour( Gwen::Texture* pTexture, unsigned int x, unsigned int y, const Gwen::Color& col_default = Gwen::Color( 255, 255, 255, 255 ) );

	//virtual Gwen::Renderer::ICacheToTexture* GetCTT();

	virtual void LoadFont( Gwen::Font* pFont );
	virtual void FreeFont( Gwen::Font* pFont );
	virtual void RenderText( Gwen::Font* pFont, Gwen::Point pos, const Gwen::UnicodeString& text );
	virtual Gwen::Point MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString& text );

	//
	// No need to implement these functions in your derived class, but if 
	// you can do them faster than the default implementation it's a good idea to.
	//
	// virtual void DrawLinedRect( Gwen::Rect rect );
	// virtual void DrawPixel( int x, int y );
	// virtual void DrawShavedCornerRect( Gwen::Rect rect, bool bSlight = false );
	// virtual Gwen::Point MeasureText( Gwen::Font* pFont, const Gwen::String& text );
	// virtual void RenderText( Gwen::Font* pFont, Gwen::Point pos, const Gwen::String& text );

private:
	struct Vertex
	{
		float x, y, z;
		float u, v;
		unsigned char r, g, b, a;
	};

	static const int	s_maxVerts = 1024;

	void Flush();
	void AddVertex(int x, int y, float u = 0.0f , float v = 0.0f);

	Gwen::Color			_color;
	int					_vertNum;
	Vertex				_vertices[ s_maxVerts ];
    
    unsigned int        _windowWidth, _windowHeight;

	std::map<Gwen::UnicodeString, String> _unicodeCache;
    std::vector<Color> _skinTexture;
};

