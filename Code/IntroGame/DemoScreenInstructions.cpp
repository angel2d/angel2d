#include "stdafx.h"
#include "DemoScreenInstructions.h"


DemoScreenInstructions::DemoScreenInstructions()
{
}

void DemoScreenInstructions::Start()
{
	//Just some text actors to give instructions. Nothing much to see here. 
	TextActor *t = new TextActor("Console", "This demo is designed to be super simple. Maybe too much so.");
	t->SetPosition(0, 3.5);
	t->SetAlignment(TXT_Center);
	TextActor *t2 = new TextActor("Console", "Each example is self-contained within the file shown at the bottom left.");
	t2->SetPosition(0, 2);
	t2->SetAlignment(TXT_Center);
	TextActor *t3 = new TextActor("Console", "The files are pretty thoroughly commented, so check them out to see how we do things.");
	t3->SetPosition(0, 0.5);
	t3->SetAlignment(TXT_Center);
	TextActor *t4 = new TextActor("Console", "Press [A] on the 360 Controller to go to the next example, and Back to go back.");
	t4->SetPosition(0, -3.5);
	t4->SetAlignment(TXT_Center);

	theWorld.Add(t);
	theWorld.Add(t2);
	theWorld.Add(t3);
	theWorld.Add(t4);





	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenInstructions.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(t2);
	_objects.push_back(t3);
	_objects.push_back(t4);
	#pragma endregion
}
