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
#include "../UI/GwenRenderer.h"

#include "Gwen/Utility.h"
#include "Gwen/Font.h"
#include "Gwen/Texture.h"
#include "Gwen/WindowProvider.h"

#include "../Infrastructure/Textures.h"
#include "../Infrastructure/TextRendering.h"
#include "../Infrastructure/Camera.h"
#include "../Infrastructure/Log.h"
#include "../Util/MathUtil.h"
#include "../Util/DrawUtil.h"



GwenRenderer::GwenRenderer(const String& texturePath)
{
	_vertNum = 0;

	for (int i=0; i < s_maxVerts; i++)
	{
		_vertices[ i ].z = 0.5f;
	}
	
	_windowWidth = _windowHeight = 0;
	
	GetRawImageData(texturePath, _skinTexture);
}

GwenRenderer::~GwenRenderer()
{

}


void GwenRenderer::FinishInit()
{
	_skinTexture.clear(); // just saving memory
}

void GwenRenderer::Begin()
{
	glAlphaFunc( GL_GREATER, 1.0f );

	_windowWidth = theCamera.GetWindowWidth();
	_windowHeight = theCamera.GetWindowHeight();

	//set up projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, _windowWidth, _windowHeight, 0);
	
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
	glDisable(GL_TEXTURE_2D);
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
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
	glColor4ub(color.r, color.g, color.b, color.a);
	//glColor4ubv( (GLubyte*)&color );
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

	AddVertex( rect.x, rect.y + rect.h );
	AddVertex( rect.x+rect.w, rect.y );
	AddVertex( rect.x, rect.y );

	AddVertex( rect.x, rect.y + rect.h );
	AddVertex( rect.x+rect.w, rect.y+rect.h );
	AddVertex( rect.x+rect.w, rect.y );
}

void GwenRenderer::DrawTexturedRect( Gwen::Texture* texture, Gwen::Rect targetRect, float u1, float v1, float u2, float v2)
{
	GLuint* tex = (GLuint*)texture->data;

	if (!tex)
	{
		return DrawMissingImage(targetRect);
	}

	v1 = 1.0f - v1;
	v2 = 1.0f - v2;

	Translate(targetRect);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, *tex);

	AddVertex( targetRect.x, targetRect.y + targetRect.h,				u1, v2 );
	AddVertex( targetRect.x+targetRect.w, targetRect.y,					u2, v1 );
	AddVertex( targetRect.x, targetRect.y,								u1, v1 );

	AddVertex( targetRect.x, targetRect.y + targetRect.h,				u1, v2 );
	AddVertex( targetRect.x+targetRect.w, targetRect.y+targetRect.h,	u2, v2 );
	AddVertex( targetRect.x+targetRect.w, targetRect.y,					u2, v1 );
}

void GwenRenderer::StartClip()
{
	Flush();
	Gwen::Rect rect = ClipRegion();

	// OpenGL's coords are from the bottom left
	// so we need to translate them here.
	{
		GLint view[4];
		glGetIntegerv( GL_VIEWPORT, &view[0] );
		rect.y = view[3] - (rect.y + rect.h);
	}

	glScissor( rect.x * Scale(), rect.y * Scale(), rect.w * Scale(), rect.h * Scale() );
	glEnable( GL_SCISSOR_TEST );
}

void GwenRenderer::EndClip()
{
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
		texture->data = new GLuint;
		*((GLuint*)texture->data) = texID;
		const Vec2i dimensions = GetTextureSize(texture->name.Get());
		texture->width = dimensions.X;
		texture->height = dimensions.Y;
	}
}

void GwenRenderer::FreeTexture( Gwen::Texture* texture )
{
	PurgeTexture(texture->name.Get());
	GLuint* tex = (GLuint*)texture->data;
	if (tex)
	{
		delete tex;
		texture->data = NULL;
	}
}

//void GwenRenderer::DrawMissingImage( Gwen::Rect targetRect )
//{
//
//}

Gwen::Color GwenRenderer::PixelColour( Gwen::Texture* texture, unsigned int x, unsigned int y, const Gwen::Color& col_default)
{
	if (texture == NULL) 
	{
		return col_default;
	}

	unsigned int offset = ((texture->height - y) * texture->width) + x;
	if (offset >= _skinTexture.size())
	{
		return col_default;
	}

	Gwen::Color c;
	c.r = int(_skinTexture[offset].R * 255.0f);
	c.g = int(_skinTexture[offset].G * 255.0f);
	c.b = int(_skinTexture[offset].B * 255.0f);
	c.a = int(_skinTexture[offset].A * 255.0f);
	
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
	Flush();
	Translate(pos.x, pos.y);

	String fontConv = Gwen::Utility::UnicodeToString(font->facename);
	pos.y += GetTextAscenderHeight(fontConv);

	glColor4ub(_color.r, _color.g, _color.b, _color.a);
	//glColor4ubv( (GLubyte*)&_color );
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, _windowWidth, 0, _windowHeight);
	
	DrawGameTextRaw(Gwen::Utility::UnicodeToString(text), fontConv, pos.x, pos.y);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, _windowWidth, _windowHeight, 0);
	glMatrixMode(GL_MODELVIEW);
	
}

Gwen::Point GwenRenderer::MeasureText( Gwen::Font* font, const Gwen::UnicodeString& text )
{
	if (font->data == NULL)
	{
		LoadFont(font);
	}
	Vector2 extents = GetTextExtents(Gwen::Utility::UnicodeToString(text), Gwen::Utility::UnicodeToString(font->facename));
	#if ANGEL_MOBILE
		extents.Y = extents.Y * 2.0f;
	#endif
	return Gwen::Point(MathUtil::RoundToInt(extents.X), MathUtil::RoundToInt(extents.Y));
}

