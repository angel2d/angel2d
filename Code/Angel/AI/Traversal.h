#pragma once

#include "../Infrastructure/Common.h"
#include "../Infrastructure/Vector2.h"
#include "../AI/SpatialGraph.h"

#include <deque>

class SpatialGraphKDNode;

class Traversal
{
	typedef hashmap_ns::hash_map<SpatialGraphKDNode*, int> VisitedNeighborsTable;
	typedef std::deque<SpatialGraphKDNode*> CurrentNodesQueue;
public:

	Traversal()
		: _traversalInitialized(false) {}
	virtual ~Traversal() {}
	
	virtual void StartTraversal( const Vector2& vStartPoint, int maxResults = -1, int maxIterations = -1 );
	virtual bool DoNextTraversal();
	virtual void ExecuteFullTraversal();

	virtual std::vector<Vector2>& GetResults();

protected:
	virtual void EvaluateNode( SpatialGraphKDNode* pNode ) = 0;
	virtual void AddSuccessors( SpatialGraphKDNode* pCurrent);

	virtual void AddNodeToVisit( SpatialGraphKDNode* pNode );
	virtual bool HasNodesToVist();
	virtual SpatialGraphKDNode* PopNextNode();
	virtual void SetVisited( SpatialGraphKDNode* pNode );
	virtual bool WasVisited( SpatialGraphKDNode* pNode );
	virtual void ClearAllVisited();
private:

	bool					_traversalInitialized;
	int						_maxIterations;
	int						_numIterations;
	int						_maxResults;
	std::vector<Vector2>	_results;
	CurrentNodesQueue		_nodesToVisit;
	VisitedNeighborsTable	_visited;
};