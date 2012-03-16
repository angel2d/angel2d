/*
 * FTGL - OpenGL font library
 *
 * Copyright (c) 2001-2004 Henry Maddocks <ftgl@opengl.geek.nz>
 * Copyright (c) 2008 Éric Beets <ericbeets@free.fr>
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

#include "FTGL/ftgles.h"

#include "FTInternals.h"
#include "FTOutlineGlyphImpl.h"
#include "FTVectoriser.h"


//
//  FTGLOutlineGlyph
//


FTOutlineGlyph::FTOutlineGlyph(FT_GlyphSlot glyph, float outset,
                               bool useDisplayList) :
    FTGlyph(new FTOutlineGlyphImpl(glyph, outset, useDisplayList))
{}


FTOutlineGlyph::~FTOutlineGlyph()
{}


const FTPoint& FTOutlineGlyph::Render(const FTPoint& pen, int renderMode)
{
    FTOutlineGlyphImpl *myimpl = dynamic_cast<FTOutlineGlyphImpl *>(impl);
    return myimpl->RenderImpl(pen, renderMode);
}


//
//  FTGLOutlineGlyphImpl
//


FTOutlineGlyphImpl::FTOutlineGlyphImpl(FT_GlyphSlot glyph, float _outset,
                                       bool useDisplayList)
:   FTGlyphImpl(glyph),
    glList(0)
{
    if(ft_glyph_format_outline != glyph->format)
    {
        err = 0x14; // Invalid_Outline
        return;
    }

    vectoriser = new FTVectoriser(glyph);

    if((vectoriser->ContourCount() < 1) || (vectoriser->PointCount() < 3))
    {
        delete vectoriser;
        vectoriser = NULL;
        return;
    }

    outset = _outset;
}


FTOutlineGlyphImpl::~FTOutlineGlyphImpl()
{
	if (vectoriser)
    {
        delete vectoriser;
    }
}


const FTPoint& FTOutlineGlyphImpl::RenderImpl(const FTPoint& pen,
                                              int renderMode)
{
    if(vectoriser)
    {
        RenderContours(pen);
    }

    return advance;
}


void FTOutlineGlyphImpl::RenderContours(const FTPoint& pen)
{
	for(unsigned int c = 0; c < vectoriser->ContourCount(); ++c)
    {
        const FTContour* contour = vectoriser->Contour(c);
		
		for(unsigned int i = 0; i < contour->PointCount(); ++i)
		{
			unsigned ii = (i+1 == contour->PointCount()) ? 0 : i+1;
			
			FTPoint point1 = FTPoint(contour->Point(i).X() + contour->Outset(i).X() * outset,
									 contour->Point(i).Y() + contour->Outset(i).Y() * outset,
									 0);
			FTPoint point2 = FTPoint(contour->Point(ii).X() + contour->Outset(ii).X() * outset,
									 contour->Point(ii).Y() + contour->Outset(ii).Y() * outset,
									 0);
			ftglVertex2f((point1.Xf() / 64.0f) + pen.Xf(), 
						 (point1.Yf() / 64.0f) + pen.Yf());
			ftglVertex2f((point2.Xf() / 64.0f) + pen.Xf(), 
						 (point2.Yf() / 64.0f) + pen.Yf());
		}
        
    }
}

