#include "stdafx.h"
#include "Triangle.h"
#include "Edge.h"
#include "assert.h"
CommonUtilities::Triangle::Triangle()
{
	myEdges[0] = NULL;
	myEdges[1] = NULL;
	myEdges[2] = NULL;
	myIsBlocked = false;
}

CommonUtilities::Triangle::~Triangle()
{
}


CommonUtilities::Edge* CommonUtilities::Triangle::GetEdgeWithPoints(CU::Vector2f aFirstPoint, CU::Vector2f aSecondPoint)
{
	for(int i = 0; i < 3; i++)
	{
		if(myEdges[i] != NULL)
		{
			int pointCounter = 0;
			if(myEdges[i]->myPoints[0] == aFirstPoint)
			{
				pointCounter++;
			}
			if(myEdges[i]->myPoints[0] == aSecondPoint)
			{
				pointCounter++;
			}
			if(myEdges[i]->myPoints[1] == aFirstPoint)
			{
				pointCounter++;
			}
			if(myEdges[i]->myPoints[1] == aSecondPoint)
			{
				pointCounter++;
			}
			if(pointCounter == 2)
			{
				return myEdges[i];
			}
		}
		else
		{
			assert(0 && "a tri shouldnt have null edges");
		}
	}
	assert(0 && "didnt find the edge");
	return NULL;
}

CU::Vector2f CommonUtilities::Triangle::GetOpositePoint(Edge* aEdge)
{
	for(int edgeIndex = 0; edgeIndex < 3; edgeIndex++)
	{
		if(myEdges[edgeIndex] != aEdge)
		{
			if((myEdges[edgeIndex]->myPoints[0] == aEdge->myPoints[0]) == false && (myEdges[edgeIndex]->myPoints[0] == aEdge->myPoints[1]) == false)
			{
				return myEdges[edgeIndex]->myPoints[0];
			}
			else if((myEdges[edgeIndex]->myPoints[1] == aEdge->myPoints[0]) == false && (myEdges[edgeIndex]->myPoints[1] == aEdge->myPoints[1]) == false)
			{
				return myEdges[edgeIndex]->myPoints[1];
			}
			assert(0 && "fCommonUtilities");
		}
	}
	assert(0 && "fCommonUtilities");
	return myEdges[0]->myPoints[1];
}

CU::Vector2f CommonUtilities::Triangle::GetMiddlePoint()
{
	CU::Vector2f p1 = myEdges[0]->myPoints[0];
	CU::Vector2f p2 = myEdges[0]->myPoints[1];
	CU::Vector2f p3 = GetOpositePoint(myEdges[0]);

	p1 += p2;
	p1 += p3;
	p1 /= 3;
	return p1;
}

