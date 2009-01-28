#pragma once

#include "DemoGameManager.h"


class DemoScreenRenderLayers : public DemoScreen
{
public:
	DemoScreenRenderLayers();

	virtual void Start();
	virtual void Update(float dt);

private:
	TextActor *t1;
	TextActor *t2;
	Actor *a1;
	Actor *a2;
};
