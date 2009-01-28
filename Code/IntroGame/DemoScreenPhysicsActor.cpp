#include "stdafx.h"
#include "DemoScreenPhysicsActor.h"


DemoScreenPhysicsActor::DemoScreenPhysicsActor()
{
}

void DemoScreenPhysicsActor::Start()
{
	p1 = new PhysicsActor();
	//PhysicsActors have all the same attributes as regular ones...
	p1->SetSize(1.0f);
	p1->SetColor(1.0f, 0.0f, 1.0f);

	//...but with a little bit of magic pixie dust
	p1->SetDensity(0.8f);
	p1->SetFriction(0.5f);
	p1->SetRestitution(0.7f);
	p1->SetShapeType(PhysicsActor::SHAPETYPE_BOX);
	p1->InitPhysics();
	//That's the basics of what we've exposed from Box2d. There's lots
	//  more to it, though, and we encourage you to check out their
	//  documentation. http://box2d.org

	p2 = new PhysicsActor();
	p2->SetPosition(0.0f, -11.0f);
	p2->SetSize(30.0f, 5.0f);
	p2->SetColor(0.0f, 1.0f, 0.0f);
	p2->SetDensity(0.0f); //no density (static)
	p2->SetFriction(0.1f); //little friction
	p2->InitPhysics(); 

	//NOTE: After you call InitPhysics, you can't directly set an Actor's
	// position or rotation -- you've turned those over to the physics engine.
	// You can't change the size, either, since that would mess up the simulation.

	theWorld.Add(p1);
	theWorld.Add(p2);





	//Demo housekeeping below this point. 
	#pragma region Demo Housekeeping
	t = new TextActor("Console", "These Actors use physics. Press [B].\n\n\n\n(Yes, the ground is an Actor.)");
	t->SetPosition(0.0f, 3.5f);
	t->SetAlignment(TXT_Center);
	theWorld.Add(t);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenPhysicsActor.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(p1);
	_objects.push_back(p2);
	#pragma endregion
}

void DemoScreenPhysicsActor::Update(float dt)
{
	if (theController.IsConnected() && theController.IsBButtonDown())
	{
		//punch it upwards
		p1->ApplyForce(Vector2(0, 20.0f), Vector2());
	}
}
