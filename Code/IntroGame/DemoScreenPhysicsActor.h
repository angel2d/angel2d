#pragma once

#include "DemoGameManager.h"


class DemoScreenPhysicsActor : public DemoScreen
{
public:
	DemoScreenPhysicsActor();

	virtual void Start();
	virtual void Update(float dt);

private:
	TextActor* t;
	PhysicsActor *p1;
	PhysicsActor *p2;
};
