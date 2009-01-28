#include "stdafx.h"
#include "DemoScreenBindingInstructions.h"

DemoScreenBindingInstructions::DemoScreenBindingInstructions()
{
}

void DemoScreenBindingInstructions::Start()
{
	//Some TextActors pointing you to other files that do cool stuff. 
	String explanation = "While we're looking at config files, check out input_bindings.ini.";
	explanation += "\nIt shows how to do controller and keyboard bindings.";
	explanation += "\n\n(Input bindings are based around Messages, which we'll deal with in a bit.)";
	TextActor *t = new TextActor("Console", explanation);
	t->SetPosition(0, 3.5);
	t->SetAlignment(TXT_Center);

	theWorld.Add(t);






	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenBindingInstructions.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	#pragma endregion
}
