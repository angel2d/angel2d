//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2010, Shane J. M. Liesegang
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
#include "DemoScreenPathfinding.h"

class MazeFinder;

DemoScreenPathfinding::DemoScreenPathfinding()
{
}

void DemoScreenPathfinding::Start()
{
	//Set up our obstacle course
	theWorld.LoadLevel("maze");
	
	//Create the bounding box that will limit the pathfinding search area
	BoundingBox bounds(Vector2(-20, -20), Vector2(20, 20));
	
	//Create our pathfinding graph. In our 2D worlds, this is a relatively fast
	// operation -- you shouldn't be doing it every frame, but recalculating every
	// so often if your world has changed is not inappropriate. 
	theSpatialGraph.CreateGraph(
		0.75f, //The size of the entity you want to pathfind (so the generator
		       //  can know how small a space can be and still have it fit.)
		bounds //The search area
	);
	
	//Create a MazeFinder (class definition below), and put him in the bottom
	//  left corner of the maze
	MazeFinder *mf = new MazeFinder();
	mf->SetPosition(-11.5, -8);
	theWorld.Add(mf);
	
	//Send him to the upper right, watch him scurry
	mf->GoTo(Vector2(11.5, 8));
	
	
	
	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	String description = "This little dude is pathfinding through the area.";
	description += "\n\nClick the mouse to give him a new target.";
	description += "\n\nPress [B] to see the pathfinding graph.";
	TextActor *t = new TextActor("Console", description);
	t->SetAlignment(TXT_Center);
	t->SetPosition(0.0f, -5.0f);
	theWorld.Add(t);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenPathfinding.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	_objects.push_back(mf);
	ActorSet walls = theTagList.GetObjectsTagged("maze_wall");
	ActorSet::iterator it = walls.begin();
	while (it != walls.end())
	{
		_objects.push_back(*it);
		it++;
	}
	#pragma endregion
}

void DemoScreenPathfinding::Update(float dt)
{
	if ((theController.IsConnected() && theController.IsBButtonDown()) || theInput.IsKeyDown('b'))
	{
		theSpatialGraph.EnableDrawGraph(true);
	}
	else
	{
		theSpatialGraph.EnableDrawGraph(false);
	}
}

void DemoScreenPathfinding::Stop()
{
	theSpatialGraph.EnableDrawGraph(false);
	DemoScreen::Stop();
}

void DemoScreenPathfinding::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button)
{
	TypedMessage<Vec2i> *m = new TypedMessage<Vec2i>("MouseDown", screenCoordinates);
	theSwitchboard.Broadcast(m);
}

MazeFinder::MazeFinder()
{
	SetColor(1, 0, 0);
	SetSize(0.75f);
	SetDrawShape(ADS_Circle);
	theSwitchboard.SubscribeTo(this, "MazeFinderPathPointReached");
	theSwitchboard.SubscribeTo(this, "MouseDown");
	_pathIndex = 0;
}

void MazeFinder::GoTo(Vector2 newDestination)
{
	Vector2List pathTest;
	theSpatialGraph.GetPath(GetPosition(), newDestination, pathTest);
	
	if (pathTest.size() > 0)
	{
		_pathPoints = pathTest;
		_pathIndex = 0;
		GetToNextPoint();
	}
}

void MazeFinder::ReceiveMessage(Message *message)
{
	if (message->GetMessageName() == "MazeFinderPathPointReached")
	{
		if (_pathIndex < _pathPoints.size() - 1)
		{
			GetToNextPoint();
		}
	}
	else if (message->GetMessageName() == "MouseDown")
	{
		TypedMessage<Vec2i> *m = (TypedMessage<Vec2i>*)message;
		Vec2i screenCoordinates = m->GetValue();
		Vector2 worldCoordinates = MathUtil::ScreenToWorld(screenCoordinates);
		GoTo(worldCoordinates);
	}
}

void MazeFinder::GetToNextPoint()
{
	Vector2 next = _pathPoints[++_pathIndex];
	float distance = Vector2::Distance(_position, next);
	//Want this guy to move at a constant rate of 8.0 units per second
	float time = distance / 8.0f;
	MoveTo(next, time, false, "MazeFinderPathPointReached");
}

