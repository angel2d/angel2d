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
#include "../Input/Input.h"

#include "../Infrastructure/Camera.h"
#include "../Infrastructure/World.h"
#include "../Infrastructure/Console.h"
#include "../Input/InputManager.h"


void charInput(GLFWwindow* window, unsigned int key)
{
	if (key != theWorld.GetConsole()->GetToggleConsoleKey())
	{
		if (theWorld.GetConsole()->GetInput(key))
			return;
	}
}

void keyboardInput(GLFWwindow* window, int key, int scancode, int state, int mods)
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

		if (key == GLFW_KEY_ESCAPE)
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

