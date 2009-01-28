#pragma once

#include "../Physics/PhysicsActor.h"
#include "../Infrastructure/Common.h"
#include "../Util/StringUtil.h"

class CollisionResponse;

class PhysicsEventActor : public PhysicsActor
{
protected:
	typedef std::vector<PhysicsEventActor*>					PhysicsEventActorList;
	typedef std::vector<CollisionResponse*>					CollisionResponseList;
	typedef hashmap_ns::hash_map<String, CollisionResponseList*>	CollisionResponseTable;
public:

	PhysicsEventActor();
	virtual ~PhysicsEventActor();

	virtual void Update(float dt);

	//Construction functions
	virtual void RegisterCollisionResponse( const String& key, CollisionResponse* colResponse );
	virtual void RemoveCollisionResponse( const String& key, CollisionResponse* colResponse );
	void SetCollisionId( const String& colId ) {_collisionId = ToUpper(colId);}
	virtual void OnCollidedWith( PhysicsEventActor* actor );
	virtual bool HandlesCollisionEvents() {return true;}
	virtual void OnNamedEvent( const String& /*eventId*/ ) {}

protected:
	virtual void AddCollision( PhysicsEventActor* otherActor );
	void ProcessCollisions();
	virtual void ProcessCollisionInternal();
	CollisionResponseList* FindCollisionResponses( const String& key );
	CollisionResponseList* GetCollisionResponses( const String& key );

	CollisionResponseTable			_collisionResponseTable;
	PhysicsEventActorList			_collisions;
	String							_collisionId;


};


class PhysicsEventActorFactoryDelegate : public PhysicsActorFactoryDelegate
{
public:
	virtual void RegisterOriginalConsoleCommands();
	virtual Actor* CreateInstance(); 
	virtual void RegisterCollisionResponse( const String& key, CollisionResponse* pColResponse );
	virtual void SetCollisionId( const String& id );
};



