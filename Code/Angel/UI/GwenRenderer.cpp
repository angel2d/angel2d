//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2012, Shane Liesegang
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
#include "../UI/GwenRenderer.h"

#include "Gwen/Utility.h"
#include "Gwen/Font.h"
#include "Gwen/Texture.h"
#include "Gwen/WindowProvider.h"

#include "../Infrastructure/Textures.h"
#include "../Infrastructure/TextRendering.h"
#include "../Infrastructure/Camera.h"

GwenRenderer::GwenRenderer()
{
	_vertNum = 0;

	for (int i=0; i < s_maxVerts; i++)
	{
		_vertices[ i ].z = 0.5f;
	}
}

GwenRenderer::~GwenRenderer()
{

}


void GwenRenderer::Init()
{

}

void GwenRenderer::Begin()
{
	glAlphaFunc( GL_GREATER, 1.0f );

	Vec2i winDimensions;
	winDimensions.X = theCamera.GetWindowWidth();
	winDimensions.Y = theCamera.GetWindowHeight();
	
	//set up projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, winDimensions.X, 0, winDimensions.Y);
	
	//set up modelview
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void GwenRenderer::End()
{
	Flush();
	glAlphaFunc(GL_ALWAYS, 0.0f);

    glDisableClientState( GL_COLOR_ARRAY );
    
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void GwenRenderer::Flush()
{
	if ( _vertNum == 0 ) 
	{
		return;
	}

	glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), (void*) &_vertices[0].x );
	glEnableClientState( GL_VERTEX_ARRAY );

	glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)&_vertices[0].r );
	glEnableClientState( GL_COLOR_ARRAY );

	glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), (void*) &_vertices[0].u );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	glDrawArrays( GL_TRIANGLES, 0, (GLsizei) _vertNum );

	_vertNum = 0;
}

void GwenRenderer::AddVertex(int x, int y, float u, float v)
{
	if ( _vertNum >= s_maxVerts - 1 )
	{
		Flush();
	}

	_vertices[ _vertNum ].x = (float)x;
	_vertices[ _vertNum ].y = (float)y;
	_vertices[ _vertNum ].u = u;
	_vertices[ _vertNum ].v = v;

	_vertices[ _vertNum ].r = _color.r;
	_vertices[ _vertNum ].g = _color.g;
	_vertices[ _vertNum ].b = _color.b;
	_vertices[ _vertNum ].a = _color.a;

	_vertNum++;
}

void GwenRenderer::SetDrawColor( Gwen::Color color )
{
	glColor4ubv( (GLubyte*)&color );
	_color = color;
}

void GwenRenderer::DrawFilledRect( Gwen::Rect rect )
{
	GLboolean texturesOn;

	glGetBooleanv(GL_TEXTURE_2D, &texturesOn);
	if ( texturesOn )
	{
		Flush();
		glDisable(GL_TEXTURE_2D);
	}

	Translate( rect );

	AddVertex( rect.x, rect.y );
	AddVertex( rect.x+rect.w, rect.y );
	AddVertex( rect.x, rect.y + rect.h );

	AddVertex( rect.x+rect.w, rect.y );
	AddVertex( rect.x+rect.w, rect.y+rect.h );
	AddVertex( rect.x, rect.y + rect.h );
}

void GwenRenderer::StartClip()
{
    return;
    
	Flush();
	Gwen::Rect rect = ClipRegion();

	// OpenGL's coords are from the bottom left
	// so we need to translate them here.
//	{
//		GLint view[4];
//		glGetIntegerv( GL_VIEWPORT, &view[0] );
//		rect.y = view[3] - (rect.y + rect.h);
//	}

	glScissor( rect.x * Scale(), rect.y * Scale(), rect.w * Scale(), rect.h * Scale() );
	glEnable( GL_SCISSOR_TEST );
}

void GwenRenderer::EndClip()
{
    return;
	Flush();
	glDisable( GL_SCISSOR_TEST );
}

void GwenRenderer::LoadTexture( Gwen::Texture* texture )
{
	const int texID = GetTextureReference(texture->name.Get());
	if (texID < 0)
	{
		texture->failed = true;
		texture->data = 0;
	}
	else
	{
		texture->failed = false;
		texture->data = (void*)texID;
		const Vec2i dimensions = GetTextureSize(texture->name.Get());
		texture->width = dimensions.X;
		texture->height = dimensions.Y;
	}
}

