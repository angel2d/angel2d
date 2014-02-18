%module angel
%{
#include "../../Infrastructure/Vector2.h"
#include "../../Infrastructure/Vector3.h"
#include "../../Infrastructure/VecStructs.h"
%}

#ifdef SWIGLUA
%typemap(out) std::vector<Vector2>
%{
	{
		lua_newtable(L);
		if ($1.size() > 0)
		{
			for (unsigned int i=0; i <= $1.size(); i++)
			{
				lua_pushnumber(L, i);
				SWIG_NewPointerObj(L, $i.at(i-1), SWIGTYPE_p_Vector2, 1);
				lua_settable(L, -3);
			}
		}
	
		SWIG_arg += 1; 
	}
%}


%typemap(in) Vec2i
{
	// Vec2i conversion
	Vec2i *vecPtr;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&vecPtr,SWIGTYPE_p_Vec2i,0)))
	{
		$1 = *vecPtr;
	}
	else
	{
		// convert table parameters to ints
		lua_pushinteger(L, 1);
		lua_gettable(L, $input);
		int x = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pushinteger(L, 2);
		lua_gettable(L, $input);
		int y = lua_tointeger(L, -1);
		lua_pop(L, 1);
		
		// build the vector
		$1 = Vec2i(x, y);
	}
}

%typemap(in) const Vec2i&
{
	// const Vec2i& conversion
	Vec2i *vecPtr;
	Vec2i vec;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&vecPtr,SWIGTYPE_p_Vec2i,0)))
	{
		$1 = vecPtr;
	}
	else
	{
		// convert table parameters to ints
		lua_pushinteger(L, 1);
		lua_gettable(L, $input);
		int x = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pushinteger(L, 2);
		lua_gettable(L, $input);
		int y = lua_tointeger(L, -1);
		lua_pop(L, 1);
		
		// build the vector
		vec.X = x;
		vec.Y = y;
		$1 = &vec;
	}
}

%typemap(in) Vec2ui
{
	// Vec2ui conversion
	Vec2ui *vecPtr;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&vecPtr,SWIGTYPE_p_Vec2ui,0)))
	{
		$1 = *vecPtr;
	}
	else
	{
		// convert table parameters to ints
		lua_pushinteger(L, 1);
		lua_gettable(L, $input);
		unsigned int x = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pushinteger(L, 2);
		lua_gettable(L, $input);
		unsigned int y = lua_tointeger(L, -1);
		lua_pop(L, 1);
		
		// build the vector
		$1 = Vec2ui(x, y);
	}
}

%typemap(in) const Vec2ui&
{
	// cosnt Vec2ui& conversion
	Vec2ui *vecPtr;
	Vec2ui vec;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&vecPtr,SWIGTYPE_p_Vec2ui,0)))
	{
		$1 = vecPtr;
	}
	else
	{
		// convert table parameters to ints
		lua_pushinteger(L, 1);
		lua_gettable(L, $input);
		unsigned int x = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pushinteger(L, 2);
		lua_gettable(L, $input);
		unsigned int y = lua_tointeger(L, -1);
		lua_pop(L, 1);
		
		// build the vector
		vec.X = x;
		vec.Y = y;
		$1 = &vec;
	}
}

%typemap(in) Vec3i
{
	// Vec3i conversion
	Vec3i *vecPtr;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&vecPtr,SWIGTYPE_p_Vec3i,0)))
	{
		$1 = *vecPtr;
	}
	else
	{
		// convert table parameters to ints
		lua_pushinteger(L, 1);
		lua_gettable(L, $input);
		int x = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pushinteger(L, 2);
		lua_gettable(L, $input);
		int y = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pushinteger(L, 3);
		lua_gettable(L, $input);
		int z = lua_tointeger(L, -1);
		lua_pop(L, 1);
		
		// build the vector
		$1 = Vec3i(x, y, z);
	}
}

