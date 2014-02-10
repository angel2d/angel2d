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

#include "../AI/BoundingShapes.h"
#include "../Infrastructure/Vector2.h"
#include "../Infrastructure/VecStructs.h"

///A set of static functions that handle typical math needed for games
/** 
 * This class is just a wrapper around a whole bunch of otherwise-loose 
 *  functions that handle all kinds of math that is typically required in a 
 *  game. 
 * 
 * It also contains a set of constants so you don't have to look them up
 *  or declare them yourself. 
 */
class MathUtil
{
public:
	/** 
	 * Euler's number: http://en.wikipedia.org/wiki/E_(mathematical_constant)
	 */
	static const float E;
	
	/** 
	 * Base-10 logarithm of Euler's number
	 */
	static const float Log10E;
	
	/** 
	 * Base-2 logarithm of Euler's number
	 */
	static const float Log2E;
	
	/** 
	 * Pi: http://en.wikipedia.org/wiki/Pi
	 */
	static const float Pi;
	
	/** 
	 * Pi divided by 2
	 */
	static const float PiOver2;
	
	/** 
	 * Pi divided by 4
	 */
	static const float PiOver4;
	
	/** 
	 * 2 times Pi (Tau)
	 */
	static const float TwoPi;
	
	/** 
	 * The maximum value that can be represented by a 32-bit floating point
	 *  number
	 */
	static const float MaxFloat;
	
	/** 
	 * The minimum value that can be represented by a 32-bit floating point
	 *  number
	 */
	static const float MinFloat;
	
	/** 
	 * A very tiny number, useful for floating point comparisons (10e-6)
	 */
	static const float Epsilon;
	
	/** 
	 * A templated absolute value function that can handle any class where
	 *  a comparison against 0 makes sense (floats and ints, mostly). 
	 * 
	 * @param val The number
	 * @return The absolute value of that number
	 */
	template<typename T>
	static T Abs(T val )
	{
		return val >= 0 ? val : -val;
	}
	
	/**
	 * A templated max function that returns the greater of two values. Works
	 *  for any class that implements a > operator. 
	 * 
	 * @param value1 The first value
	 * @param value2 The second value
	 * @return The greater of the two
	 */
	template<typename T>
	static T Max(T value1, T value2)
	{
		return value1 > value2 ? value1 : value2;
	}

	/**
	 * A templated min function that returns the lesser of two values. Works
	 *  for any class that implements a < operator. 
	 * 
	 * @param value1 The first value
	 * @param value2 The second value
	 * @return The lesser of the two
	 */
	template<typename T>
	static T Min(T value1, T value2)
	{
		return value1 < value2 ? value1 : value2;
	}
	
	/**
	 * Find the distance between two values. Works for any class that has a 
	 *  subtraction operator and will work with the #Abs function. 
	 * 
	 * @param value1 The first value
	 * @param value2 The second value
	 * @return The distance between them
	 */
	template<typename T>
	static T Distance(T value1, T value2)
	{
		return Abs(value1 - value2);
	}
	
	/**
	 * Linearly interpolates between two values. Works for any classes that
	 *  define addition, subtraction, and multiplication (by a float)
	 *  operators. 
	 * 
	 * http://en.wikipedia.org/wiki/Lerp_(computing)
	 * 
	 * @param value1 The starting value
	 * @param value2 The ending value
	 * @param amount The amount to lerp (from 0.0 to 1.0)
	 * @return The interpolated value
	 */
	template<typename T>
	static T Lerp(T value1, T value2, float amount)
	{
		return T(value1 + ((T)(value2 - value1) * amount ));
	}
	
	/**
	 * Smoothly step between two values. Works for any classes that Lerp
	 *  would work for (and is essentially a drop-in replacement). 
	 *  Often looks visually better than a simple linear interpolation as
	 *  it gives ease-in and ease-out. 
	 * 
	 * http://www.fundza.com/rman_shaders/smoothstep/index.html
	 * 
	 * @param value1 The starting value
	 * @param value2 The ending value
	 * @param amount The amount to interpolate (from 0.0 to 1.0)
	 * @return The interpolated value
	 */
	template<typename T>
	static T SmoothStep(T value1, T value2, float amount)
	{
		float num = Clamp(amount, 0.0f, 1.0f);
		return Lerp(value1, value2, (num * num) * (3.0f - (2.0f * num)));
	}

	/**
	 * Clamps an integer to a specified range
	 * 
	 * @param value The integer in question
	 * @param min The minimum of the range
	 * @param max The maximum of the range
	 * @return The clamped value
	 */
	static int Clamp(int value, int min, int max)
	{
		return Max(min, Min(max, value));
	}
	
	/**
	 * Clamps a float to a specified range
	 * 
	 * @param value The float in question
	 * @param min The minimum of the range
	 * @param max The maximum of the range
	 * @return The clamped value
	 */
	static float Clamp(float value, float min, float max)
	{
		return Max(min, Min(max, value));
	}
	
