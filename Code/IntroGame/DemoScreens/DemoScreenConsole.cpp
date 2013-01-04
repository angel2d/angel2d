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
#include "DemoScreenConsole.h"


Actor* localActor = NULL;

void AddTexture(const String& input)
{
	localActor->SetSprite("Resources/Images/angel.png");
}

DemoScreenConsole::DemoScreenConsole()
{
}

void DemoScreenConsole::Start()
{
	//Place the actor from a definition file
	localActor = a = Actor::Create("simple_actor");
	theWorld.Add(a);
	
	//Give it a name that our script hooks can latch onto. 
	a->SetName("ForDemoConsole");







	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	String explanation = "This demo shows off the console.";
	explanation += "\n\nPress ~ to open it up. Execute \"add_texture()\", enjoying the tab-completion.";
	explanation += "\nThen try executing \"change_size(3.14)\" or whatever number suits your fancy.";
	explanation += "\n\nThe console is a (nearly) fully functional Lua interpreter.";
	explanation += "\nThe sample functions are defined in \"Resources/Scripts/client_start.lua\".";
	t = new TextActor("Console", explanation);
	t->SetPosition(0, -3.5f);
	t->SetAlignment(TXT_Center);
	theWorld.Add(t);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenConsole.cpp, demo_actors.lua, client_start.lua");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(a);
	#pragma endregion
}

