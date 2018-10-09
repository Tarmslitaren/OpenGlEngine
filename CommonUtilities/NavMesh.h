#ifndef NAV_MESH_HEADER
#define NAV_MESH_HEADER

#include "AstarGraph.h"
#include "Graph.h"
#include "Edge.h"
#include "Triangle.h"

namespace CommonUtilities
{

	struct SquareWrap
	{
		CU::Vector2f myFirstPoint;
		CU::Vector2f mySecondPoint;
	};
	struct LineWrap
	{
		CU::Vector2f myStart;
		CU::Vector2f myEnd;
	};

	class NavMesh
	{
	public:
		NavMesh();
		~NavMesh();
		void Init(CU::Vector2f aUppderLeftPos, CU::Vector2f aLowerRightPos);
		void MakeAstarGraph();
		void StencilOutAASquare(CU::Vector2f aSquareFirstPos, CU::Vector2f aSquareSecondPos);
		void StencilOutTriangle(CU::Vector2f aTrianglePoint1, CU::Vector2f aTrianglePoint2, CU::Vector2f aTrianglePoint3);

		CU::GrowingArray<CU::Vector2f> GetPath(CU::Vector2f aStartPoint, CU::Vector2f aEndPoint);
		std::vector<CU::Vector2f> GetBlockedTriangles();
		CU::GrowingArray<CU::Triangle*> myTriangles;
		std::vector<CU::Vector2f> GetAllTriPoints();
		std::vector<CU::Vector2f> GetAllNonBlockedPoints();
		std::vector<CU::Vector2f> GetAllBlockedTriPoints();

		CU::GrowingArray<CU::Vector2f> GetAllStarNodes();
		CU::GrowingArray<CU::Edge*> myEdges;
		const CU::GrowingArray<SquareWrap>& GetAllBlockedSquares();

		const CU::GrowingArray<CU::Edge*>& GetAllBlockedEdges();

		
		void AddBlockedSquare(CU::Vector2f aFirstPoint,CU::Vector2f aSecondPoint);
		void BlockAllAddedSquares();
	private:
		void BlockSquare(CU::Vector2f aFirstPoint,CU::Vector2f aSecondPoint);
		void CollideLine(CU::Vector2f aFirstPoint, CU::Vector2f aSecondPoint);
		void CollideLineWithTheseTris(CU::Vector2f aFirstPoint, CU::Vector2f aSecondPoint, CU::GrowingArray<CU::Triangle*> aTris);
		void Split(Edge* aSplitingEdge, CU::Vector2f aSplitPoint);
		void SplitOneSide(Triangle* aOldTriangle, Edge* aSplitingEdge, CU::Vector2f aSplitPoint);
		void SplitTwoSides(Triangle* aFirstOldTriangle, Triangle* aSecondOldTriangle, Edge* aSplitingEdge, CU::Vector2f aSplitPoint);

		//CU::GrowingArray<CU::Triangle*> myTriangles;
		
		CU::Vector2f myUppderLeftPos;
		CU::Vector2f myLowerRightPos;

		CU::GrowingArray<CU::Edge*> myBlockedEdges;
		CU::GrowingArray<SquareWrap> myBlockedSquares;
		int GetTriIndex(CU::Triangle* aTri);
		Graph myGraph;
		AstarGraph myAGraph;
		
	};
};
#endif