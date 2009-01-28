#pragma once

#include "../CollisionResponse/CollisionResponse.h"

class StunCollisionResponse : public CollisionResponse
{
public:
	DECLARE_COLLISIONRESPONSE(StunCollisionResponse)

	virtual void Execute();

};