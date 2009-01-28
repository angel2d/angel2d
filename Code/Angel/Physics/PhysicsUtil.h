#pragma once

#include "../Util/MathUtil.h"

class b2Shape;

class CollisionListener
{
public:
	virtual void OnCollision(b2Shape* s1, b2Shape* s2, float normalImpulse, Vector2& hitLocation)=0;
};
