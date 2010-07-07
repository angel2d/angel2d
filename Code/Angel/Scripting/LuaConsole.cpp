#include "stdafx.h"
#include "../Scripting/LuaConsole.h"

#include "../Scripting/LuaModule.h"

LuaConsole::LuaConsole()
{
	String motd = String(LUA_RELEASE) + " " + String(LUA_COPYRIGHT) + "\n\n";
	motd += "This console is almost the same as the interactive Lua interpreter. Just make sure not\n";
	motd += "to run any code that blocks on console input, or the whole engine will hang.\n\n";
	WriteToOutput(motd);
	
	_mainPrompt = "> ";
	_secondaryPrompt = ">> ";
	_partialInput.clear();
	_firstLine = true;
	_tabWidth = 16; //makes most Lua tables a bit easier to read when they're printed
	SetPrompt(_mainPrompt);
}


void LuaConsole::Execute(String input)
{
	lua_State *L = LuaScriptingModule::GetLuaState();
	
	WriteToOutput(_prompt + input + "\n");
	
	if (_firstLine && input.substr(0,1) == "=")
	{
		input = "return tostring(" + input.substr(1, input.length()-1) + ")";
	}
	
	_partialInput += " " + input;
	_firstLine = false;
	
	if (luaL_loadstring(L, _partialInput.c_str()))
	{
		String error(lua_tostring(L, -1));
		lua_pop(L, 1);
		
		// this may seem hacky, but it's exactly the same way the official
		//  interpreter does it!
		if (error.substr(error.length()-6, 5) != "<eof>")
		{
			_partialInput.clear();
			_firstLine = true;
			WriteToOutput("ERROR: " + error + "\n");
			SetPrompt(_mainPrompt);
		}
		else
		{
			SetPrompt(_secondaryPrompt); 
		}
		return;
	}
	else
	{
		if (lua_pcall(L, 0, LUA_MULTRET, 0 ) )
		{
			// error, will be in the stack trace
			lua_gc(L, LUA_GCCOLLECT, 0); // garbage collect on error
		}
	}
	
	// print out any return values left on the stack
	if (lua_gettop(L) > 0)
	{
		lua_getglobal(L, "print");
		lua_insert(L, 1);
		lua_pcall(L, lua_gettop(L)-1, 0, 0);
	}
	
	_partialInput.clear();
	_firstLine = true;
	SetPrompt(_mainPrompt);
	
	lua_settop(L, 0);
}


StringList LuaConsole::GetCompletions(String input)
{
	StringList forReturn;
	
	lua_State *L = LuaScriptingModule::GetLuaState();
	lua_getglobal(L, "getAutoCompletions");
	lua_pushstring(L, input.c_str());
	if (lua_pcall(L, 1, 1, 0) != 0)
	{
		String out = "ERROR: running autocompletions: ";
		out += lua_tostring(L, -1);
		out += "\n";
		WriteToOutput(out);
	}
	if (lua_istable(L, -1))
	{
		// get table values
		int size = lua_objlen(L, -1);
		for (int i=0; i < size; i++)
		{
			lua_pushinteger(L, i+1);
			lua_gettable(L, -2);
			forReturn.push_back(lua_tostring(L, -1));
			lua_pop(L, 1);
		}
	}

	
	//pop it
	lua_pop(L, 1);
	
	return forReturn;
}

void LuaWrite(String output)
{
	LuaConsole* lc = (LuaConsole*)theWorld.GetConsole();
	lc->WriteToOutput(output + "\n");
}