%typemap(in) const Vec3i&
{
	// const Vec3i& conversion
	Vec3i *vecPtr;
	Vec3i vec;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&vecPtr,SWIGTYPE_p_Vec3i,0)))
	{
		$1 = vecPtr;
	}
	else
	{
		// convert table parameters to ints
		lua_pushinteger(L, 1);
		lua_gettable(L, $input);
		int x = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pushinteger(L, 2);
		lua_gettable(L, $input);
		int y = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pushinteger(L, 3);
		lua_gettable(L, $input);
		int z = lua_tointeger(L, -1);
		lua_pop(L, 1);
		
		// build the vector
		vec.X = x;
		vec.Y = y;
		vec.Z = z;
		$1 = &vec;
	}
}

%typemap(in) Vec3ui
{
	// Vec3ui conversion
	Vec3ui *vecPtr;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&vecPtr,SWIGTYPE_p_Vec3ui,0)))
	{
		$1 = *vecPtr;
	}
	else
	{
		// convert table parameters to ints
		lua_pushinteger(L, 1);
		lua_gettable(L, $input);
		unsigned int x = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pushinteger(L, 2);
		lua_gettable(L, $input);
		unsigned int y = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pushinteger(L, 3);
		lua_gettable(L, $input);
		unsigned int z = lua_tointeger(L, -1);
		lua_pop(L, 1);
		
		// build the vector
		$1 = Vec3ui(x, y, z);
	}
}

%typemap(in) const Vec3ui&
{
	// const Vec3ui& conversion
	Vec3ui *vecPtr;
	Vec3ui vec;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&vecPtr,SWIGTYPE_p_Vec3ui,0)))
	{
		$1 = vecPtr;
	}
	else
	{
		// convert table parameters to ints
		lua_pushinteger(L, 1);
		lua_gettable(L, $input);
		unsigned int x = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pushinteger(L, 2);
		lua_gettable(L, $input);
		unsigned int y = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pushinteger(L, 3);
		lua_gettable(L, $input);
		unsigned int z = lua_tointeger(L, -1);
		lua_pop(L, 1);
		
		// build the vector
		vec.X = x;
		vec.Y = y;
		vec.Z = z;
		$1 = &vec;
	}
}

%typemap(in) Vector2
{
	// Vector2 conversion
	Vector2 *vecPtr;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&vecPtr,SWIGTYPE_p_Vector2,0))) 
	{
		$1 = *vecPtr;
	}
	else
	{
		// convert table parameters to floats
		lua_pushinteger(L, 1);
		lua_gettable(L, $input);
		float x = lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_pushinteger(L, 2);
		lua_gettable(L, $input);
		float y = lua_tonumber(L, -1);
		lua_pop(L, 1);
		
		// build the vector
		$1 = Vector2(x, y);
	}
}

%typemap(in) const Vector2&
{
	// const Vector2& conversion
	Vector2 *vecPtr;
	Vector2 vec;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&vecPtr,SWIGTYPE_p_Vector2,0))) 
	{
		$1 = vecPtr;
	}
	else
	{
		// convert table parameters to floats
		lua_pushinteger(L, 1);
		lua_gettable(L, $input);
		float x = lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_pushinteger(L, 2);
		lua_gettable(L, $input);
		float y = lua_tonumber(L, -1);
		lua_pop(L, 1);
		
		// build the vector
		vec.X = x;
		vec.Y = y;
		$1 = &vec;
	}
}

%typemap(in) Vector3
{
	// Vector3 conversion
	Vector3 *vecPtr;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&vecPtr,SWIGTYPE_p_Vector3,0))) 
	{
		$1 = *vecPtr;
	}
	else
	{
		// convert table parameters to floats
		lua_pushinteger(L, 1);
		lua_gettable(L, $input);
		float x = lua_tonumber(L, -1);
		lua_pop(L, 1);

		lua_pushinteger(L, 2);
		lua_gettable(L, $input);
		float y = lua_tonumber(L, -1);
		lua_pop(L, 1);

		lua_pushinteger(L, 3);
		lua_gettable(L, $input);
		float z = lua_tonumber(L, -1);
		lua_pop(L, 1);
		
		// build the vector
		$1 = Vector3(x, y, z);
	}
}

