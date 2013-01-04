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
			   // IMPORTANT NOTE: If this number is made smaller, the resuling 
			   //  graph will be tighter, but take longer to generate. This
			   //  difference is magnified in debug mode and, within reasonable
			   //  sizes, is negligible when building for release. When creating
			   //  your own games, this may be a variable worth tuning. 
		bounds //The search area
	);
	
	//MazeFinder is a class that we've defined in IntroGame (as opposed to the
	// Angel library itself). In order to use it as an actor definition (and 
	// subsequently a level file), we have to let the scripting layer know about it.
	// The file scripting_interface.i will get pulled in by SWIG when it creates the
	// wrappings for Lua. Take a look there for instructions on how to get your own
	// classes into the scripts. 
	MazeFinder* mf = (MazeFinder*)Actor::GetNamed("RedRunner");
	if (mf != NULL)
	{
		mf->GoTo(Vector2(11.5, 8));
	}
	
	
	//Demo housekeeping below this point. 
	#pragma region Demo housekeeping
	String description = "This little dude is pathfinding through the area.";
	description += "\n\nClick the mouse to give him a new target.";
	description += "\n\nPress [B] to see the pathfinding graph";
	description += "\nor [Y] to see the current planned path.";
	TextActor *t = new TextActor("Console", description);
	t->SetAlignment(TXT_Center);
	t->SetPosition(0.0f, -5.0f);
	theWorld.Add(t);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenPathfinding.cpp, script_interface.i");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(t);
	ActorSet walls = theTagList.GetObjectsTagged("maze_wall");
	ActorSet::iterator it = walls.begin();
	while (it != walls.end())
	{
		_objects.push_back(*it);
		it++;
	}
	_objects.push_back(mf);
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
	
	MazeFinder* mf = (MazeFinder*)Actor::GetNamed("MazeFinder");
	if (mf != NULL)
	{
		if ((theController.IsConnected() && theController.IsYButtonDown()) || theInput.IsKeyDown('y'))
		{	
			mf->ToggleDrawPath(true);
		}
		else
		{
			mf->ToggleDrawPath(false);
		}
	}
}

void DemoScreenPathfinding::Stop()
{
	theSpatialGraph.EnableDrawGraph(false);
	DemoScreen::Stop();
}

void DemoScreenPathfinding::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button)
{
	if ( ((DemoGameManager*)theWorld.GetGameManager())->GetCurrentScreen() != this)
	{
		return;
	}
	TypedMessage<Vec2i> *m = new TypedMessage<Vec2i>("MouseDown", screenCoordinates);
	theSwitchboard.Broadcast(m);	
}



//Implementation of our AI to move through the maze towards specified points using A*.
MazeFinder::MazeFinder()
{
	SetColor(1, 0, 0);
	SetSize(0.75f);
	SetDrawShape(ADS_Circle);
	theSwitchboard.SubscribeTo(this, "MazeFinderPathPointReached");
	theSwitchboard.SubscribeTo(this, "MouseDown");
	_pathIndex = 0;
	_drawPath = false;
}

void MazeFinder::GoTo(Vector2 newDestination)
{
	Vector2List pathTest;

	//GetPath() fills the pathTest variable with a sequence of valid points
	// which make up the path from start to end. 
	// All that's left for us to do is follow them. 
	theSpatialGraph.GetPath(GetPosition(), newDestination, pathTest);
	
	if (pathTest.size() > 0)
	{
		_pathPoints = pathTest;
		_pathIndex = 0;
		GetToNextPoint();
	}
}

//Called at the start and every point in between to set up the movement to our
// next point in the path.
void MazeFinder::GetToNextPoint()
{
	Vector2 next = _pathPoints[++_pathIndex];
	float distance = Vector2::Distance(_position, next);
	//Want this guy to move at a constant rate of 8.0 units per second
	float time = distance / 8.0f;
	MoveTo(next, time, false, "MazeFinderPathPointReached");
}

void MazeFinder::ReceiveMessage(Message *message)
{
	// Well get this PointReached message every time we hit a waypoint in the path.
	//  Just sets us up to go the next point if there is one. 
	if ( (message->GetMessageName() == "MazeFinderPathPointReached") && (message->GetSender() == this) )
	{
		if (_pathIndex < _pathPoints.size() - 1)
		{
			GetToNextPoint();
		}
		else 
		{
			theSwitchboard.Broadcast(new Message("MazeFinderEndPointReached", this));
			_pathPoints.clear();
			_pathIndex = 0;
		}

	}

	// When the player clicks, start a new path. 
	else if (message->GetMessageName() == "MouseDown")
	{
		TypedMessage<Vec2i> *m = (TypedMessage<Vec2i>*)message;
		Vec2i screenCoordinates = m->GetValue();
		Vector2 worldCoordinates = MathUtil::ScreenToWorld(screenCoordinates);
		GoTo(worldCoordinates);
	}
}

void MazeFinder::ToggleDrawPath(bool draw)
{
	_drawPath = draw;
}

void MazeFinder::Render()
{
	if (_drawPath && _pathPoints.size() > 0)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		glLineWidth(10.0f);
		for (unsigned int i=0; i < _pathPoints.size()-1; i++)
		{
			DrawLine(_pathPoints[i], _pathPoints[i+1]);
		}
		glLineWidth(5.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		for (unsigned int i=0; i < _pathPoints.size(); i++)
		{
			DrawCross(_pathPoints[i], 0.5f);
		}
		glLineWidth(1.0f);
	}
	Actor::Render();
}
