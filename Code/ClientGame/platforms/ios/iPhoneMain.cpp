// This file is only relevant to the iPhone build of Angel. If you're building
//  a desktop app, you can ignore it. 


#include "iPhoneMain.h"


// This function is called by the iPhone setup process -- it's put here
//  so that you don't have to slog through a bunch of Objective-C UI code
//  if you don't want to. 
void AngelGameInit()
{
	//adds a grid so you can more easily place Actors
	GridActor *g = new GridActor();
	g->SetMinCoord(Vector2(-20, -15));
	g->SetMaxCoord(Vector2( 20,  15));
	theWorld.Add(g, -1);
	
	
	
	//YOUR GAME SETUP CODE HERE
	
	
	
	
	
	
	
}
