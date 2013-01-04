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

#include "stdafx.h"
#include "DemoScreenMultipleControllers.h"

DemoScreenMultipleControllers::DemoScreenMultipleControllers()
{
}

void DemoScreenMultipleControllers::Start()
{
	//Create two Actors that we're going to manipulate with the two 
	// controllers. All the actual interesting stuff happens in the
	// DemoScreenMultipleControllers::Update function. 
	a = new Actor();
	a->SetSize(4.0f);
	a->SetPosition(-4.0f, 0.0f);
	a->SetColor(1.0f, 1.0f, 0.0f, 0.5f);
	theWorld.Add(a);
	
	a2 = new Actor();
	a2->SetSize(4.0f);
	a2->SetPosition(4.0f, 0.0f);
	a2->SetColor(1.0f, 1.0f, 0.0f, 0.5f);
	theWorld.Add(a2);
	
	
	
	
	//Demo housekeeping below this point. 
#pragma region Demo Housekeeping
	t = new TextActor("Console", "These two actors are connected to different controllers.");
	t->SetPosition(0, 3.5);
	t->SetAlignment(TXT_Center);
	t2 = new TextActor("Console", "You can use multiple controllers for two-player games.");
	t2->SetPosition(0, -4);
	t2->SetAlignment(TXT_Center);
	t3 = new TextActor("Console", "(If you only have one [or zero] controllers connected, \nthis screen is kind of boring.)");
	t3->SetPosition(0, -8);
	t3->SetAlignment(TXT_Center);
	theWorld.Add(t);
	theWorld.Add(t2);
	theWorld.Add(t3);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenMultipleControllers.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(t2);
	_objects.push_back(t3);
	_objects.push_back(a);
	_objects.push_back(a2);
#pragma endregion
}

void DemoScreenMultipleControllers::Update(float dt)
{
	//We can access the controllers via the shortcuts:
	//  controllerOne (identical to theController, if you like that
	//                 nomenclature better in a one-player setting)
	//  controllerTwo (exactly what you think it is)
	//
	//The movements we're applying here are the same as the ones in 
	// DemoScreenMovingActor.cpp
	
	//We always want to do the IsConnected check before reading input, since
	// you may get junk values otherwise. 
	if (controllerOne.IsConnected()) 
	{
		Vec2i movementL = controllerOne.GetLeftThumbstick();

		Vector2 position;
		if (movementL.X)
		{
			position.X = -4.0f + (3.0f * ((float)movementL.X / 32768.0f));
		}
		else
		{
			position.X = -4.0f;
		}
		if (movementL.Y)
		{
			position.Y = 3.0f * ((float)movementL.Y / 32768.0f);
		}
		else
		{
			position.Y = 0.0f;
		}
		
		a->SetPosition(position);
		
		if (controllerOne.IsBButtonDown())
		{
			a->SetRotation(a->GetRotation() + (90.0f * dt)); 
			if (a->GetRotation() > 360.0f)
			{
				a->SetRotation(a->GetRotation() - 360.0f);
			}
		}
	}
	
	if (controllerTwo.IsConnected())
	{
		Vec2i movementL = controllerTwo.GetLeftThumbstick(); 
		
		Vector2 position;
		if (movementL.X)
		{
			position.X = 4.0f + (3.0f * ((float)movementL.X / 32768.0f));
		}
		else
		{
			position.X = 4.0f;
		}
		if (movementL.Y)
		{
			position.Y = 3.0f * ((float)movementL.Y / 32768.0f);
		}
		else
		{
			position.Y = 0.0f;
		}
		
		a2->SetPosition(position);
		
		if (controllerTwo.IsBButtonDown())
		{
			a2->SetRotation(a2->GetRotation() + (90.0f * dt)); 
			if (a2->GetRotation() > 360.0f)
			{
				a2->SetRotation(a2->GetRotation() - 360.0f);
			}
		}
	}
}
