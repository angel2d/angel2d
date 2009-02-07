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

DemoScreen::DemoScreen() {}

void DemoScreen::Start(){}

void DemoScreen::Stop()
{
	std::vector<Renderable*>::iterator it = _objects.begin();
	while(_objects.end() != it)
	{
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

	_screens.push_back(new DemoScreenStart());							// 0
	_screens.push_back(new DemoScreenInstructions());					// 1
	_screens.push_back(new DemoScreenSimpleActor());					// 2
	_screens.push_back(new DemoScreenRenderLayers());					// 3
	_screens.push_back(new DemoScreenMovingActor());					// 4
	_screens.push_back(new DemoScreenDefFile());						// 5
	_screens.push_back(new DemoScreenLevelFile());						// 6
	_screens.push_back(new DemoScreenBindingInstructions());			// 7
	_screens.push_back(new DemoScreenParticleActors());					// 8
	_screens.push_back(new DemoScreenPhysicsActor());					// 9
	_screens.push_back(new DemoScreenMessagePassing());					//10
	_screens.push_back(new DemoScreenIntervals());						//11
	_screens.push_back(new DemoScreenCollisionLevelFile());				//12
	_screens.push_back(new DemoScreenLayeredCollisionLevelFile());		//13
	_screens.push_back(new DemoScreenConsole());						//14
	_screens.push_back(new DemoScreenPathfinding());					//15
	_screens.push_back(new DemoScreenByeBye());							//16

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
	if (message->GetMessageType() == "MoveForwards")
	{
		MoveForwards();
	}
	else if (message->GetMessageType() == "MoveBackwards")
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
