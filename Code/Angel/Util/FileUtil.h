/** 
 * @file FileUtil.h
 * A set of C-style utility functions to handle reading and writing files. 
 */
#pragma once

#include "../Util/StringUtil.h"

/**
 * Gets the entire contents of a file with each line separated for you. 
 *  (Doesn't do smart streaming, so don't pass it bajigabyte sized files.)
 * 
 * @param fileName The path to the file to load
 * @param outList A StringList to which the file's lines will be appended, 
 *   with each line being its own value.
 * @return True if we could read the file, false if we couldn't
 */
bool GetLinesFromFile(const String& fileName, StringList& outList );

/**
 * Writes a set of lines to a file. Will wipe out any existing file contents.
 * 
 * @param fileName The path of the file to write to
 * @param strings The StringList to be written (each string will get its
 *   own line)
 * @return True if we could write to the file, false if we couldn't
 */
bool WriteLinesToFile( const String& fileName, const StringList& strings );

/**
 * Appends a set of lines to a file. 
 * 
 * @param fileName The path of the file to append to
 * @param strings The StringList to be append (each string will get its
 *   own line)
 * @return True if we could write to the file, false if we couldn't
 */
bool AppendLineToFile( const String& fileName, const String& line );
