#pragma once

#include "../Util/StringUtil.h"


/*abstract*/ class DeveloperLog
{
public:
	virtual ~DeveloperLog() {}

	virtual void Log( const String& val ) = 0;
};


class CompoundLog : public DeveloperLog
{
	typedef std::vector<DeveloperLog*> LogList;
public:
	void AddLog( DeveloperLog* addLog );
	virtual void Log( const String& val );

private:
	LogList _logs;
};

class ConsoleLog : public DeveloperLog
{
public:
	virtual void Log( const String& val);
	const String& GetLogLine( int lineIndex );
	int NumLogLines();
private:
	StringList _logLines;
};

class FileLog : public DeveloperLog
{
public:
	static String MakeLogFileName( const String& fileName );
	FileLog( const String& fileName );

	virtual void Log( const String& val);

private:
	String _fileName;
};


