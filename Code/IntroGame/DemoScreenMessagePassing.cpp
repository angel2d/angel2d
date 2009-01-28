#include "stdafx.h"
#include "DemoScreenMessagePassing.h"


DemoScreenMessagePassing::DemoScreenMessagePassing()
{
	Setup();
}

void DemoScreenMessagePassing::Setup()
{
	//Create a new physics actor, but don't initialize its physics just yet. We'll start 
	// physics in response to some messages later on. 
	p1 = new PhysicsActor();
	p1->SetSize(1.0f);
	p1->SetColor(1.0f, 0.0f, 1.0f);
	p1->SetPosition(-8.0f, 12.6f);
	p1->SetRotation(1.0f);

	//Make a friend for him, and don't initialize its physics just yet either. 
	p2 = new PhysicsActor();
	p2->SetSize(1.0f);
	p2->SetColor(0.0f, 0.0f, 1.0f);
	p2->SetPosition(8.0f, 12.6f);

	//Add them all to the world. When we add them they are assigned names, which are
	// guaranteed to be unique. You can also assign your own name to any Actor with
	// SetName(), which returns the unique name it was actually given. (Numbers will 
	// be appended if the name was already taken.)
	// 
	//There's also a static function Actor::GetNamed() that you pass a string name
	// and will return either the Actor with that name or NULL. 
	theWorld.Add(p1);
	theWorld.Add(p2);
	
	//Subscribe the DemoScreen to some specific messages. We'll receive notification
	// when these messages get broadcast. Look below at the ReceiveMessage() function,
	// which is part of the MessageListener interface, to see how to handle the messages. 
	theSwitchboard.SubscribeTo(this, "ScreenStarted");
	
	//This message is interesting -- all collision messages take the form "CollisionWith"
	// plus the name of the actor colliding. Note that this means if you change the name
	// of the actor, you need to change your subscriptions if you want to hear about 
	// collisions. 
	theSwitchboard.SubscribeTo(this, "CollisionWith" + p1->GetName());
	theSwitchboard.SubscribeTo(this, "CollisionWith" + p2->GetName());

	bounceSample = theSound.LoadSample("Resources/Sounds/sprong.wav", false /*no stream*/);
}

void DemoScreenMessagePassing::Start()
{
	//Kick off one message -- it'll get physics going on this screen. 
	theSwitchboard.Broadcast(new Message("ScreenStarted"));

	//Add the ground actor so they'll have something to bounce off. 
	p3 = new PhysicsActor();
	p3->SetPosition(0.0f, -11.0f);
	p3->SetSize(30.0f, 5.0f);
	p3->SetColor(0.0f, 1.0f, 0.0f);
	p3->SetDensity(0.0f);
	p3->SetFriction(0.1f);
	p3->InitPhysics(); 

	theWorld.Add(p3);


	//Demo housekeeping below this point. 
#pragma region Demo Housekeeping
	String outputText = "These actors are responding to Messages\nthat we're sending through our central Switchboard.";
	outputText += "\n\nYou can have actors respond to and broadcast arbitrary messages,\nwhich makes it easy to handle events in your game.";
	outputText += "\n\n\n(Those actors have been hanging out up there this whole time,\nwaiting for the message that this screen had started\nbefore they dropped in.)";
	t = new TextActor("Console", outputText);
	t->SetPosition(0.0f, 3.5f);
	t->SetAlignment(TXT_Center);
	theWorld.Add(t);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenMessagePassing.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(p1);
	_objects.push_back(p2);
	_objects.push_back(p3);
#pragma endregion
}

void DemoScreenMessagePassing::ReceiveMessage(Message *message)
{
	//Respond to the ScreenStarted message that we sent when the screen started. 
	if (message->GetMessageType() == "ScreenStarted")
	{
		p1->SetDensity(0.8f);
		p1->SetFriction(0.5f);
		p1->SetRestitution(0.7f);
		p1->InitPhysics();
	}
	
	//When the first actor collides, we kick off the physics for the second actor. 
	if (message->GetMessageType() == "CollisionWith" + p1->GetName())
	{
		// Only init the physics if it isn't initialized.
		if (!p2->GetBody())
		{
			p2->SetDensity(0.8f);
			p2->SetFriction(0.5f);
			p2->SetRestitution(0.7f);
			p2->InitPhysics();
		}
		
		//In this case we want to unsubscribe from this message, since initializing the
		// physics for that actor more than once can cause "issues." Comment this line
		// out if you're curious. 
		theSwitchboard.UnsubscribeFrom(this, "CollisionWith" + p1->GetName());

		//If you need more data about the collision, collision messages always come *from*
		// the actor colliding with the one you care about, and carry a pointer to the 
		// relevant Box2D contact point, which contains more information like the normal force,
		// position, tangent, etc. 
		// 
		//You can get these from GetSender() and GetPayload(), which are generic functions on
		// every message.

		b2Vec2 vel = p1->GetBody()->GetLinearVelocity();
		if (bounceSample && fabsf(vel.y) > 5.0f)
			theSound.PlaySound(bounceSample, 1.0f, false/*no loop*/, 0);
	}
	else if (message->GetMessageType() == "CollisionWith" + p2->GetName())
	{
		b2Vec2 vel = p2->GetBody()->GetLinearVelocity();
		if (bounceSample && fabsf(vel.y) > 5.0f)
			theSound.PlaySound(bounceSample, 1.0f, false/*no loop*/, 0);
	}
}


void DemoScreenMessagePassing::Stop()
{
	DemoScreen::Stop();
	Setup();
}