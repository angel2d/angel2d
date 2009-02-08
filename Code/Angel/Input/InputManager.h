#pragma once

#include "../Infrastructure/Common.h"
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
 * Unless you're working on the engine itself, there's really no reason for
 *  you to worry about this class. 
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

	void HandleControl( class Controller& controller );

protected:
	InputManager() {}
	~InputManager();
	void Initialize();

private:
	InputBinding* GetBinding( int hashVal );
	int GetHashFromKeyName( const String& keyId );
	void BindKeyCommand( const String& input );
	void UnbindKeyCommand( const String& input );
	void ClearXboxButtonStates();

private:
	static InputManager* s_Input;

	KeyNameTable		_keyNameTable;
	BindingTable		_bindingTable;
	XboxButtonState		_xBoxButtonStates[MAX_CONTROLLERS];
};