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

#pragma once

#include "../Util/StringUtil.h"

///A class to encapsulate color information
/** 
 * This class consolidates all color information into a single unit that can
 *  be easily passed around functions, manipulated, and lerped.
 * 
 * The four color components are public members since they are frequently
 *  accessed and there is no real reason to hide them behind accessors. They 
 *  are always stored as floats and range from 0.0f to 1.0f. 
 * 
 * Note that the common arithmetical and comparison operators are defined for
 *  this class, to make it easy to mathematically manipulate the color of your
 *  Actors. 
 */
class Color
{
public:
	/** 
	 * The Red component
	 */
	float R;
	/** 
	 * The Green component
	 */
	float G;
	/** 
	 * The Blue component
	 */
	float B;
	/** 
	 * The Alpha component (1.0 == opaque, 0.0 == invisible)
	 */
	float A;
	
	/**
	 * The default constructor creates an opaque, pure white (all components
	 *  are 1.0f).
	 */
	Color();
	
	/**
	 * A constructor to specify component values right from the start. 
	 * 
	 * @param r The Red component
	 * @param g The Green component
	 * @param b The Blue component
	 * @param a The Alpha component
	 * @param clamp Whether or not to clamp the components to the range 0.0 to 
	 *   1.0. Usually you want to do this (and the default reflects this case), 
	 *   unless you're doing some kind of nutty color math, in which case you 
	 *   should set this to false. 
	 */
	Color(float r, float g, float b, float a=1.0f, bool clamp=true);
	
	/**
	 * A function to specify colors as integers from 0 to 255. Useful if
	 *  you've got a color picker you like that gives you values in this range. 
	 *  
	 * Note that internally the numbers are converted to floats from 0 to 1. 
	 * 
	 * @param r The Red component
	 * @param g The Green component
	 * @param b The Blue component
	 * @param a The Alpha component
	 * @param clamp Whether or not to clamp the components to the range 0.0 to 
	 *   1.0. Usually you want to do this (and the default reflects this case), 
	 *   unless you're doing some kind of nutty color math, in which case you 
	 *   should set this to false.
	 */
	static Color FromInts(int r, int g, int b, int a=255, bool clamp=true);
	
	/**
	 * A function to specify a color as a hex string, like in CSS. For those
	 *  used to specifying colors for web pages, you have an option here. 
	 * 
	 * @param hexString The string identifying the color ("0xfff", "#fa6244", etc.)
	 */
	static Color FromHexString(String hexString);
	
	bool operator==(const Color &c) const;
	bool operator!=(const Color &c) const;
	
	Color operator-(const Color &c) const;
	Color operator+(const Color &c) const;
	Color operator/(float divider) const;
	Color operator*(float scaleFactor) const;
	
private:
	static int HexToInteger(String hex);
	void ClampMe();
};
