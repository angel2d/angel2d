#pragma once

#if defined(WIN32)
	#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
	#include <windows.h>
	#include <hash_map>
	#define hashmap_ns stdext
	#include <GL/glu.h>

#elif defined(__APPLE__)
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <ext/hash_map>
	#define hashmap_ns __gnu_cxx
	namespace hashmap_ns
	{
		template<> struct hash< std::string >
		{
			size_t operator()( const std::string& x ) const
			{
				return hash< const char* >()( x.c_str() );
			}
		};
	}
#endif

#include <GL/glfw.h>

#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

