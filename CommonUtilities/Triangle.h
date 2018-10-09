#ifndef TRIANGLE_HEADER
#define TRIANGLE_HEADER

namespace CommonUtilities
{
	class Edge;
	class Triangle
	{
	public:
		Triangle();
		~Triangle();
		Edge* myEdges[3];
		
		Edge* GetEdgeWithPoints(CU::Vector2f aFirstPoint, CU::Vector2f aSecondPoint);
		CU::Vector2f GetOpositePoint(Edge* aEdge);
		CU::Vector2f GetMiddlePoint();
		bool myIsBlocked;
	};
};
#endif