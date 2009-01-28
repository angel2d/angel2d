#pragma once

#include "../Infrastructure/Common.h"
#include "../Infrastructure/Vector2.h"

typedef std::string			String;
typedef std::vector<String>	StringList;
typedef std::set<String>	StringSet;

int StringToInt( const String& s );
float StringToFloat( const String& s );
bool StringToBool( const String& s );
Vector2 StringToVector2( const String& s );


String IntToString( int val );
String FloatToStr( float val );
String BoolToStr( bool val );
String Vector2ToString( const Vector2& val );

String ToUpper( const String& s );
String ToLower( const String& s );

StringList SplitString( const String& splitMe, const String& splitChars, bool bRemoveEmptyEntries = true );
StringList SplitString( const String& splitMe );

String TrimString( const String& trimMe, const String& trimChars );
String TrimString( const String& trimMe );

void GetCarCdr( StringList& inputStrings, String& car, String& cdr, int numInputStrings = -1 );
