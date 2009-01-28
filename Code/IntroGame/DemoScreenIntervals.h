#pragma once

#include "DemoGameManager.h"


class DemoScreenIntervals : public DemoScreen, public MessageListener
{
public:
	DemoScreenIntervals();

	virtual void Start();
	virtual void ReceiveMessage(Message *message);

private:
	TextActor* t;
	TextActor* t2;
	Actor *a;
};