%typemap(in) const Vector3&
{
	// const Vector3& conversion
	Vector3 *vecPtr;
	Vector3 vec;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&vecPtr,SWIGTYPE_p_Vector3,0))) 
	{
		$1 = vecPtr;
	}
	else
	{
		// convert table parameters to floats
		lua_pushinteger(L, 1);
		lua_gettable(L, $input);
		float x = lua_tonumber(L, -1);
		lua_pop(L, 1);

		lua_pushinteger(L, 2);
		lua_gettable(L, $input);
		float y = lua_tonumber(L, -1);
		lua_pop(L, 1);

		lua_pushinteger(L, 3);
		lua_gettable(L, $input);
		float z = lua_tonumber(L, -1);
		lua_pop(L, 1);
		
		// build the vector
		vec.X = x;
		vec.Y = y;
		vec.Z = z;
		$1 = &vec;
	}
}

%typecheck(SWIG_TYPECHECK_POINTER) Vector2, const Vector2&
{
	// Vector2 / const Vector2& typecheck
	$1 = 0;
	swig_lua_userdata* usr;
	swig_cast_info *cast;
	usr=(swig_lua_userdata*)lua_touserdata(L,$input);
	if (usr != NULL)
	{
		cast=SWIG_TypeCheckStruct(usr->type, SWIGTYPE_p_Vector2);
		if (cast)
		{
			$1 = 1;
		}
	}
	
	if (!$1)
	{
		if (lua_istable(L, $input) && (lua_rawlen(L, $input) >= 2))
		{
			// verify that at least the first two elements of the table contain numbers
			lua_pushinteger(L, 1);
			lua_gettable(L, $input);
			int v1 = lua_isnumber(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 2);
			lua_gettable(L, $input);
			int v2 = lua_isnumber(L, -1);
			lua_pop(L, 1);
			$1 = (v1 && v2);
		}
		else
		{
			$1 = 0;
		}
	}
}

%typecheck(SWIG_TYPECHECK_POINTER) Vector3, const Vector3&
{
	// Vector3 / const Vector3& typecheck
	$1 = 0;
	swig_lua_userdata* usr;
	swig_cast_info *cast;
	usr=(swig_lua_userdata*)lua_touserdata(L,$input);
	if (usr != NULL)
	{
		cast=SWIG_TypeCheckStruct(usr->type, SWIGTYPE_p_Vector3);
		if (cast)
		{
			$1 = 1;
		}
	}
	
	if (!$1)
	{
		if (lua_istable(L, $input) && (lua_rawlen(L, $input) >= 3))
		{
			// verify that at least the first three elements of the table contain numbers
			lua_pushinteger(L, 1);
			lua_gettable(L, $input);
			int v1 = lua_isnumber(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 2);
			lua_gettable(L, $input);
			int v2 = lua_isnumber(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 3);
			lua_gettable(L, $input);
			int v3 = lua_isnumber(L, -1);
			lua_pop(L, 1);
			$1 = (v1 && v2 && v3);
		}
		else
		{
			$1 = 0;
		}
	}
}

%typecheck(SWIG_TYPECHECK_POINTER) Vec2i, const Vec2i&
{
	// Vec2i / const Vec2i& typecheck
	$1 = 0;
	swig_lua_userdata* usr;
	swig_cast_info *cast;
	usr=(swig_lua_userdata*)lua_touserdata(L,$input);
	if (usr != NULL)
	{
		cast=SWIG_TypeCheckStruct(usr->type, SWIGTYPE_p_Vec2i);
		if (cast)
		{
			$1 = 1;
		}
	}

	if (!$1)
	{
		if (lua_istable(L, $input) && (lua_rawlen(L, $input) >= 2))
		{
			// verify that at least the first two elements of the table contain integers
			lua_pushinteger(L, 1);
			lua_gettable(L, $input);
			int v1 = lua_isnumber(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 2);
			lua_gettable(L, $input);
			int v2 = lua_isnumber(L, -1);
			lua_pop(L, 1);
			$1 = (v1 && v2);
		}
		else
		{
			$1 = 0;
		}
	}
}

