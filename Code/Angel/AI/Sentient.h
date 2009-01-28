#pragma once

#include "../Physics/PhysicsEventActor.h"
#include "../AI/PathFinder.h"
#include "../AI/Brain.h"
#include "../Util/StringUtil.h"

class Sentient : public PhysicsEventActor
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

class SentientFactoryDelegate : public PhysicsEventActorFactoryDelegate
{
public:
	virtual void RegisterOriginalConsoleCommands() {}
	virtual Actor* CreateInstance() {return new Sentient(); }

protected:
	virtual void InitializeDelegate();

};

