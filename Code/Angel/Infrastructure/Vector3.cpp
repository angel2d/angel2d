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


#include <iostream>
using namespace std;

ostream& operator<<(ostream& stream, const Vector3& out)
{
	return stream << out.X << ", " << out.Y << ", " << out.Z;
}

// /*static*/ void Vector3::UnitTest()
// {
// 	Vector3 test(3, 4, 5);
// 
// 	cout << test << endl;;
// 
// 	cout << "Length Sqr: " << test.LengthSquared() << endl;
// 
// 	cout << "Length: " << test.Length() << endl;
// 
// 
// 	cout << "Distance: " << Vector3::Distance(test, Vector3::Zero) << endl;
// 	cout << "Square Distance: " << Vector3::DistanceSquared(test, Vector3::Zero) << endl;
// 
// 	cout << "Dot: " << Vector3::Dot( Vector3(1), test ) << endl;
// 
// 	test.Normalize();
// 	cout << "Normal: " << test << " yields length: " << test.Length() << endl;
// 	test = Vector3(3,-4, 5);
// 	{
// 		Vector3 checkIt(Vector3::Zero);
// 		cout << "Normal: " << Vector3::Normalize(checkIt) << endl;
// 
// 	}
// 
// 	cout << "Reflect: " << Vector3::Reflect( Vector3(10, -10, 10), Vector3::Normalize( Vector3(-1, 1, 1) )) << endl;
// 
// 	cout << "Max: " << Vector3::Max( Vector3(100), Vector3(9, 1000, 9)) << endl;
// 	cout << "Min: " << Vector3::Min( Vector3(100), Vector3(9, 1000, 9)) << endl;
// 	cout << "Clamp: " << Vector3::Clamp( Vector3(0), Vector3(9, 1000, 9), Vector3(1000, 1100, 1000)) << endl;
// 
// 
// 	if( Vector3(10) == Vector3(10,10,10) )
// 		cout << "Equal!" << endl;
// 
// 	if( Vector3(0,1,0) != Vector3(1,0,0) )
// 		cout << "Not Equal!" << endl;
// 
// 	cout << (Vector3(10) + Vector3(9, 0, 9)) << endl;
// 
// }
