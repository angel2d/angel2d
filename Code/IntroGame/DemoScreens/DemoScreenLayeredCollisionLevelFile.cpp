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
#include "DemoScreenLayeredCollisionLevelFile.h"


DemoScreenLayeredCollisionLevelFile::DemoScreenLayeredCollisionLevelFile()
{
}

void DemoScreenLayeredCollisionLevelFile::Start()
{
	//Give names to some layers so we can reference them more easily
	theWorld.NameLayer("background", 0);
	theWorld.NameLayer("foreground", 1);
	theWorld.NameLayer("hud", 2);
	
	//Loads the file from Config\ActorDef\layeredcollisionlevel_demo.lua
	theWorld.LoadLevel("layeredcollisionlevel_demo");

	//All the magic happens in the level file!





	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	t2 = new TextActor("Console", "These new Actors were assigned layers in their level file.");
	t2->SetPosition(0, 5.5);
	t2->SetAlignment(TXT_Center);
	theWorld.Add(t2, 10);
	t3 = new TextActor("Console", "Layers can be given string names as well as numbers");
	t3->SetPosition(0, 4.5);
	t3->SetAlignment(TXT_Center);
	theWorld.Add(t3, 10);
	t4 = new TextActor("Console", "and assigned to Actors in their definition file or at runtime.");
	t4->SetPosition(0, 3.5);
	t4->SetAlignment(TXT_Center);
	theWorld.Add(t4, 10);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenLayeredCollisionLevelFile.cpp, layeredcollisionlevel_demo.lua");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc, 10);
	_objects.push_back(fileLoc);
	_objects.push_back(t2);
	_objects.push_back(t3);
	_objects.push_back(t4);
	ActorSet spawnedActors = theTagList.GetObjectsTagged("spawned");
	ActorSet::iterator it = spawnedActors.begin();
	while (it != spawnedActors.end())
	{
		_objects.push_back(*it);
		it++;
	}
	#pragma endregion
}

