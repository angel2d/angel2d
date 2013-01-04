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

#pragma once

#include "../Util/StringUtil.h"
#include "../Input/Controller.h"

///(Internal) Handles the binding of keypresses to Messages
/** 
 * An internal class used by the InputManager, mapping keydown and keyup 
 *  events to the appropriate Messages. 
 */
class InputBinding
{
public:

	void SetKeyDownMessage( const String& keyDownMessage );
	void SetKeyUpMessage( const String& keyUpMessage );

	void OnKeyDown();
	void OnKeyUp();

private:
	String _keyDownMessage;
	String _keyUpMessage;
};

enum InputKeys
{
#define USEINPUTKEY(e,hashVal,text) \
	e=hashVal,
#include "InputKeys.h"
#undef USEINPUTKEY
};

#define theInput InputManager::GetInstance()

///(Internal) Handles keyboard input, and mapping controller input to messages
/** 
 * This internal class is used by the engine to take the settings from 
 *  input_bindings.ini and process all keyboard and controller data. 
 * 
 * Unless you're working on the engine itself, the only function in here that
 *  matters to you would be InputManager::IsKeyDown. 
 */
class InputManager
{
	typedef hashmap_ns::hash_map<int, InputBinding*>		BindingTable;
	typedef hashmap_ns::hash_map<String, int>				KeyNameTable;
	typedef hashmap_ns::hash_map<int, bool>					XboxButtonState;

public:
	static InputManager &GetInstance();
	static void Destroy();

	void BindKey( const String& keyId, const String& command );
	void UnbindKey( const String& keyId );

	bool OnKeyDown( int keyVal );
	bool OnKeyUp( int keyVal );
	
	/**
	 * Find out whether a key is currently pressed. Can either be passed an
	 *  individual char or any of the defined values in GL/glfw.h.
	 * 
	 * @param keyVal The key value to test for (usually a char)
	 * @return Whether the user is currently pressing that key. 
	 */
	bool IsKeyDown(int keyVal);

	void HandleControl( class Controller& controller );

protected:
	InputManager() {}
	~InputManager();
	void Initialize();

private:
	InputBinding* GetBinding( int hashVal );
	int GetHashFromKeyName( const String& keyId );
	void ClearXboxButtonStates();

private:
	static InputManager* s_Input;

	KeyNameTable		_keyNameTable;
	BindingTable		_bindingTable;
	XboxButtonState		_xBoxButtonStates[MAX_CONTROLLERS];
};