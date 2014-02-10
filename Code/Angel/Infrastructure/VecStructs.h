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

#pragma once

///A handy set of structures for passing around sets of numbers
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

	bool operator==(const Vec2i &v) const { return ((X == v.X) && (Y == v.Y)); }
	bool operator!=(const Vec2i &v) const { return !(*this == v); }
};

/** 
 * Similar to Vec2i, but for situations that demand unsigned integers.
 */
struct Vec2ui
{
	unsigned int X, Y;
	Vec2ui(unsigned int x, unsigned int y) : X(x), Y(y) {}
	Vec2ui() : X(0), Y(0) {}

	bool operator==(const Vec2ui &v) const { return ((X == v.X) && (Y == v.Y)); }
	bool operator!=(const Vec2ui &v) const { return !(*this == v); }
};

/** 
 * The 3-integer version of Vec2i.
 */
struct Vec3i
{
	int X, Y, Z;
	Vec3i(int x, int y, int z) : X(x), Y(y), Z(z) {}
	Vec3i() : X(0), Y(0), Z(0) {}

	bool operator==(const Vec3i &v) const { return ((X == v.X) && (Y == v.Y) && (Z == v.Z)); }
	bool operator!=(const Vec3i &v) const { return !(*this == v); }
};

/** 
 * The 3-integer version of Vec2ui.
 */
struct Vec3ui
{
	unsigned int X, Y, Z;
	Vec3ui(unsigned int x, unsigned int y, unsigned int z) : X(x), Y(y), Z(z) {}
	Vec3ui() : X(0), Y(0), Z(0) {}

	bool operator==(const Vec3ui &v) const { return ((X == v.X) && (Y == v.Y) && (Z == v.Z)); }
	bool operator!=(const Vec3ui &v) const { return !(*this == v); }
};
