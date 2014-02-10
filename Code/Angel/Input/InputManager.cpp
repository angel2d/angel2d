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
#include "../Input/InputManager.h"

#include "../Infrastructure/World.h"
#include "../Input/Controller.h"
#include "../Messaging/Switchboard.h"
#include "../Util/StringUtil.h"
#include "../Util/FileUtil.h"
#include "../Infrastructure/Log.h"

void InputBinding::SetKeyDownMessage( const String& keyDownMessage )
{
	_keyDownMessage = keyDownMessage;
}

void InputBinding::SetKeyUpMessage( const String& keyUpMessage )
{
	_keyUpMessage = keyUpMessage;
}


void InputBinding::OnKeyDown()
{
	if( _keyDownMessage.length() == 0 )
		return;
	
	theSwitchboard.Broadcast(new Message(_keyDownMessage));
}

void InputBinding::OnKeyUp()
{
	if( _keyUpMessage.length() == 0 )
		return;

	theSwitchboard.Broadcast(new Message(_keyUpMessage));
}

InputManager* InputManager::s_Input = NULL;

InputManager &InputManager::GetInstance()
{
	if( s_Input == NULL )
	{
		s_Input = new InputManager();
		s_Input->Initialize();
	}
	return *s_Input;
}

void InputManager::Destroy()
{
	if( s_Input != NULL )
	{
		delete s_Input;
		s_Input = NULL;
	}
}

void TestBinding( const String& input )
{
	sysLog.Log("BUTTON: " + input);
}

void InputManager::Initialize()
{
#define USEINPUTKEY(e,hashVal,text) \
	_keyNameTable[ToUpper(text)] = e;
#include "InputKeys.h"
#undef USEINPUTKEY

	//Clear Xbox Button States
	ClearXboxButtonStates();
	
	StringList bindings;
	GetLinesFromFile("Config/input_bindings.ini", bindings);
	StringList::iterator it = bindings.begin();
	while (it != bindings.end())
	{
		if (((*it).size() == 0) || ((*it)[0] == ';'))
		{
			it++;
			continue;
		}
		StringList splitBinding = SplitString(*it, "=:", false);
		if (splitBinding.size() >= 2)
		{
			splitBinding[0] = TrimString(splitBinding[0]);
			splitBinding[1] = TrimString(splitBinding[1]);
			BindKey(splitBinding[0], splitBinding[1]);
		}
		it++;
	}
}

InputManager::~InputManager()
{
	for( BindingTable::iterator itr = _bindingTable.begin(); itr != _bindingTable.end(); itr++ )
	{
		delete (*itr).second;
	}

	_bindingTable.clear();
}

void InputManager::BindKey( const String& keyId, const String& command )
{
	if( command.length() == 0 )
		return;

	int hashVal = GetHashFromKeyName( keyId );

	InputBinding* pBinding = GetBinding(hashVal);
	if( pBinding == NULL )
	{
		pBinding = new InputBinding();
		_bindingTable[hashVal] = pBinding;
	}

	String setCommand = command;
	if( setCommand[0] == '-' )
	{
		setCommand.erase(0,1);
		pBinding->SetKeyUpMessage( setCommand );
	}
	else
	{
		if( setCommand[0] == '+' )
			setCommand.erase(0,1);

		pBinding->SetKeyDownMessage( setCommand );
	}

}

void InputManager::UnbindKey( const String& keyId )
{
	int hashVal = GetHashFromKeyName( keyId );

	InputBinding* pBinding = GetBinding(hashVal);
	if( pBinding == NULL )
		return;

	delete pBinding;
	_bindingTable.erase( hashVal );
}

bool InputManager::OnKeyDown( int keyVal )
{
	InputBinding* pBinding = GetBinding( tolower(keyVal) );
	if( pBinding == NULL )
		return false;

	pBinding->OnKeyDown();

	return true;
}

bool InputManager::OnKeyUp( int keyVal )
{
	InputBinding* pBinding = GetBinding( tolower(keyVal) );
	if( pBinding == NULL )
		return false;

	pBinding->OnKeyUp();

	return true;
}

struct XboxButtonBindRecord
{
	int HashKey;
	const bool (Controller::*CheckFunc)();
};

XboxButtonBindRecord sBindRecordsOne[] =
{
	{ P1BUTTON_A, &Controller::IsAButtonDown },
	{ P1BUTTON_B, &Controller::IsBButtonDown },
	{ P1BUTTON_X, &Controller::IsXButtonDown },
	{ P1BUTTON_Y, &Controller::IsYButtonDown },

	{ P1BUTTON_START, &Controller::IsStartButtonDown },
	{ P1BUTTON_BACK, &Controller::IsBackButtonDown },

	{ P1BUTTON_LEFTTHUMB, &Controller::IsLeftThumbstickButtonDown },
	{ P1BUTTON_RIGHTTHUMB, &Controller::IsRightThumbstickButtonDown },

	{ P1BUTTON_LEFTTRIGGER, &Controller::IsLeftTriggerPressed },
	{ P1BUTTON_RIGHTTRIGGER, &Controller::IsRightTriggerPressed },

	{ P1BUTTON_LEFTBUMPER, &Controller::IsLeftBumperDown },
	{ P1BUTTON_RIGHTBUMPER, &Controller::IsRightBumperDown },
};

