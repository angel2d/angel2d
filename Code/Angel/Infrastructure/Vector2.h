#pragma once

struct Vector2
{
	static void UnitTest();

	float X;
	float Y;

	static Vector2 Zero;
	static Vector2 One;
	static Vector2 UnitX;
	static Vector2 UnitY;
	Vector2(float x, float y);
	Vector2(float value);
	Vector2();


	float Length();
	float LengthSquared();

	static float Distance(const Vector2& value1, const Vector2& value2);
	static float DistanceSquared(const Vector2& value1, const Vector2& value2);
	static float Dot(const Vector2& value1, const Vector2& value2);
	
	void Normalize();
	static Vector2 Normalize(const Vector2& value);

	static Vector2 Reflect(const Vector2& vector, const Vector2& normal);
	static Vector2 Min(const Vector2& value1, const Vector2& value2);
	static Vector2 Max(const Vector2& value1, const Vector2& value2);
	static Vector2 Clamp(const Vector2& value1, const Vector2& min, const Vector2& max);
	static Vector2 Lerp(const Vector2& value1, const Vector2& value2, float amount);
	static Vector2 Negate(const Vector2& value);
	static Vector2 Rotated(const Vector2& value, const float Radians);
	
	bool operator==(const Vector2 &v) const;
	bool operator!=(const Vector2 &v) const;
	
	Vector2 operator-() const;
	Vector2 operator-(const Vector2 &v) const;
	Vector2 operator+(const Vector2 &v) const;
	Vector2 operator/(float divider) const;
	Vector2 operator*(float scaleFactor) const;
};
