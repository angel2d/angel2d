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
#include "../Infrastructure/Vector3.h"

#include "../Util/MathUtil.h"

#include <math.h>

Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
Vector3 Vector3::One(1.0f, 1.0f, 1.0f);
Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);

Vector3::Vector3(float x, float y, float z)
: X(x)
, Y(y)
, Z(z)
{}

Vector3::Vector3(float value)
: X(value)
, Y(value)
, Z(value)
{}

Vector3::Vector3()
: X(0)
, Y(0)
, Z(0)
{}

float Vector3::Length()
{
	return sqrt(LengthSquared());
}

float Vector3::LengthSquared()
{
	return (X * X) + (Y * Y) + (Z * Z);
}

/*static*/ float Vector3::Distance(const Vector3& value1, const Vector3& value2)
{
	return Vector3(value1 - value2).Length();
}

/*static*/ float Vector3::DistanceSquared(const Vector3& value1, const Vector3& value2)
{
	return Vector3(value1 - value2).LengthSquared();

}

/*static*/ float Vector3::Dot(const Vector3& value1, const Vector3& value2)
{
	return ((value1.X * value2.X) + (value1.Y * value2.Y) + (value1.Z * value2.Z));
}

void Vector3::Normalize()
{
	float len = Length();


	if( len < MathUtil::Epsilon )
	{
		if( Y > X )
			*this = UnitY;
		else if (X > Z) //favoring the 2d components first
			*this = UnitX;
		else
			*this = UnitZ;
	}
	else
	{
		*this = *this / len;
	}
}

/*static*/ Vector3 Vector3::Normalize(const Vector3& value)
{
	Vector3 retVal(value);
	retVal.Normalize();
	return retVal;
}

/*static*/ Vector3 Vector3::Reflect(const Vector3& vector, const Vector3& normal)
{
	return vector - (normal * 2.0f * Dot(vector, normal));
}

/*static*/ Vector3 Vector3::Min(const Vector3& value1, const Vector3& value2)
{
	return Vector3(MathUtil::Min(value1.X, value2.X), MathUtil::Min(value1.Y, value2.Y), MathUtil::Min(value1.Z, value2.Z));
}

/*static*/ Vector3 Vector3::Max(const Vector3& value1, const Vector3& value2)
{
	return Vector3(MathUtil::Max(value1.X, value2.X), MathUtil::Max(value1.Y, value2.Y), MathUtil::Max(value1.Z, value2.Z));
}

/*static*/ Vector3 Vector3::Clamp(const Vector3& value1, const Vector3& min, const Vector3& max)
{
	return Vector3(MathUtil::Clamp(value1.X, min.X, max.X), MathUtil::Clamp(value1.Y, min.Y, max.Y), MathUtil::Clamp(value1.Z, min.Z, max.Z));
}

/*static*/ Vector3 Vector3::Lerp(const Vector3& value1, const Vector3& value2, float amount)
{
	return Vector3( MathUtil::Lerp( value1.X, value2.X, amount ), MathUtil::Lerp( value1.Y, value2.Y, amount ), MathUtil::Lerp(value1.Z, value2.Z, amount));
}
/*static*/ Vector3 Vector3::Negate(const Vector3& value)
{
	return -value;
}

bool Vector3::operator==(const Vector3 &v) const
{
	return X == v.X && Y == v.Y && Z == v.Z;
}

bool Vector3::operator!=(const Vector3 &v) const
{
	return !(*this == v);
}

Vector3 Vector3::operator-() const
{
	return Vector3::Zero - *this;
}

Vector3 Vector3::operator-(const Vector3 &v) const
{
	return Vector3(X - v.X, Y - v.Y, Z - v.Z);
}

Vector3 Vector3::operator+(const Vector3 &v) const
{
	return Vector3(X + v.X, Y + v.Y, Z + v.Z);
}

Vector3 Vector3::operator/(float divider) const
{
	return Vector3(X / divider, Y / divider, Z / divider);
}

Vector3 Vector3::operator*(float scaleFactor) const
{
	return Vector3(X * scaleFactor, Y * scaleFactor, Z * scaleFactor);
}

Vector3& Vector3::operator+=(const Vector3 &v)
{
	X += v.X;
	Y += v.Y;
	Z += v.Z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3 &v)
{
	X -= v.X;
	Y -= v.Y;
	Z -= v.Z;
	return *this;
}

Vector3& Vector3::operator*=(float scaleFactor)
{
	X *= scaleFactor;
	Y *= scaleFactor;
	Z *= scaleFactor;
	return *this;
}

Vector3& Vector3::operator/=(float scaleFactor)
{
	X /= scaleFactor;
	Y /= scaleFactor;
	Z /= scaleFactor;
	return *this;
}


#include <iostream>
using namespace std;

ostream& operator<<(ostream& stream, const Vector3& out)
{
	return stream << out.X << ", " << out.Y << ", " << out.Z;
}
