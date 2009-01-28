#include "../CollisionResponse/StunCollisionResponse.h"

#include "../Physics/PhysicsEventActor.h"
#include "../Util/StringUtil.h"

void StunCollisionResponse::Execute()
{
	_struck->OnNamedEvent( "stun" );
}

CollisionResponse* StunCollisionResponse::FactoryMethod( const StringList& /*input*/ )
{
	return new StunCollisionResponse();
}
