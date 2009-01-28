#include "stdafx.h"
#include "DemoScreenStart.h"


DemoScreenStart::DemoScreenStart()
{
	music = theSound.LoadSample("Resources/Sounds/techno.mp3", true /*stream*/);
	if (music)
		theSound.PlaySound(music, 0.5f, true, 0);
}

void DemoScreenStart::Start()
{
	//TextActors, oddly enough, let you display text!
	TextActor *t = new TextActor("Console", "Welcome to Angel. This is a quick demo of what we can do.");
	t->SetPosition(0, 3.5);
	t->SetAlignment(TXT_Center);
	TextActor *t2 = new TextActor("Console", "(press [A] on the 360 controller or space bar to continue)");
	t2->SetPosition(0, 2);
	t2->SetAlignment(TXT_Center);

	theWorld.Add(t);
	theWorld.Add(t2);

	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenStart.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(t2);
	#pragma endregion
}
