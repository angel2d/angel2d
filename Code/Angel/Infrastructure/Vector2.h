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

#pragma once

#include "../Infrastructure/Common.h"
#include "../Infrastructure/VecStructs.h"

///A two-dimensional floating point vector and associated math functions
/** 
 * A floating point two-dimensional vector. Can be used either as a traditional
 *  vector (indicating a direction) or a position (treating X and Y as 
 *  coordinates). 
 */
struct Vector2
{
	/** 
	 * The X dimension, publicly available because it's so often gotten or
	 *  set and there's no good reason to encapsulate it. 
	 */
	float X;
	
	/** 
	 * The Y dimension, also publicly available. 
	 */
	float Y;
	
	/** 
	 * A reference to a zero-length vector (0, 0)
	 * 
	 * NB: We can't make a static member variable constant, so it is 
	 *  possible to change this value. That is a horrible idea and will make
	 *  the engine act "odd" at best. 
	 */
	static Vector2 Zero;
	
	/** 
	 * A reference to a (1, 1) vector
	 * 
	 * NB: We can't make a static member variable constant, so it is 
	 *  possible to change this value. That is a horrible idea and will make
	 *  the engine act "odd" at best.
	 */
	static Vector2 One;
	
	/** 
	 * A reference to a (1, 0) vector
	 * 
	 * NB: We can't make a static member variable constant, so it is 
	 *  possible to change this value. That is a horrible idea and will make
	 *  the engine act "odd" at best.
	 */
	static Vector2 UnitX;
	
	/** 
	 * A reference to a (0, 1) vector
	 * 
	 * NB: We can't make a static member variable constant, so it is 
	 *  possible to change this value. That is a horrible idea and will make
	 *  the engine act "odd" at best.
	 */
	static Vector2 UnitY;
	
	/**
	 * Constructor to initialize the vector to set dimensions
	 * 
	 * @param x The X dimension
	 * @param y The Y dimension
	 */
	Vector2(float x, float y);
	
	/**
	 * Constructor to initialize the vector to uniform dimensions
	 * 
	 * @param value The value to use for both the X and Y dimension
	 */
	Vector2(float value);

	/**
	 * Constructor to initalize from a Vec2i struct.
	 * 
	 * @param copy The Vec2i to be converted into a Vector2.
	 */
	Vector2(const Vec2i& copy);
	
	/**
	 * Constructor to initialize a zero-length vector (0, 0)
	 */
	Vector2();
	
	
	/**
	 * Get the absolute magnitude of the vector. Uses a square-root, so be 
	 *  careful calling this too much within a loop.
	 * 
	 * @return The length (magnitude) of the vector
	 */
	float Length();
	
	/**
	 * Get the squared magnitude of the vector -- if all you care about is
	 *  comparison, it's a lot faster to consider the squared lengths of 
	 *  the vectors.
	 * 
	 * @return The length (magnitude) of the vector squared
	 */
	float LengthSquared();

	/**
	 * Get the absolute distance between two points (most useful if the
	 *  Vector2 represents a position). Uses a square-root, so be careful
	 *  calling this too much within a loop.
	 * 
	 * @param value1 The first point
	 * @param value2 The second point
	 * @return The distance between the two points
	 */
	static float Distance(const Vector2& value1, const Vector2& value2);
	
	/**
	 * Get the absolute distance between two points -- if all you care about
	 *  is comparison, it's a lot faster to consider the squared lengths of
	 *  the vectors.
	 * 
	 * @param value1 The first point
	 * @param value2 The second point
	 * @return The distance between the two points squared
	 */
	static float DistanceSquared(const Vector2& value1, const Vector2& value2);
	
	/**
	 * Get the dot product of two vectors.
	 * 
	 * @param value1 The first vector
	 * @param value2 The second vector
	 * @return The dot product
	 */
	static float Dot(const Vector2& value1, const Vector2& value2);
	
	/**
	 * Get the cross product of two vectors. Note that the \b mathematical 
	 *  definition of a cross product results in another vector perpendicular
	 *  to the two inputs, but since both of our vectors are 2D, the 
	 *  returned vector will always have X and Y components of 0. Thus 
	 *  this function returns what would be the Z component of that vector.
	 * 
	 * @param value1 The first vector
	 * @param value2 The second vector
	 * @return The Z component of the cross product
	 */
	static float Cross(const Vector2& value1, const Vector2& value2);

	/**
	 * Normalizes a vector in place -- retains its direction, but ensures
	 *  that its magnitude is equal to 1.0. 
	 */
	void Normalize();
	
	/**
	 * Get the normalized value for a Vector2 without affecting the original. 
	 * 
	 * @param value The Vector2 to normalize
	 * @return A normalized version of the passed-in Vector2
	 */
	static Vector2 Normalize(const Vector2& value);
	
	/**
	 * Reflect one Vector around another
	 * 
	 * @param vector The vector to reflect
	 * @param normal The normal to reflect it around
	 * @return The new vector resulting from the reflection
	 */
	static Vector2 Reflect(const Vector2& vector, const Vector2& normal);
	
	/**
	 * Get a new vector from the minimum X and minimum Y of the two
	 * 
	 * @return The vector composed from minimums on both axes
	 */
	static Vector2 Min(const Vector2& value1, const Vector2& value2);
	
	/**
	 * Get a new vector from the maximum X and maximum Y of the two
	 * 
	 * @return The vector composed from the maximums on both axes
	 */
	static Vector2 Max(const Vector2& value1, const Vector2& value2);
	
	/**
	 * Clamp a vector to a given minimum and maximum
	 * 
	 * @param value The vector to be clamped
	 * @param min The vector representing the X and Y minimums for the clamping
	 * @param max The vector representing the X and Y maximums for the clamping
	 * @return The clamped vector
	 */
	static Vector2 Clamp(const Vector2& value, const Vector2& min, const Vector2& max);
	
	/**
	 * Perform a linear interpolation between two vectors
	 * 
	 * @param value1 The starting point vector
	 * @param value2 The ending point vector
	 * @param amount The amount (from 0.0 to 1.0) to interpolate between them
	 * @return The interpolated vector
	 */
	static Vector2 Lerp(const Vector2& value1, const Vector2& value2, float amount);
	
	/**
	 * Get a negated vector -- if you add the result and the original, you
	 *  should get a zero-length vector (0, 0)
	 * 
	 * @param value The vector to negate
	 * @return The negated vector
	 */
	static Vector2 Negate(const Vector2& value);
	
	/**
	 * Rotate a vector
	 * 
	 * @param value The original vector to rotate
	 * @param radians The rotation angle (in radians)
	 * @return The rotated vector
	 */
	static Vector2 Rotate(const Vector2& value, const float radians);
	
	bool operator==(const Vector2 &v) const;
	bool operator!=(const Vector2 &v) const;
	
	Vector2 operator-() const;
	Vector2 operator-(const Vector2 &v) const;
	Vector2 operator+(const Vector2 &v) const;
	Vector2 operator/(float divider) const;
	Vector2 operator*(float scaleFactor) const;

	Vector2& operator+=(const Vector2 &v);
	Vector2& operator-=(const Vector2 &v);
	Vector2& operator*=(float f);
	Vector2& operator/=(float f);
};

typedef std::vector<Vector2> Vector2List;
