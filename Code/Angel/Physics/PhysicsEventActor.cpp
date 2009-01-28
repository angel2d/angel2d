#include "../Physics/PhysicsEventActor.h"

#include "../CollisionResponse/CollisionResponse.h"
#include "../Actors/ActorFactory.h"
#include "../Infrastructure/DeveloperConsole.h"

PhysicsEventActor::PhysicsEventActor()
{
	theCollisionResponseFactory.AddPhysicsEventActor( this );
}

PhysicsEventActor::~PhysicsEventActor()
{
	for( CollisionResponseTable::iterator itr = _collisionResponseTable.begin(); itr != _collisionResponseTable.end(); itr++ )
	{
		CollisionResponseList* pResponseList = (*itr).second;
		for( unsigned int i = 0; i < pResponseList->size(); i++ )
		{
			delete (*pResponseList)[i];
		}
		pResponseList->clear();
		delete pResponseList;
	}

	_collisionResponseTable.clear();

	theCollisionResponseFactory.RemovePhysicsEventActor( this );
}

void PhysicsEventActor::Update(float dt)
{
	ProcessCollisions();
	PhysicsActor::Update(dt);
}

void PhysicsEventActor::AddCollision( PhysicsEventActor* otherActor )
{
	_collisions.push_back( otherActor );
}

void PhysicsEventActor::OnCollidedWith( PhysicsEventActor* actor )
{
	AddCollision( actor );
}


void PhysicsEventActor::RegisterCollisionResponse( const String& key, CollisionResponse* colResponse )
{
	if (colResponse)
	{
		CollisionResponseList* responseList = GetCollisionResponses( ToUpper(key) );
		colResponse->SetStruck(this);
		responseList->push_back( colResponse );
	}
}

void PhysicsEventActor::RemoveCollisionResponse( const String& key, CollisionResponse* colResponse )
{
	CollisionResponseTable::iterator itr = _collisionResponseTable.find( key );
	//List not found, nothing to remove
	if( itr == _collisionResponseTable.end() )
		return;

	CollisionResponseList* pList = (*itr).second;

	for( CollisionResponseList::iterator itr = pList->begin(); itr != pList->end(); itr++)
	{
		CollisionResponse* pResponse = (*itr);
		if( pResponse == colResponse )
		{
			pList->erase( itr );
			delete pResponse;
			return;
		}
	}
}


void PhysicsEventActor::ProcessCollisions()
{
	ProcessCollisionInternal();
	_collisions.clear();
}

void PhysicsEventActor::ProcessCollisionInternal()
{
	for( unsigned int i = 0; i < _collisions.size(); i++ )
	{
		PhysicsEventActor* pStriker = _collisions[i];
		CollisionResponseList* responseList = FindCollisionResponses( pStriker->_collisionId );
		if( responseList )
		{
			//TODO: check destroyed?
			for( unsigned int responseIndex = 0; responseIndex < responseList->size(); responseIndex++ )
			{
				CollisionResponse* pResponse = (*responseList)[responseIndex];
				pResponse->SetStriker( pStriker );
				pResponse->Execute();
			}
		}
	}
}

PhysicsEventActor::CollisionResponseList* PhysicsEventActor::FindCollisionResponses( const String& key )
{
	CollisionResponseTable::iterator itr = _collisionResponseTable.find( key );
	if( itr == _collisionResponseTable.end() )
		return NULL;

	return (*itr).second;
}

PhysicsEventActor::CollisionResponseList* PhysicsEventActor::GetCollisionResponses( const String& key )
{
	CollisionResponseTable::iterator itr = _collisionResponseTable.find( key );
	if( itr == _collisionResponseTable.end() )
	{
		CollisionResponseList* pResponseList = new CollisionResponseList();
		_collisionResponseTable[key] = pResponseList;
		return pResponseList;
	}

	return (*itr).second;
}

void ActorFactoryAddCollisionResponse( const String& input )
{
	ACTORFACTORY_GETDELEGATE(pDel, PhysicsEventActorFactoryDelegate);
	
	StringList inputStrings = SplitString(input);
	//Do nothing, we don't have enough inputs
	if( inputStrings.size() < 2 )
		return;

	String key = inputStrings[0];
	inputStrings.erase( inputStrings.begin() );
	String type = inputStrings[0];
	inputStrings.erase( inputStrings.begin() );
	CollisionResponse* pResponse = theCollisionResponseFactory.CreateCollisionResponse( type, inputStrings );
	if( pResponse )
	{
		pDel->RegisterCollisionResponse( key, pResponse );
	}
}

void ActorFactorySetCollisionId( const String& input )
{
	ACTORFACTORY_GETDELEGATE(pDel, PhysicsEventActorFactoryDelegate);
	StringList inputStrings = SplitString( input );
	if( inputStrings.size() < 1 )
		return;

	pDel->SetCollisionId( inputStrings[0] );
}

void PhysicsEventActorFactoryDelegate::RegisterOriginalConsoleCommands()
{
	CONSOLE_DECLARECMDSTATICFLAGS( ActorFactoryAddCollisionResponse, ActorFactoryAddCollisionResponse, ConsoleCommand::CCF_CONFIG );
	CONSOLE_DECLARECMDSTATICFLAGS( ActorFactorySetCollisionId, ActorFactorySetCollisionId, ConsoleCommand::CCF_CONFIG );
}

Actor* PhysicsEventActorFactoryDelegate::CreateInstance()
{
	return new PhysicsEventActor();
}

void PhysicsEventActorFactoryDelegate::RegisterCollisionResponse( const String& key, CollisionResponse* pColResponse )
{
	ACTORFACTORY_GETACTOR( pActor, PhysicsEventActor );
	pActor->RegisterCollisionResponse(key, pColResponse);

}

void PhysicsEventActorFactoryDelegate::SetCollisionId( const String& id )
{
	ACTORFACTORY_GETACTOR( pActor, PhysicsEventActor );
	pActor->SetCollisionId(id);

}


