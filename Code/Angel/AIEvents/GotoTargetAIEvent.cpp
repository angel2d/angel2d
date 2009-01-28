#include "../AIEvents/GotoTargetAIEvent.h"

#include "../AI/Sentient.h"
#include "../AI/PathFinder.h"
#include "../AI/SpatialGraph.h"
#include "../Infrastructure/TagCollection.h"

#include "Box2D.h"


GotoTargetAIEvent* GotoTargetAIEvent::Initialize( const String& targetTag, float moveSpeed, float arrivalDist )
{
	_targetTag = targetTag;
	GotoAIEvent::Initialize( Vector2::Zero, moveSpeed, arrivalDist );
	return this;
}

void GotoTargetAIEvent::Update(float dt)
{
	ActorSet taggedActors = theTagList.GetObjectsTagged(_targetTag);
	for( ActorSet::iterator itr = taggedActors.begin(); itr != taggedActors.end(); itr++ )
	{
		Actor* pTargetActor = (*itr);
		if( theSpatialGraph.IsInPathableSpace( pTargetActor->GetPosition() ) )
		{
			_destination = pTargetActor->GetPosition();
			GotoAIEvent::Update( dt );
			return;
		}
	}

	//otherwise, we failed
	_moveFailed = true;
	IssueCallback();

}
