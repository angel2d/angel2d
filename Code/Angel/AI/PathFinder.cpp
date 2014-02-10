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
#include "../AI/PathFinder.h"

#include "../AI/SpatialGraph.h"
#include "../Infrastructure/TextRendering.h"
#include "../Util/DrawUtil.h"
#include "../Util/StringUtil.h"
#include "../Util/MathUtil.h"

bool PathFinder::_drawPaths = false;

PathFinder::PathFinder()
: _currentPathIndex(-1)
, _currentState(PFMS_START)
, _arrivalDist(0.0f)
{
	InitializeStates();
}

PathFinder::~PathFinder()
{
	for( int i = 0; i < PFMS_COUNT; i++ )
	{
		delete _states[i];
	}

}


void PathFinder::FindNextMove( const Vector2& from, const Vector2& to, float arrivalDist, PathFinderMove& move )
{
	_currentPos = from;
	_currentDest = to;
	_arrivalDist = arrivalDist;

	move.LastResult = PathFinder::PFMR_PATH_FOUND;

	while(!GetCurrentState()->Update( move ) );
}


void PathFinder::Render()
{
	if( !_drawPaths )
		return;
	if( _currentPath.size() > 0 )
	{
		Vector2 lastPt;

		glColor3f(0,0,1.f);
		for ( unsigned int i = 0; i < _currentPath.size(); i++ )
		{
			Vector2 curPt = _currentPath[i];
			if( lastPt != Vector2(0) )
			{
				DrawLine( curPt, lastPt );
			}
			lastPt = curPt;
		}

		if( _currentPathIndex >= 0 && _currentPathIndex < (int)_currentPath.size() )
		{
			glColor3f(1,0,1.f);
			
			DrawLine( _currentPath[_currentPathIndex], _currentPos );
			DrawPoint( _currentPath[_currentPathIndex], 0.1f );
		}
		DrawPoint( _currentPath[_currentPath.size()-1], 0.1f );
	}

	String currentState = GetCurrentState()->GetName();

	Vector2 screenCenter = MathUtil::WorldToScreen( _currentPos.X, _currentPos.Y );
	//Print some vals
	glColor3f(0,1.f,1.f);
	DrawGameText( currentState + String(" ") + IntToString(_currentPathIndex), "ConsoleSmall", (int)screenCenter.X, (int)screenCenter.Y );

}

void PathFinder::EnableDrawPaths(bool enable)
{
	_drawPaths = enable;
}


class StartMoveState : public FindNextMoveState
{
public:
	virtual ~StartMoveState() {}
	virtual const char* GetName() {return "Start";}
	virtual bool Update( PathFinderMove& move )
	{
		if( !theSpatialGraph.IsInPathableSpace( GetCurrentPosition() ) )
		{
			SetNewState(PathFinder::PFMS_STARTRECOVER);
			return true;
		}
		//find path
		GetCurrentPath().clear();
		bool retVal = theSpatialGraph.GetPath( GetCurrentPosition(), GetCurrentDestination(), GetCurrentPath() );

		if( retVal )
		{
			move.LastResult = PathFinder::PFMR_PATH_FOUND;
			//Initialize path index
			GetCurrentPathIndex() = 0;

			SetNewState( PathFinder::PFMS_FOLLOW );
			//Keep ticking
			return true;
		}
		else
		{
			move.LastResult = PathFinder::PFMR_PATH_NOT_FOUND;
		}

		//We're done if path failed
		return false;
	}

};

class ValidateMoveState : public FindNextMoveState
{
public:
	virtual ~ValidateMoveState() {}
	virtual const char* GetName() {return "Validate";}
	virtual bool Update( PathFinderMove& /*move*/ )
	{
		//Make sure we can keep heading to our current subgoal
		const Vector2List& currentPath = GetCurrentPath();
		int currentPathIndex = GetCurrentPathIndex();

		//has the destination changed
		Vector2 vDest = currentPath[currentPath.size()-1];
		if( vDest == GetCurrentDestination() )
		{
			if( theSpatialGraph.CanGo( GetCurrentPosition(), currentPath[currentPathIndex] ) )
			{
				SetNewState( PathFinder::PFMS_FOLLOW );
				return true;
			}
			else if( !theSpatialGraph.CanGo( GetCurrentPosition(), GetCurrentPosition() ) )
			{
				//are we blocked
				SetNewState( PathFinder::PFMS_RECOVER );
				return true;
			}
		}

		//otherwise, try again
		SetNewState( PathFinder::PFMS_START );
		return true;
	}
};

