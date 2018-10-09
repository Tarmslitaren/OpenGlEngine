#include "stdafx.h"
#include "Edge.h"
#include <vector>

#include "assert.h"
#include "triangle.h"
CommonUtilities::Edge::Edge()
{
	mySides[0] = NULL;
	mySides[1] = NULL;
	myIsConnected = false;
}

CommonUtilities::Edge::~Edge()
{
}


bool CommonUtilities::Edge::LineIntersect(CU::Vector2f aLineStart,CU::Vector2f aLineEnd,CU::Vector2f& anIntersectionPoint)
{
	CU::Vector2f kDiff = myPoints[0] - aLineStart;
	CU::Vector2f myDir = myPoints[1] - myPoints[0];
	CU::Vector2f lineDir = aLineEnd - aLineStart;

	float fD0DotPerpD1 = lineDir.DotPerd(myDir);
	if (abs(fD0DotPerpD1) > 0.001f)
	{
		// lines intersect in a single point
		float fInvD0DotPerpD1 = (1.0f)/fD0DotPerpD1;
		float fDiffDotPerpD0 = kDiff.DotPerd(lineDir);
		float fDiffDotPerpD1 = kDiff.DotPerd(myDir);
		float as[2];
		as[0]= fDiffDotPerpD0*fInvD0DotPerpD1;
		as[1]= fDiffDotPerpD1*fInvD0DotPerpD1;
		if((as[0]<0) || (as[0]>1)) return(false); 
		if((as[1]<0) || (as[1]>1)) return(false); 
		anIntersectionPoint=myPoints[0]+myDir*as[0];
		return true;
	}
	return false;
}


CU::Vector2f CommonUtilities::Edge::GetUnConnectedPoint(Edge* anEdge)
{
	bool isConnected = false;
	if (anEdge->myPoints[0] == myPoints[0])
	{
		isConnected = true;
		return myPoints[1];

	}
	else if (anEdge->myPoints[1] == myPoints[0])
	{
		isConnected = true;
		return myPoints[1];
	}
	else if (anEdge->myPoints[0] == myPoints[1])
	{
		isConnected = true;
		return myPoints[0];
	}
	else if (anEdge->myPoints[1] == myPoints[1])
	{
		isConnected = true;
		return myPoints[0];
	}
	assert( 0 && "edge not in triangle!");
	return CU::Vector2f(0.0f,0.0f);
}

int CommonUtilities::Edge::GetTriangleIndex(Triangle* aTriangle)
{
	int returnVal = 0;
	for(;returnVal < 2; returnVal++)
	{
		if(mySides[returnVal] == aTriangle)
		{
			return returnVal;
		}
	}
	assert(0 && "didnt find the tri");
	return 0;
}