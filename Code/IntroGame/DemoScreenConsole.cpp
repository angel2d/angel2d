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
	explanation += "\n\nThe console is a (nearly) fully functional Python interpreter.";
	explanation += "\nThe sample functions are defined in \"Resources/Scripts/client_start.py\".";
	t = new TextActor("Console", explanation);
	t->SetPosition(0, -3.5f);
	t->SetAlignment(TXT_Center);
	theWorld.Add(t);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenConsole.cpp, simple_actor.adf, client_start.py");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(a);
	#pragma endregion
}

//void DemoScreenConsole::ChangeSize(const String& input)
//{
//	a->SetSize(StringToFloat(input));
//}
