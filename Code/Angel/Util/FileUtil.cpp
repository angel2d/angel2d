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

#include "../Util/FileUtil.h"

#include "../Infrastructure/Common.h"
#include "../Util/StringUtil.h"
#if defined(WIN32)
	#include <shlobj.h>
#elif defined(__APPLE__)
	#include <sys/stat.h>
#elif defined(__linux__)
	#include <sys/stat.h>
	#include <linux/limits.h>
#endif
#include <fstream>

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

bool WriteLinesToFile( const String& fileName, const StringList& strings )
{
	ofstream outputFile( fileName.c_str());
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
