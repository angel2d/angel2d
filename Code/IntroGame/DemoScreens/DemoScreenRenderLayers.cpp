//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2012, Shane Liesegang
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
#include "DemoScreenRenderLayers.h"


DemoScreenRenderLayers::DemoScreenRenderLayers()
{
}

void DemoScreenRenderLayers::Start()
{
	//Create overlapping actors
	a1 = new Actor();
	a1->SetSize(5.0f);
	a1->SetColor(0,0,1);
	a1->SetPosition(-1, -1);
	a2 = new Actor();
	a2->SetSize(5.0f);
	a2->SetColor(1,0,0);
	a2->SetPosition(1, 1);


	theWorld.Add(a1, 0); //Adding this actor to layer 0
	theWorld.Add(a2, 1); //Adding this actor to layer 1

	//For your game, you may want to use an enum
	//  or name the layers (see World.cpp or the later
	//  DemoScreenLayeredCollisionLevelFile.cpp for more
	//  information).





	//Demo housekeeping below this point. 
	#pragma region Demo Housekeeping
	t1 = new TextActor("Console", "These Actors overlap.");
	t1->SetPosition(0, 5.5);
	t1->SetAlignment(TXT_Center);
	theWorld.Add(t1);
	t2 = new TextActor("Console", "Use the controller's bumper buttons or \nthe right and left arrow keys to change their layer ordering.");
	t2->SetPosition(0, 4.5);
	t2->SetAlignment(TXT_Center);
	theWorld.Add(t2);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenRenderLayers.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t1);
	_objects.push_back(t2);
	_objects.push_back(a1);
	_objects.push_back(a2);
	#pragma endregion
}

void DemoScreenRenderLayers::Update(float dt)
{
	//NOTE: a2 has been added to layer one, so this function moves a1 around it.
	if ((theController.IsConnected() && theController.IsLeftBumperDown()) || theInput.IsKeyDown(GLFW_KEY_LEFT))
	{
		theWorld.UpdateLayer(a1, 0); //moves the actor to the requested layer
	}
	else if ((theController.IsConnected() && theController.IsRightBumperDown()) || theInput.IsKeyDown(GLFW_KEY_RIGHT))
	{
		theWorld.UpdateLayer(a1, 2);
	}
}
