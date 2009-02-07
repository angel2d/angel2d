#pragma once

///A handy structure for passing around 2d integer coordinates
/** 
 * The little brother of Vector2 and Vector3, which handle floats, Vec2i 
 *  simply bundles together two integers to make it easier to pass around
 *  things like pixel coordinates. 
 */
struct Vec2i
{
	int X, Y;
	Vec2i(int x, int y) : X(x), Y(y) {}
	Vec2i() : X(0), Y(0) {}
};
