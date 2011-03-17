// This file is only relevant to the iPhone build of Angel. If you're building
//  a desktop app, you can ignore it. 


#include "iPhoneMain.h"

#include "DemoGameManager.h"

// This function is called by the iPhone setup process -- it's put here
//  so that you don't have to slog through a bunch of Objective-C UI code
//  if you don't want to. 
void AngelGameInit()
{
	//add the default grid so we can see where our Actors are in the world
	theWorld.Add(new GridActor());
	
	//theDemoGame is our DemoGameManager singleton
	// all the cool stuff happens there -- check it out. 
	theWorld.SetGameManager(&theDemoGame);
}
