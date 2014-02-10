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
bool WriteLinesToFile(const String& fileName, const StringList& strings );

/**
 * Appends a set of lines to a file. 
 * 
 * @param fileName The path of the file to append to
 * @param strings The StringList to be append (each string will get its
 *   own line)
 * @return True if we could write to the file, false if we couldn't
 */
bool AppendLineToFile(const String& fileName, const String& line );

/**
 * Ensures that a path of directories exists -- returns true if it does,
 *  false if it doesn't (if, for example, the program doesn't have 
 *  sufficient permissions to create the path).
 * 
 * @param path The path to create
 * @return Whether it actually exists at the end of this function
 */
bool MakeDirectories(const String& path );

/**
 * Convenience function for reading an entire file as a single string.
 *  If there is no such file, and empty string will be returned.
 * 
 * @param fileName The file to read
 * @return The complete text of the file
 */
const String ReadWholeFile(const String& fileName);

/**
 * Gives a system-appropriate writable directory for the use of logs,
 *  preference files, etc. 
 * 
 * @return The path to the defined writable directory.
 */
const String GetStorageDirectory();

/**
 * Returns a path to the My Documents directory on Windows, or the 
 *  ~/Documents folder on Mac. On Linux? Who knows?!
 *
 * @return Path to the user's documents
 */
const String GetDocumentsPath();

/**
 * Gives the name of the current executable. 
 *
 * @return The name of the current executable
 */
const String GetExeName();

/**
 * Returns the modification time of a file. Defined as number of seconds
 *  after a system-specific epoch, so not portable between operating 
 *  systems, but useful for comparisons within a single build. 
 *
 * @param fileName The file to check
 * @return The modification time of the file. Returns 0 if file could
 *   not be found. NOTE: this actually *is* a valid modification time,
 *   so apologies if you happen to have a file that was modified exactly
 *   on your epoch time.
 */
const long GetModificationTime(const String& fileName);
