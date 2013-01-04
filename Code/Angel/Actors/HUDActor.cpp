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

#include "stdafx.h"
#include "../Actors/HUDActor.h"

#include "../Infrastructure/VecStructs.h"
#include "../Infrastructure/Camera.h"
#include "../Util/MathUtil.h"
#include "../Infrastructure/Log.h"

void HUDActor::Render()
{
	Vec2i winDimensions;
	winDimensions.X = theCamera.GetWindowWidth();
	winDimensions.Y = theCamera.GetWindowHeight();
	float pixelY = winDimensions.Y - _position.Y;
	
	//set up projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, winDimensions.X, 0, winDimensions.Y);
	
	//set up modelview
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(_position.X, pixelY, 0);
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
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

