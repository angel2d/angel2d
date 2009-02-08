#include "../Input/InputManager.h"

#include "../Input/Controller.h"
#include "../Messaging/Switchboard.h"
#include "../Util/StringUtil.h"
#include "../Util/FileUtil.h"

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
	std::cout << "BUTTON: " << input << std::endl;
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

void InputManager::BindKeyCommand( const String& input )
{
	if( input.length() == 0 )
		return;

	StringList bindInput = SplitString( input );
	if( bindInput.size() < 2 )
		return;

	String car, cdr;
	GetCarCdr( bindInput, car, cdr );

	BindKey( car, cdr );
}

void InputManager::UnbindKeyCommand( const String& input )
{
	if( input.length() == 0 )
		return;

	StringList bindInput = SplitString( input );

	UnbindKey( bindInput[0] );
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
	InputBinding* pBinding = GetBinding( keyVal );
	if( pBinding == NULL )
		return false;

	pBinding->OnKeyDown();

	return true;
}

bool InputManager::OnKeyUp( int keyVal )
{
	InputBinding* pBinding = GetBinding( keyVal );
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
		std::cout << "Bad controller ID." << std::endl;
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
