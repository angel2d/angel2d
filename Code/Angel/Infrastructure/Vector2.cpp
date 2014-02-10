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

#include "stdafx.h"
#include "../Infrastructure/Vector2.h"

#include "../Util/MathUtil.h"

#include <math.h>

Vector2 Vector2::Zero(0.0f, 0.0f);
Vector2 Vector2::One(1.0f, 1.0f);
Vector2 Vector2::UnitX(1.0f, 0.0f);
Vector2 Vector2::UnitY(0.0f, 1.0f);

Vector2::Vector2(float x, float y)
: X(x)
, Y(y)
{}

Vector2::Vector2(float value)
: X(value)
, Y(value)
{}

Vector2::Vector2()
: X(0)
, Y(0)
{}

Vector2::Vector2(const Vec2i& copy)
: X(copy.X)
, Y(copy.Y)
{}

float Vector2::Length()
{
	return sqrt(LengthSquared());
}

float Vector2::LengthSquared()
{
	return (X * X) + (Y * Y);
}

/*static*/ float Vector2::Distance(const Vector2& value1, const Vector2& value2)
{
	return Vector2(value1 - value2).Length();
}

/*static*/ float Vector2::DistanceSquared(const Vector2& value1, const Vector2& value2)
{
	return Vector2(value1 - value2).LengthSquared();
}

/*static*/ float Vector2::Dot(const Vector2& value1, const Vector2& value2)
{
	return (value1.X * value2.X) + (value1.Y * value2.Y);
}

/*static*/ float Vector2::Cross(const Vector2& value1, const Vector2& value2)
{
	return (value1.X * value2.Y) - (value1.Y * value2.X);
}

void Vector2::Normalize()
{
	float len = Length();


	if( len < 1e-7f )
	{
		if( Y > X )
			*this = UnitY;
		else
			*this = UnitX;
	}
	else
	{
		*this = *this / len;
	}
}

/*static*/ Vector2 Vector2::Normalize(const Vector2& value)
{
	Vector2 retVal(value);
	retVal.Normalize();
	return retVal;
}

/*static*/ Vector2 Vector2::Reflect(const Vector2& vector, const Vector2& normal)
{
	return vector - (normal * 2.0f * Dot(vector, normal));
}

/*static*/ Vector2 Vector2::Min(const Vector2& value1, const Vector2& value2)
{
	return Vector2(MathUtil::Min(value1.X, value2.X), MathUtil::Min(value1.Y, value2.Y));
}

/*static*/ Vector2 Vector2::Max(const Vector2& value1, const Vector2& value2)
{
	return Vector2(MathUtil::Max(value1.X, value2.X), MathUtil::Max(value1.Y, value2.Y));
}

/*static*/ Vector2 Vector2::Clamp(const Vector2& value, const Vector2& min, const Vector2& max)
{
	return Vector2(MathUtil::Clamp(value.X, min.X, max.X), MathUtil::Clamp(value.Y, min.Y, max.Y));
}

/*static*/ Vector2 Vector2::Lerp(const Vector2& value1, const Vector2& value2, float amount)
{
	return Vector2( MathUtil::Lerp( value1.X, value2.X, amount ), MathUtil::Lerp( value1.Y, value2.Y, amount ) );
}

/*static*/ Vector2 Vector2::Negate(const Vector2& value)
{
	return -value;
}

/*static*/ Vector2 Vector2::Rotate(const Vector2& value, const float radians)
{
	float c = cos(radians);
	float s = sin(radians);
	return Vector2(value.X*c-value.Y*s,value.Y*c+value.X*s);
}

bool Vector2::operator==(const Vector2 &v) const
{
	return X == v.X && Y == v.Y;
}

bool Vector2::operator!=(const Vector2 &v) const
{
	return !(*this == v);
}

Vector2 Vector2::operator-() const
{
	return Vector2::Zero - *this;
}

Vector2 Vector2::operator-(const Vector2 &v) const
{
	return Vector2(X - v.X, Y - v.Y);
}

Vector2 Vector2::operator+(const Vector2 &v) const
{
	return Vector2(X + v.X, Y + v.Y);
}

Vector2 Vector2::operator/(float divider) const
{
	return Vector2(X / divider, Y / divider);
}

Vector2 Vector2::operator*(float scaleFactor) const
{
	return Vector2(X * scaleFactor, Y * scaleFactor);
}

Vector2& Vector2::operator+=(const Vector2 &v)
{
	X += v.X;
	Y += v.Y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2 &v)
{
	X -= v.X;
	Y -= v.Y;
	return *this;
}

Vector2& Vector2::operator*=(float scaleFactor)
{
	X *= scaleFactor;
	Y *= scaleFactor;
	return *this;
}

Vector2& Vector2::operator/=(float scaleFactor)
{
	X /= scaleFactor;
	Y /= scaleFactor;
	return *this;
}


#include <iostream>
using namespace std;

ostream& operator<<(ostream& stream, const Vector2& out)
{
	return stream << out.X << ", " << out.Y;
}
