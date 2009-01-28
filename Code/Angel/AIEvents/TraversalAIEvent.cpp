#include "../AIEvents/TraversalAIEvent.h"

#include "../AI/Traversal.h"


TraversalAIEvent* TraversalAIEvent::Initialize( Traversal* traversal, Vector2& startPos, int numIterationsPerFrame, int maxResults, int maxIterations )
{
	_numIterationsPerFrame = numIterationsPerFrame;
	_traversal = traversal;

	_traversal->StartTraversal( startPos, maxResults, maxIterations );

	return this;
}

void TraversalAIEvent::Update(float /*dt*/)
{
	if( _numIterationsPerFrame < 0 )
	{
		_traversal->ExecuteFullTraversal();
		IssueCallback();
		return;
	}

	for( int i = 0; i < _numIterationsPerFrame; i++ )
	{
		//callback when we're done
		if( !_traversal->DoNextTraversal() )
		{
			IssueCallback();
			return;
		}
	}
}

void TraversalAIEvent::Stop()
{
	delete _traversal;
}

std::vector<Vector2>& TraversalAIEvent::GetResults()
{
	return _traversal->GetResults();
}

