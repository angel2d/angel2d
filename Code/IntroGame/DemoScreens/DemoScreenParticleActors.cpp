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
#include "DemoScreenParticleActors.h"


DemoScreenParticleActors::DemoScreenParticleActors()
{
	_isActive = false;
}

void DemoScreenParticleActors::Start()
{
	pa = new ParticleActor();
	pa->SetColor(1.0f, 1.0f, 1.0f);  //Sets the initial color of the particles. 
									 // Since the image file we'll be using already
									 // has a color, we set this to pure white. 
	
	pa->SetSize(Vector2(0.2f, 0.2f)); //The size of each particle, in GL units
	pa->SetSprite("Resources/Images/Test.png"); //The image file we want to use (otherwise 
												// it'll just be colored squares).
	pa->SetMaxParticles(500); //The maximum number of particles this system will ever handle. 
	pa->SetParticlesPerSecond(100.0f); //Emission Rate
	pa->SetParticleLifetime(1.5f); //How long each particles lasts before disappearing
	pa->SetSpread(MathUtil::Pi); //The angle in radians at which particles will be emitted. 
	pa->SetEndScale(2.0f); //If you want the particles to change size over their lifetimes
	pa->SetEndColor(Color(1.0f, 1.0f, 1.0f, 0.0f)); //Our particles disappear over time
	pa->SetSpeedRange(3.0f, 4.0f); //The minimum and maximum range of speeds (so you can have
								   // some variation).
	pa->SetGravity(Vector2::Zero); //You can pull the particles in a particular direction (default is
								   // downwards, so zero it out if you need to).
	theWorld.Add(pa);

	_isActive = true; //lets the mouse events know that they should care

	//Demo housekeeping below this point. 
	#pragma region Demo Housekeeping
	t = new TextActor("Console", "Here's a ParticleActor. (Try moving and clicking the mouse!)");
	t->SetPosition(0, 3.5);
	t->SetAlignment(TXT_Center);
	theWorld.Add(t);
	t2 = new TextActor("Console", "Press [B] to change its properties.");
	t2->SetPosition(0, 2.5);
	t2->SetAlignment(TXT_Center);
	theWorld.Add(t2);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenParticleActors.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(t2);
	_objects.push_back(pa);
	#pragma endregion
}

void DemoScreenParticleActors::Update(float dt)
{
	//This is the same kind of input processing we did in DemoScreenSimpleActor.cpp,
	//  but here we're playing with various properties of the particles. 
	if ((theController.IsConnected() && theController.IsBButtonDown()) || theInput.IsKeyDown('b'))
	{
		pa->SetColor(1.0f, 0.0f, 0.0f, .25f);
		pa->SetSize(0.5f, 0.5f);
		pa->SetGravity( Vector2::Zero );
		pa->ClearSpriteInfo();
		t->SetDisplayString("Now it's red and translucent. Press [Y].");
		t2->SetDisplayString("");
	}
	if ((theController.IsConnected() && theController.IsYButtonDown()) || theInput.IsKeyDown('y'))
	{
		pa->SetColor(0,0,1,1); 		
		pa->SetSize(0.5f, 0.5f);
		Vector2 grav = Vector2(0.0f, -8.0f);
		pa->SetGravity( grav );
		pa->ClearSpriteInfo();
		t->SetDisplayString("Now it's blue and has density. Press [X] for the coolest thing ever.");
		t2->SetDisplayString("");
	}
	if ((theController.IsConnected() && theController.IsXButtonDown()) || theInput.IsKeyDown('x'))
	{
		pa->SetSize(4.0f, 4.0f);
		pa->SetColor(1,1,1,1);
		pa->SetGravity( Vector2::Zero );
		pa->LoadSpriteFrames("Resources/Images/numbers/angel_01.png");
		pa->PlaySpriteAnimation(0.5f, SAT_Loop, 0, 4);

		t->SetDisplayString("That's right, animated textures. You love it.");
		t2->SetDisplayString("");
	}
}

void DemoScreenParticleActors::MouseMotionEvent(Vec2i screenCoordinates)
{
	if (_isActive) //we only want to move around if this screen is currently active
	{
		pa->SetPosition(MathUtil::ScreenToWorld(screenCoordinates.X, screenCoordinates.Y));
	}
}

void DemoScreenParticleActors::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button)
{
	if (_isActive)
	{
		// Create the particle actor via the Actor Definition system
		ParticleActor *oneOff = (ParticleActor*)Actor::Create("particle_demo");
		if (oneOff)
		{
			// Note we can still change properties of actors loaded as definitions
			oneOff->SetColor(0, 0, 1);
			oneOff->SetSprite("Resources/Images/triangle.png");
			//We can set the position to where the mouse click happened.
			oneOff->SetPosition(MathUtil::ScreenToWorld(screenCoordinates.X, screenCoordinates.Y));

			//The system will remove itself from the world and deallocate its memory
			//  when the lifetime ends. (If it's 0.0, it's assumed to be infinite.)
			oneOff->SetSystemLifetime(1.0f);
			
			//Make sure to add it to the world!
			theWorld.Add(oneOff);
		}
	}
}

void DemoScreenParticleActors::Stop()
{
	DemoScreen::Stop();

	// Now that DemoScreen cleaned up...
	_isActive = false;
}