	/**
	 * Clamps a double-precision float to a specified range
	 * 
	 * @param value The double in question
	 * @param min The minimum of the range
	 * @param max The maximum of the range
	 * @return The clamped value
	 */
	static double Clamp(double value, double min, double max)
	{
		return Max(min, Min(max, value));
	}
	
	/**
	 * Convert radians to degrees
	 * 
	 * @param radians The angle in radians
	 * @return The angle in degrees
	 */
	static float ToDegrees(float radians);
	
	/**
	 * Convert degrees to radians
	 * 
	 * @param degrees The angle in degrees
	 * @return The angle in radians
	 */
	static float ToRadians(float degrees);
	
	/**
	 * Get a unit-length vector which indicate a direction along the given
	 *  angle relative to the screen. 
	 * 
	 * @param angle_in_degrees The angle, in degrees
	 * @return A vector moving along that angle
	 */
	static Vector2 VectorFromAngle(float angle_in_degrees);
	
	/**
	 * Get an angle from a vector indicating direction
	 * 
	 * @param v1 The vector direction
	 * @return The vector's angle
	 */
	static float AngleFromVector(const Vector2& v1);
	
	/**
	 * Get the angle between two vectors
	 * 
	 * @param v1 The first vector
	 * @param v2 The second vector
	 * @return The angle between them in radians
	 */
	static float AngleFromVectors(const Vector2& v1, const Vector2& v2);
	
	/**
	 * Takes a double or float and removes everything after the decimal
	 *  point, making it into an integer. 
	 * 
	 * @param x The double or float to round
	 * @return The rounded integer
	 */
	static int RoundToInt(double x);
	
	/**
	 * Get a random non-negative integer.
	 * 
	 * @param maximum The maximum value you want to see
	 * @return A random number between 0 (inclusive) and maximum (exclusive)
	 */
	static int RandomInt(int maximum);
	
	/**
	 * Get a random integer in a specified range.
	 * 
	 * @param min The minimum value you want to see
	 * @param max The maximum value you want to see
	 * @return A random number between min (inclusive) and max (exclusive)
	 */
	static int RandomIntInRange(int min, int max);
	
	/**
	 * Get a random integer within a specified range of another one. 
	 * 
	 * @param target The target integer
	 * @param error The maximum amount the returned value can differ from
	 *  the target (in either direction)
	 * @return A random int from (target - error) to (target + error)
	 */
	static int RandomIntWithError(int target, int error);
	
	/**
	 * Get a random non-negative float.
	 * 
	 * @param maximum The maximum value you want to see
	 * @return A random number between 0.0 (inclusive) and maximum (exclusive)
	 */
	static float RandomFloat(float maximum=1.0f);
	
	/**
	 * Get a random float in a specified range.
	 * 
	 * @param min The minimum value you want to see
	 * @param max The maximum value you want to see
	 * @return A random number between min (inclusive) and max (exclusive)
	 */
	static float RandomFloatInRange(float min, float max);
	
	/**
	 * Get a random float within a specified range of another one. 
	 * 
	 * @param target The target float
	 * @param error The maximum amount the returned value can differ from
	 *  the target (in either direction)
	 * @return A random float from (target - error) to (target + error)
	 */
	static float RandomFloatWithError(float target, float error);
	
	/**
	 * Get a random bool.
	 * 
	 * @return Either true or false, randomly. :-)
	 */
	static bool RandomBool();
	
	/**
	 * Get a random unit-length Vector2
	 * 
	 * @return A unit-length Vector2 pointing in a random direction
	 */
	static Vector2 RandomVector();
	
	/**
	 * Get a random Vector2 with specified maximum values
	 * 
	 * @param maxValues The highest values for both axes
	 * @return A random vector ranging from (0, 0) to (maxValues.X, 
	 *   maxValuesY)
	 */
	static Vector2 RandomVector(const Vector2& maxValues);
	
	/**
	 * Get a random Vector2 within a specified range
	 * 
	 * @param minValues The lowest values for both axes
	 * @param maxValues The highest values for both axes
	 * @return A random vector ranging from (minValues.X, minValues.Y) to 
	 *   (maxValues.X, maxValues.y)
	 */
	static Vector2 RandomVector(const Vector2& minValues, const Vector2& maxValues);
	
	/**
	 * Get a set of random points in a Poisson disc distribution. (If you're not
	 *  familiar with that term, just know that it's more likely to give a somewhat
	 *  even distribution of random points, a more "natural" looking distribution,
	 *  along the lines of what you're imagining when you think of "random."
	 * 
	 * @param numPoints The desired number of points
	 * @param minValue A point representing the bottom-left coordinate of the field
	 * @param maxValue A point representing the top-right coordinate of the field
	 * @param minDistance The smallest distance that will be allowed in the field,
	 *   effectively determining the spacing. Note that this value will iteratively
	 *   decrease if the field ends up too tightly packed. 
	 * @return The list of generated points
	 */
	static Vector2List RandomPointField(int numPoints, const Vector2& minValue, const Vector2& maxValue, float minDistance=0.5f);
	
