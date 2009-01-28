#include "../InfraStructure/Console.h"

#include "../Infrastructure/Common.h"
#include "../Infrastructure/Camera.h"
#include "../Infrastructure/Vector2.h"
#include "../Infrastructure/TextRendering.h"
#include "../Util/MathUtil.h"
#include "../Util/StringUtil.h"



Console::Console()
: _enabled(false),
_currentInput(""),
_inputHistoryPos(0)
{
	RegisterFont("Resources/Fonts/Inconsolata.otf", 24, "Console");
	RegisterFont("Resources/Fonts/Inconsolata.otf", 18, "ConsoleSmall");
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
	glBegin(GL_QUADS);
	{
		glVertex2f( 0.0f,  0.0f);
		glVertex2f((GLfloat)width, 0.0f);
		glVertex2f((GLfloat)width, (GLfloat)height);
		glVertex2f(0.0f, (GLfloat)height);
	}
	glEnd();

	//	glPopAttrib();

	glEnable(GL_DEPTH_TEST);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void Console::Enable(bool bEnable /* = true  */)
{
	_enabled = bEnable;

	if( _enabled )
	{
		glfwEnable(GLFW_KEY_REPEAT);
	}
	else
	{
		glfwDisable(GLFW_KEY_REPEAT);
	}
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
		_currentInput += key;
		if (_currentInput.size() > 2)
		{
			_autoCompleteList = GetCompletions(_currentInput);			
		}
	}

	return true;
}

bool Console::GetSpecialInputDown( int key )
{
	if( !IsEnabled() )
		return false;

	if( key == GLFW_KEY_ESC || key == GetToggleConsoleKey() )
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
	else if( key == GLFW_KEY_BACKSPACE )
	{
		int size = _currentInput.size();
		if( size > 0 )
		{
			_currentInput =  _currentInput.substr( 0, size-1 );
			_autoCompleteList = GetCompletions(_currentInput);
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

void Console::WriteToOutput(String output)
{
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
}

void Console::AcceptAutocomplete()
{
	if( _autoCompleteList.size() == 0 )
		return;
	
	//TODO: allow user to select autocomplete
	_currentInput = _autoCompleteList[0];
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
}

void Console::ToggleConsole( const String& /*input*/ )
{
	Enable( !IsEnabled() );
}

void Console::SetPrompt(String prompt)
{
	_prompt = prompt;
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
			Vector2 textSize = DrawGameText( *it, "ConsoleSmall", sLogXPos, logYPos );
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
	printInput += _currentInput + "_";
	DrawGameText(printInput.c_str(), "ConsoleSmall", textBoxXPos, textBoxYPos);

	//Draw autocomplete
	static int sMaxAutoCompleteLines = 7;
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

