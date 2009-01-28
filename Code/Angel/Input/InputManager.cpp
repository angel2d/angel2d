#include "../Input/InputManager.h"

#include "../Input/Controller.h"
#include "../Infrastructure/DeveloperConsole.h"
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

	CONSOLE_DECLARECMDMETHOD( Bind, this, InputManager, BindKeyCommand );
	CONSOLE_DECLARECMDMETHOD( UnBind, this, InputManager, UnbindKeyCommand );

	CONSOLE_DECLARECMDSTATIC( TestBinding, TestBinding );

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

XboxButtonBindRecord sBindRecords[] =
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

void InputManager::HandleControl( Controller& controller )
{
	//Ignore XBOX input when the console is live if you want
	CONSOLE_DECLAREVAR(in_disableControllerWithConsoleDown);
	if( in_disableControllerWithConsoleDown->GetIntVal() == 1 && theDevConsole.IsEnabled() )
		return;

	int numXboxButtons = sizeof( sBindRecords ) / sizeof(sBindRecords[0] );

	for( int i = 0; i < numXboxButtons; i++ )
	{
		XboxButtonBindRecord& rec = sBindRecords[i];

		//Is button currently down
		bool bIsDown = (controller.*rec.CheckFunc)();
		bool bWasDown = _xBoxButtonStates[rec.HashKey];

		//Update key value
		_xBoxButtonStates[rec.HashKey] = bIsDown;

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

void InputManager::ClearXboxButtonStates()
{
	int numXboxButtons = sizeof( sBindRecords ) / sizeof(sBindRecords[0] );

	for( int i = 0; i < numXboxButtons; i++ )
	{
		XboxButtonBindRecord& rec = sBindRecords[i];
		_xBoxButtonStates[rec.HashKey] = false;
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
