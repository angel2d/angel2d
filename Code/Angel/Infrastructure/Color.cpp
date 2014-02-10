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
#include "../Infrastructure/Color.h"

#include "../Util/MathUtil.h"
#include <cstdio>

Color::Color()
{
	//default color is white
	R = G = B = A = 1.0f;
}

Color::Color(float r, float g, float b, float a, bool clamp)
{
	R = r;
	G = g;
	B = b;
	A = a;  // (Very Ayn Rand of us)
	
	if (clamp)
	{
		ClampMe();		
	}
}

Color Color::FromInts(int r, int g, int b, int a, bool clamp)
{
	Color forReturn;
	forReturn.R = (float)r / 255.0f;
	forReturn.G = (float)g / 255.0f;
	forReturn.B = (float)b / 255.0f;
	forReturn.A = (float)a / 255.0f;
	
	if (clamp)
	{
		forReturn.ClampMe();		
	}

	return forReturn;
}

Color Color::FromHexString(String hexString)
{
	Color forReturn;
	bool isHex = false;
	if (hexString[0] == '#')
	{
		hexString = hexString.substr(1);
		isHex = true;
	}
	if ( (hexString.substr(0, 2) == "0x") || (hexString.substr(0, 2) == "0X") )
	{
		hexString = hexString.substr(2);
		isHex = true;
	}
	
	if (isHex)
	{
		if ( (hexString.length() != 3) && (hexString.length() != 6) )
		{
			//invalid length, set to white
			return Color();
		}
		
		if (hexString.length() == 3)
		{
			//expand to 6
			String newString = "";
			newString += hexString.substr(0,1) + hexString.substr(0,1);
			newString += hexString.substr(1,1) + hexString.substr(1,1);
			newString += hexString.substr(2,1) + hexString.substr(2,1);
			hexString = newString;
		}
		
		String rString = hexString.substr(0,2);
		String gString = hexString.substr(2,2);
		String bString = hexString.substr(4,2);
		
		int rInt = HexToInteger(rString);
		int gInt = HexToInteger(gString);
		int bInt = HexToInteger(bString);
		
		forReturn.R = (float)rInt / 255.0f;
		forReturn.G = (float)gInt / 255.0f;
		forReturn.B = (float)bInt / 255.0f;
		forReturn.A = 1.0f;
		
		forReturn.ClampMe();
		return forReturn;
	}
	else
	{
		// no support for other string-defined colors -- to white with you
		return Color();
	}
}

int Color::HexToInteger(String hex)
{
	return strtol(hex.c_str(), NULL, 16);
}

void Color::ClampMe()
{
	R = MathUtil::Clamp(R, 0.0f, 1.0f);
	G = MathUtil::Clamp(G, 0.0f, 1.0f);
	B = MathUtil::Clamp(B, 0.0f, 1.0f);
	A = MathUtil::Clamp(A, 0.0f, 1.0f);
}

bool Color::operator==(const Color &c) const
{
	return R == c.R && G == c.G && B == c.B && A == c.A;
}

bool Color::operator!=(const Color &c) const
{
	return !(*this == c);
}

Color Color::operator-(const Color &c) const
{
	return Color(R - c.R, G - c.G, B - c.B, A - c.A, false);
}

Color Color::operator+(const Color &c) const
{
	return Color(R + c.R, G + c.G, B + c.B, A + c.A, false);
}

Color Color::operator/(float divider) const
{
	return Color(R / divider, G / divider, B / divider, A / divider, false);
}

Color Color::operator*(float scaleFactor) const
{
	return Color(R * scaleFactor, G * scaleFactor, B * scaleFactor, A * scaleFactor, false);
}
