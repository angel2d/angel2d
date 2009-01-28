#pragma once

#include "DemoGameManager.h"


class DemoScreenMovingActor : public DemoScreen
{
public:
	DemoScreenMovingActor();

	virtual void Start();
	virtual void Update(float dt);

private:
	TextActor* t;
	TextActor* t2;
	TextActor* t3;
	Actor *a;
};
