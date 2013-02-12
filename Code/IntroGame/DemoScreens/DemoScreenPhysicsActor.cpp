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
	p1->InitPhysics(); // Note that none of the actor's physics are being 
	                   //  simulated until this call.

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
	if ((theController.IsConnected() && theController.IsBButtonDown()) || (theInput.IsKeyDown('b')))
	{
		//punch it upwards
		p1->ApplyForce(Vector2(0, 700.0f) * dt, Vector2());
	}
}
