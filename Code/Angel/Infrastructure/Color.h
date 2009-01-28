#pragma once

#include "../Infrastructure/Common.h"
#include "../Util/StringUtil.h"

class Color
{
public:
	float R, G, B, A;
	
	Color();
	Color(float r, float g, float b, float a=1.0f, bool clamp=true);
	Color(int r, int g, int b, int a=255, bool clamp=true);
	Color(String hexString);
	
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
