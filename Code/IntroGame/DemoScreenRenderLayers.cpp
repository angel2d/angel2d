#include "stdafx.h"
#include "DemoScreenRenderLayers.h"


DemoScreenRenderLayers::DemoScreenRenderLayers()
{
}

void DemoScreenRenderLayers::Start()
{
	//Create overlapping actors
	a1 = new Actor();
	a1->SetSize(5.0f);
	a1->SetColor(0,0,1);
	a1->SetPosition(-1, -1);
	a2 = new Actor();
	a2->SetSize(5.0f);
	a2->SetColor(1,0,0);
	a2->SetPosition(1, 1);


	theWorld.Add(a1, 0); //Adding this actor to layer 0
	theWorld.Add(a2, 1); //Adding this actor to layer 1

	//For your game, you may want to use an enum
	//  for these values so you don't have to keep
	//  the integers straight. 





	//Demo housekeeping below this point. 
	#pragma region Demo Housekeeping
	t1 = new TextActor("Console", "These Actors overlap.");
	t1->SetPosition(0, 5.5);
	t1->SetAlignment(TXT_Center);
	theWorld.Add(t1);
	t2 = new TextActor("Console", "Use the controller's bumper buttons to change their layer ordering.");
	t2->SetPosition(0, 4.5);
	t2->SetAlignment(TXT_Center);
	theWorld.Add(t2);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenRenderLayers.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t1);
	_objects.push_back(t2);
	_objects.push_back(a1);
	_objects.push_back(a2);
	#pragma endregion
}

void DemoScreenRenderLayers::Update(float dt)
{
	if (!theController.IsConnected())
	{
		return;
	}
	//NOTE: a2 has been added to layer one, so this function moves a1 around it.
	if (theController.IsLeftBumperDown())
	{
		theWorld.UpdateLayer(a1, 0); //moves the actor to the requested layer
	}
	else if (theController.IsRightBumperDown())
	{
		theWorld.UpdateLayer(a1, 2);
	}
}
