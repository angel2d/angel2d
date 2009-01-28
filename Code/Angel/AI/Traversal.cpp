#include "../AI/Traversal.h"

#include "../AI/SpatialGraph.h"

void Traversal::StartTraversal( const Vector2& vStartPoint, int maxResults, int maxIterations )
{
	_traversalInitialized = true;
	_maxIterations = maxIterations;
	_numIterations = 0;
	_maxResults = maxResults;
	ClearAllVisited();
	_results.clear();
	_nodesToVisit.clear();

	//Add start node
	AddNodeToVisit(theSpatialGraph.GetGraph()->FindNode( vStartPoint ));
}

bool Traversal::DoNextTraversal()
{
	if( !_traversalInitialized )
		return false;

	while( HasNodesToVist() )
	{
		//get next node
		SpatialGraphKDNode* pNextNode = PopNextNode();

		EvaluateNode(pNextNode);

		if( _maxResults != -1 && (int)_results.size() >= _maxResults )
			return false;

		_numIterations++;
		if( _maxIterations != -1 && _numIterations >= _maxIterations )
			return false;

	}

	return false;
}

void Traversal::ExecuteFullTraversal()
{
	while( DoNextTraversal() ) {}
}

std::vector<Vector2>& Traversal::GetResults()
{
	return _results;
}

void Traversal::AddSuccessors( SpatialGraphKDNode* pCurrent)
{
	for( unsigned int i = 0; i < pCurrent->NeighborLOS.size(); i++ )
	{
		if( pCurrent->NeighborLOS[i] )
		{
			SpatialGraphKDNode* pNeighbor = pCurrent->Neighbors[i];
			if( WasVisited(pNeighbor) )
				AddNodeToVisit( pNeighbor );
		}
	}
}

void Traversal::AddNodeToVisit( SpatialGraphKDNode* pNode )
{
	_nodesToVisit.push_back( pNode );
	SetVisited(pNode);
}

bool Traversal::HasNodesToVist()
{
	return _nodesToVisit.size() > 0;
}

SpatialGraphKDNode* Traversal::PopNextNode()
{
	SpatialGraphKDNode* pNext = _nodesToVisit.back();
	_nodesToVisit.pop_front();

	return pNext;
}

void Traversal::SetVisited( SpatialGraphKDNode* pNode )
{
	_visited[pNode] = 1;
}

bool Traversal::WasVisited( SpatialGraphKDNode* pNode )
{
	return _visited.find(pNode) != _visited.end();
}

void Traversal::ClearAllVisited()
{
	_visited.clear();
}

