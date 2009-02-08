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


