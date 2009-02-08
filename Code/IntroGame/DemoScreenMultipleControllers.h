#pragma once

#include "DemoGameManager.h"


class DemoScreenMultipleControllers : public DemoScreen
{
public:
	DemoScreenMultipleControllers();
	
	virtual void Start();
	virtual void Update(float dt);
	
private:
	TextActor* t;
	TextActor* t2;
	TextActor* t3;
	Actor *a;
	Actor *a2;
};
