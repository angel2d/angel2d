
#include "stdafx.h"


void ButtonPressed()
{
   sysLog.Printf("Button was pressed!");
}

void ChoiceMade(int button)
{
	sysLog.Printf("Pressed button %i", button);
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
	//AngelUIHandle button = theUI.AddButton("Test Button", Vec2i(100, 100), ButtonPressed);
//    theUI.RemoveUIElement(button);
	StringList labels;
	labels.push_back("Test 1");
	labels.push_back("Test 2");
	labels.push_back("");
	labels.push_back("A longer one with more text");
	theUI.ShowChoiceBox(labels, Vec2i(100, 100), ChoiceMade);

	
	
	
	
	
	
	// do all your setup first, because this function won't return until you're exiting
	theWorld.StartGame();
	
	// any cleanup can go here
	theWorld.Destroy();
	
	return 0;
}
