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
