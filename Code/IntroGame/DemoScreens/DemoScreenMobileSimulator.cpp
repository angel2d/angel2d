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
#include "DemoScreenMobileSimulator.h"


DemoScreenMobileSimulator::DemoScreenMobileSimulator()
{
	// Creating a new object for the World that will simulate the hardware
	//  of the mobile phone, filling the same data structures you can read
	//  in the desktop version of the engine. 
	//
	// Note that we're doing conditional compilation here to not add the 
	//  simulator when we're actually building for the iPhone. This same
	//  DemoScreen runs in the IntroGame for iOS. 
	#if !ANGEL_MOBILE
		_ms = new MobileSimulator();
	#endif
}

void DemoScreenMobileSimulator::Start()
{
	// Add the MobileSimulator object to the world.
	#if !ANGEL_MOBILE
		theWorld.Add(_ms);
	#endif
	
	// Set ourselves up to receive the messages that we'll get from the
	//  mobile hardware or the simulator. 
	theSwitchboard.SubscribeTo(this, "MultiTouchPinch");
	theSwitchboard.SubscribeTo(this, "MultiTouchRotate");
	
	// Making an Actor that we'll manipulate with the mobile data.
	Actor* a = new Actor();
	a->SetSize(5.0f);
	a->SetSprite("Resources/Images/angel.png");
	a->SetName("TouchedActor"); // We'll use this name to find it.
	theWorld.Add(a);
	
	//Demo housekeeping below this point. 
	#pragma region Demo Housekeeping
	#if !ANGEL_MOBILE
		String description = "This is a fun screen. \n\n";
		description +=		 "Angel supports iOS, but you probably don't\n";
		description +=		 "have multi-touch or an accelerometer in \n";
		description +=		 "your desktop machine.\n\n";
		description +=		 "No problem!";
		TextActor *t = new TextActor("Console", description);
		t->SetPosition(-11.5f, 9.2f);
		theWorld.Add(t);
		description  = "We provide a simulator functionality that lets you pretend that you're\n";
		description += "working on an iPhone. This means you can do 90% of the work of making\n";
		description += "an iPhone or iPad game without having the hardware!\n\n";
		description += "Mouse clicks are like touches. Hold down Control to play with\n";
		description += "multi-touch gestures. The Xbox 360 thumbsticks serve as fake\n";
		description += "accelerometers, so you can pretend you're getting your tilt on.";
		TextActor *t2 = new TextActor("Console", description);
		t2->SetPosition(11.5f, -4.0f);
		t2->SetAlignment(TXT_Right);
		theWorld.Add(t2);
		_objects.push_back(t);
		_objects.push_back(t2);
	#endif
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenMobileSimulator.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(a);
	#pragma endregion
}

void DemoScreenMobileSimulator::Stop()
{
	// Clear out the simulator and unsubscribe from messages when we move
	//  away from this screen. 
	
	#if !ANGEL_MOBILE
		theWorld.Remove(_ms);
	#endif
	
	theSwitchboard.UnsubscribeFrom(this, "MultiTouchPinch");
	theSwitchboard.UnsubscribeFrom(this, "MultiTouchRotate");
	
	DemoScreen::Stop();
}

void DemoScreenMobileSimulator::ReceiveMessage(Message *m)
{
	// Here's where we respond to MultiTouch events that get sent from 
	//  both the mobile simulator and the actual hardware. 
	
	if (m->GetMessageName() == "MultiTouchPinch")
	{
		// The multitouch pinch and rotation messages both deliver data
		//  in the form of a GestureData struct. In a punch message, 
		//  the "GestureMagnitude" value indicates the scale of the
		//  current pinch from where it started. (Relative to 1.0).
		//
		// This code will scale the actor up or down depending on whether
		//  GestureMagnitude is less than or greater than 1. 
		GestureData gd = ((TypedMessage<GestureData>*)m)->GetValue();
		Actor* tA = Actor::GetNamed("TouchedActor");
		tA->SetSize(5.0f * gd.GestureMagnitude);
	}
	else if (m->GetMessageName() == "MultiTouchRotate")
	{
		GestureData gd = ((TypedMessage<GestureData>*)m)->GetValue();
		Actor* tA = Actor::GetNamed("TouchedActor");
		
		// With a rotation message, the GestureMagnitude is the angle
		//  of the rotation in radians. So if you want to pass that 
		//  data to an Angel actor, be sure to translate it to degrees
		//  first. 
		tA->SetRotation(MathUtil::ToDegrees(gd.GestureMagnitude));
	}
	
	// Other messages available include:
	//	- MultiTouchSwipeUp
	//  - MultiTouchSwipeDown
	//  - MultiTouchSwipeLeft
	//  - MultiTouchSwipeRight
	// As well as separate messages sent if the swipe was made with 
	//  two fingers instead of one:
	//	- MultiTouchSwipeUpDouble
	//  - MultiTouchSwipeDownDouble
	//  - MultiTouchSwipeLeftDouble
	//  - MultiTouchSwipeRightDouble
}

void DemoScreenMobileSimulator::Render()
{
	// If you just want access to the raw touch data to do your own 
	//  processing on it, you can get that pretty easily, too. This
	//  Render method will draw a cross wherever the system is currently
	//  detecting a touch. Different platforms (iPhone vs. iPad, for 
	//  instance) have different maximums for the number of touches 
	//  they will detect simultaneously. 
	
	glColor3f(1.0f, 0.0f, 0.0f);

	TouchList tl = TouchListener::GetTouchList();
	TouchList::iterator it = tl.begin();
	while (it != tl.end())
	{
		DrawCross(MathUtil::ScreenToWorld((*it)->CurrentPoint), 3.0f);
		it++;
	}
}

void DemoScreenMobileSimulator::Update(float dt)
{
	// Finally, you can also access the accelerometer data. With the 
	//  simulator, its read from the Xbox 360 thumbsticks. 
	// 
	// On the real hardware, we do some simple buffering/averaging to
	//  smooth out the values here. The tradeoff is smoothness for lag.
	//  If you want to tweak this tradeoff, edit the 
	//  ANGEL_ACCEL_BUFFER_SIZE value found in AngelAppDelegate.m. 
	
	Vector3 accel = Accelerometer::GetInstance().GetData();
	Actor* tA = Actor::GetNamed("TouchedActor");
	Vector2 pos(accel.X, accel.Y);
	pos *= 4.0f;
	tA->SetPosition(pos);
}
