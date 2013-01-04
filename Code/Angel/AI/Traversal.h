//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
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