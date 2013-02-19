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
#include "DemoScreenUI.h"



AngelUIHandle DemoScreenUI::_choiceBox = NULL;
TextActor* DemoScreenUI::_output = NULL;

DemoScreenUI::DemoScreenUI()
{
}

void ChoiceMade(int choice)
{
	String out = "";
	if (choice == 0)
	{
		out = "You pressed the first button.";
		DemoScreenUI::_output->SetColor(1.0f, 0.0f, 0.0f);
	}
	else if (choice == 1)
	{
		out = "You pressed the second button.";
		DemoScreenUI::_output->SetColor(0.0f, 1.0f, 0.0f);
	}
	else if (choice == 2)
	{
		out = "You pressed the third button.";
		DemoScreenUI::_output->SetColor(0.0f, 0.0f, 1.0f);
	}
	else
	{
		out = "Ummm.... this shouldn't happen. Should be impossible.";
	}
	
	DemoScreenUI::_output->SetDisplayString(out);
}

void ButtonPress()
{
	// We want to bring up a choice list here.
	
	// First we construct a list of the labels that will go on the buttons.
	StringList labels;
	labels.push_back("Option 1");
	labels.push_back("Option 2");
	labels.push_back("A longer option with more text");
	
	DemoScreenUI::_choiceBox = theUI.ShowChoiceBox(
						"A choice!", // The title on the choice box
						labels, // The list of labels we just constructed
						ChoiceMade 	// The function that will be called when one of the buttons is pressed.
									//   Must return void and take a single integer as a parameter. That
									//   integer will be the index of the clicked button.
						);
	
	// Note that a choice box will remove itself once one of its buttons is clicked, so you
	//   don't have to track its handle unless you want to remove it manually.
}

void DemoScreenUI::Start()
{
	/*AngelUIHandle*/ _button =	// AngelUIHandle is an opaque type that's returned from Angel UI functions.
								//   After you create a button, in this instance, you'll need to hang on to
								//   this handle so you can use it to remove the button later. (See the Stop()
								//   method at the bottom of this file for an example.)
		theUI.AddButton(
						"Press this to bring up a choice box.", // The label for the button
						Vec2i(512, 300), // The position of the button (note that it's in pixels)
						ButtonPress, // The function that will be called when the button is pressed.
									 //   It must return void and take no parameters.
						true		// Whether or not to center the button around the given position. If false,
									//   the position will be the buttons top left corner. 
						);



	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	TextActor *t = new TextActor("Console", "Angel has some basic GUI features to make your prototyping easier.");
	t->SetPosition(0, 5.5);
	t->SetAlignment(TXT_Center);
	theWorld.Add(t);
	TextActor *t2 = new TextActor("Console", "(It's based on the GWEN UI toolkit, so if you need\nfancier UI functionality it's all there.\nhttp://gwen.googlecode.com)");
	t2->SetPosition(0, -5.5);
	t2->SetAlignment(TXT_Center);
	theWorld.Add(t2);
	_output = new TextActor("Console", "");
	_output->SetPosition(0, -2.5);
	_output->SetAlignment(TXT_Center);
	theWorld.Add(_output);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenUI.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(t2);
	#pragma endregion
}

void DemoScreenUI::Stop()
{
	theUI.RemoveUIElement(_button);
	theUI.RemoveUIElement(DemoScreenUI::_choiceBox);
	theWorld.Remove(_output);
	
	DemoScreen::Stop();
}
