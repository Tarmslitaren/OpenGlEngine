#ifndef EDGE_HEADER
#define EDGE_HEADER


namespace CommonUtilities
{
	class Triangle;
	class Edge
	{
	public:
		Edge();
		~Edge();

		CU::Vector2f GetUnConnectedPoint(Edge* anEdge);
		bool LineIntersect(CU::Vector2f aLineStart,CU::Vector2f aLineEnd,CU::Vector2f& anIntersectionPoint);
		CU::Vector2f myPoints[2];
		Triangle* mySides[2];
		int GetTriangleIndex(Triangle* aTriangle);
		bool myIsConnected;
	};
};
#endif