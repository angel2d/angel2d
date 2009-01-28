#pragma once

#include "../Physics/PhysicsUtil.h"
#include "../Util/StringUtil.h"

#include <deque>

class PhysicsEventActor;

/*abstract*/ class CollisionResponse
{
public:
	virtual ~CollisionResponse() {}

	virtual void SetStruck( PhysicsEventActor* struck ) {_struck = struck;}
	virtual void SetStriker( PhysicsEventActor* striker ) {_striker = striker;}

	virtual void Execute()=0;

protected:
	PhysicsEventActor*		_struck;
	PhysicsEventActor*		_striker;
};

#define theCollisionResponseFactory CollisionResponseFactory::GetInstance()
#define COLLISIONRESPONSEFACTORY_ADD(cls) theCollisionResponseFactory.AddDelegate(#cls, cls::FactoryMethod)
#define DECLARE_COLLISIONRESPONSE(cls) \
	static void RegisterFactoryMethod() \
	{ \
		COLLISIONRESPONSEFACTORY_ADD(cls); \
	} \
	static CollisionResponse* FactoryMethod( const StringList& input );



class CollisionResponseFactory : public CollisionListener
{
	struct CollisionPair
	{
		PhysicsEventActor* LHS;
		PhysicsEventActor* RHS;
		//ADD Other Params
	};
public:
	typedef CollisionResponse* (*FactoryFunc)(const StringList& input);
	static CollisionResponseFactory &GetInstance();

	void Initialize();
	void Destroy();

	void AddDelegate( const String& id, FactoryFunc func);

	CollisionResponse* CreateCollisionResponse( const String& id, const StringList& input );
	virtual void OnCollision(b2Shape* s1, b2Shape* s2, float normalImpulse, Vector2& hitLocation);

	void AddPhysicsEventActor( PhysicsEventActor* actor);
	void RemovePhysicsEventActor( PhysicsEventActor* actor);

	void ProcessCollisions();

protected:
	CollisionResponseFactory();
	virtual ~CollisionResponseFactory();
	static CollisionResponseFactory *s_CollisionResponseFactory;

private:
	typedef hashmap_ns::hash_map<String, FactoryFunc> FactoryDelegateTable;

	void AddCollision( PhysicsEventActor* actor1, PhysicsEventActor* actor2 );

	FactoryDelegateTable			_table;
	std::set<PhysicsEventActor*>	_physicsEventActors;
	std::deque<CollisionPair>		_accumulatedCollisions;

};



