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

/** 
 * @file DrawUtil.h
 * A set of C-style utility functions to draw things on the screen. Good
 *  for quick debug work. 
 */
#pragma once

#include "../Infrastructure/Vector2.h"

/**
 * Draws a cross on the screen. Will be in whatever color you last passed in
 *  to a glColor* function. 
 * 
 * @param point The point for the center of the cross (in world space)
 * @param size How long each arm should be (in GL units)
 */
void DrawCross( const Vector2& point, float size );

/**
 * Draws a point on the screen. Will be in whatever color you last passed in
 *  to a glColor* function. 
 * 
 * @param point The point to draw (in world space)
 * @param size How large the point should appear (in GL units)
 */
void DrawPoint( const Vector2& point, float size );

/**
 * Draws a line on the screen. Will be in whatever color you last passed in
 *  to a glColor* function. 
 * 
 * @param from The starting point in world space
 * @param to The ending point in world space
 */
void DrawLine( const Vector2& from, const Vector2& to );

/**
 * Checks for OpenGL errors and prints any found to the log.
 *
 * @return Whether or not any errors were found. 
 */
bool HandleGLErrors();
