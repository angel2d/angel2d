//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2009, Shane J. M. Liesegang
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

#include "StdAfx.h"
#include "DemoGameManager.h"


#include "DemoScreenStart.h"
#include "DemoScreenInstructions.h"
#include "DemoScreenSimpleActor.h"
#include "DemoScreenMovingActor.h"
#include "DemoScreenIntervals.h"
#include "DemoScreenPhysicsActor.h"
#include "DemoScreenDefFile.h"
#include "DemoScreenLevelFile.h"
#include "DemoScreenCollisionLevelFile.h"
#include "DemoScreenConsole.h"
#include "DemoScreenByeBye.h"
#include "DemoScreenRenderLayers.h"
#include "DemoScreenBindingInstructions.h"
#include "DemoScreenLayeredCollisionLevelFile.h"
#include "DemoScreenParticleActors.h"
#include "DemoScreenMessagePassing.h"
#include "DemoScreenPathfinding.h"
#include "DemoScreenMultipleControllers.h"

DemoScreen::DemoScreen() {}

void DemoScreen::Start(){}

void DemoScreen::Stop()
{
	std::vector<Renderable*>::iterator it = _objects.begin();
	while(_objects.end() != it)
	{
		theWorld.Remove(*it);
		delete *it;
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

	_screens.push_back(new DemoScreenStart());							// 0
	_screens.push_back(new DemoScreenInstructions());					// 1
	_screens.push_back(new DemoScreenSimpleActor());					// 2
	_screens.push_back(new DemoScreenRenderLayers());					// 3
	_screens.push_back(new DemoScreenMovingActor());					// 4
	_screens.push_back(new DemoScreenMultipleControllers());			// 5
	_screens.push_back(new DemoScreenDefFile());						// 6
	_screens.push_back(new DemoScreenLevelFile());						// 7
	_screens.push_back(new DemoScreenBindingInstructions());			// 8
	_screens.push_back(new DemoScreenParticleActors());					// 9
	_screens.push_back(new DemoScreenPhysicsActor());					//10
	_screens.push_back(new DemoScreenMessagePassing());					//11
	_screens.push_back(new DemoScreenIntervals());						//12
	_screens.push_back(new DemoScreenCollisionLevelFile());				//13
	_screens.push_back(new DemoScreenLayeredCollisionLevelFile());		//14
	_screens.push_back(new DemoScreenConsole());						//15
	_screens.push_back(new DemoScreenPathfinding());					//16
	_screens.push_back(new DemoScreenByeBye());							//17

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
		infoString = "[A]: Next ";
		xOffset = 925;
	}
	else if (_current == _screens.size() - 1)
	{
		infoString = "[Back]: Previous";
		xOffset = 870;
	}
	else
	{
		infoString = "[A]: Next [Back]: Previous";
		xOffset = 785;
	}
	DrawGameText(infoString, "ConsoleSmall", xOffset, 763);
}

void DemoGameManager::SoundEnded(SOUND_HANDLE sound)
{	
	// Detect sounds that have ended here.	
}
