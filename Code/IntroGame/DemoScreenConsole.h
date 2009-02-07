#pragma once

#include "DemoGameManager.h"


class DemoScreenConsole : public DemoScreen
{
public:
	DemoScreenConsole();

	virtual void Start();

private:
	TextActor *t;
	Actor *a;
};
