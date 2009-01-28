#include "../Scripting/PythonModule.h"

#include "../Infrastructure/Common.h"
#include "../Util/StringUtil.h"

#if defined(__APPLE__)
	#include <Python/Python.h>
#else
	#include <Python.h>
#endif

extern "C" 
{
	void init_angel(void);
}

bool PythonScriptingModule::isInitialized = false;

void PythonScriptingModule::Initialize()
{
	#if defined(WIN32)
		//We set paths to use our local Python distribution.
		// If you want to use a version of Python that's installed
		// on your machine, you'll want to comment this out. 
		// (You'll also want to kill the build steps that copy over
		// the Python DLLs.)
		_putenv( "PYTHONPATH=pylib;..\\Tools\\Python25\\Lib");

		//Note on the Mac we just use the built-in system Python
		// by linking against Python.framework. 
	#endif


	Py_Initialize();
	
	init_angel();

	FILE* startFile;
	char* startFileName = "./Resources/Scripts/start.py";

	startFile = fopen(startFileName, "r");
	if (startFile != NULL)
	{
		PyObject* PyFileObject = PyFile_FromString(startFileName, "r");
		PyRun_SimpleFile(PyFile_AsFile(PyFileObject), startFileName);
		isInitialized = true;
		std::cout << "Python initialized." << std::endl;
	}
	else
	{
		Py_Finalize();
		isInitialized = false;
		std::cout << "Error initializing Python: couldn't find startup file." << std::endl;
	}
	fclose(startFile);
}

void PythonScriptingModule::Finalize()
{
	if (!isInitialized)
	{
		return;
	}
	Py_Finalize();
}

void PythonScriptingModule::ExecuteInScript(String code)
{
	if (!isInitialized)
	{
		return;
	}
	PyRun_SimpleString(code.c_str());
}