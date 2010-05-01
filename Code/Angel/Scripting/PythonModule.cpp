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

#include "../Scripting/PythonModule.h"

#include "../Infrastructure/Common.h"
#include "../Util/StringUtil.h"
#include "../Infrastructure/Log.h"

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
	//We set paths to use our local Python distribution.
	#if defined(WIN32)
		_putenv("PYTHONPATH=python26.zip;..\\Tools\\Python26\\Lib");
	#elif defined(__APPLE__)
		putenv("PYTHONPATH=Frameworks/Python.framework/Versions/Current/lib/python26.zip:/usr/lib/python2.6");
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
		sysLog.Log("Python initialized.");
		fclose(startFile);
	}
	else
	{
		Py_Finalize();
		isInitialized = false;
		sysLog.Log("Error initializing Python: couldn't find startup file.");
	}
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
