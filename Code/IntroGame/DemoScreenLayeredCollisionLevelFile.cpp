#include "stdafx.h"
#include "DemoScreenLayeredCollisionLevelFile.h"


DemoScreenLayeredCollisionLevelFile::DemoScreenLayeredCollisionLevelFile()
{
}

void DemoScreenLayeredCollisionLevelFile::Start()
{
	//
	theWorld.NameLayer("background", 0);
	theWorld.NameLayer("foreground", 1);
	theWorld.NameLayer("hud", 2);
	
	//Loads the file from Config\ActorDef\layeredcollisionlevel_demo.lvl
	theWorld.LoadLevel("layeredcollisionlevel_demo");

	//All the magic happens in the level file!





	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	t2 = new TextActor("Console", "These new Actors were assigned layers in the level file.");
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
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenLayeredCollisionLevelFile.cpp, layeredcollisionlevel_demo.lvl");
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

