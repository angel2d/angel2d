#include "../Util/StringUtil.h"

#include <sstream>
#include <algorithm>
#include <cctype>

#ifdef WIN32
	#define ci_strcmp _stricmp
#endif
#if defined(__APPLE__)
	#define ci_strcmp strcasecmp
#endif

const char StringUtil_WhiteSpaceChars[] = " \t\n\r";

template <class T>
bool from_string(T& t, 
				 const String& s, 
				 std::ios_base& (*f)(std::ios_base&))
{
	std::istringstream iss(s);
	return !(iss >> f >> t).fail();
}

template <class T>
String to_string(T& t, 
			 std::ios_base& (*f)(std::ios_base&))
{
	std::stringstream ss;
	ss << f << t;
	return ss.str();
}

int StringToInt( const String& s )
{
	int retVal = 0;
	from_string<int>( retVal, s, std::dec );
	return retVal;
}

float StringToFloat( const String& s )
{
	float retVal = 0.0f;
	from_string<float>( retVal, s, std::dec );
	return retVal;
}

bool StringToBool( const String& s )
{
	//compare to boolean vals first
	if( !ci_strcmp( s.c_str(), "true") )
		return true;
	else if( !ci_strcmp(s.c_str(), "false") )
		return false;
	return StringToInt(s) != 0;
}

Vector2 StringToVector2( const String& s )
{
	StringList split = SplitString(s);
	Vector2 retVal;

	if( split.size() > 0 )
		retVal.X = StringToFloat(split[0]);

	if( split.size() > 1 )
		retVal.Y = StringToFloat(split[1]);

	return retVal;
}


String IntToString( int val )
{
	return to_string( val, std::dec );
}

String FloatToStr( float val )
{
	return to_string( val, std::dec );
}

String BoolToStr( bool val )
{
	return IntToString( val );
}

String Vector2ToString( const Vector2& val )
{
	return FloatToStr( val.X ) + " " + FloatToStr( val.Y );
}


String ToUpper( const String& s )
{
	String retVal = s;
	// explicit cast needed to resolve ambiguity
	std::transform(retVal.begin(), retVal.end(), retVal.begin(),
		(int(*)(int)) std::toupper);

	return retVal;
}

String ToLower( const String& s )
{
	String retVal = s;
	// explicit cast needed to resolve ambiguity
	std::transform(retVal.begin(), retVal.end(), retVal.begin(),
		(int(*)(int)) std::tolower);

	return retVal;
}


StringList SplitString( const String& splitMe, const String& splitChars, bool bRemoveEmptyEntries /*=true*/)
{
	StringList retVal;

	//iterate over string
	String buildString;
	for ( unsigned int i = 0; i < splitMe.length(); i++ )
	{
		char ch = splitMe[i];
		if( splitChars.find( ch ) != String::npos)
		{
			//Add the build string to our return val
			if( !bRemoveEmptyEntries || buildString.length() > 0 )
				retVal.push_back( buildString );
			buildString.clear();
		}
		else
		{
			buildString += ch;
		}
	}

	//handle any dangling strings
	if( buildString.length() > 0 )
		retVal.push_back( buildString );

	return retVal;
}

StringList SplitString( const String& splitMe )
{
	return SplitString( splitMe, StringUtil_WhiteSpaceChars );
}


String TrimString( const String& trimMe, const String& trimChars )
{
	String retVal;

	if( trimChars.length() == 0 )
		return retVal;

	//trim from the front
	int trimStart = -1;
	for( unsigned int i = 0; i < trimMe.length(); i++ )
	{
		char ch = trimMe[i];
		if( trimChars.find(ch) == String::npos)
		{
			trimStart = i;
			break;
		}
	}

	if( trimStart >= 0 && trimStart < ((int)trimMe.length()) )
	{
		for( int i = (int)trimMe.length()-1; i >= 0; i-- )
		{
			char ch = trimMe[i];
			if( trimChars.find(ch) == String::npos )
			{
				retVal = trimMe.substr( trimStart, i - trimStart + 1);
				break;
			}
		}
	}

	return retVal;
}

String TrimString( const String& trimMe )
{
	return TrimString( trimMe, StringUtil_WhiteSpaceChars );
}

void GetCarCdr( StringList& inputStrings, String& car, String& cdr, int numInputStrings )
{
	if( inputStrings.size() == 0 )
		return;

	if( numInputStrings < 0 )
		numInputStrings = (int)inputStrings.size();

	car = inputStrings[0];
	for( int i = 1; i < numInputStrings; i++ )
	{
		cdr += inputStrings[i];
		//Only add a space between args that aren't at the end of the input string
		if( i < numInputStrings - 1 )
			cdr += " ";

	}
}