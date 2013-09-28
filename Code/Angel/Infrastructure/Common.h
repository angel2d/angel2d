//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
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

/** 
 * @file Common.h 
 *  This file handles the common definitions and includes that each platform
 *   uses, as well as the C++ libraries used frequently in Angel. 
 */
#pragma once

#if defined(WIN32)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <direct.h>
	#include <hash_map>
	#define hashmap_ns stdext
	#include <GL/gl.h>
	#include <GL/glu.h>
#elif defined(__APPLE__)
	#include "TargetConditionals.h"
	#if ANGEL_MOBILE
		#include <OpenGLES/ES1/gl.h>
		#include "glu.h"
		#include <sys/time.h>
		#import <Availability.h>
		#ifndef __IPHONE_5_0
			#warning "This project uses features only available in iPhone SDK 5.0 and later."
		#endif
		#ifdef __OBJC__
			#import <Foundation/Foundation.h>
			#import <UIKit/UIKit.h>
		#else
			#include <CoreFoundation/CoreFoundation.h>
		#endif
	#else
		#include <OpenGL/gl.h>
		#include <OpenGL/glu.h>
		#ifndef __OBJC__
			#include <CoreFoundation/CoreFoundation.h>
		#endif
	#endif
#endif
#if defined(__APPLE__) || defined(__linux__)
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
	#if ANGEL_MOBILE
		// making up for OpenGL|ES missing pieces
		#define glColor3f(r,g,b) glColor4f(r,g,b,1.0f)
		#define GL_CLAMP GL_CLAMP_TO_EDGE
	#endif
#endif

#if !ANGEL_MOBILE
	#define GLFW_INCLUDE_GLU
	#include <GLFW/glfw3.h>
#endif

#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

