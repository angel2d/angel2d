#include "stdafx.h"
#include "DemoScreenByeBye.h"


DemoScreenByeBye::DemoScreenByeBye()
{
}

void DemoScreenByeBye::Start()
{
	//"Goodnight, Gracie."
	TextActor *t = new TextActor("Console", "That's all we've got in the demo app.");
	t->SetPosition(0, 3.5);
	t->SetAlignment(TXT_Center);
	TextActor *t2 = new TextActor("Console", "Make sure to check out the documentation -- there are lots of other features.");
	t2->SetPosition(0, 2);
	t2->SetAlignment(TXT_Center);
	TextActor *t3 = new TextActor("Console", "Press Esc to exit.");
	t3->SetPosition(0, -1);
	t3->SetAlignment(TXT_Center);

	theWorld.Add(t);
	theWorld.Add(t2);
	theWorld.Add(t3);






	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenByeBye.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(t2);
	_objects.push_back(t3);
	#pragma endregion
}
