#include "stdafx.h"
#include "DemoScreenMultipleControllers.h"

DemoScreenMultipleControllers::DemoScreenMultipleControllers()
{
}

void DemoScreenMultipleControllers::Start()
{
	//Set up the actor
	a = new Actor();
	a->SetSize(4.0f);
	a->SetPosition(-4.0f, 0.0f);
	a->SetColor(1.0f, 1.0f, 0.0f, 0.5f);
	theWorld.Add(a);
	
	a2 = new Actor();
	a2->SetSize(4.0f);
	a2->SetPosition(4.0f, 0.0f);
	a2->SetColor(1.0f, 1.0f, 0.0f, 0.5f);
	theWorld.Add(a2);
	
	
	//Demo housekeeping below this point. 
#pragma region Demo Housekeeping
	t = new TextActor("Console", "These two actors are connected to different controllers.");
	t->SetPosition(0, 3.5);
	t->SetAlignment(TXT_Center);
	t2 = new TextActor("Console", "You can use multiple controllers for two-player games.");
	t2->SetPosition(0, -4);
	t2->SetAlignment(TXT_Center);
	t3 = new TextActor("Console", "(If you only have one [or zero] controllers connected, \nthis screen is kind of boring.)");
	t3->SetPosition(0, -8);
	t3->SetAlignment(TXT_Center);
	theWorld.Add(t);
	theWorld.Add(t2);
	theWorld.Add(t3);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenMultipleControllers.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(t2);
	_objects.push_back(t3);
	_objects.push_back(a);
	_objects.push_back(a2);
#pragma endregion
}

void DemoScreenMultipleControllers::Update(float dt)
{
	if (controllerOne.IsConnected())
	{
		Vec2i movementL = controllerOne.GetLeftThumbstick(); //returns a 2d integer vector

		Vector2 position;
		if (movementL.X)
		{
			position.X = -4.0f + (3.0f * ((float)movementL.X / 32768.0f));
		}
		else
		{
			position.X = -4.0f;
		}
		if (movementL.Y)
		{
			position.Y = 3.0f * ((float)movementL.Y / 32768.0f);
		}
		else
		{
			position.Y = 0.0f;
		}
		
		//Update the position with our calculated values. 
		a->SetPosition(position);
		
		//Every tick, update the rotation if B is held down
		if (controllerOne.IsBButtonDown())
		{
			a->SetRotation(a->GetRotation() + (90.0f * dt)); //90 degrees per second
			if (a->GetRotation() > 360.0f)
			{
				a->SetRotation(a->GetRotation() - 360.0f);
			}
		}
	}
	
	if (controllerTwo.IsConnected())
	{
		Vec2i movementL = controllerTwo.GetLeftThumbstick(); //returns a 2d integer vector
		
		Vector2 position;
		if (movementL.X)
		{
			position.X = 4.0f + (3.0f * ((float)movementL.X / 32768.0f));
		}
		else
		{
			position.X = 4.0f;
		}
		if (movementL.Y)
		{
			position.Y = 3.0f * ((float)movementL.Y / 32768.0f);
		}
		else
		{
			position.Y = 0.0f;
		}
		
		//Update the position with our calculated values. 
		a2->SetPosition(position);
		
		//Every tick, update the rotation if B is held down
		if (controllerTwo.IsBButtonDown())
		{
			a2->SetRotation(a2->GetRotation() + (90.0f * dt)); //90 degrees per second
			if (a2->GetRotation() > 360.0f)
			{
				a2->SetRotation(a2->GetRotation() - 360.0f);
			}
		}
	}
}
