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
#include "DemoGameManager.h"

#if !ANGEL_MOBILE
	#include "DemoScreenStart.h"
	#include "DemoScreenInstructions.h"
	#include "DemoScreenSimpleActor.h"
	#include "DemoScreenMovingActor.h"
	#include "DemoScreenIntervals.h"
	#include "DemoScreenPhysicsActor.h"
	#include "DemoScreenDefFile.h"
	#include "DemoScreenLevelFile.h"
	#include "DemoScreenConsole.h"
	#include "DemoScreenByeBye.h"
	#include "DemoScreenRenderLayers.h"
	#include "DemoScreenBindingInstructions.h"
	#include "DemoScreenLayeredCollisionLevelFile.h"
	#include "DemoScreenParticleActors.h"
	#include "DemoScreenMessagePassing.h"
	#include "DemoScreenMultipleControllers.h"
	#include "DemoScreenControllerInstructions.h"
	#include "DemoScreenTuningVariables.h"
	#include "DemoScreenImageMap.h"
	#include "DemoScreenPathfinding.h"
	#include "DemoScreenUI.h"
#endif

#include "DemoScreenMobileSimulator.h"

DemoScreen::DemoScreen() {}

void DemoScreen::Start(){}

void DemoScreen::Stop()
{
	std::vector<Renderable*>::iterator it = _objects.begin();
	while(_objects.end() != it)
	{
		// we're pre-destroying physics bodies here because it 
		//  can mess with the pathfinding regeneration.
		PhysicsActor* pa = dynamic_cast<PhysicsActor*> (*it);
		if (pa != NULL)
		{
			if (pa->GetBody() != NULL)
			{
				pa->GetBody()->SetUserData(NULL);
				theWorld.GetPhysicsWorld().DestroyBody(pa->GetBody());
				pa->ResetBody();
			}
		}
		(*it)->Destroy();
		it++;
	}
	_objects.clear();
}

void DemoScreen::Update(float dt) {}
void DemoScreen::Render() {}



DemoGameManager* DemoGameManager::s_DemoGameManager = NULL;

DemoGameManager::DemoGameManager()
{	
	//subscribe to messages
	theSwitchboard.SubscribeTo(this, "MoveForwards");
	theSwitchboard.SubscribeTo(this, "MoveBackwards");
	
	#if ANGEL_MOBILE
		_screens.push_back(new DemoScreenMobileSimulator());				// 0
	#else
		_screens.push_back(new DemoScreenStart());							// 0
		_screens.push_back(new DemoScreenInstructions());					// 1
		_screens.push_back(new DemoScreenSimpleActor());					// 2
		_screens.push_back(new DemoScreenRenderLayers());					// 3
		_screens.push_back(new DemoScreenControllerInstructions());			// 4
		_screens.push_back(new DemoScreenMovingActor());					// 5
		_screens.push_back(new DemoScreenMultipleControllers());			// 6
		_screens.push_back(new DemoScreenMobileSimulator());				// 7
		_screens.push_back(new DemoScreenDefFile());						// 8
		_screens.push_back(new DemoScreenLevelFile());						// 9
		_screens.push_back(new DemoScreenBindingInstructions());			//10
		_screens.push_back(new DemoScreenParticleActors());					//11
		_screens.push_back(new DemoScreenPhysicsActor());					//12
		_screens.push_back(new DemoScreenMessagePassing());					//13
		_screens.push_back(new DemoScreenIntervals());						//14
		_screens.push_back(new DemoScreenLayeredCollisionLevelFile());		//15
		_screens.push_back(new DemoScreenConsole());						//16
		_screens.push_back(new DemoScreenUI());								//17
		_screens.push_back(new DemoScreenTuningVariables());				//18
		_screens.push_back(new DemoScreenPathfinding());					//19
		_screens.push_back(new DemoScreenImageMap());						//20
		_screens.push_back(new DemoScreenByeBye());							//21
	#endif

	unsigned int startingIndex = 0;
	if (_screens.size() > startingIndex)
	{
		theWorld.Add(_screens[startingIndex]);
		_screens[startingIndex]->Start();
		_current = startingIndex;
	}
	else
	{
		_current = -1;
	}
	
	// We must set the sound callback method.  Although, I'm wondering if we should 
	// allow them to not specify it if they don't need the functionality.
	theSound.SetSoundCallback(this, &GameManager::SoundEnded);
	
	sample = theSound.LoadSample("Resources/Sounds/click.ogg", false /*no stream*/);
}

DemoGameManager& DemoGameManager::GetInstance()
{
	if (s_DemoGameManager == NULL)
	{
		s_DemoGameManager = new DemoGameManager();
	}
	return *s_DemoGameManager;
}

DemoScreen* DemoGameManager::GetCurrentScreen()
{
	return _screens[_current];
}

void DemoGameManager::ReceiveMessage(Message* message)
{
	if (message->GetMessageName() == "MoveForwards")
	{
		MoveForwards();
	}
	else if (message->GetMessageName() == "MoveBackwards")
	{
		MoveBackwards();
	}
}

void DemoGameManager::MoveForwards()
{
	if ((_current >= 0) && (_current < (int)_screens.size() - 1))
	{
		_screens[_current]->Stop();
		theWorld.Remove(_screens[_current]);
		_screens[++_current]->Start();
		theWorld.Add(_screens[_current]);
		
		if (sample)
			theSound.PlaySound(sample, 1.0f, false/*no loop*/, 0);
	}
}

void DemoGameManager::MoveBackwards()
{
	if (_current > 0)
	{
		_screens[_current]->Stop();
		theWorld.Remove(_screens[_current]);
		_screens[--_current]->Start();
		theWorld.Add(_screens[_current]);
		
		if (sample)
			theSound.PlaySound(sample, 1.0f, false/*no loop*/, 0);
	}
}

void DemoGameManager::Render()
{
	glColor3f(0.5f, 0.5f, 0.5f);
	char* infoString = "";
	int xOffset = 0;
	if (_current == 0)
	{
		infoString = "[A/Space]: Next";
		xOffset = 887;
	}
	else if (_current == _screens.size() - 1)
	{
		infoString = "[Back/Minus]: Previous";
		xOffset = 824;
	}
	else
	{
		infoString = "[A/Space]: Next [Back/Minus]: Previous";
		xOffset = 680;
	}
	
	int yOffset = 763;
	if (theWorld.IsHighResScreen())
	{
		// the perils of using pixel coordinates in a post-retina world
		xOffset *= 2;
		yOffset *= 2;
	}
	
	DrawGameText(infoString, "ConsoleSmall", xOffset, yOffset);
}

void DemoGameManager::SoundEnded(AngelSoundHandle sound)
{	
	// Detect sounds that have ended here.
}
