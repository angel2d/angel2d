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
#include "../Infrastructure/Console.h"

#include "../Infrastructure/Common.h"
#include "../Infrastructure/Camera.h"
#include "../Infrastructure/Vector2.h"
#include "../Infrastructure/TextRendering.h"
#include "../Util/MathUtil.h"
#include "../Util/StringUtil.h"


#define MAX_AUTO_COMPLETE 7


Console::Console()
: _enabled(false),
_currentInput(""),
_inputHistoryPos(0),
_cursorPos(0),
_cursorDispTime(0.0f),
_bCursorDisp(true),
_tabWidth(8)
{
	if (!IsFontRegistered("Console") || !IsFontRegistered("ConsoleSmall"))
	{
		RegisterFont("Resources/Fonts/Inconsolata.otf", 24, "Console");
		RegisterFont("Resources/Fonts/Inconsolata.otf", 18, "ConsoleSmall");
	}
}

Console::~Console()
{

}

void DrawTile( int xPos, int yPos, int width, int height )
{
	Vec2i winDimensions;
	winDimensions.X = theCamera.GetWindowWidth();
	winDimensions.Y = theCamera.GetWindowHeight();
	yPos = winDimensions.Y - yPos;

	//set up projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, winDimensions.X, 0, winDimensions.Y);

	//set up modelview
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef((GLfloat)(xPos), (GLfloat)(yPos), 0);

	glDisable(GL_DEPTH_TEST);

	//	glPushAttrib( GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);

	//Render console background
	float vertices[] = {
		(GLfloat)width, 0.0f,
		(GLfloat)width, (GLfloat)height,
		0.0f, 0.0f,
		0.0f, (GLfloat)height,
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//	glPopAttrib();

	glEnable(GL_DEPTH_TEST);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void Console::Enable(bool bEnable /* = true  */)
{
	_enabled = bEnable;
}

bool Console::GetInput( int key )
{
	if( !IsEnabled() )
		return false;

	if (key == GetToggleConsoleKey())
	{
		Enable(false);
	}
	else if( IsTextKey(key) )
	{
		String oldInput = _currentInput;
		_currentInput = oldInput.substr(0, _cursorPos);
		_currentInput += key;
		
		if (_cursorPos < oldInput.length())
		{
			_currentInput += oldInput.substr(_cursorPos, oldInput.length());
		}
		
		++_cursorPos;
		
		RefreshAutoCompletes();
	}

	return true;
}

bool Console::GetSpecialInputDown( int key )
{
	if( !IsEnabled() )
		return false;

	if( key == GLFW_KEY_ESCAPE || key == GetToggleConsoleKey() )
	{
		Enable(false);
	}
	else if( key == GLFW_KEY_ENTER )
	{
		AcceptCurrentInput();
		_autoCompleteList.clear();
	}
	else if( key == GLFW_KEY_TAB )
	{
		AcceptAutocomplete();
	}
	else if( key == GLFW_KEY_DELETE )
	{
		if (_cursorPos < _currentInput.length())
		{
			String oldInput = _currentInput;
			
			_currentInput = oldInput.substr( 0, _cursorPos );
			_currentInput += oldInput.substr(_cursorPos+1, oldInput.length());
			
			RefreshAutoCompletes();
		}
		
	}
	else if( key == GLFW_KEY_BACKSPACE )
	{
		if( _cursorPos > 0 )
		{
			String oldInput = _currentInput;
			
			_currentInput = oldInput.substr( 0, _cursorPos-1 );
			
			if (_cursorPos < oldInput.length())
			{
				_currentInput += oldInput.substr(_cursorPos, oldInput.length());
			}
			
			--_cursorPos;
			
			RefreshAutoCompletes();
		}
	}
	else if( key == GLFW_KEY_UP ) 
	{
		AdvanceInputHistory( -1 );
	}
	else if( key == GLFW_KEY_DOWN )
	{
		AdvanceInputHistory( 1 );
	}
	else if( key == GLFW_KEY_RIGHT ) 
	{
		if (_cursorPos < _currentInput.length())
		{
			++_cursorPos;
		}
	}
	else if( key == GLFW_KEY_LEFT )
	{
		if (_cursorPos > 0)
		{
			--_cursorPos;
		}
	}
	else if( key == GLFW_KEY_END )
	{
		_cursorPos = _currentInput.length();
	}
	else if( key == GLFW_KEY_HOME )
	{
		_cursorPos = 0;
	}
	//TODO: Restore
	//else if( key == GLFW_KEY_PAGEUP )
	//{
	//	AdvanceConsoleLog(-1);
	//}
	//else if( key == GLFW_KEY_PAGEDOWN )
	//{
	//	AdvanceConsoleLog(1);
	//}

	return true;

}

void Console::RefreshAutoCompletes()
{
	if (_currentInput.size() > 2)
	{
		_autoCompleteList = GetCompletions(_currentInput);
	}
	else
	{
		_autoCompleteList.clear();
	}
}

void Console::WriteToOutput(String output)
{
	// convert tabs first
	size_t tabIndex = output.find_first_of('\t');
	while (tabIndex != std::string::npos)
	{
		int numSpaces = _tabWidth - (tabIndex % _tabWidth);
		String replacement = "";
		for(int i=0; i < numSpaces; i++)
		{
			replacement += " ";
		}
		output = output.substr(0, tabIndex) + replacement + output.substr(tabIndex + 1, output.size() - 1);
		tabIndex = output.find_first_of('\t');
	}

	
	_unsplitBuffer += output;
	_buffer = SplitString(_unsplitBuffer, "\n", false);
	
	float largest = 0.0f;
	StringList::iterator it = _buffer.begin();
	Vector2 extents = Vector2::Zero;
	while(it != _buffer.end())
	{
		extents = GetTextExtents((*it), "ConsoleSmall");
		if (extents.Y > largest)
		{
			largest = extents.Y;
		}
		
		it++;
	}
	_lineHeight = largest;
}

bool Console::IsTextKey(unsigned char key)
{
	if( key >= ' ' && key <= '}' )
		return true;

	return false;
}

void Console::AcceptCurrentInput()
{
	Execute(_currentInput);
	if (_currentInput.size() > 0)
	{
		_inputHistory.push_back(_currentInput);
		_inputHistoryPos = _inputHistory.size();
	}
	_currentInput = "";
	_cursorPos = 0;
}

void Console::AcceptAutocomplete()
{
	if( _autoCompleteList.size() == 0 )
		return;
	
	//cycle through the available completions with tab
	int found = -1;
	for (int i=0; i < _autoCompleteList.size(); i++)
	{
		if (i > MAX_AUTO_COMPLETE)
		{
			break;
		}
		if (_currentInput == _autoCompleteList[i])
		{
			//found our existing match, try to cycle to the next one
			if ( (i == _autoCompleteList.size() - 1) || (i == MAX_AUTO_COMPLETE - 2) )
			{
				//found it, but at the end of the list, so cycle to top
				break;
			}
			//set the found index to the next line
			found = i+1;
			break;
		}
	}
	
	if (-1 == found)
	{
		found = 0;
	}

	_currentInput = _autoCompleteList[found];
	_cursorPos = _currentInput.length();
}

void Console::AdvanceInputHistory(int byVal)
{
	//If we have no input history, ignore this
	if( _inputHistory.size() == 0 )
		return;
	
	//If we're at the bottom of our input history, do nothing
	int lastInputIndex = _inputHistory.size();
	if( byVal >= 0 && (_inputHistoryPos + byVal) >= lastInputIndex )
	{
		_currentInput = "";
		_cursorPos = 0;
		_inputHistoryPos = lastInputIndex;
		return;
	}
	
	
	_inputHistoryPos += byVal;
	if( _inputHistoryPos > lastInputIndex )
		_inputHistoryPos = lastInputIndex;
	else if( _inputHistoryPos < 0 )
		_inputHistoryPos = 0;
	
	//otherwise, write over our current input
	_currentInput = _inputHistory[_inputHistoryPos];
	_cursorPos = _currentInput.length();
}

void Console::ToggleConsole()
{
	Enable( !IsEnabled() );
}

void Console::SetPrompt(const String& prompt)
{
	_prompt = prompt;
}

void Console::SetTabWidth(unsigned int newTabWidth)
{
	_tabWidth = newTabWidth;
}

const unsigned int Console::GetTabWidth()
{
	return _tabWidth;
}

void Console::Update( float dt )
{
	static const float CURSOR_DISPLAY_TIME = 0.5f;
	
	_cursorDispTime += dt;
	
	if (_cursorDispTime > CURSOR_DISPLAY_TIME)
	{
		_cursorDispTime = 0.0f;
		_bCursorDisp = !_bCursorDisp;
	}
}

void Console::Render()
{
	if( !IsEnabled() )
		return;

	//TODO: Clean up this nonsense

	static float sTestAlpha = 0.75;
	Vec2i winDimensions;
	winDimensions.X = theCamera.GetWindowWidth();
	winDimensions.Y = theCamera.GetWindowHeight();

	static float fScreenHeightPct = 0.5f;
	static int sTextBoxBorder = winDimensions.Y/192;
	static int sTextBoxHeight = winDimensions.Y/32 + sTextBoxBorder;

	int consoleBGHeight = (int)(fScreenHeightPct * (float)winDimensions.Y);

	int consoleBGBottomY = consoleBGHeight;

	glColor4f(0.0f,0.0f,0.0f,sTestAlpha);
	DrawTile(0, consoleBGBottomY, winDimensions.X, consoleBGHeight );

	//Draw log
	static int sLogXPos = sTextBoxBorder;
	int logYPos = consoleBGBottomY - sTextBoxBorder;
	if (_buffer.size() > 0)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		StringList::iterator it = _buffer.end();
		while (it != _buffer.begin())
		{
			it--;
			/* Vector2 textSize = */ DrawGameText( *it, "ConsoleSmall", sLogXPos, logYPos );
			logYPos -= (int)_lineHeight + sTextBoxBorder;
		}
	}

	//Draw text box border
	glColor4f(0.0f,1.0f,0.0f,sTestAlpha/2.0f);
	int textBoxBottomY = consoleBGBottomY + sTextBoxHeight;
	DrawTile(0, textBoxBottomY, winDimensions.X, sTextBoxHeight );

	//Draw text box

	int textBoxHeight = sTextBoxHeight - sTextBoxBorder;
	int textBoxWidth = winDimensions.X - sTextBoxBorder;
	int textBoxXPos = (winDimensions.X - textBoxWidth)/2;
	int textBoxYPos = textBoxBottomY - (sTextBoxHeight-textBoxHeight)/2;

	glColor4f(0.0f,0.0f,0.0f,sTestAlpha);
	DrawTile(textBoxXPos, textBoxYPos, textBoxWidth, textBoxHeight);

	textBoxXPos += sTextBoxBorder;
	textBoxYPos -= sTextBoxBorder + (sTextBoxBorder/2);

	glColor4f(0.0f,1.0f,0.0f,1.0f);
	String printInput = _prompt;
	printInput += _currentInput.substr(0, _cursorPos);
	
	if(_bCursorDisp)
	{
		printInput += "|";
	}
	else
	{
		printInput += " ";
	}
	
	if (_cursorPos < _currentInput.length())
	{
		printInput += _currentInput.substr(_cursorPos, _currentInput.length());
	}
	
	DrawGameText(printInput.c_str(), "ConsoleSmall", textBoxXPos, textBoxYPos);

	//Draw autocomplete
	static int sMaxAutoCompleteLines = MAX_AUTO_COMPLETE;
	int numAutoCompleteLines = MathUtil::Min(sMaxAutoCompleteLines, (int)_autoCompleteList.size() );
	int autoCompleteBottomY = textBoxBottomY + (numAutoCompleteLines * sTextBoxHeight);
	int autoCompleteStartY = textBoxBottomY + 2*sTextBoxHeight/3;

	int autoCompleteXPos = textBoxXPos + winDimensions.Y / 24;
	int autoCompleteBoxXPos = autoCompleteXPos - sTextBoxBorder;

	glColor4f(0.0f,0.0f,0.0f,sTestAlpha);
	DrawTile(autoCompleteBoxXPos, autoCompleteBottomY, winDimensions.X-autoCompleteBoxXPos, numAutoCompleteLines * sTextBoxHeight);

	glColor4f(0.0f,1.0f,0.0f,1.0f);
	Vector2 outPos((float)autoCompleteXPos, (float)autoCompleteStartY);
	for( int i = 0; i < numAutoCompleteLines; i++ )
	{
		if( (int)_autoCompleteList.size() > sMaxAutoCompleteLines-1 && i == sMaxAutoCompleteLines-1 )
			DrawGameText( "...", "ConsoleSmall", autoCompleteXPos, (int)outPos.Y );
		else
			DrawGameText( _autoCompleteList[i].c_str(), "ConsoleSmall", autoCompleteXPos, (int)outPos.Y );
		outPos.Y += sTextBoxHeight;
	}


}

