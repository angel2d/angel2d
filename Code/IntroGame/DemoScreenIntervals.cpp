#include "stdafx.h"
#include "DemoScreenIntervals.h"

DemoScreenIntervals::DemoScreenIntervals()
{
	//Subscribe to messages that will make the Actor bounce back and forth
	theSwitchboard.SubscribeTo(this, "IntervalScreenStarted");
	theSwitchboard.SubscribeTo(this, "RightMoveDone");
	theSwitchboard.SubscribeTo(this, "LeftMoveDone");
}

void DemoScreenIntervals::Start()
{
	//Set up the actor
	a = new Actor();
	a->SetSize(4.0f);
	a->SetPosition(-5.0f, 0.0f);
	a->SetColor(1.0f, 1.0f, 0.0f, 0.5f);
	theWorld.Add(a);

	//Send a message to kick things off (check the ReceiveMessage function to see what's happening)
	theSwitchboard.Broadcast(new Message("IntervalScreenStarted"));



	//Demo housekeeping below this point. 
	#pragma region Demo Housekeeping
	t = new TextActor("Console", "This Actor is using Intervals to change its properties. ");
	t->SetPosition(0, 3.5);
	t->SetAlignment(TXT_Center);
	String explanation = "Intervals are a kind of \"fire and forget\" function that let you";
	explanation += "\ngive a goal state and a duration, then the Actor itself";
	explanation += "\ndoes the interpolation for you.";
	t2 = new TextActor("Console", explanation);
	t2->SetPosition(0, -4);
	t2->SetAlignment(TXT_Center);
	theWorld.Add(t);
	theWorld.Add(t2);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenIntervals.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(t2);
	_objects.push_back(a);
	#pragma endregion
}

void DemoScreenIntervals::ReceiveMessage(Message *message)
{
	if (message->GetMessageName() == "LeftMoveDone")
	{
		a->MoveTo( // Change an Actor's position over an interval
				  Vector2(5.0f, 0.0f),  //the new position
				  3.0f,					//how long it should take to get there
				  true,					//whether or not the interval should use MathUtil::SmoothStep
				  "RightMoveDone"		//the (optional) message to send when the transition is done
		);
		
		a->RotateTo(45.0f, 3.0f, true);
		a->ChangeColorTo(Color(1.0f, 0.0f, 1.0f, 1.0f), 3.0f, true);
		a->ChangeSizeTo(1.0f, 3.0f); //Note that the size change is not using the smooth step
	}
	else if (message->GetMessageName() == "RightMoveDone")
	{
		a->MoveTo(Vector2(-5.0f, 0.0f), 3.0f, true, "LeftMoveDone");
		a->RotateTo(0.0f, 3.0f, true);
		a->ChangeColorTo(Color(1.0f, 1.0f, 0.0f, 0.5f), 3.0f, true);
		a->ChangeSizeTo(3.0f, 3.0f);
	}
	else if (message->GetMessageName() == "IntervalScreenStarted")
	{
		//Essentially mapping one message to another so we don't have to
		// repeat the first set of logic down here. 
		//In general, this works, but it means the logic happens one frame
		// later than it otherwise would. 
		theSwitchboard.Broadcast(new Message("LeftMoveDone"));
	}
}

