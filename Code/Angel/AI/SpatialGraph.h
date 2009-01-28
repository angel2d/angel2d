#pragma once

#include "../Infrastructure/Common.h"
#include "../Infrastructure/BoundingShapes.h"

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
#if defined(__APPLE__)
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

class SpatialGraphManager
{
public:
	static SpatialGraphManager &GetInstance();

	SpatialGraph* GetGraph() {return _spatialGraph;}
	void CreateGraph( float entityWidth, const BoundingBox& bounds );

	void Render();

	bool GetPath( const Vector2& source, const Vector2& dest, Vector2List& path );

	bool CanGo( const Vector2& from, const Vector2 to );
	bool IsInPathableSpace( const Vector2& point );
	bool FindNearestNonBlocked( const Vector2& fromPoint, Vector2& goTo );
protected:
	SpatialGraphManager();
	~SpatialGraphManager();
	void Initialize();
	static SpatialGraphManager *s_SpatialGraphManager;

private:
	SpatialGraph*				_spatialGraph;

};