	/**
	 * Compare two floating point values for "equality," with a permissible
	 *  amount of error. Oftentimes you only care if floats are "close enough
	 *  for government work," and this function lets you make that 
	 *  determination. 
	 * 
	 * (Because of rounding errors inherent in floating point arithmetic, 
	 *   direct comparison of floats is often inadvisable.
	 * http://en.wikipedia.org/wiki/Floating_point#Accuracy_problems )
	 * 
	 * @param value1 The first value
	 * @param value2 The second value
	 * @param epsilon The maximum allowable difference (defaults to 
	 *   MathUtil::Epsilon)
	 * @return Whether the two values are within epsilon of each other
	 */
	static bool FuzzyEquals(float value1, float value2, float epsilon=Epsilon);
	
	/**
	 * A Vector2 comparison function using FuzzyEquals on the components. 
	 * 
	 * @param v1 The first vector
	 * @param v2 The second vector
	 * @param epsilon The maximum allowable difference between them
	 * @return Whether the two vectors have components within epsilon of 
	 *  each other
	 */
	static bool FuzzyEquals(const Vector2& v1, const Vector2& v2, float epsilon=Epsilon);
	
	/**
	 * Convert screen (pixel) coordinates to world (GL unit) coordinates. 
	 *  This function is not terribly efficient, so be careful calling it 
	 *  too frequently. 
	 * 
	 * @param x The pixel X coordinate
	 * @param y The pixel Y coordinate
	 * @return The world space coordinates
	 */
	static Vector2 ScreenToWorld(int x, int y);
	
	/**
	 * Convert screen (pixel) coordinates to world (GL unit) coordinates. 
	 *  This function is not terribly efficient, so be careful calling it 
	 *  too frequently. 
	 * 
	 * @param screenCoordinates The pixel coordinates
	 * @return The world space coordinates
	 */
	static Vector2 ScreenToWorld(const Vec2i& screenCoordinates);
	
	/**
	 * Convert world (GL unit) coordinates to screen (pixel) coordinates. 
	 * 	This function is not terribly efficient, so be careful calling it 
	 *  too frequently.
	 * 
	 * @param x The world X coordinate
	 * @param y The world Y coordinate
	 * @return The screen space coordinates
	 */
	static Vector2 WorldToScreen(float x, float y);
	
	/**
	 * Convert world (GL unit) coordinates to screen (pixel) coordinates. 
	 * 	This function is not terribly efficient, so be careful calling it 
	 *  too frequently.
	 * 
	 * @param worldCoordinates The world coordinates
	 * @return The screen space coordinates
	 */
	static Vector2 WorldToScreen(const Vector2& worldCoordinates);
	
	/**
	 * Find out the dimensions of the area currently displayed in the window.
	 * 
	 * @return The dimensions of the viewport in GL units
	 */
	static Vector2 GetWorldDimensions();
	
	/**
	 * Take a number of pixels and find out how many GL units they cover
	 * 
	 * @param pixels The number of pixels
	 * @return The number of GL units
	 */
	static float PixelsToWorldUnits(float pixels);
	
	/**
	 * Take a number of GL units and find out how many pixels stretch across
	 *  that distance. 
	 * 
	 * @param worldUnits The number of GL units
	 * @return The number of pixels
	 */
	static float WorldUnitsToPixels(float worldUnits);
	
	enum AABBSplittingAxis
	{
		AA_X,
		AA_Y
	};
	
	/**
	 * Used internally by the SpatialGraph when it generates. 
	 * 
	 * @param source The bounding box to split
	 * @return The appropriate axis on which to split it
	 */
	static AABBSplittingAxis GetMajorAxis(const BoundingBox& source);
	
	/**
	 * Used internally by the SpatialGraph when it generates
	 * 
	 * @param source The bounding box to split
	 * @param axis The axis on which to split it
	 * @param LHS An out parameter that will be set to the left-hand-side 
	 *   bounding box resulting from the split
	 * @param RHS An out parameter that will be set to the right-hand-side
	 *   bounding box resulting from the split
	 */
	static void SplitBoundingBox(const BoundingBox& source, AABBSplittingAxis axis, BoundingBox& LHS, BoundingBox& RHS);
	
	/**
	 * Calculates the difference in two angles (in radians) and remaps it
	 *  to a range from -Pi to Pi. 
	 * 
	 * @param A1 The first angle (in radians)
	 * @param A2 The second angle (in radians)
	 * @return The difference, mapped appropriately
	 */
	static float DeltaAngle(float A1, float A2);
	
	/**
	 * Calculate the difference in angles between two vectors.
	 * 
	 * @param v1 The first vector
	 * @param v2 The second vector
	 * @return The difference in their angles
	 */
	static float VectorDeltaAngle(const Vector2& v1, const Vector2& v2);
};
