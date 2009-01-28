#include "../CollisionResponse/DestroyCollisionResponse.h"

#include "../Physics/PhysicsEventActor.h"
#include "../Util/StringUtil.h"

void DestroyCollisionResponse::Execute()
{
	_struck->Destroy();
}

CollisionResponse* DestroyCollisionResponse::FactoryMethod( const StringList& /*input*/ )
{
	return new DestroyCollisionResponse();
}
