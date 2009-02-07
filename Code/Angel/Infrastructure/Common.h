/** 
 * @file Common.h 
 *  This file handles the common definitions and includes that each platform
 *   uses, as well as the C++ libraries used frequently in Angel. 
 */
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
	
	//GCC is picky about what types are allowed to be used as indices to hashes. 
	// Defining this here lets us use std::strings to index, which is useful. 
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

