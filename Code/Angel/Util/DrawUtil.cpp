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
#include "../Util/DrawUtil.h"

#include "../Infrastructure/Common.h"
#include "../Infrastructure/Log.h"

void DrawCross( const Vector2& point, float size )
{
	size *= 0.5f;
	Vector2 north(point + Vector2::UnitY * size );
	Vector2 south(point - Vector2::UnitY * size );
	Vector2 east(point + Vector2::UnitX * size );
	Vector2 west(point - Vector2::UnitX * size );

	float points[] = {
		north.X, north.Y,
		south.X, south.Y,
		east.X, east.Y,
		west.X, west.Y,
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, points);
	glDrawArrays(GL_LINES, 0, 4);
}

void DrawPoint( const Vector2& point, float size )
{
	size *= 0.5f;
	Vector2 north(point + Vector2::UnitY * size );
	Vector2 south(point - Vector2::UnitY * size );
	Vector2 east(point + Vector2::UnitX * size );
	Vector2 west(point - Vector2::UnitX * size );

	float points[] = {
		north.X, north.Y,
		east.X, east.Y,
		south.X, south.Y,
		west.X, west.Y,
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, points);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void DrawLine( const Vector2& vFrom, const Vector2& vTo )
{
	float points[] = {
		vFrom.X, vFrom.Y,
		vTo.X, vTo.Y
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, points);
	glDrawArrays(GL_LINES, 0, 2);
}

bool HandleGLErrors()
{
    bool errorFound = false;
	GLenum errorCode;
	const GLubyte *errorString;
	do
	{
		errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
            errorFound = true;
			errorString = gluErrorString(errorCode);
			sysLog.Printf("OpenGL Error: %s", errorString);
		}
	} while (errorCode != GL_NO_ERROR);
    
    return errorFound;
}
