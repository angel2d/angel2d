#pragma once

#include "DemoGameManager.h"


class ParticleActor;

class DemoScreenParticleActors : public DemoScreen, public MouseListener
{
public:
	DemoScreenParticleActors();

	virtual void Start();
	virtual void Stop();
	virtual void Update(float dt);
	virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);
	virtual void MouseMotionEvent(Vec2i screenCoordinates);

private:
	TextActor *t;
	TextActor *t2;
	ParticleActor *pa;

	bool _isActive;
};
