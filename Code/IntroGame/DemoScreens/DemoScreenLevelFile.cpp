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
#include "DemoScreenLevelFile.h"


DemoScreenLevelFile::DemoScreenLevelFile()
{
}

void DemoScreenLevelFile::Start()
{
	//Loads the file from Config\ActorDef\level_demo.lua
	// Level files automatically add their actors to the world. 
	theWorld.LoadLevel("level_demo");

	//Since the Actors were just added directly to the world,
	//  we don't have handles to them. The level definition
	//  gave them the tag "spawned," so we can get them that way.
	ActorSet spawnedActors = theTagList.GetObjectsTagged("spawned");
	ActorSet::iterator it = spawnedActors.begin();
	while (it != spawnedActors.end())
	{
		//Can check Individual actors for tags as well.
		if ((*it)->IsTagged("left-tilted")) 
		{
			(*it)->SetRotation(25.0f);
		}
		else if ((*it)->IsTagged("right-tilted"))
		{
			(*it)->SetRotation(-25.0f);
		}
		//Applying tags
		(*it)->Tag("rotated");

		//Removing tags
		(*it)->Untag("spawned");
		it++;
	}





	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	t = new TextActor("Console", "These Actors were placed and tagged (\"left-tilted\"");
	t->SetPosition(0, 5.5);
	t->SetAlignment(TXT_Center);
	theWorld.Add(t);
	t2 = new TextActor("Console", "and \"right-tilted\") using a level definition file.");
	t2->SetPosition(0, 4.5);
	t2->SetAlignment(TXT_Center);
	theWorld.Add(t2);
	t3 = new TextActor("Console", "Then their rotations were set based on those tags.");
	t3->SetPosition(0, -4.5);
	t3->SetAlignment(TXT_Center);
	theWorld.Add(t3);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenLevelFile.cpp, level_demo.lua");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(t2);
	_objects.push_back(t3);
	it = spawnedActors.begin();
	while (it != spawnedActors.end())
	{
		_objects.push_back(*it);
		it++;
	}
	#pragma endregion
}

