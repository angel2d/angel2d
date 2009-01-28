#pragma once

#include "DemoGameManager.h"


class DemoScreenConsole : public DemoScreen, public CCmdMemberFunctorOwner
{
public:
	DemoScreenConsole();

	virtual void Start();
	void ChangeSize(const String& input);

private:
	TextActor *t;
	Actor *a;
};
