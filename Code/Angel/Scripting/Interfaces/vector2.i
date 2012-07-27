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

struct Vec2ui
{
	unsigned int X, Y;
	Vec2ui(unsigned int x, unsigned int y) : X(x), Y(y) {}
	Vec2ui() : X(0), Y(0) {}
};

struct Vec3i
{
	int X, Y, Z;
	Vec3i(int x, int y, int z) : X(x), Y(y), Z(z) {}
	Vec3i() : X(0), Y(0), Z(0) {}
};

struct Vec3ui
{
	unsigned int X, Y, Z;
	Vec3ui(unsigned int x, unsigned int y, unsigned int z) : X(x), Y(y), Z(z) {}
	Vec3ui() : X(0), Y(0), Z(0) {}
};


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

%typemap(in) Vector2
{
	// Vector2 conversion
	Vector2 *vec;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&vec,SWIGTYPE_p_Vector2,0))) 
	{
		$1 = *vec;
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

%typemap(in) Vec2i
{
	// Vec2i conversion
	Vec2i *vec;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&vec,SWIGTYPE_p_Vec2i,0))) 
	{
		$1 = *vec;
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

%typecheck(SWIG_TYPECHECK_POINTER) Vector2
{
	// Vector2 typecheck
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

%typecheck(SWIG_TYPECHECK_POINTER) Vec2i
{
	// Vec2i typecheck
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
#endif

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
