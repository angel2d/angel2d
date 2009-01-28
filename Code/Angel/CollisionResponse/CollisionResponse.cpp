#include "../CollisionResponse/CollisionResponse.h"

#include "../Physics/PhysicsEventActor.h"
#include "../Infrastructure/World.h"

#include "Box2D.h"

CollisionResponseFactory* CollisionResponseFactory::s_CollisionResponseFactory = NULL;

CollisionResponseFactory::CollisionResponseFactory() {}
CollisionResponseFactory::~CollisionResponseFactory()
{
}


CollisionResponseFactory &CollisionResponseFactory::GetInstance()
{
	if( s_CollisionResponseFactory == NULL )
	{
		s_CollisionResponseFactory = new CollisionResponseFactory();
		s_CollisionResponseFactory->Initialize();
		theWorld.AddCollisionListener( s_CollisionResponseFactory );
	}
	return *s_CollisionResponseFactory;
}

#include "CollisionResponseRegistry.h"
void CollisionResponseFactory::Initialize()
{
#define COLRES_REG(cls) cls::RegisterFactoryMethod();
#include "CollisionResponseRegistry.inc"
#undef COLRES_REG
}

void CollisionResponseFactory::Destroy()
{
	if( s_CollisionResponseFactory )
	{
		theWorld.RemoveCollisionListener( s_CollisionResponseFactory );
		delete s_CollisionResponseFactory;
		s_CollisionResponseFactory = NULL;
	}
}

void CollisionResponseFactory::AddDelegate( const String& id, FactoryFunc func)
{
	_table[id] = func;
}

CollisionResponse* CollisionResponseFactory::CreateCollisionResponse( const String& id, const StringList& input )
{
	FactoryDelegateTable::iterator itr = _table.find(id);
	if( itr != _table.end() )
	{
		return (*itr).second(input);
	}

	return NULL;

}

void CollisionResponseFactory::OnCollision(b2Shape* s1, b2Shape* s2, float /*normalImpulse*/, Vector2& /*hitLocation*/)
{
	PhysicsActor* actor1 = reinterpret_cast<PhysicsActor*>(s1->GetBody()->GetUserData());
	PhysicsActor* actor2 = reinterpret_cast<PhysicsActor*>(s2->GetBody()->GetUserData());
	if( actor1 == NULL || actor2 == NULL )
		return;

	if( actor1 == actor2 )
		return;

	if( !actor1->HandlesCollisionEvents() || !actor2->HandlesCollisionEvents() )
		return;

	AddCollision( reinterpret_cast<PhysicsEventActor*>(actor1), reinterpret_cast<PhysicsEventActor*>(actor2));
}

void CollisionResponseFactory::AddPhysicsEventActor( PhysicsEventActor* actor)
{
	_physicsEventActors.insert( actor );
}

void CollisionResponseFactory::RemovePhysicsEventActor( PhysicsEventActor* actor)
{
	_physicsEventActors.erase( actor );
}

void CollisionResponseFactory::ProcessCollisions()
{
	for( unsigned int i = 0; i < _accumulatedCollisions.size(); i++ )
	{
		CollisionPair& cpRef = _accumulatedCollisions[i];
		cpRef.LHS->OnCollidedWith( cpRef.RHS );
		cpRef.RHS->OnCollidedWith( cpRef.LHS );
	}
	_accumulatedCollisions.clear();
}

void CollisionResponseFactory::AddCollision( PhysicsEventActor* actor1, PhysicsEventActor* actor2 )
{
	CollisionPair cp;
	//Get the lower address on the LHS all the time so we can have cleaner compares
	if( (void*)actor1 < (void*)actor2 )
	{
		cp.LHS = actor1;
		cp.RHS = actor2;
	}
	else
	{
		cp.LHS = actor2;
		cp.RHS = actor1;
	}

	for( unsigned int i = 0; i < _accumulatedCollisions.size(); i++ )
	{
		CollisionPair& cpRef = _accumulatedCollisions[i];
		//Bail out if we already have an entry for this guy
		if( cpRef.LHS == cp.LHS && cpRef.RHS == cp.RHS )
			return;
	}

	_accumulatedCollisions.push_front( cp );

}

