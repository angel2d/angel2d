#pragma once

#include "../Util/StringUtil.h"

bool GetLinesFromFile(const String& fileName, StringList& outList );
bool WriteLinesToFile( const String& fileName, const StringList& strings );
bool AppendLineToFile( const String& fileName, const String& line );
