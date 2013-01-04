//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

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
	String explanation = "Intervals are kind of \"fire and forget\" functions that let you";
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
	if (message->GetMessageName() == "LeftMoveDone" || message->GetMessageName() == "IntervalScreenStarted")
	{
		a->MoveTo( // Change an Actor's position over an interval
				  Vector2(5.0f, 0.0f),  //the new position
				  3.0f,					//how long it should take to get there
				  true,					//whether or not the interval should use MathUtil::SmoothStep
				  "RightMoveDone"		//the (optional) message to send when the transition is done
		);
		
		a->RotateTo(45.0f, 3.0f, true);
		a->ChangeColorTo(Color(1.0f, 0.0f, 1.0f, 1.0f), 3.0f, true);
		a->ChangeSizeTo(1.0f, 3.0f, true);
	}
	else if (message->GetMessageName() == "RightMoveDone")
	{
		a->MoveTo(Vector2(-5.0f, 0.0f), 3.0f, true, "LeftMoveDone");
		a->RotateTo(0.0f, 3.0f, true);
		a->ChangeColorTo(Color(1.0f, 1.0f, 0.0f, 0.5f), 3.0f, true);
		a->ChangeSizeTo(3.0f, 3.0f, true);
	}
}

