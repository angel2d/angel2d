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
	Actor* box = new Actor();
	box->SetColor(0.0f, 0.0f, 0.0f, 0.6f);
	box->SetSize(16.0f, 4.0f);
	box->SetPosition(0.0f, -1.2f);
	theWorld.Add(box);
	String description = "This little dude is pathfinding through the area.";
	description += "\n\nClick the mouse to give him a new target.";
	description += "\n\nPress [B] to see the pathfinding graph.";
	TextActor *t = new TextActor("Console", description);
	t->SetAlignment(TXT_Center);
	t->SetColor(1.0f, 1.0f, 1.0f);
	theWorld.Add(t);
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenPathfinding.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	_objects.push_back(box);
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
	if (theController.IsConnected() && theController.IsBButtonDown())
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
	MoveTo(next, time, "MazeFinderPathPointReached");
}

