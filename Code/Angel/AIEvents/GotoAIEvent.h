#pragma once

#include "../AI/Brain.h"
#include "../Infrastructure/Vector2.h"

class PathFinder;

class GotoAIEvent : public AIEvent
{
public:

	virtual GotoAIEvent* Initialize( const Vector2& destination, float moveSpeed, float arrivalDist = 0.2f );
	virtual void Update(float dt);

protected:
	PathFinder& GetPathfinder();

protected:
	bool			_moveFailed;
	Vector2			_destination;
	float			_moveSpeed;
	float			_arrivalDist;

};

DECLARE_AIEVENT_BASE( GotoAIEvent )
