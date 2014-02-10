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
#include "../Util/FileUtil.h"

#include "../Infrastructure/Common.h"
#include "../Infrastructure/Log.h"
#include "../Util/StringUtil.h"

#if defined(WIN32)
	#include <shlobj.h>
#elif defined(__linux__)
	#include <linux/limits.h>
	#include <unistd.h>
#endif
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>


using namespace std;

bool GetLinesFromFile(const String& fileName, StringList& outList )
{
	ifstream inputFile( fileName.c_str() );
	if( inputFile.is_open() )
	{
		while (! inputFile.eof() )
		{
			String line;
			getline (inputFile,line);
			outList.push_back( line );
		}
		inputFile.close();
		return true;
	}

	return false;
}

const String ReadWholeFile(const String& fileName)
{
	String forReturn = "";
	StringList lines;
	GetLinesFromFile(fileName, lines);
	for (int i=0; i < lines.size(); i++)
	{
		forReturn += lines[i];
	}
	return forReturn;
}

bool WriteLinesToFile( const String& fileName, const StringList& strings )
{
	ofstream outputFile( fileName.c_str(), ios_base::trunc );
	if( outputFile.is_open() )
	{
		for( unsigned int i = 0; i < strings.size(); i++ )
		{
			outputFile << strings[i] << endl;
		}
		outputFile.close();
		return true;
	}
	return false;
}

bool AppendLineToFile( const String& fileName, const String& line )
{
	ofstream outputFile( fileName.c_str(), ios_base::app );
	if( outputFile.is_open() )
	{
		outputFile << line << endl;
		outputFile.close();
		return true;
	}
	return false;
}

bool MakeDirectories( const String& path )
{
	#if defined(WIN32)
		if (SHCreateDirectoryExA(NULL, path.c_str(), NULL) == ERROR_SUCCESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	#else
		char currentDir[PATH_MAX];
		getcwd(currentDir, PATH_MAX);
		chdir("/");
		bool retVal = true;
	
		StringList elements = SplitString(path, "/");
		struct stat statInfo;
		StringList::iterator it = elements.begin();
		String pathAccum;
		while (it != elements.end())
		{
			pathAccum += *it;
			if (stat(pathAccum.c_str(), &statInfo) < 0)
			{
				//path doesn't exist
				if (mkdir(pathAccum.c_str(), S_IRWXU) != 0)
				{
					//couldn't be made
					retVal = false;
					break;
				}
			}
			if (!S_ISDIR(statInfo.st_mode))
			{
				//exists, but it's not a directory
				retVal = false;
				break;
			}
		
			pathAccum += "/";
			it++;
		}
	
		chdir(currentDir);
		return retVal;
	#endif
}

const String GetStorageDirectory()
{
	#if defined(WIN32)
		return "./";
	#elif defined(__APPLE__)
		#if !ANGEL_MOBILE
			String writeDirectory = getenv("HOME");
			writeDirectory += "/Library/Application Support/Angel Games/" + GetExeName() + "/";
			return writeDirectory;
		#else
			NSArray* arrayPaths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
			NSString* docPath = [arrayPaths objectAtIndex:0];
			String writeDirectory = [docPath UTF8String];
			writeDirectory += "/" + GetExeName() + "/";
			return writeDirectory;
		#endif
	#elif defined(__linux__)
		String writeDirectory = getenv("HOME");
		writeDirectory += "/.angel/" + GetExeName() + "/";
		return writeDirectory;
	#endif
}

const String GetDocumentsPath()
{
	#if defined(WIN32)
		char myDocs[MAX_PATH];
		HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, myDocs);
		if (result != S_OK)
		{
			sysLog.Log("ERROR: Couldn't get path to \"My Documents\" directory.");
			return String("");
		}
		else
		{
			return String(myDocs);
		}
	#elif defined(__APPLE__)
		String path = getenv("HOME");
		return path + "/Documents/";
	#elif defined(__linux__)
		String path = getenv("HOME");
		return path + "/Documents/";
	#endif
}

const String GetExeName() 
{
	String pathSplit = "/";
	#if defined (WIN32)
		TCHAR exePathWin[MAX_PATH];
		GetModuleFileName( NULL, exePathWin, MAX_PATH );
		String exePath(exePathWin);
		int length = exePath.length();
		if (exePath.substr(length - 4, length) == ".exe")
		{
			exePath = exePath.substr(0, length - 4);
		}
		pathSplit = "\\";
	#elif defined (__APPLE__)
		CFBundleRef mainBundle = CFBundleGetMainBundle();
		CFURLRef exeURL = CFBundleCopyExecutableURL(mainBundle);
		char exePath[PATH_MAX];
		if (!CFURLGetFileSystemRepresentation(exeURL, TRUE, (UInt8 *)exePath, PATH_MAX))
		{
			CFRelease(exeURL);
			sysLog.Log("Couldn't get exe name.");
			return "";
		}
		CFRelease(exeURL);
	#elif defined (__linux__)
		String exePath = ReadWholeFile("/proc/self/cmdline");
		String splitChars = "";
		splitChars.push_back('\0'); // have to construct null-containing strings carefully
		exePath = SplitString(exePath, splitChars)[0];
	#endif
	
	StringList pathElements = SplitString(exePath, pathSplit);
	String exeName = pathElements[pathElements.size()-1];

	return exeName;
}

const long GetModificationTime(const String& fileName)
{
	struct stat statInfo;
	if (stat(fileName.c_str(), &statInfo) != -1)
	{
		#if defined(__APPLE__)
			return statInfo.st_mtimespec.tv_sec;
		#else //Linux or Windows
			return statInfo.st_mtime;
		#endif
	}
	else 
	{
		return 0;
	}
}
