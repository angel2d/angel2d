//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2010, Shane J. M. Liesegang
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

#include "../Infrastructure/Log.h"

#include "../Util/MathUtil.h"
#include "../Util/FileUtil.h"

#include <stdio.h>
#include <time.h>
#include <cstdarg>


CompoundLog* CompoundLog::_sysLog = NULL;

#define MAX_LOG_STRING 1024

void DeveloperLog::Printf(const String& format, ...)
{
	char buff[MAX_LOG_STRING];
	va_list args;
	va_start(args, format);
	vsprintf(buff, format.c_str(), args);
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
		theWorld.GetConsole()->WriteToOutput(val + "\n");
	}
}

String FileLog::MakeLogFileName( const String& fileName )
{
	#if defined(WIN32)
		String logDir = "Logs/";
	#elif defined(__APPLE__) || defined(__linux__)
		String logDir = getenv("HOME");
		logDir += "/Library/Application Support/Angel Games/Logs/";
		MakeDirectories(logDir);
	#endif
	
	return logDir + fileName + ".log";
}


FileLog::FileLog( const String& fileName )
: _fileName(fileName)
{
	time_t rawtime;
	time ( &rawtime );

	//TODO: may want to backup the old log?
	//Clear the current log
	StringList logHeader;
	logHeader.push_back( String("Opened Log: ") + _fileName );
	#if defined(WIN32)
		const unsigned int timeWidth = 26; 
		char timeString[timeWidth]; //ctime_s fills a string of exactly 26 characters
		ctime_s(timeString, timeWidth, &rawtime);
	#elif defined(__APPLE__) || defined(__linux__)
		char *timeString = ctime(&rawtime);
	#endif
		logHeader.push_back( String("On: ") + timeString );
		WriteLinesToFile( _fileName, logHeader );
}

void FileLog::Log( const String& val)
{
	AppendLineToFile( _fileName, val );
}


void SystemLog::Log( const String &val)
{
	#if defined(_MSC_VER)
		//convert string to wstring
		String prepped = val + "\n";
		int len;
		int slength = (int)prepped.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, prepped.c_str(), slength, 0, 0); 
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, prepped.c_str(), slength, buf, len);
		std::wstring wval(buf);
		delete[] buf;
	
		//output to pane
		OutputDebugString(wval.c_str());
	#else
		std::cout << val << std::endl;
	#endif
}