%typecheck(SWIG_TYPECHECK_POINTER) Vec2ui, const Vec2ui&
{
	// Vec2ui / const Vec2ui& typecheck
	$1 = 0;
	swig_lua_userdata* usr;
	swig_cast_info *cast;
	usr=(swig_lua_userdata*)lua_touserdata(L,$input);
	if (usr != NULL)
	{
		cast=SWIG_TypeCheckStruct(usr->type, SWIGTYPE_p_Vec2ui);
		if (cast)
		{
			$1 = 1;
		}
	}
	
	if (!$1)
	{
		if (lua_istable(L, $input) && (lua_rawlen(L, $input) >= 2))
		{
			// verify that at least the first two elements of the table contain non-negative integers
			lua_pushinteger(L, 1);
			lua_gettable(L, $input);
			int v1 = lua_isnumber(L, -1);
			int x  = lua_tointeger(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 2);
			lua_gettable(L, $input);
			int v2 = lua_isnumber(L, -1);
			int y  = lua_tointeger(L, -1);
			lua_pop(L, 1);
			$1 = (v1 && v2 && (x >= 0) && (y >= 0));
		}
		else
		{
			$1 = 0;
		}
	}
}

%typecheck(SWIG_TYPECHECK_POINTER) Vec3i, const Vec3i&
{
	// Vec3i / const Vec3i& typecheck
	$1 = 0;
	swig_lua_userdata* usr;
	swig_cast_info *cast;
	usr=(swig_lua_userdata*)lua_touserdata(L,$input);
	if (usr != NULL)
	{
		cast=SWIG_TypeCheckStruct(usr->type, SWIGTYPE_p_Vec3i);
		if (cast)
		{
			$1 = 1;
		}
	}
	
	if (!$1)
	{
		if (lua_istable(L, $input) && (lua_rawlen(L, $input) >= 3))
		{
			// verify that at least the first three elements of the table contain integers
			lua_pushinteger(L, 1);
			lua_gettable(L, $input);
			int v1 = lua_isnumber(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 2);
			lua_gettable(L, $input);
			int v2 = lua_isnumber(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 3);
			lua_gettable(L, $input);
			int v3 = lua_isnumber(L, -1);
			lua_pop(L, 1);
			$1 = (v1 && v2 && v3);
		}
		else
		{
			$1 = 0;
		}
	}
}

%typecheck(SWIG_TYPECHECK_POINTER) Vec3ui, const Vec3ui&
{
	// Vec3ui / const Vec3ui typecheck
	$1 = 0;
	swig_lua_userdata* usr;
	swig_cast_info *cast;
	usr=(swig_lua_userdata*)lua_touserdata(L,$input);
	if (usr != NULL)
	{
		cast=SWIG_TypeCheckStruct(usr->type, SWIGTYPE_p_Vec3ui);
		if (cast)
		{
			$1 = 1;
		}
	}
	
	if (!$1)
	{
		if (lua_istable(L, $input) && (lua_rawlen(L, $input) >= 3))
		{
			// verify that at least the first three elements of the table contain non-negative integers
			lua_pushinteger(L, 1);
			lua_gettable(L, $input);
			int v1 = lua_isnumber(L, -1);
			int x  = lua_tointeger(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 2);
			lua_gettable(L, $input);
			int v2 = lua_isnumber(L, -1);
			int y  = lua_tointeger(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 3);
			lua_gettable(L, $input);
			int v3 = lua_isnumber(L, -1);
			int z  = lua_tointeger(L, -1);
			lua_pop	(L, 1);
			$1 = (v1 && v2 && v3 && (x >= 0) && (y >= 0) && (z >= 0));
		}
		else
		{
			$1 = 0;
		}
	}
}
#endif

