#include "../Input/Input.h"

#include "../Infrastructure/Camera.h"
#include "../Infrastructure/World.h"
#include "../Infrastructure/Console.h"
#include "../Input/InputManager.h"


void charInput(int key, int state)
{
	if (state == GLFW_PRESS && key != theWorld.GetConsole()->GetToggleConsoleKey())
	{
		if (theWorld.GetConsole()->GetInput(key))
			return;
	}
}

void keyboardInput(int key, int state)
{
	if (state == GLFW_PRESS)
	{
		if (key == theWorld.GetConsole()->GetToggleConsoleKey())
		{
			theWorld.GetConsole()->Enable(!theWorld.GetConsole()->IsEnabled());
			return;
		}
		else if (theWorld.GetConsole()->GetSpecialInputDown(key))
		{
			return;
		}

		if (theInput.OnKeyDown(key))
			return;

		if (key == GLFW_KEY_ESC)
		{
			theWorld.StopGame();
		}
	}
	else
	{
		if( theWorld.GetConsole()->IsEnabled() )
			return;

		if( theInput.OnKeyUp((int)key))
			return;
	}
}

