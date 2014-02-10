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

#pragma once

#include "../Util/StringUtil.h"
#include "../Infrastructure/Console.h"

///Abstract base class for logs
/** 
 * The DeveloperLog simply provides an interface for other Log classes to 
 *  implement. 
 */
class DeveloperLog
{
public:
	/**
	 * Virtual destructor needed in abstract base class. 
	 */
	virtual ~DeveloperLog() {}

	/**
	 * Logs a string. 
	 * 
	 * Pure virtual function; must be implemented in the subclass.
	 * 
	 * @param val The string to be logged. 
	 */
	virtual void Log( const String& val ) = 0;
	
	/**
	 * Log a formatted string using printf syntax. 
	 * 
	 * http://www.cplusplus.com/reference/clibrary/cstdio/printf.html
	 * 
	 * @param format The format string
	 * @param ... The parameters to substitute into the format string
	 */
	void Printf(const char* format, ...);
};

///A log that writes to the current Console
/** 
 * This type of Log will append any text you give it to the Console's log 
 *  area (visible by toggling the Console on [the '~' key by default]). 
 */
class ConsoleLog : public DeveloperLog
{
public:
	/**
	 * Writes the string to the Console
	 * 
	 * @param val The string to be logged
	 */
	virtual void Log( const String& val);
};

///A log which writes to a file on disk. 
/** 
 * This type of Log appends its text to a specified file in the Logs directory. 
 */
class FileLog : public DeveloperLog
{
public:
	/**
	 * Gives the relative path to the log file from a desired name. 
	 * 
	 * @param fileName The desired name (for example: "StartupLog")
	 * @return The path to the file (for example: "Logs/StartupLog.log"). This
	 *   path is relative to the executable. 
	 */
	static String MakeLogFileName( const String& fileName );
	
	/**
	 * The constructor takes a filename (which can be generated from 
	 *  FileLog::MakeLogFileName). \b NB: If the file already exists, it will 
	 *  be cleared. The file will get a timestamp at the top saying when it
	 *  was first opened. 
	 * 
	 * @param fileName 
	 */
	FileLog( const String& fileName );

	/**
	 * The string to be logged in the file. 
	 * 
	 * @param val The string to put in the file
	 */
	virtual void Log( const String& val);

private:
	String _fileName;
};

///A log which writes to standard output (rather than the in-game console)
/** 
 * This type of log writes its output straight to the program's standard 
 *  output. On Windows, it will output to the output pane of Visual Studio
 *  (easier to see while you're debugging).
 */
class SystemLog : public DeveloperLog
{
public:
	/**
	 * The string to be logged to the output. 
	 * 
	 * @param val The string
	 */
	virtual void Log( const String& val);
};

#define sysLog CompoundLog::GetSystemLog()

///Lets you write to multiple logs at once
/** 
 * This class collects various other logs together and lets you write the
 *  same value to them simultaneously. This is useful if you want to write 
 *  something to both the screen and a file at the same time. 
 */
class CompoundLog : public DeveloperLog
{
public:
	/**
	 * Add a log to the list of receivers. 
	 * 
	 * @param addLog The log you wish to add. 
	 */
	void AddLog( DeveloperLog* addLog );
	
	/**
	 * Writes a string to all registered logs
	 * 
	 * @param val The string to log. 
	 */
	virtual void Log( const String& val );
	
	/**
	 * A reference to the system log (where Angel will spew its information,
	 *  and to which you can attach another log if you want).
	 * 
	 * @return The system log
	 */
	static CompoundLog& GetSystemLog();

private:
	std::vector<DeveloperLog*> _logs;
	
	static CompoundLog *_sysLog;
};
