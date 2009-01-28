#include "stdafx.h"
#include "DemoScreenLevelFile.h"


DemoScreenLevelFile::DemoScreenLevelFile()
{
}

void DemoScreenLevelFile::Start()
{
	//Loads the file from Config\ActorDef\level_demo.lvl
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
	t2 = new TextActor("Console", "and \"right-tilted\") using a Level file.");
	t2->SetPosition(0, 4.5);
	t2->SetAlignment(TXT_Center);
	theWorld.Add(t2);
	t3 = new TextActor("Console", "Then their rotations were set based on those tags.");
	t3->SetPosition(0, -4.5);
	t3->SetAlignment(TXT_Center);
	theWorld.Add(t3);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenLevelFile.cpp, level_demo.lvl");
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

