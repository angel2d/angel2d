%module angel
%{
#include "../../Infrastructure/Vector2.h"
#include "../../Infrastructure/VecStructs.h"
%}

struct Vec2i
{
	int X, Y;
	Vec2i(int x, int y) : X(x), Y(y) {}
	Vec2i() : X(0), Y(0) {}
};

#ifdef SWIGPYTHON
//all this junk just lets us treat lists as Vectors
%typemap(in) Vector2
{
	bool error = false;
	if (PyList_Check($input))
	{
		int arrLength = PyList_Size($input);
		if (arrLength < 2)
		{
			error = true;
		}
		else
		{
			PyObject* px = PyList_GetItem($input, 0);
			PyObject* py = PyList_GetItem($input, 1);
			
			float x, y;
			if (PyFloat_Check(px))
			{
				x = PyFloat_AsDouble(px);
			}
			else if (PyInt_Check(px))
			{
				x = (float)PyInt_AsLong(px);
			}
			else
			{
				error = true;
			}
			
			if (PyFloat_Check(py))
			{
				y = PyFloat_AsDouble(py);
			}
			else if (PyInt_Check(py))
			{
				y = (float)PyInt_AsLong(py);
			}
			else
			{
				error = true;
			}
			
			if (!error)
			{
				$1 = Vector2(x, y);
			}
		}
	}
	else
	{
		error = true;
	}
	
	if (error)
	{
		int result;
		void* arg_pointer;
		result = SWIG_ConvertPtr($input, &arg_pointer, SWIGTYPE_p_Vector2,  0 );
		if (!SWIG_IsOK(result)) {
			%argument_fail(result,"$type", $symname, $argnum);
		}  
		if (!arg_pointer) {
			%argument_nullref("$type", $symname, $argnum);
		} else {
			$1 = *(reinterpret_cast< Vector2 * >(arg_pointer));
		}
	}
}

%typecheck(SWIG_TYPECHECK_POINTER) Vector2
{
	if (PyList_Check($input))
	{
		$1 = 1;
	}
	else
	{
		PyObject* classType = PyObject_GetAttrString($input, "__class__");
		PyObject* pythonName = PyObject_GetAttrString(classType, "__name__");
		const char* className = PyString_AsString(pythonName);
		int length = PyString_Size(pythonName);
		if (strncmp("Vector2", className, length) == 0)
		{
			$1 = 1;
		}
		else
		{
			$1 = 0;
		}
	}
}
#endif

typedef std::vector<Vector2>	VectorList;
%template(VectorList)			std::vector<Vector2>;

struct Vector2
{
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
	//static Vector2 Normalize(const Vector2& value);

	static Vector2 Reflect(const Vector2& vector, const Vector2& normal);
	static Vector2 Min(const Vector2& value1, const Vector2& value2);
	static Vector2 Max(const Vector2& value1, const Vector2& value2);
	static Vector2 Clamp(const Vector2& value, const Vector2& min, const Vector2& max);
	static Vector2 Lerp(const Vector2& value1, const Vector2& value2, float amount);
	static Vector2 Negate(const Vector2& value);
	static Vector2 Rotate(const Vector2& value, const float radians);
	
	bool operator==(const Vector2 &v) const;
	bool operator!=(const Vector2 &v) const;
	
	Vector2 operator-() const;
	Vector2 operator-(const Vector2 &v) const;
	Vector2 operator+(const Vector2 &v) const;
	Vector2 operator/(float divider) const;
	Vector2 operator*(float scaleFactor) const;
};
