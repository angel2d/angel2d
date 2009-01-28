#pragma once

#include "../Util/StringUtil.h"

class PythonScriptingModule
{
public:
	static void Initialize();
	static void Finalize();
	
	static void ExecuteInScript(String code);

private:
	static bool isInitialized;
};
