#pragma once

#include "DemoGameManager.h"

class DemoScreenStart : public DemoScreen
{
public:
	DemoScreenStart();

	virtual void Start();

private:
	SAMPLE_HANDLE music;
};
