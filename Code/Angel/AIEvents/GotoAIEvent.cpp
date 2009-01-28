#include "../AIEvents/GotoAIEvent.h"

#include "../AI/Sentient.h"
#include "../AI/PathFinder.h"

#include "Box2D.h"

GotoAIEvent* GotoAIEvent::Initialize(const Vector2& destination, float moveSpeed, float arrivalDist)
{
	_destination = destination;
	_moveSpeed = moveSpeed;
	_arrivalDist = arrivalDist;
	_moveFailed = false;
	return this;
}

void GotoAIEvent::Update(float /*dt*/)
{
	Sentient* pActor = GetActor();

	PathFinderMove move;
	GetPathfinder().FindNextMove( pActor->GetPosition(), _destination, _arrivalDist, move );

	if( move.LastResult == PathFinder::PFMR_PATH_FOUND)
	{
		pActor->ApplyImpulse( move.MoveDir * _moveSpeed * pActor->GetBody()->GetMass(), Vector2::Zero );
	}
	else if( move.LastResult == PathFinder::PFMR_ARRIVED )
	{
		_moveFailed = false;
		IssueCallback();
	}
	else if( move.LastResult == PathFinder::PFMR_PATH_NOT_FOUND )
	{
		_moveFailed = true;
		IssueCallback();
	}

}

PathFinder& GotoAIEvent::GetPathfinder()
{
	return GetActor()->GetPathfinder();
}
