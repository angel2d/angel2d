//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2010, Shane J. M. Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//	   * Redistributions of source code must retain the above copyright 
//		 notice, this list of conditions and the following disclaimer.
//	   * Redistributions in binary form must reproduce the above copyright 
//		 notice, this list of conditions and the following disclaimer in the 
//		 documentation and/or other materials provided with the distribution.
//	   * Neither the name of the copyright holder nor the names of any 
//		 contributors may be used to endorse or promote products derived from 
//		 this software without specific prior written permission.
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
#include "DemoScreenTuningVariables.h"

DemoScreenTuningVariables::DemoScreenTuningVariables()
{
}

void DemoScreenTuningVariables::Update(float dt)
{
	// Tuning Variables are defined in the Config/tuning.ini file. We can
	//  access them at runtime by passing their name to theTuning singleton.
	//  If you pass the name for a non-existant tuning variable, you'll get 
	//  a reasonable default (0 for ints, 0.0f for floats, an empty string, and
	//  a zero-length vector.)
	float bouncePeriod = theTuning.GetFloat("BouncePeriod");
	
	float p = MathUtil::Clamp(bouncePeriod, 0.00001f, 1000000.f);
	float t = MathUtil::TwoPi * theWorld.GetCurrentTimeSeconds() / p;
	
	a->SetSize(0.5f + MathUtil::Abs(theTuning.GetFloat("BounceSize") * sin(0.5f*t))); // halve t since we are using abs
	a->SetPosition(theTuning.GetFloat("BounceDist") * cos(0.5f*t), 0.f);
}

void DemoScreenTuningVariables::Start()
{
	// You can declare tuning variables at runtime as well. When you save
	//  out the values by called SaveTuningVariables() from the console, they
	//  will be written to the file. 
	theTuning.SetFloat("BounceSize", 5.3f);
	theTuning.SetFloat("BounceDist", 5.2f);
	
	//Place the actor from a definition file
	a = Actor::Create("simple_actor");
	theWorld.Add(a);
	
	
	
	
	
	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	String explanation = "This demo shows off tuning variables.";
	explanation += "\nTuning variables can be edited in the console, written/read";
	explanation += "\nvia ini files, and are accessible to C++ as well as Python.";
	explanation += "\nOpen the console (~) and enter \"tune('BounceSize', 14.0)\".";
	explanation += "\nThis screen also uses variables \"BouncePeriod\" and \"BounceDist\".";
	explanation += "\nTry changing them!";
	explanation += "\n\nTake a gander at the C++ source and the tuning.ini\nfile to see how they are defined and used.";
	t = new TextActor("Console", explanation);
	t->SetPosition(0, -3.5f);
	t->SetAlignment(TXT_Center);
	theWorld.Add(t);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenTuningVariables.cpp, tuning.ini, demo_actors.ini");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(a);
	#pragma endregion
}
