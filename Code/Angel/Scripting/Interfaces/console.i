#ifdef SWIGPYTHON
%module(directors="1") angel
%{
#include "../../Infrastructure/Console.h"
%}

%feature("director") Console;
class Console
{
public:
	virtual ~Console();

	void WriteToOutput(String output);
	void SetPrompt(String prompt);
	
	virtual void Execute(String input) = 0;
	virtual StringList GetCompletions(String input) = 0;
};
#endif

#ifdef SWIGLUA
%module angel
%{
#include "../../Scripting/LuaConsole.h"
%}

void LuaWrite(String output);

#endif