%module(directors="1") angel
%{
#include "../../Infrastructure/Log.h"
%}

class DeveloperLog
{
public:
	virtual ~DeveloperLog() {}
	virtual void Log( const String& val ) = 0;
	void Printf(const char* format, ...);
};

class ConsoleLog : public DeveloperLog
{
public:
	virtual void Log( const String& val);
};

class FileLog : public DeveloperLog
{
public:
	static String MakeLogFileName( const String& fileName );
	FileLog( const String& fileName );
	virtual void Log( const String& val);
};

class SystemLog : public DeveloperLog
{
public:
	virtual void Log( const String& val);
};

class CompoundLog : public DeveloperLog
{
public:
	void AddLog( DeveloperLog* addLog );
	virtual void Log( const String& val );
	static CompoundLog& GetSystemLog();
};
