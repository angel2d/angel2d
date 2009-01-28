#pragma once

#include "../Infrastructure/Common.h"
#include "../Infrastructure/Vector2.h"
#include "../AI/Brain.h"


class Traversal;

class TraversalAIEvent : public AIEvent
{
public:
	virtual TraversalAIEvent* Initialize( Traversal* pTraversal, Vector2& vStartPos, int numIterationsPerFrame = 10, int maxResults = -1, int maxIterations = -1 );
	virtual void Update(float dt);
	virtual void Stop();

	virtual std::vector<Vector2>& GetResults();
	virtual std::vector<Vector2> CopyResults() {return GetResults();}
private:
	Traversal*	_traversal;
	int			_numIterationsPerFrame;
};

DECLARE_AIEVENT_BASE( TraversalAIEvent )

