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
#include "FTPolygonGlyphImpl.h"
#include "FTVectoriser.h"


//
//  FTGLPolyGlyph
//


FTPolygonGlyph::FTPolygonGlyph(FT_GlyphSlot glyph, float outset,
                               bool useDisplayList) :
    FTGlyph(new FTPolygonGlyphImpl(glyph, outset, useDisplayList))
{}


FTPolygonGlyph::~FTPolygonGlyph()
{}


const FTPoint& FTPolygonGlyph::Render(const FTPoint& pen, int renderMode)
{
    FTPolygonGlyphImpl *myimpl = dynamic_cast<FTPolygonGlyphImpl *>(impl);
    return myimpl->RenderImpl(pen, renderMode);
}


//
//  FTGLPolyGlyphImpl
//


FTPolygonGlyphImpl::FTPolygonGlyphImpl(FT_GlyphSlot glyph, float _outset,
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

    /*
     * David Petrie Note:
     * 
     * The original FTGL code included support for gl display lists (via 
     * glGenList, etc). This has been removed because OpenGL ES 1.1 has
     * no support for them.
     */
    
    hscale = glyph->face->size->metrics.x_ppem * 64;
    vscale = glyph->face->size->metrics.y_ppem * 64;
    outset = _outset;
    
    /*
     * David Petrie Note:
     * 
     * vectoriser->MakeMesh was being called every DoRender() in the
     * original FTGL code. I've shifted it here so it is only called once,
     * as the iPhone is not efficient enough to handle a tesselation
     * on each frame.
     */
    if (vectoriser)
        vectoriser->MakeMesh(1.0, 1, outset);
}


FTPolygonGlyphImpl::~FTPolygonGlyphImpl()
{
    if (vectoriser)
    {
        delete vectoriser;
    }
}   


const FTPoint& FTPolygonGlyphImpl::RenderImpl(const FTPoint& pen,
                                              int renderMode)
{
    glTranslatef(pen.Xf(), pen.Yf(), pen.Zf());
    if (vectoriser)
    {
        DoRender();
    }
    glTranslatef(-pen.Xf(), -pen.Yf(), -pen.Zf());
    return advance;
}


void FTPolygonGlyphImpl::DoRender()
{
    GLfloat colors[4];
    
    const FTMesh *mesh = vectoriser->GetMesh();

    for(unsigned int t = 0; t < mesh->TesselationCount(); ++t)
    {
        const FTTesselation* subMesh = mesh->Tesselation(t);
        unsigned int polygonType = subMesh->PolygonType();
        
        glGetFloatv(GL_CURRENT_COLOR, colors);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        ftglBegin(polygonType);
        ftglColor4f(colors[0], colors[1], colors[2], colors[3]);
        for(unsigned int i = 0; i < subMesh->PointCount(); ++i)
        {
            FTPoint point = subMesh->Point(i);
            ftglTexCoord2f(point.Xf() / hscale, point.Yf() / vscale);
            ftglVertex3f(point.Xf() / 64.0f, point.Yf() / 64.0f, 0.0f);
        }
        ftglEnd();
    }
}

