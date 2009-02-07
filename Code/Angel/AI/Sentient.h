#pragma once

#include "../AI/PathFinder.h"
#include "../AI/Brain.h"
#include "../Util/StringUtil.h"
#include "../Physics/PhysicsActor.h"

class Sentient : public PhysicsActor
{
public:
	Sentient();

	virtual void Update(float dt);
	virtual void Render();

	PathFinder&		GetPathfinder() {return _pathFinder;}
	virtual void OnNamedEvent( const String& /*eventId*/ ) {}

	virtual void InitializeBrain() {}
	virtual void StartBrain() {}

protected:
	PathFinder		_pathFinder;
	AIBrain			_brain;
};



