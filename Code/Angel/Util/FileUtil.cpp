#include "../Util/FileUtil.h"

#include "../Infrastructure/Common.h"

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