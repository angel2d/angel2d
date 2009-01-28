#include "stdafx.h"
#include "DemoScreenDefFile.h"

DemoScreenDefFile::DemoScreenDefFile()
{
}

void DemoScreenDefFile::Start()
{

	//CreateActor loads up an Actor Definition file and makes the actor from it
	a = Actor::Create("simple_actor"); //string is the file to load from -- 
									   // must be located in Config/ActorDef and end with ".adf"
	
	//You still need to add it to the world after it's been created
	theWorld.Add(a);
	
	





	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	t = new TextActor("Console", "This Actor was placed using an ActorDef file.");
	t->SetPosition(0, 4.5);
	t->SetAlignment(TXT_Center);
	theWorld.Add(t);
	t2 = new TextActor("Console", "You can be data-driven if you want to!");
	t2->SetPosition(0, 3.5);
	t2->SetAlignment(TXT_Center);
	theWorld.Add(t2);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenDefFile.cpp, simple_actor.adf");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(t2);
	_objects.push_back(a);
	#pragma endregion
}

