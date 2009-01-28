#pragma once

#include "../Infrastructure/Common.h"
#include "../Infrastructure/Vector2.h"

typedef std::vector<Vector2> Vector2List;

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

