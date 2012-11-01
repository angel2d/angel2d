
#include "stdafx.h"

#include "UI/UserInterface.h"

void ButtonPressed()
{
    printf("Button was pressed!\n");
}

int main(int argc, char* argv[])
{
	// get things going
	//  optional parameters:
	//		int windowWidth			default: 1024
	//		int windowHeight		default: 768
	//		std::string windowName	default: "Angel Engine"
	//		bool antiAliasing		default: false
	//		bool fullScreen			default: false
	theWorld.Initialize();
	
	//adds the default grid so you can more easily place Actors
	theWorld.Add(new GridActor(), -1);
	
	//YOUR GAME SETUP CODE HERE
	theUI.AddButton("TTT", Vec2i(100, 100), ButtonPressed);
    theUI.AddButton("Tesgt", Vec2i(100, 150), ButtonPressed);
    theUI.AddButton("gggg", Vec2i(100, 200), ButtonPressed);
    theUI.AddButton("aceors", Vec2i(100, 250), ButtonPressed);
	   

	
	
	
	
	
	
	// do all your setup first, because this function won't return until you're exiting
	theWorld.StartGame();
	
	// any cleanup can go here
	theWorld.Destroy();
	
	return 0;
}
