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
#include "../Scripting/LuaConsole.h"

#include "../Infrastructure/World.h"
#include "../Scripting/LuaModule.h"

LuaConsole::LuaConsole()
{
	String motd = String(LUA_COPYRIGHT) + "\n\n";
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


StringList LuaConsole::GetCompletions(const String& input)
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
		int size = lua_rawlen(L, -1);
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