XboxButtonBindRecord sBindRecordsTwo[] =
{
	{ P2BUTTON_A, &Controller::IsAButtonDown },
	{ P2BUTTON_B, &Controller::IsBButtonDown },
	{ P2BUTTON_X, &Controller::IsXButtonDown },
	{ P2BUTTON_Y, &Controller::IsYButtonDown },

	{ P2BUTTON_START, &Controller::IsStartButtonDown },
	{ P2BUTTON_BACK, &Controller::IsBackButtonDown },

	{ P2BUTTON_LEFTTHUMB, &Controller::IsLeftThumbstickButtonDown },
	{ P2BUTTON_RIGHTTHUMB, &Controller::IsRightThumbstickButtonDown },

	{ P2BUTTON_LEFTTRIGGER, &Controller::IsLeftTriggerPressed },
	{ P2BUTTON_RIGHTTRIGGER, &Controller::IsRightTriggerPressed },

	{ P2BUTTON_LEFTBUMPER, &Controller::IsLeftBumperDown },
	{ P2BUTTON_RIGHTBUMPER, &Controller::IsRightBumperDown },
};

void InputManager::HandleControl( Controller& controller )
{
	//TODO: make this so it's not just cut-and-pasted code iterating over two enums

	if (controller.GetControllerID() == 0)
	{
		int numXboxButtons = sizeof( sBindRecordsOne ) / sizeof(sBindRecordsOne[0] );
		for( int i = 0; i < numXboxButtons; i++ )
		{
			XboxButtonBindRecord& rec = sBindRecordsOne[i];
			
			//Is button currently down
			bool bIsDown = (controller.*rec.CheckFunc)();
			bool bWasDown = _xBoxButtonStates[controller.GetControllerID()][rec.HashKey];
			
			//Update key value
			_xBoxButtonStates[controller.GetControllerID()][rec.HashKey] = bIsDown;
			
			InputBinding* pBinding = GetBinding( rec.HashKey );
			if( pBinding == NULL )
				continue;
			
			if( !bWasDown && bIsDown )
			{
				//BUTTON DOWN
				pBinding->OnKeyDown();
			}
			else if( bWasDown && !bIsDown )
			{
				//BUTTON UP
				pBinding->OnKeyUp();
			}
		}
	}
	else if (controller.GetControllerID() == 1)
	{
		int numXboxButtons = sizeof( sBindRecordsTwo ) / sizeof(sBindRecordsTwo[0] );
		for( int i = 0; i < numXboxButtons; i++ )
		{
			XboxButtonBindRecord& rec = sBindRecordsTwo[i];
			
			//Is button currently down
			bool bIsDown = (controller.*rec.CheckFunc)();
			bool bWasDown = _xBoxButtonStates[controller.GetControllerID()][rec.HashKey];
			
			//Update key value
			_xBoxButtonStates[controller.GetControllerID()][rec.HashKey] = bIsDown;
			
			InputBinding* pBinding = GetBinding( rec.HashKey );
			if( pBinding == NULL )
				continue;
			
			if( !bWasDown && bIsDown )
			{
				//BUTTON DOWN
				pBinding->OnKeyDown();
			}
			else if( bWasDown && !bIsDown )
			{
				//BUTTON UP
				pBinding->OnKeyUp();
			}
		}
	}
	else
	{
		sysLog.Log("Bad controller ID.");
		return;
	}

}

void InputManager::ClearXboxButtonStates()
{
	int numXboxButtons = sizeof( sBindRecordsOne ) / sizeof(sBindRecordsOne[0] );
	for( int i = 0; i < numXboxButtons; i++ )
	{
		XboxButtonBindRecord& rec = sBindRecordsOne[i];
		_xBoxButtonStates[0][rec.HashKey] = false;	
	}
	
	numXboxButtons = sizeof( sBindRecordsTwo ) / sizeof(sBindRecordsTwo[0] );
	for( int i = 0; i < numXboxButtons; i++ )
	{
		XboxButtonBindRecord& rec = sBindRecordsTwo[i];
		_xBoxButtonStates[1][rec.HashKey] = false;	
	}
}

bool InputManager::IsKeyDown(int keyVal)
{
	if (glfwGetKey(theWorld.GetMainWindow(), toupper(keyVal)) == GLFW_PRESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

InputBinding* InputManager::GetBinding( int hashVal )
{
	//Find existing binding
	BindingTable::iterator itr = _bindingTable.find(hashVal);
	if( itr == _bindingTable.end() )
		return NULL;

	return (*itr).second;
}

int InputManager::GetHashFromKeyName( const String& keyId )
{
	//Find key ID
	KeyNameTable::iterator itr = _keyNameTable.find(ToUpper(keyId));
	if( itr == _keyNameTable.end() )
		return -1;

	return (*itr).second;

}