void GwenRenderer::FreeTexture( Gwen::Texture* texture )
{
	PurgeTexture(texture->name.Get());
}

void GwenRenderer::DrawTexturedRect( Gwen::Texture* texture, Gwen::Rect targetRect, float u1, float v1, float u2, float v2)
{
//	GLuint* tex = (GLuint*)texture->data;
//
//	if (!tex)
//	{
//		return DrawMissingImage(targetRect);
//	}
//
//	Translate(targetRect);
//
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, *tex);
//
//	AddVertex( targetRect.x, targetRect.y,			u1, v1 );
//	AddVertex( targetRect.x+targetRect.w, targetRect.y,		u2, v1 );
//	AddVertex( targetRect.x, targetRect.y + targetRect.h,	u1, v2 );
//
//	AddVertex( targetRect.x+targetRect.w, targetRect.y,		u2, v1 );
//	AddVertex( targetRect.x+targetRect.w, targetRect.y+targetRect.h, u2, v2 );
//	AddVertex( targetRect.x, targetRect.y + targetRect.h, u1, v2 );	
}

//void GwenRenderer::DrawMissingImage( Gwen::Rect targetRect )
//{
//
//}

Gwen::Color GwenRenderer::PixelColour( Gwen::Texture* texture, unsigned int x, unsigned int y, const Gwen::Color& col_default)
{
	GLuint* tex = (GLuint*)texture->data;
	if ( !tex ) return col_default;

	unsigned int pixelSize = sizeof(unsigned char) * 4;

	glBindTexture( GL_TEXTURE_2D, *tex );

	unsigned char* data = (unsigned char*) malloc( pixelSize * texture->width * texture->height );

	glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	unsigned int offset = (y * texture->width + x) * 4;

	Gwen::Color c;
	c.r = data[0 + offset];
	c.g = data[1 + offset];
	c.b = data[2 + offset];
	c.a = data[3 + offset];

	//
	// Retrieving the entire texture for a single pixel read
	// is kind of a waste - maybe cache this pointer in the texture
	// data and then release later on? It's never called during runtime
	// - only during initialization.
	//
	free( data );

	return c;
}

//Gwen::Renderer::ICacheToTexture* GwenRenderer::GetCTT()
//{
//    return NULL;
//}

void GwenRenderer::LoadFont( Gwen::Font* font )
{
	font->realsize = font->size * Scale();
	String fontName = Gwen::Utility::UnicodeToString(font->facename);
	_unicodeCache[font->facename] = fontName;
	if (!IsFontRegistered(fontName))
	{
		if (RegisterFont(fontName, font->realsize, fontName))
		{
			font->data = (void*)1;
		}
		else
		{
			font->data = NULL;
		}
	}
}

void GwenRenderer::FreeFont( Gwen::Font* font )
{
	std::map<Gwen::UnicodeString, String>::iterator it = _unicodeCache.find(font->facename);
	if (it != _unicodeCache.end())
	{
        UnRegisterFont(it->second);
	}
}

void GwenRenderer::RenderText( Gwen::Font* font, Gwen::Point pos, const Gwen::UnicodeString& text )
{
    Translate(pos.x, pos.y);
    glColor4ubv( (GLubyte*)&_color );
	DrawGameTextRaw(Gwen::Utility::UnicodeToString(text), Gwen::Utility::UnicodeToString(font->facename), pos.x, pos.y);
}

Gwen::Point GwenRenderer::MeasureText( Gwen::Font* font, const Gwen::UnicodeString& text )
{
	if (font->data == NULL)
	{
		LoadFont(font);
	}
	Vector2 extents = GetTextExtents(Gwen::Utility::UnicodeToString(text), Gwen::Utility::UnicodeToString(font->facename));
    return Gwen::Point((int)extents.X, (int)extents.Y);
}

//
// No need to implement these functions in your derived class, but if 
// you can do them faster than the default implementation it's a good idea to.
//
/*
void GwenRenderer::DrawLinedRect( Gwen::Rect rect )
{

}
void GwenRenderer::DrawPixel( int x, int y )
{

}
void GwenRenderer::DrawShavedCornerRect( Gwen::Rect rect, bool bSlight = false )
{

}
Gwen::Point GwenRenderer::MeasureText( Gwen::Font* font, const Gwen::String& text )
{

}
void GwenRenderer::RenderText( Gwen::Font* font, Gwen::Point pos, const Gwen::String& text )
{

}
*/