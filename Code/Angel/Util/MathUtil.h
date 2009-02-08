#pragma once

#include "../AI/BoundingShapes.h"
#include "../Infrastructure/Vector2.h"
#include "../Infrastructure/VecStructs.h"

class MathUtil
{
public:
	static const float E;
	static const float Log10E;
	static const float Log2E;
	static const float Pi;
	static const float PiOver2;
	static const float PiOver4;
	static const float TwoPi;
	static const float MaxFloat;
	static const float MinFloat;
	static const float Epsilon;

	template<typename T>
	static T Abs(T val )
	{
		return val >= 0 ? val : -val;
	}

	template<typename T>
	static T Max(T value1, T value2)
	{
		return value1 > value2 ? value1 : value2;
	}

	template<typename T>
	static T Min(T value1, T value2)
	{
		return value1 < value2 ? value1 : value2;
	}

	template<typename T>
	static T Distance(T value1, T value2)
	{
		return Abs(value1 - value2);
	}

	template<typename T>
	static T Lerp(T value1, T value2, float amount)
	{
		return T(value1 + ((T)(value2 - value1) * amount ));
	}

	static int Clamp(int value, int min, int max)
	{
		return Max(min, Min(max, value));
	}

	static float Clamp(float value, float min, float max)
	{
		return Max(min, Min(max, value));
	}

	static double Clamp(double value, double min, double max)
	{
		return Max(min, Min(max, value));
	}

	static float SmoothStep(float value1, float value2, float amount);
	static float ToDegrees(float radians);
	static float ToRadians(float degrees);

	//distance functions
	static double DistanceSquared(double x1, double y1, double x2, double y2);
	static double Distance(double x1, double y1, double x2, double y2);

	//vector functions
	static Vector2 VectorFromAngle(float angle_in_degrees);
	static float AngleFromVector(const Vector2& v1);
	static float AngleFromVectors(const Vector2& v1, const Vector2& v2);

	//misc functions
	static int RoundToInt(double x);
	static int RandomInt(int maximum);
	static int RandomIntInRange(int min, int max);
	static int RandomIntWithError(int target, int error);
	static float RandomFloat(float maximum=1.0f);
	static float RandomFloatInRange(float min, float max);
	static float RandomFloatWithError(float target, float error);
	static bool RandomBool();
	static Vector2 RandomVector();
	static Vector2 RandomVector(Vector2 maxValues);
	static Vector2 RandomVector(Vector2 minValues, Vector2 maxValues);

	static bool FuzzyEquals(float x, float y, float epsilon=Epsilon);
	static bool FuzzyEquals(Vector2 v1, Vector2 v2, float epsilon=Epsilon);

	static Vector2 ScreenToWorld(int x, int y);
	static Vector2 ScreenToWorld(Vec2i screenCoordinates);
	static Vector2 WorldToScreen(float x, float y);
	static Vector2 WorldToScreen(Vector2 worldCoordinates);
	static Vector2 GetWorldDimensions();
	static float PixelsToWorldUnits(float pixels);
	static float WorldUnitsToPixels(float worldUnits);

	enum AABBSplittingAxis
	{
		AA_X,
		AA_Y
	};

	static AABBSplittingAxis GetMajorAxis(const BoundingBox& source);
	static void SplitBoundingBox(const BoundingBox& source, AABBSplittingAxis axis, BoundingBox& LHS, BoundingBox& RHS);
	static float DeltaAngle(float A1, float A2);
	static float VectorDeltaAngle(Vector2 v1, Vector2 v2);

};
