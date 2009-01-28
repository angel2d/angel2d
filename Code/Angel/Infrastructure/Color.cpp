#include "../Infrastructure/Color.h"

#include "../Util/MathUtil.h"

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

Color::Color(int r, int g, int b, int a, bool clamp)
{
	R = (float)r / 255.0f;
	G = (float)g / 255.0f;
	B = (float)b / 255.0f;
	A = (float)a / 255.0f;
	
	if (clamp)
	{
		ClampMe();		
	}
}

Color::Color(String hexString)
{
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
			R = G = B = A = 1.0f;
			return;
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
		
		R = (float)rInt / 255.0f;
		G = (float)gInt / 255.0f;
		B = (float)bInt / 255.0f;
		A = 1.0f;
		
		ClampMe();
	}
	else
	{
		// no support for other string-defined colors -- to white with you
		R = G = B = A = 1.0f;
		return;
	}
}

int Color::HexToInteger(String hex)
{
	int hexInt;
	sscanf( hex.c_str(), "%x", &hexInt );
	return hexInt; 
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
