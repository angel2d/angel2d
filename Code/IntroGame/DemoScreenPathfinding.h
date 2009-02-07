#pragma once

#include "DemoGameManager.h"

class DemoScreenPathfinding : public DemoScreen, public MouseListener
{
public:
	DemoScreenPathfinding();
	
	virtual void Start();
	virtual void Stop();
	
	virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);
	
	virtual void Update(float dt);
};


class MazeFinder : public Actor
{
public:
	MazeFinder();
	void GoTo(Vector2 newDestination);
	virtual void ReceiveMessage(Message *message);
	
private:
	Vector2List _pathPoints;
	unsigned int _pathIndex;
	
	void GetToNextPoint();
};
