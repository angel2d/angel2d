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

///A three-dimensional floating point vector and associated math functions
/** 
 * A floating point three-dimensional vector. Can be used either as a traditional
 *  vector (indicating a direction) or a position (treating X, Y, and Z as 
 *  coordinates). 
 */
struct Vector3
{
	/** 
	 * The X dimension, publicly available because it's so often gotten or
	 *  set and there's no good reason to encapsulate it. 
	 */
	float X;
	
	/** 
	 * The Z dimension, publicly available because it's so often gotten or
	 *  set and there's no good reason to encapsulate it. 
	 */
	float Y;
	
	/** 
	 * The Z dimension, publicly available because it's so often gotten or
	 *  set and there's no good reason to encapsulate it. 
	 */
	float Z;
	
	/** 
	 * A reference to a zero-length vector (0, 0, 0)
	 * 
	 * NB: We can't make a static member variable constant, so it is 
	 *  possible to change this value. That is a horrible idea and will make
	 *  the engine act "odd" at best. 
	 */
	static Vector3 Zero;
	
	/** 
	 * A reference to a (1, 1, 1) vector
	 * 
	 * NB: We can't make a static member variable constant, so it is 
	 *  possible to change this value. That is a horrible idea and will make
	 *  the engine act "odd" at best.
	 */
	static Vector3 One;
	
	/** 
	 * A reference to a (1, 0, 0) vector
	 * 
	 * NB: We can't make a static member variable constant, so it is 
	 *  possible to change this value. That is a horrible idea and will make
	 *  the engine act "odd" at best.
	 */
	static Vector3 UnitX;
	
	/** 
	 * A reference to a (0, 1, 0) vector
	 * 
	 * NB: We can't make a static member variable constant, so it is 
	 *  possible to change this value. That is a horrible idea and will make
	 *  the engine act "odd" at best.
	 */
	static Vector3 UnitY;
	
	/** 
	 * A reference to a (0, 0, 1) vector
	 * 
	 * NB: We can't make a static member variable constant, so it is 
	 *  possible to change this value. That is a horrible idea and will make
	 *  the engine act "odd" at best.
	 */
	static Vector3 UnitZ;
	
	/**
	 * Constructor to initialize the vector to set dimensions
	 * 
	 * @param x The X dimension
	 * @param y The Y dimension
	 * @param z The Z dimension
	 */
	Vector3(float x, float y, float z);
	
	/**
	 * Constructor to initialize the vector to uniform dimensions
	 * 
	 * @param value The value to use for the X, Y, and Z dimensions
	 */
	Vector3(float value);
	
	/**
	 * Constructor to initialize a zero-length vector (0, 0, 0)
	 */
	Vector3();
	
	
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
	static float Distance(const Vector3& value1, const Vector3& value2);
	
	/**
	 * Get the absolute distance between two points -- if all you care about
	 *  is comparison, it's a lot faster to consider the squared lengths of
	 *  the vectors.
	 * 
	 * @param value1 The first point
	 * @param value2 The second point
	 * @return The distance between the two points squared
	 */
	static float DistanceSquared(const Vector3& value1, const Vector3& value2);
	
	/**
	 * Get the dot product of two vectors.
	 * 
	 * @param value1 The first vector
	 * @param value2 The second vector
	 * @return The dot product
	 */
	static float Dot(const Vector3& value1, const Vector3& value2);
	
	/**
	 * Normalizes a vector in place -- retains its direction, but ensures
	 *  that its magnitude is equal to 1.0. 
	 */
	void Normalize();
	
	/**
	 * Get the normalized value for a Vector2 without affecting the original. 
	 * 
	 * @param value The Vector3 to normalize
	 * @return A normalized version of the passed-in Vector3
	 */
	static Vector3 Normalize(const Vector3& value);

	/**
	 * Reflect one Vector around another
	 * 
	 * @param vector The vector to reflect
	 * @param normal The normal to reflect it around
	 * @return The new vector resulting from the reflection
	 */
	static Vector3 Reflect(const Vector3& vector, const Vector3& normal);
	
	/**
	 * Get a new vector from the minimum X, Y, and Z of the two
	 * 
	 * @return The vector composed from minimums on all axes
	 */
	static Vector3 Min(const Vector3& value1, const Vector3& value2);
	
	/**
	 * Get a new vector from the maximum X, Y, and Z of the two
	 * 
	 * @return The vector composed from the maximums on all axes
	 */
	static Vector3 Max(const Vector3& value1, const Vector3& value2);
	
	/**
	 * Clamp a vector to a given minimum and maximum
	 * 
	 * @param value The vector to be clamped
	 * @param min The vector representing the X, Y, and Z minimums for the clamping
	 * @param max The vector representing the X, Y, and Z maximums for the clamping
	 * @return The clamped vector
	 */
	static Vector3 Clamp(const Vector3& value1, const Vector3& min, const Vector3& max);
	
	/**
	 * Perform a linear interpolation between two vectors
	 * 
	 * @param value1 The starting point vector
	 * @param value2 The ending point vector
	 * @param amount The amount (from 0.0 to 1.0) to interpolate between them
	 * @return The interpolated vector
	 */
	static Vector3 Lerp(const Vector3& value1, const Vector3& value2, float amount);
	
	/**
	 * Get a negated vector -- if you add the result and the original, you
	 *  should get a zero-length vector (0, 0)
	 * 
	 * @param value The vector to negate
	 * @return The negated vector
	 */
	static Vector3 Negate(const Vector3& value);
	
	bool operator==(const Vector3 &v) const;
	bool operator!=(const Vector3 &v) const;
	
	Vector3 operator-() const;
	Vector3 operator-(const Vector3 &v) const;
	Vector3 operator+(const Vector3 &v) const;
	Vector3 operator/(float divider) const;
	Vector3 operator*(float scaleFactor) const;

	Vector3& operator+=(const Vector3 &v);
	Vector3& operator-=(const Vector3 &v);
	Vector3& operator*=(float f);
	Vector3& operator/=(float f);
};
