#pragma once

#include "../Util/StringUtil.h"
#include "../Infrastructure/ValueCache.h"
#include "../Infrastructure/Log.h"
#include "../Infrastructure/Vector2.h"



class Console
{
public:
	Console();
	virtual ~Console();

	void Render();
	void Update( float /*dt*/ ) {}

	void Enable( bool bEnable = true );
	bool IsEnabled() {return _enabled;}

	bool GetInput(int key);
	bool GetSpecialInputDown( int key );
	void Console::ToggleConsole( const String& input );
	unsigned char GetToggleConsoleKey()	{return '`';}

	void WriteToOutput(String output);
	void SetPrompt(String prompt);
	void AdvanceInputHistory( int byVal );
	void AcceptAutocomplete();

	//For the script function to override
	virtual void Execute(String input) = 0;
	virtual StringList GetCompletions(String input) = 0;

private:
	bool Console::IsTextKey(unsigned char key);
	void AcceptCurrentInput();
	String _currentInput;
	StringList _inputHistory;
	int _inputHistoryPos;
	String _prompt;
	StringList _buffer;
	String _unsplitBuffer;
	float _lineHeight;
	StringList _autoCompleteList;

	bool _enabled;
};


class TestConsole : public Console
{
public:
	TestConsole()
	{
		SetPrompt("::>");
	}

	virtual void Execute(String input) { WriteToOutput("Test Console Echo: " + input); }
	virtual StringList GetCompletions(String input) { return StringList(); }
};