#pragma once

#include "../Infrastructure/Console.h"

///Console to process Lua input during the game
/**
 * An implementation of the Console class that runs input strings 
 *  of Lua code, and prints output from the Lua runtime. 
 */
class LuaConsole : public Console
{
public:
    /**
     * Basic constructor; sets up our prompts and prints the welcome
     *  message.
     */
	LuaConsole();

    /**
     * Attempts to execute the given string as Lua. Any errors will 
     *  be output the console.
     * 
     * @param input the string to execute
     */
	virtual void Execute(String input);
    
    /**
     * Gets potential autocompletions from the Lua runtime given
     *  a starting string. 
     * 
     * @param input the beginning of the string to try to complete
     * @return a list of potential matches
     */
	virtual StringList GetCompletions(const String& input);
	
private:
	String _mainPrompt;
	String _secondaryPrompt;
	
	bool _firstLine;
	String _partialInput;
};


void LuaWrite(String output);