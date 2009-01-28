#include "stdafx.h"
#include "DemoScreenCollisionLevelFile.h"


DemoScreenCollisionLevelFile::DemoScreenCollisionLevelFile()
{
}

void DemoScreenCollisionLevelFile::Start()
{
	//Loads the file from Config\ActorDef\collisionlevel_demo.lvl
	theWorld.LoadLevel("collisionlevel_demo");

	//All the magic happens in the level file!





	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	t = new TextActor("Console", "These Actors were also placed using a level file.");
	t->SetPosition(0, 4.5);
	t->SetAlignment(TXT_Center);
	theWorld.Add(t, 10);
	t2 = new TextActor("Console", "Their physics-related properties came from actor definitions.");
	t2->SetPosition(0, -3.5);
	t2->SetAlignment(TXT_Center);
	theWorld.Add(t2, 10);
	//t3 = new TextActor("Console", "They respond to sound in a data driven way.");
	//t3->SetPosition(0, -4.5);
	//t3->SetAlignment(TXT_Center);
	//theWorld.Add(t3, 10);
	//t4 = new TextActor("Console", "If the only collision response you need is sound, this is easier.");
	//t4->SetPosition(0, -5.5);
	//t4->SetAlignment(TXT_Center);
	//theWorld.Add(t4, 10);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenCollisionLevelFile.cpp, collisionlevel_demo.lvl,");
	TextActor *fileLoc2 = new TextActor("ConsoleSmall", "      ground_actor.adf, physics_event_actor.adf");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 745));
	fileLoc->SetColor(.3f, .3f, .3f);
	fileLoc2->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc2->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc, 10);
	theWorld.Add(fileLoc2, 10);
	_objects.push_back(fileLoc);
	_objects.push_back(fileLoc2);
	_objects.push_back(t);
	_objects.push_back(t2);
	//_objects.push_back(t3);
	//_objects.push_back(t4);
	ActorSet spawnedActors = theTagList.GetObjectsTagged("spawned");
	ActorSet::iterator it = spawnedActors.begin();
	while (it != spawnedActors.end())
	{
		_objects.push_back(*it);
		it++;
	}
	#pragma endregion
}

