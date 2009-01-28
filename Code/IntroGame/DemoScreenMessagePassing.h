#pragma once

#include "DemoGameManager.h"


class DemoScreenMessagePassing : public DemoScreen, public MessageListener
{
public:
	DemoScreenMessagePassing();

	virtual void Start();
	virtual void Stop();
	virtual void ReceiveMessage(Message *message);
	
	void Setup();

private:
	TextActor* t;
	PhysicsActor *p1;
	PhysicsActor *p2;
	PhysicsActor *p3;

	SAMPLE_HANDLE bounceSample;
};
