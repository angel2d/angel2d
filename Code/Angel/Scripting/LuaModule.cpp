//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
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
#include "../Scripting/LuaModule.h"

#include "../Infrastructure/Common.h"
#include "../Messaging/Switchboard.h"
#include "../Util/StringUtil.h"
#include "../Infrastructure/Log.h"
#include "../Infrastructure/World.h"
#if !ANGEL_MOBILE
	#include "../Scripting/LuaConsole.h"
	#include "../Util/FileUtil.h"
#endif

extern "C"
{	
	int luaopen_angel(lua_State* L);
}

bool LuaScriptingModule::isInitialized = false;
lua_State* LuaScriptingModule::L = NULL;
ConfigUpdater* LuaScriptingModule::_configUpdater = NULL;

void LuaScriptingModule::Prep()
{
	L = luaL_newstate();
	
	lua_gc(L, LUA_GCSTOP, 0);
	luaL_openlibs(L);
	luaopen_angel(L);
	lua_gc(L, LUA_GCRESTART, 0);
	
	// need to manually clean up the stack since SWIG is acting funny with Lua 5.1 now.
	while (lua_gettop(L) > 0)
	{
		lua_pop(L, 1);
	}
	
	#if !ANGEL_MOBILE
		lua_pushboolean(L, 0);
		lua_setglobal(L, "ANGEL_MOBILE");
	#else
		lua_pushboolean(L, 1);
		lua_setglobal(L, "ANGEL_MOBILE");
	#endif
	
	luaL_dofile(L, "./Resources/Scripts/pref_load.lua");
}

void LuaScriptingModule::Initialize()
{
	#if !ANGEL_MOBILE
		LuaConsole *lc = new LuaConsole();
		theWorld.RegisterConsole(lc);
	#endif
	
	int result = luaL_dofile(L, "./Resources/Scripts/start.lua");
		
	isInitialized = !result;
	if (isInitialized)
	{
		sysLog.Log("Lua initialized!");
	}
	else 
	{
		sysLog.Log(lua_tostring(L, -1));
	}
	
	_configUpdater = new ConfigUpdater();
}

void LuaScriptingModule::Finalize()
{
	if (!isInitialized)
	{
		return;
	}
	
	lua_close(L);
}

void LuaScriptingModule::ExecuteInScript(const String& code)
{
	if (!isInitialized)
	{
		return;
	}
		
	if (luaL_loadstring(L, code.c_str()))
	{
		String error(lua_tostring(L, -1));
		lua_pop(L, 1);
		
		if (error.substr(error.length()-6, 5) != "<eof>")
		{
			#if !ANGEL_MOBILE
				theWorld.GetConsole()->WriteToOutput("ERROR: " + error + "\n");
			#endif
		}
		else
		{
			// partial input -- do we want to handle this?
		}
		return;
	}
	else
	{
		if (lua_pcall(L, 0, LUA_MULTRET, 0 ))
		{
			const char* errs = lua_tostring(L, -1);
			sysLog.Printf("ERROR: %s\n", errs);
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
	
	lua_settop(L, 0);
}

lua_State* LuaScriptingModule::GetLuaState()
{
	return L;
}

void LuaScriptingModule::DumpStack()
{
	int top = lua_gettop(L);

	sysLog.Printf("Total in stack: %d\n", top);

	for (int i=1; i <= top; i++)
	{
		int t = lua_type(L, i);
		switch (t) {
			case LUA_TSTRING:
				printf("string: '%s'\n", lua_tostring(L, i));
				break;
			case LUA_TBOOLEAN:
				printf("boolean %s\n",lua_toboolean(L, i) ? "true" : "false");
				break;
			case LUA_TNUMBER:
				printf("number: %g\n", lua_tonumber(L, i));
				break;
			default:
				printf("%s\n", lua_typename(L, t));
				break;
		}
		printf("  ");
	}
	printf("\n");
}

#define TUNING_FILE_CHECK_DELAY 	1.0f
#define TUNING_MESSAGE_NAME 		"TuningCheckTick"


ConfigUpdater::ConfigUpdater()
{
	Reload();
	
	#if !defined(ANGEL_MOBILE)
		_updateTime = GetModificationTime("Config/tuning.lua");
		theSwitchboard.SubscribeTo(this, TUNING_MESSAGE_NAME);
		theSwitchboard.DeferredBroadcast(new Message(TUNING_MESSAGE_NAME), TUNING_FILE_CHECK_DELAY);
	#endif
}

void ConfigUpdater::Reload()
{
	lua_State* L = LuaScriptingModule::GetLuaState();
	lua_getglobal(L, "LoadTuningVariables");
	if (lua_pcall(L, 0, 0, 0))
	{
		const char* errs = lua_tostring(L, -1);
		sysLog.Printf("ERROR: %s\n", errs);
		// error, will be in the stack trace
		lua_gc(L, LUA_GCCOLLECT, 0); // garbage collect on error
	}
}

void ConfigUpdater::ReceiveMessage(Message *message)
{
	#if !defined(ANGEL_MOBILE)
		if (message->GetMessageName() == TUNING_MESSAGE_NAME)
		{
			long modTime = GetModificationTime("Config/tuning.lua");
			if (_updateTime < modTime)
			{
				Reload();
				_updateTime = modTime;
			}
			theSwitchboard.DeferredBroadcast(new Message(TUNING_MESSAGE_NAME), TUNING_FILE_CHECK_DELAY);
		}
	#endif
}
