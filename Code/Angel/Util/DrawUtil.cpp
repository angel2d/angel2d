//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2010, Shane J. M. Liesegang
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

#include "../Util/DrawUtil.h"

#include "../Infrastructure/Common.h"

void DrawCross( const Vector2& point, float size )
{
	size *= 0.5f;
	Vector2 north(point + Vector2::UnitY * size );
	Vector2 south(point - Vector2::UnitY * size );
	Vector2 east(point + Vector2::UnitX * size );
	Vector2 west(point - Vector2::UnitX * size );

	glBegin(GL_LINES);

	glVertex2f(north.X, north.Y);
	glVertex2f(south.X, south.Y);
	glVertex2f(east.X, east.Y);
	glVertex2f(west.X, west.Y);

	glEnd();
}

void DrawPoint( const Vector2& point, float size )
{
	size *= 0.5f;
	Vector2 north(point + Vector2::UnitY * size );
	Vector2 south(point - Vector2::UnitY * size );
	Vector2 east(point + Vector2::UnitX * size );
	Vector2 west(point - Vector2::UnitX * size );

	glBegin(GL_LINES);

	glVertex2f(north.X, north.Y);
	glVertex2f(east.X, east.Y);

	glVertex2f(east.X, east.Y);
	glVertex2f(south.X, south.Y);

	glVertex2f(south.X, south.Y);
	glVertex2f(west.X, west.Y);

	glVertex2f(west.X, west.Y);
	glVertex2f(north.X, north.Y);

	glEnd();
}

void DrawLine( const Vector2& vFrom, const Vector2& vTo )
{
	glBegin(GL_LINES);

	glVertex2f(vFrom.X, vFrom.Y);
	glVertex2f(vTo.X, vTo.Y);

	glEnd();
}

