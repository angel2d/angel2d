//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
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

#pragma once

#include "../Infrastructure/Vector2.h"

struct PathFinderMove;
class FindNextMoveState;

class PathFinder
{
public:
	enum ePFMoveResult
	{
		PFMR_PATH_NOT_FOUND,
		PFMR_PATH_FOUND,
		PFMR_ARRIVED,
	};

	PathFinder();
	virtual ~PathFinder();

	void FindNextMove( const Vector2& from, const Vector2& to, float arrivalDist, PathFinderMove& move );

	enum ePFMoveState
	{
		PFMS_START,
		PFMS_VALIDATE,
		PFMS_FOLLOW,
		PFMS_RECOVER,
		PFMS_STARTRECOVER,

		PFMS_COUNT
	};

	void Render();
	static void EnableDrawPaths(bool enable);
	
private:
	void InitializeStates();

	FindNextMoveState* GetCurrentState();
	void SetNewState( ePFMoveState newState );

	Vector2List		_currentPath;
	int				_currentPathIndex;
	ePFMoveState	_currentState;
	Vector2			_currentPos;
	Vector2			_currentDest;
	float			_arrivalDist;

	FindNextMoveState* _states[PFMS_COUNT];

	friend class FindNextMoveState;
	
	static bool _drawPaths;

};

/* abstract */ class FindNextMoveState
{
public:
	virtual ~FindNextMoveState() {}
	virtual void Initialize( PathFinder* pathFinder ) {_pathFinder = pathFinder;}
	virtual bool Update( PathFinderMove& move ) = 0;
	virtual void BeginState( PathFinder::ePFMoveState /*lastState*/ ) {}
	virtual void EndState( PathFinder::ePFMoveState /*nextState*/ ) {}
	virtual const char* GetName() = 0;

protected:
	void SetNewState( PathFinder::ePFMoveState newState );
	Vector2List& GetCurrentPath() {return _pathFinder->_currentPath;}
	const Vector2& GetCurrentPosition() { return _pathFinder->_currentPos; }
	const Vector2& GetCurrentDestination() { return _pathFinder->_currentDest; }
	int& GetCurrentPathIndex() {return _pathFinder->_currentPathIndex; }
	float GetCurrentArrivalDist() {return _pathFinder->_arrivalDist; }


	PathFinder*	_pathFinder;
};


struct PathFinderMove
{
	Vector2						MoveDir;
	Vector2						NextSubgoalPos;
	PathFinder::ePFMoveResult	LastResult;
};