struct Vec2i
{
	int X, Y;
	Vec2i(int x, int y) : X(x), Y(y) {}
	Vec2i() : X(0), Y(0) {}
	
	bool operator==(const Vec2i &v) const;
	bool operator!=(const Vec2i &v) const;
};

struct Vec2ui
{
	unsigned int X, Y;
	Vec2ui(unsigned int x, unsigned int y) : X(x), Y(y) {}
	Vec2ui() : X(0), Y(0) {}
	
	bool operator==(const Vec2ui &v) const;
	bool operator!=(const Vec2ui &v) const;
};

struct Vec3i
{
	int X, Y, Z;
	Vec3i(int x, int y, int z) : X(x), Y(y), Z(z) {}
	Vec3i() : X(0), Y(0), Z(0) {}
	
	bool operator==(const Vec3i &v) const;
	bool operator!=(const Vec3i &v) const;
};

struct Vec3ui
{
	unsigned int X, Y, Z;
	Vec3ui(unsigned int x, unsigned int y, unsigned int z) : X(x), Y(y), Z(z) {}
	Vec3ui() : X(0), Y(0), Z(0) {}
	
	bool operator==(const Vec3ui &v) const;
	bool operator!=(const Vec3ui &v) const;
};

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

	static Vector2 Reflect(const Vector2& vector, const Vector2& normal);
	static Vector2 Min(const Vector2& value1, const Vector2& value2);
	static Vector2 Max(const Vector2& value1, const Vector2& value2);
	static Vector2 Clamp(const Vector2& value, const Vector2& min, const Vector2& max);
	static Vector2 Lerp(const Vector2& value1, const Vector2& value2, float amount);
	static Vector2 Negate(const Vector2& value);
	static Vector2 Rotate(const Vector2& value, float radians);
	
	bool operator==(const Vector2& v) const;
	bool operator!=(const Vector2& v) const;
	
	Vector2 operator-() const;
	Vector2 operator-(const Vector2& v) const;
	Vector2 operator+(const Vector2& v) const;
	Vector2 operator/(float divider) const;
	Vector2 operator*(float scaleFactor) const;

	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float f);
	Vector2& operator/=(float f);
};


struct Vector3
{
	float X;
	float Y;
	float Z;
	
	static Vector3 Zero;
	static Vector3 One;
	static Vector3 UnitX;
	static Vector3 UnitY;
	static Vector3 UnitZ;
	Vector3(float x, float y, float z);
	Vector3(float value);
	Vector3();
	
	float Length();
	float LengthSquared();

	static float Distance(const Vector3& value1, const Vector3& value2);
	static float DistanceSquared(const Vector3& value1, const Vector3& value2);
	static float Dot(const Vector3& value1, const Vector3& value2);
	
	void Normalize();

	static Vector3 Reflect(const Vector3& vector, const Vector3& normal);
	static Vector3 Min(const Vector3& value1, const Vector3& value2);
	static Vector3 Max(const Vector3& value1, const Vector3& value2);
	static Vector3 Clamp(const Vector3& value1, const Vector3& min, const Vector3& max);
	static Vector3 Lerp(const Vector3& value1, const Vector3& value2, float amount);
	static Vector3 Negate(const Vector3& value);
	
	bool operator==(const Vector3& v) const;
	bool operator!=(const Vector3& v) const;
	
	Vector3 operator-() const;
	Vector3 operator-(const Vector3& v) const;
	Vector3 operator+(const Vector3& v) const;
	Vector3 operator/(float divider) const;
	Vector3 operator*(float scaleFactor) const;

	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float f);
	Vector3& operator/=(float f);
};
