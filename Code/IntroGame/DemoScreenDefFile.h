#pragma once

#include "DemoGameManager.h"


class DemoScreenDefFile : public DemoScreen
{
public:
	DemoScreenDefFile();

	virtual void Start();

private:
	TextActor *t;
	TextActor *t2;
	Actor *a;
};
