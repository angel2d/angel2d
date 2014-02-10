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
#include "../Infrastructure/Log.h"

#include "../Infrastructure/World.h"
#include "../Util/MathUtil.h"
#include "../Util/FileUtil.h"

#include <stdio.h>
#include <time.h>
#include <cstdarg>


CompoundLog* CompoundLog::_sysLog = NULL;

#define MAX_LOG_STRING 1024

const String __GetTimeString()
{
	time_t rawtime;
	time ( &rawtime );
	
	#if defined(WIN32)
		const unsigned int timeWidth = 26; 
		char timeString[timeWidth]; //ctime_s fills a string of exactly 26 characters
		ctime_s(timeString, timeWidth, &rawtime);
	#elif defined(__APPLE__) || defined(__linux__)
		char *timeString = ctime(&rawtime);
	#endif
	return TrimString(timeString);
}

void DeveloperLog::Printf(const char* format, ...)
{
	char buff[MAX_LOG_STRING];
	va_list args;
	va_start(args, format);
	vsnprintf(buff, MAX_LOG_STRING, format, args);
	va_end(args);
	
	this->Log(String(buff));
}

void CompoundLog::AddLog( DeveloperLog* addLog )
{
	//Add unique
	for( unsigned int i = 0; i < _logs.size(); i++ )
	{
		if( addLog == _logs[i] )
			return;
	}

	_logs.push_back( addLog );
}

void CompoundLog::Log( const String& val )
{
	for( unsigned int i = 0; i < _logs.size(); i++ )
	{
		_logs[i]->Log( val );
	}
}

CompoundLog& CompoundLog::GetSystemLog()
{
	if (_sysLog == NULL)
	{
		_sysLog = new CompoundLog();
		_sysLog->AddLog(new SystemLog());
	}
	return *_sysLog;
}


void ConsoleLog::Log( const String& val)
{
	if (theWorld.GetConsole() != NULL)
	{
		#if !ANGEL_MOBILE
			theWorld.GetConsole()->WriteToOutput(val + "\n");
		#endif
	}
}

String FileLog::MakeLogFileName( const String& fileName )
{
	String logDir = GetStorageDirectory() + "Logs/";
	#if defined(WIN32)
		// logDir is already sufficient
	#elif defined(__APPLE__)
		MakeDirectories(logDir);
	#elif defined(__linux__)
		// logDir is already sufficient
	#endif
	
	return logDir + fileName + ".log";
}


FileLog::FileLog( const String& fileName )
: _fileName(fileName)
{
	//TODO: may want to backup the old log?
	//Clear the current log
	StringList logHeader;
	logHeader.push_back( String("Opened Log: ") + _fileName );
	logHeader.push_back( String("On: ") + __GetTimeString() );
	logHeader.push_back("");
	WriteLinesToFile( _fileName, logHeader );
}

void FileLog::Log( const String& val)
{
	AppendLineToFile( _fileName, __GetTimeString() + ": " + val );
}


void SystemLog::Log( const String &val)
{
	#if defined(_MSC_VER)
		//output to pane
		OutputDebugString(val.c_str());
		OutputDebugString("\n");
	#else
		std::cout << val << std::endl;
	#endif
}
