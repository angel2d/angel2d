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
#include "DemoScreenImageMap.h"


DemoScreenImageMap::DemoScreenImageMap()
{
	theSwitchboard.SubscribeTo(this, "MazeFinderEndPointReached");
}

void DemoScreenImageMap::Start()
{
	// This screen is all about showing off the PixelsToPositions function. While 
	//  the level loading system we previously showed off works pretty well for
	//  simple layouts, more complicated scenes often benefit from being able to
	//  visualize them as you're laying them out. 
	//
	// The PixelsToPositions function reads in an image, scans it for pixels of a
	//  specific color, and fills a passed Vector2List with the positions of
	//  those pixels. You can assign colors to specific actor types, author a
	//  layout using an image editor like Photoshop, GIMP, or Paint.NET.

	Vector2List positions;
	if (
		PixelsToPositions(
			"./Resources/Images/map.png",  // The file to analyze. This can be
										   //  in any file format that Angel
										   //  understands, but works most reliably
										   //  with images that do not include 
										   //  transparency. PNG and other lossless
										   //  formats are recommended, as they 
										   //  provide pixel-perfect reproduction.
			positions, // The vector to fill with positions
			1.0f, 	   // The scale to multiply the found positions by to make
					   //  translating into world coordinates easier
			Color(0.0f, 0.0f, 0.0f) // The color to seek (black in this case)
		)
	)
	{
		for(unsigned int i=0; i < positions.size(); i++)
		{
			// Loop over the found positions, place an immovable wall at each
			//  spot. 
			PhysicsActor *wallPiece = new PhysicsActor();
			wallPiece->SetColor(0.5f, 0.5f, 0.8f);
			wallPiece->SetPosition(positions[i] + Vector2(0.5f, 0.5f));
			wallPiece->SetDensity(0.0f);
			wallPiece->InitPhysics();
			wallPiece->Tag("wall-piece");
			theWorld.Add(wallPiece);
		}
	}
	
	// Generate the pathfinding graph, as seen in the previous screen. 
	//  Note that because our usage of the image map resulted in lots of small
	//  objects to path around, the graph takes longer to generate than it did
	//  on the previous screen.
	BoundingBox bounds(Vector2(-20, -20), Vector2(20, 20));
	theSpatialGraph.CreateGraph(0.5f, bounds);
	
	// Now find all the blue pixels
	PixelsToPositions("./Resources/Images/map.png", _availableTargets, 1.0f, Color(0.0f, 0.0f, 1.0f));
	for(unsigned int i=0; i < _availableTargets.size(); i++)
	{
		// Store each of these positions as a potential target for our little
		//  navigators. 
		_availableTargets[i] = _availableTargets[i] + Vector2(0.5f, 0.5f);
	}
	
	// Finally, we look for red pixels, and place a maze finder at each one. 
	positions.clear();
	if (PixelsToPositions("./Resources/Images/map.png", positions, 1.0f, Color(1.0f, 0.0f, 0.0f)))
	{
		for(unsigned int i=0; i < positions.size(); i++)
		{
			MazeFinder* mf = new MazeFinder();
			mf->SetPosition(positions[i] + Vector2(0.5f, 0.5f));
			mf->SetSize(0.5f);
			mf->Tag("maze-finder");
			theWorld.Add(mf);
			
			// send him on his merry way
			PickNewTarget(mf);
		}
	}

	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	String description = "These little busybodies are also \n";
	description += "pathfinding around a maze. But this \n";
	description += "time the walls, red guys, and their \n";
	description += "targets were all placed by interpreting \n";
	description += "an image map. It can be a lot easier \n";
	description += "to do visual layout of spaces this way.\n\n";
	description += "Press [B] to see the image that was\n";
	description += "used to generate this space.";
	TextActor *t = new TextActor("Console", description);
	t->SetAlignment(TXT_Left);
	t->SetPosition(-4.5f, -2.0f);
	theWorld.Add(t);
	Actor *image = new Actor();
	image->SetPosition(-3.0f, 3.0f);
	image->SetSize(Vector2(4.9f, 3.5f));
	image->SetSprite("Resources/Images/map.png", 0, GL_CLAMP, GL_NEAREST);
	image->SetAlpha(0.0f);
	image->SetName("ImageMap");
	theWorld.Add(image);
	_objects.push_back(image);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenImageMap.cpp, map.png");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	ActorSet pieces = theTagList.GetObjectsTagged("wall-piece");
	ActorSet::iterator it = pieces.begin();
	while (it != pieces.end())
	{
		_objects.push_back(*it);
		it++;
	}
	ActorSet finders = theTagList.GetObjectsTagged("maze-finder");
	it = finders.begin();
	while (it != finders.end())
	{
		_objects.push_back(*it);
		it++;
	}
	#pragma endregion
}

void DemoScreenImageMap::PickNewTarget(MazeFinder* mf)
{
	// Send the maze finder to a new point. 
	int index = MathUtil::RandomInt(_availableTargets.size());
	Vector2List::iterator it = _availableTargets.begin();
	it += index;
		
	mf->GoTo(*it);

	_availableTargets.erase(it);
}

void DemoScreenImageMap::ReceiveMessage(Message* m)
{
	if ( ((DemoGameManager*)theWorld.GetGameManager())->GetCurrentScreen() != this)
	{
		return;
	}

	// Set the red dudes off to a new place when they reach the end
	//  of their paths. 
	if (m->GetMessageName() == "MazeFinderEndPointReached")
	{
		MazeFinder *mf = (MazeFinder*)m->GetSender();
		Vector2 currPos = mf->GetPosition();
		PickNewTarget(mf);
		_availableTargets.push_back(currPos);
	}
}

void DemoScreenImageMap::Stop()
{
	_availableTargets.clear();
	DemoScreen::Stop();
}

void DemoScreenImageMap::Update(float dt)
{
	Actor* image = Actor::GetNamed("ImageMap");
	if ((theController.IsConnected() && theController.IsBButtonDown()) || theInput.IsKeyDown('b'))
	{
		image->SetAlpha(1.0f);
	}
	else 
	{
		image->SetAlpha(0.0f);
	}

}
