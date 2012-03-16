/*
 * FTGL - OpenGL font library
 *
 * Copyright (c) 2001-2004 Henry Maddocks <ftgl@opengl.geek.nz>
 * Copyright (c) 2008 Sam Hocevar <sam@zoy.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "config.h"

#include <cassert>
#include <string> // For memset

#include "FTGL/ftgles.h"

#include "FTInternals.h"

#include "../FTGlyph/FTTextureGlyphImpl.h"
#include "./FTTextureFontImpl.h"


//
//  FTTextureFont
//


FTTextureFont::FTTextureFont(char const *fontFilePath) :
    FTFont(new FTTextureFontImpl(this, fontFilePath))
{}


FTTextureFont::FTTextureFont(const unsigned char *pBufferBytes,
                             size_t bufferSizeInBytes) :
    FTFont(new FTTextureFontImpl(this, pBufferBytes, bufferSizeInBytes))
{}


FTTextureFont::~FTTextureFont()
{}


FTGlyph* FTTextureFont::MakeGlyph(FT_GlyphSlot ftGlyph)
{
    FTTextureFontImpl *myimpl = dynamic_cast<FTTextureFontImpl *>(impl);
    if(!myimpl)
    {
        return NULL;
    }

    return myimpl->MakeGlyphImpl(ftGlyph);
}


//
//  FTTextureFontImpl
//


static inline GLuint NextPowerOf2(GLuint in)
{
     in -= 1;

     in |= in >> 16;
     in |= in >> 8;
     in |= in >> 4;
     in |= in >> 2;
     in |= in >> 1;

     return in + 1;
}


FTTextureFontImpl::FTTextureFontImpl(FTFont *ftFont, const char* fontFilePath)
:   FTFontImpl(ftFont, fontFilePath),
    maximumGLTextureSize(0),
    textureWidth(0),
    textureHeight(0),
    glyphHeight(0),
    glyphWidth(0),
    padding(3),
    xOffset(0),
    yOffset(0)
{
    load_flags = FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP;
    remGlyphs = numGlyphs = face.GlyphCount();
	preRendered = false;
}


FTTextureFontImpl::FTTextureFontImpl(FTFont *ftFont,
                                     const unsigned char *pBufferBytes,
                                     size_t bufferSizeInBytes)
:   FTFontImpl(ftFont, pBufferBytes, bufferSizeInBytes),
    maximumGLTextureSize(0),
    textureWidth(0),
    textureHeight(0),
    glyphHeight(0),
    glyphWidth(0),
    padding(3),
    xOffset(0),
    yOffset(0)
{
    load_flags = FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP;
    remGlyphs = numGlyphs = face.GlyphCount();
}


FTTextureFontImpl::~FTTextureFontImpl()
{
    if(textureIDList.size())
    {
        glDeleteTextures((GLsizei)textureIDList.size(),
                         (const GLuint*)&textureIDList[0]);
    }
}


FTGlyph* FTTextureFontImpl::MakeGlyphImpl(FT_GlyphSlot ftGlyph)
{
    glyphHeight = static_cast<int>(charSize.Height() + 0.5);
    glyphWidth = static_cast<int>(charSize.Width() + 0.5);

    if(glyphHeight < 1) glyphHeight = 1;
    if(glyphWidth < 1) glyphWidth = 1;
	
    if(textureIDList.empty())
    {
        textureIDList.push_back(CreateTexture());
        xOffset = yOffset = padding;
    }

    if(xOffset > (textureWidth - glyphWidth))
    {
        xOffset = padding;
        yOffset += glyphHeight;

        if(yOffset > (textureHeight - glyphHeight))
        {
            textureIDList.push_back(CreateTexture());
            yOffset = padding;
        }
    }

    FTTextureGlyph* tempGlyph = new FTTextureGlyph(ftGlyph, textureIDList[textureIDList.size() - 1],
                                                    xOffset, yOffset, textureWidth, textureHeight);
    xOffset += static_cast<int>(tempGlyph->BBox().Upper().X() - tempGlyph->BBox().Lower().X() + padding + 0.5);
	
	--remGlyphs;

    return tempGlyph;
}


void FTTextureFontImpl::CalculateTextureSize()
{
    //if(!maximumGLTextureSize)
   // {
    //    maximumGLTextureSize = 512;
   //     glGetIntegerv(GL_MAX_TEXTURE_SIZE, (GLint*)&maximumGLTextureSize);
    //    assert(maximumGLTextureSize); // If you hit this then you have an invalid OpenGL context.
   // }
	maximumGLTextureSize = 1024;
    textureWidth = NextPowerOf2((remGlyphs * glyphWidth) + (padding * 2));
    textureWidth = textureWidth > maximumGLTextureSize ? maximumGLTextureSize : textureWidth;

    int h = static_cast<int>((textureWidth - (padding * 2)) / glyphWidth + 0.5);

    textureHeight = NextPowerOf2(((numGlyphs / h) + 1) * glyphHeight);
    textureHeight = textureHeight > maximumGLTextureSize ? maximumGLTextureSize : textureHeight;
}


GLuint FTTextureFontImpl::CreateTexture()
{
	CalculateTextureSize();

    int totalMemory = textureWidth * textureHeight;
    unsigned char* textureMemory = new unsigned char[totalMemory];
    memset(textureMemory, 0, totalMemory);
	
    GLuint textID;
    glGenTextures(1, (GLuint*)&textID);

    glBindTexture(GL_TEXTURE_2D, textID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, textureWidth, textureHeight,
                 0, GL_ALPHA, GL_UNSIGNED_BYTE, textureMemory);
	
	printf("texture dimensions: %d %d\n", textureWidth, textureHeight);
	
    delete [] textureMemory;

    return textID;
}


bool FTTextureFontImpl::FaceSize(const unsigned int size, const unsigned int res)
{
    if(!textureIDList.empty())
    {
        glDeleteTextures((GLsizei)textureIDList.size(), (const GLuint*)&textureIDList[0]);
        textureIDList.clear();
        remGlyphs = numGlyphs = face.GlyphCount();
    }

    return FTFontImpl::FaceSize(size, res);
}


template <typename T>
inline FTPoint FTTextureFontImpl::RenderI(const T* string, const int len,
                                          FTPoint position, FTPoint spacing,
                                          int renderMode)
{
	disableTexture2D = false;
	disableBlend = false;
	FTPoint tmp;
	
	if (preRendered)
	{
		tmp = FTFontImpl::Render(string, len, position, spacing, renderMode);
	}
	else 
	{
		PreRender();
		tmp = FTFontImpl::Render(string, len, position, spacing, renderMode);
		PostRender();
	}
    return tmp;
}


void FTTextureFontImpl::PreRender() 
{
	disableTexture2D = false;
	disableBlend = false;
	GLfloat colors[4];
	preRendered = true;
	if (!glIsEnabled(GL_BLEND))
	{
		glEnable(GL_BLEND);
		disableBlend = true;
	}
	else 
	{
		glGetIntegerv(GL_BLEND_SRC, &originalBlendSfactor);
		glGetIntegerv(GL_BLEND_DST, &originalBlendDfactor);
	}
	
	
	if (!glIsEnabled(GL_TEXTURE_2D))
	{
		glEnable(GL_TEXTURE_2D);
		disableTexture2D = true;
	}
	
	// FTTextureGlyphImpl::ResetActiveTexture();
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glGetFloatv(GL_CURRENT_COLOR, colors);
	
	ftglColor4f(colors[0], colors[1], colors[2], colors[3]);
	ftglBegin(GL_QUADS);
}


void FTTextureFontImpl::PostRender() 
{
	preRendered = false;
	ftglEnd();
	
	if (disableBlend)
	{
		glDisable(GL_BLEND);
	}
	else
	{
		glBlendFunc(originalBlendSfactor, originalBlendDfactor);
	}
	
	if (disableTexture2D)
		glDisable(GL_TEXTURE_2D);
}


FTPoint FTTextureFontImpl::Render(const char * string, const int len,
                                  FTPoint position, FTPoint spacing,
                                  int renderMode)
{
    return RenderI(string, len, position, spacing, renderMode);
}


FTPoint FTTextureFontImpl::Render(const wchar_t * string, const int len,
                                  FTPoint position, FTPoint spacing,
                                  int renderMode)
{
    return RenderI(string, len, position, spacing, renderMode);
}

