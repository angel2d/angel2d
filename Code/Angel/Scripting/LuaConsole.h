#pragma once

#include "../Infrastructure/Console.h"


class LuaConsole : public Console
{
public:
	LuaConsole();

	virtual void Execute(String input);
	virtual StringList GetCompletions(String input);
	
private:
	String _mainPrompt;
	String _secondaryPrompt;
	
	bool _firstLine;
	String _partialInput;
};


void LuaWrite(String output);