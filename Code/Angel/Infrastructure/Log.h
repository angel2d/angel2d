#pragma once

#include "../Util/StringUtil.h"
#include "../Infrastructure/Console.h"
#include "../Infrastructure/World.h"

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
	 *  be cleared. 
	 * 
	 * @param fileName 
	 */
	FileLog( const String& fileName );

	/**
	 * The string to be logged in the file. Will append a timestamp to the
	 *  start of each line. 
	 * 
	 * @param val The string to put in the file
	 */
	virtual void Log( const String& val);

private:
	String _fileName;
};

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

private:
	std::vector<DeveloperLog*> _logs;
};