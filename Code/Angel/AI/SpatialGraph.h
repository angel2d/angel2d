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

#include "../AI/BoundingShapes.h"

#include <Box2D/Box2D.h>

class SpatialGraph;
class SpatialGraphKDNode;

typedef std::vector<SpatialGraphKDNode*>	SpatialGraphNeighborList;
typedef std::vector<Vector2>				Vector2List;
typedef std::vector<bool>					BoolList;
class SpatialGraphKDNode
{
public:

	SpatialGraphKDNode( const BoundingBox& bb, SpatialGraphKDNode* _parent )
		: BBox(bb)
		, LHC(NULL)
		, RHC(NULL)
		, Parent(_parent)
	{
	}

	void Render();

	bool HasChildren() {return LHC != NULL && RHC != NULL;}
	void GetGridPoints( Vector2List& points, int& xPoints, int& yPoints );

	BoundingBox BBox;
	SpatialGraphKDNode* LHC;
	SpatialGraphKDNode* RHC;
	SpatialGraphKDNode* Parent;
	SpatialGraph*		Tree;
	int Index;
	int Depth;
	bool bBlocked;

	SpatialGraphNeighborList	Neighbors;
	BoolList					NeighborLOS;
	
};
#if defined(__APPLE__) || defined(__linux__)
//have to give a hashing function for specific pointers
namespace hashmap_ns {
	template<> struct hash< SpatialGraphKDNode* >
	{
		size_t operator()( const SpatialGraphKDNode* const & x ) const
		{
			return hash<long int>()( (long int)x );
		}
	};
}
#endif

class SpatialGraph
{
public:
	SpatialGraph(float entityWidth, const BoundingBox& startBox );
	~SpatialGraph();
	
	SpatialGraphKDNode* FindNode(SpatialGraphKDNode* node, const BoundingBox& bbox);
	SpatialGraphKDNode* FindNode(SpatialGraphKDNode* node, const Vector2& point);
	SpatialGraphKDNode* FindNode(const BoundingBox& bbox);
	SpatialGraphKDNode* FindNode(const Vector2& point);
	void Render();

	int GetDepth() {return _depth;}
	Vector2 GetSmallestDimensions() {return _smallestDimensions;}
	bool CanGo( const Vector2& vFrom, const Vector2 vTo );

private:
	SpatialGraphKDNode* CreateTree(int depth, const BoundingBox& bbox, SpatialGraphKDNode* parent = NULL, int index = 0 );
	void AddNeighbor( SpatialGraphKDNode* node, const Vector2& pos );
	void ComputeNeighbors( SpatialGraphKDNode* node );
	void ValidateNeighbors( SpatialGraphKDNode* node );
	void DeleteNode( SpatialGraphKDNode* pNode );
	bool IsFullyBlocked( SpatialGraphKDNode* pNode );
	bool CanGoInternal( const Vector2& vFrom, const Vector2 vTo, SpatialGraphKDNode* pSourceNode, SpatialGraphKDNode* pDestNode );
	bool CanGoNodeToNode( SpatialGraphKDNode* pSourceNode, SpatialGraphKDNode* pDestNode );

private:
	int _depth;
	float _entityWidth;
	Vector2 _smallestDimensions;
	SpatialGraphKDNode* _root;
	int _dirMasks[4];

};

#define theSpatialGraph SpatialGraphManager::GetInstance()

class SpatialGraphManager : public b2QueryCallback
{
public:
	static SpatialGraphManager &GetInstance();

	bool ReportFixture(b2Fixture* fixture);
	
	SpatialGraph* GetGraph() {return _spatialGraph;}
	void CreateGraph( float entityWidth, const BoundingBox& bounds );

	void Render();

	bool GetPath( const Vector2& source, const Vector2& dest, Vector2List& path );

	bool CanGo( const Vector2& from, const Vector2 to );
	bool IsInPathableSpace( const Vector2& point );
	bool FindNearestNonBlocked( const Vector2& fromPoint, Vector2& goTo );
	
	void EnableDrawBounds(bool enable);
	const bool ToggleDrawBounds();
	const bool GetDrawBounds();
	void EnableDrawBlocked(bool enable);
	const bool ToggleDrawBlocked();
	const bool GetDrawBlocked();
	void EnableDrawGridPoints(bool enable);
	const bool ToggleDrawGridPoints();
	const bool GetDrawGridPoints();
	void EnableDrawGraph(bool enable);
	const bool ToggleDrawGraph();
	const bool GetDrawGraph();
	void EnableDrawNodeIndex(bool enable);
	const bool ToggleDrawNodeIndex();
	const bool GetDrawNodeIndex();
	
protected:
	SpatialGraphManager();
	~SpatialGraphManager();
	void Initialize();
	static SpatialGraphManager *s_SpatialGraphManager;

private:
	SpatialGraph*				_spatialGraph;
	
	bool _drawBounds;
	bool _drawBlocked;
	bool _drawGridPoints;
	bool _drawGraph;
	bool _drawNodeIndex;
};