class FollowMoveState : public FindNextMoveState
{
public:
	virtual ~FollowMoveState() {}
	virtual const char* GetName() {return "Follow";}
	virtual bool Update( PathFinderMove& move )
	{
		//check our current path index
		const int iLookAheadCount = 3;

		const Vector2List& currentPath = GetCurrentPath();
		int nextPathIndex = GetCurrentPathIndex();

		//Are we at our goal index
		if( nextPathIndex == (int)currentPath.size() - 1 )
		{
			move.NextSubgoalPos = currentPath[nextPathIndex];
			//check distance to goal
			float sqDist = Vector2::DistanceSquared( GetCurrentPosition(), move.NextSubgoalPos );
			float arrivalDistSq = GetCurrentArrivalDist();
			arrivalDistSq *= arrivalDistSq;
			if( sqDist <= arrivalDistSq )
			{
				//don't set move dir (we've arrived)
				move.LastResult = PathFinder::PFMR_ARRIVED;
				SetNewState( PathFinder::PFMS_VALIDATE );
				return false;
			}
		}
		else
		{
			//otherwise, see if we can advance our next subgoal
			for( int i = 0 ; i < iLookAheadCount && (nextPathIndex+1) < (int)currentPath.size(); i++ )
			{
				if( theSpatialGraph.CanGo( GetCurrentPosition(), currentPath[nextPathIndex+1] ) )
				{
					++nextPathIndex;
				}
			}

			GetCurrentPathIndex() = nextPathIndex;
			move.NextSubgoalPos = currentPath[nextPathIndex];
		}

		//Move dir is normalized towards next subgoal
		move.MoveDir = Vector2::Normalize( move.NextSubgoalPos - GetCurrentPosition() );
		//we're done this round
		SetNewState( PathFinder::PFMS_VALIDATE );
		return false;
	}

};

class RecoverMoveState : public FindNextMoveState
{
public:
	virtual ~RecoverMoveState() {}
	virtual const char* GetName() {return "Recover";}
	virtual bool Update( PathFinderMove& move )
	{
		//are we back in pathable space?
		if( theSpatialGraph.IsInPathableSpace( GetCurrentPosition() ) )
		{
			SetNewState( PathFinder::PFMS_FOLLOW );
			return true;
		}

		const Vector2List& currentPath = GetCurrentPath();
		int currentPathIndex = GetCurrentPathIndex();

		//otherwise, head toward our current pathnode
		move.MoveDir = Vector2::Normalize( currentPath[currentPathIndex] - GetCurrentPosition() );

		return false;
	}
};

class StartRecoverMoveState : public FindNextMoveState
{
public:
	virtual ~StartRecoverMoveState() {}
	virtual const char* GetName() {return "StartRecover";}
	virtual bool Update( PathFinderMove& move )
	{
		//are we back in pathable space?
		if( theSpatialGraph.IsInPathableSpace( GetCurrentPosition() ) )
		{
			SetNewState( PathFinder::PFMS_START );
			return true;
		}

		//find the nearest non-blocked neighbor I can move to
		Vector2 vGoTo;
		if( theSpatialGraph.FindNearestNonBlocked( GetCurrentPosition(), vGoTo) )
		{
			move.MoveDir = Vector2::Normalize( vGoTo - GetCurrentPosition() );
		}
		else
		{
			move.LastResult = PathFinder::PFMR_PATH_NOT_FOUND;
		}

		return false;
	}
};

void PathFinder::InitializeStates()
{
	//Init states
	_states[PFMS_START] = new StartMoveState();
	_states[PFMS_START]->Initialize( this );

	_states[PFMS_VALIDATE] = new ValidateMoveState();
	_states[PFMS_VALIDATE]->Initialize( this );

	_states[PFMS_FOLLOW] = new FollowMoveState();
	_states[PFMS_FOLLOW]->Initialize( this );

	_states[PFMS_RECOVER] = new RecoverMoveState();
	_states[PFMS_RECOVER]->Initialize( this );

	_states[PFMS_STARTRECOVER] = new StartRecoverMoveState();
	_states[PFMS_STARTRECOVER]->Initialize( this );


}


FindNextMoveState* PathFinder::GetCurrentState()
{
	return _states[_currentState];
}
void PathFinder::SetNewState( ePFMoveState newState )
{
	//ignore gotos to the same state
	if( newState == _currentState )
		return;

	if( newState < 0 || newState >= PFMS_COUNT )
		return;

	_currentState = newState;
}


void FindNextMoveState::SetNewState( PathFinder::ePFMoveState newState )
{
	_pathFinder->SetNewState( newState );
}
