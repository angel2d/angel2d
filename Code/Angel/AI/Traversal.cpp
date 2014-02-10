//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2014, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
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

