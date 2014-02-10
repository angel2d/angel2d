//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2014, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIEvents/GotoAIEvent.h"

#include "../AI/Sentient.h"
#include "../AI/PathFinder.h"

#include <Box2D/Box2D.h>

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
		pActor->ApplyLinearImpulse( move.MoveDir * _moveSpeed * pActor->GetBody()->GetMass(), Vector2::Zero );
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
