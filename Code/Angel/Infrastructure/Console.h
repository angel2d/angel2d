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
#include "../Infrastructure/Vector2.h"


///The on-screen console: handles input, history, and executing commands
/** 
 * This abstract base class contains everything you need to create your own
 *  console that responds to user input. The base class handles displaying and
 *  hiding the console, taking input, and recording command history. 
 * 
 * To make a console, your subclass needs to implement the Execute function
 *  (which gets called with a string whenever the user enters input) and the
 *  GetCompletions function, which returns a StringList of potential 
 *  auto-complete values. 
 * 
 * Most of this is academic, as you'll probably use the Lua console, which
 *  has already implemented all of this for you.
 * 
 * There's also a TestConsole implementation that does nothing but echo your
 *  commands back at you. It's the default console, so if you ever see its 
 *  prompt (\c ::>), you know something has gone wrong with loading the 
 *  real console. 
 */
class Console
{
public:
	/**
	 * The default constructor makes sure our console font (Inconsolata at)
	 *  18 points) is registered with the text rendering system. 
	 */
	Console();
	
	/**
	 * Does nothing in the base class, but you gotta have it
	 */
	virtual ~Console();

	/**
	 * Override of the Renderable::Render function that actually draws the console,
	 *  if necessary.
	 */
	void Render();
	
	/**
	 * Oddly enough, doesn't do anything. All the changes happen at user
	 *  input instead of in the update loop. 
	 * 
	 * @param dt
	 */
	void Update( float /*dt*/ );

	/**
	 * Turns the console on (or off), which makes it get drawn in the render loop and 
	 *  steals keyboard input from the rest of the game. 
	 * 
	 * @param bEnable If true, the Console is activate; if false, it's deactivated. 
	 */
	void Enable( bool bEnable = true );
	
	/**
	 * Whether the Console is currently being displayed and accepting input right now. 
	 * 
	 * @return True if it's enabled, false if it's not
	 */
	bool IsEnabled() {return _enabled;}
	
	/**
	 * Adds the given key to the Console's current input string. Should only be 
	 *  called by the input handling functions. 
	 * 
	 * @param key The numeric representation of the key
	 * @return Whether or not the key was added to the input string (false if
	 *   the Console is currently disabled or that was the key which toggled it.)
	 */
	bool GetInput(int key);
	
	/**
	 * Handles special input like Enter, Escape, arrow keys, etc. Again, this 
	 *  should only be called by the input handling functions. 
	 * 
	 * @param key The numeric representation of the special key
	 * @return Whether or not the input was accepted by the Console (false if
	 *   the Console is currently disabled.)
	 */
	bool GetSpecialInputDown( int key );
	
	/**
	 * Switches the console from on to off, or from off to on. 
	 */
	void ToggleConsole();
	
	/**
	 * Lets you know what key is set to toggle the Console. (Hard-coded to
	 *  \c '`' at the moment.)
	 * 
	 * @return The toggle console key
	 */
	unsigned char GetToggleConsoleKey()	{return '`';}
	
	/**
	 * Writes a string to the log area of the console. Used internally by 
	 *  Console implementations to display the results of commands. 
	 * 
	 * @param output The string to be appended to the log area. 
	 */
	void WriteToOutput(String output);
	
	/**
	 * Set the prompt characters that users will see at the beginning of their
	 *  input line. Some consoles like to change this to reflect their current
	 *  state. 
	 * 
	 * @param prompt The new prompt string
	 */
	void SetPrompt(const String& prompt);

	/**
	 * Get the width of tabs when output to this console.
	 */
	const unsigned int GetTabWidth();

	/**
	 * Get the width of tabs when output to this console. Defaults to 8.
	 * 
	 * @param newTabWidth The desired tab width in spaces
	 */
	void SetTabWidth(unsigned int newTabWidth);
	
	/**
	 * Replaces the current input string with a value from the input history. 
	 * 
	 * @param byVal The offset from the current history. Negative numbers will
	 *   go back in the history, positive ones will go forward. 
	 */
	void AdvanceInputHistory( int byVal );
	
	/**
	 * Replaces the input string with the current top auto-complete choice. 
	 */
	void AcceptAutocomplete();

	/**
	 * Process the current input string, work whatever magic is appropriate. 
	 *
	 * Pure virtual function; must be implemented in the subclass.
	 * 
	 * @param input The string to process in the Console
	 */
	virtual void Execute(String input) = 0;
	
	/**
	 * Gets a set of strings that are potential auto-complete matches for the
	 *  current input. 
	 * 
	 * Pure virtual function; must be implemented in the subclass. 
	 * 
	 * @param input The input string to try and match. 
	 * @return The list of potential matches
	 */
	virtual StringList GetCompletions(const String& input) = 0;

protected:
	bool IsTextKey(unsigned char key);
	void AcceptCurrentInput();
	String _currentInput;
	StringList _inputHistory;
	int _inputHistoryPos;
	String _prompt;
	StringList _buffer;
	String _unsplitBuffer;
	float _lineHeight;
	StringList _autoCompleteList;
	int _cursorPos;
	unsigned int _tabWidth;
	
private:
	void RefreshAutoCompletes();
	float _cursorDispTime;
	bool _bCursorDisp;
	
	bool _enabled;
};

///An example Console implementation
/**
 * A degenerate case of a Console; does nothing but echo the user input back
 *  into the screen log. 
 */ 
class TestConsole : public Console
{
public:
	/**
	 * Sets up the prompt (\c ::>); 
	 */
	TestConsole()
	{
		SetPrompt("::>");
	}

	/**
	 * Echos the input right back out. 
	 * 
	 * @param input The string to echo
	 */
	virtual void Execute(String input) { WriteToOutput("Test Console Echo: " + input); }
	
	/**
	 * Returns an empty StringList. 
	 * 
	 * @param input The input to be ignored
	 * @return An empty list
	 */
	virtual StringList GetCompletions(const String& input) { return StringList(); }
};
