#include "stdafx.h"
#include "NavMesh.h"
#include "intersections.h"
#include "Converters.h"

CU::NavMesh::NavMesh()
{
	myTriangles.Init(1000,1000);
	myEdges.Init(1000,1000);
	myBlockedEdges.Init(1000,1000);
	myBlockedSquares.Init(100,100);
}

CU::NavMesh::~NavMesh()
{
}

void CU::NavMesh::Init(CU::Vector2f aUppderLeftPos, CU::Vector2f aLowerRightPos)
{
	myUppderLeftPos = aUppderLeftPos;
	myLowerRightPos = aLowerRightPos;

	CU::Triangle* firstTri = new CU::Triangle();
	CU::Edge* Edge1 = new CU::Edge();
	CU::Edge* Edge2 = new CU::Edge();
	CU::Edge* Edge3 = new CU::Edge();

	Edge1->myPoints[0].Set(aUppderLeftPos.myX,aUppderLeftPos.myY);
	Edge1->myPoints[1].Set(aLowerRightPos.myX,aUppderLeftPos.myY);
	Edge2->myPoints[0].Set(aLowerRightPos.myX,aUppderLeftPos.myY);
	Edge2->myPoints[1].Set(aLowerRightPos.myX,aLowerRightPos.myY);
	Edge3->myPoints[0].Set(aLowerRightPos.myX,aLowerRightPos.myY);
	Edge3->myPoints[1].Set(aUppderLeftPos.myX,aUppderLeftPos.myY);

	myTriangles.Add(firstTri);

	myEdges.Add(Edge1);
	myEdges.Add(Edge2);
	myEdges.Add(Edge3);

	myTriangles[0]->myEdges[0] = myEdges[0];
	myTriangles[0]->myEdges[1] = myEdges[1];
	myTriangles[0]->myEdges[2] = myEdges[2];

	myEdges[0]->mySides[0] = myTriangles[0];
	myEdges[1]->mySides[0] = myTriangles[0];
	myEdges[2]->mySides[0] = myTriangles[0];

	CU::Triangle* secondTri = new CU::Triangle();

	CU::Edge* Edge4 = new CU::Edge();
	CU::Edge* Edge5 = new CU::Edge();

	Edge4->myPoints[0].Set(aUppderLeftPos.myX,aUppderLeftPos.myY);
	Edge4->myPoints[1].Set(aUppderLeftPos.myX,aLowerRightPos.myY);

	Edge5->myPoints[0].Set(aUppderLeftPos.myX,aLowerRightPos.myY);
	Edge5->myPoints[1].Set(aLowerRightPos.myX,aLowerRightPos.myY);

	myTriangles.Add(secondTri);

	myEdges.Add(Edge4);
	myEdges.Add(Edge5);

	myTriangles[1]->myEdges[0] = myEdges[2];
	myTriangles[1]->myEdges[1] = myEdges[3];
	myTriangles[1]->myEdges[2] = myEdges[4];

	myEdges[2]->mySides[1] = myTriangles[1];
	myEdges[3]->mySides[0] = myTriangles[1];
	myEdges[4]->mySides[0] = myTriangles[1];
	
	
}

void CU::NavMesh::MakeAstarGraph()
{
	for(int triIndex = 0; triIndex < myTriangles.Count(); triIndex++)
	{
		myGraph.AddNode(Node(CU::Vector3f(myTriangles[triIndex]->GetMiddlePoint().myX,myTriangles[triIndex]->GetMiddlePoint().myY,0)));
	}

	for(int triIndex = 0; triIndex < myTriangles.Count(); triIndex++)
	{
		for(int edgeIndex = 0; edgeIndex < 3; edgeIndex++)
		{
			if(myTriangles[triIndex]->myEdges[edgeIndex]->myIsConnected == false)
			{
				Triangle* firstTri = NULL;
				Triangle* secondTri = NULL;

				firstTri = myTriangles[triIndex];

				if(firstTri != NULL && firstTri->myIsBlocked == false)
				{
					if(myTriangles[triIndex]->myEdges[edgeIndex]->mySides[0] != firstTri)
					{
						secondTri = myTriangles[triIndex]->myEdges[edgeIndex]->mySides[0];
						if( secondTri != NULL && secondTri->myIsBlocked == false)
						{
							myGraph.CreateLink(&myGraph.myNodes[triIndex],&myGraph.myNodes[GetTriIndex( myTriangles[triIndex]->myEdges[edgeIndex]->mySides[0])]);
							myTriangles[triIndex]->myEdges[edgeIndex]->myIsConnected = true;
						}
					}

					if(myTriangles[triIndex]->myEdges[edgeIndex]->mySides[1] != firstTri)
					{
						secondTri = myTriangles[triIndex]->myEdges[edgeIndex]->mySides[1];
						if(secondTri != NULL && secondTri->myIsBlocked == false)
						{
							myGraph.CreateLink(&myGraph.myNodes[triIndex],&myGraph.myNodes[GetTriIndex(myTriangles[triIndex]->myEdges[edgeIndex]->mySides[1])]);
							myTriangles[triIndex]->myEdges[edgeIndex]->myIsConnected = true;
						}
					}
				}
			}
		}
	}
}

void CU::NavMesh::CollideLine(CU::Vector2f aFirstPoint, CU::Vector2f aSecondPoint)
{
	std::vector<CU::Edge*> splitThis;
	std::vector<CU::Vector2f> splitPoints;
	splitThis.reserve(1000);

	for (int i = 0; i < myEdges.Count();i++)
	{
		CU::Vector2f splitPoint;
		if(myEdges[i] != NULL)
		{
			if (myEdges[i]->LineIntersect(aFirstPoint, aSecondPoint, splitPoint))
			{
				splitThis.push_back(myEdges[i]);
				splitPoints.push_back(splitPoint);
			}
		}

	}

	for(unsigned int splitIndex = 0; splitIndex < splitThis.size(); splitIndex++)
	{
		Split(splitThis[splitIndex], splitPoints[splitIndex]);	
	}
}

void CU::NavMesh::CollideLineWithTheseTris(CU::Vector2f aFirstPoint, CU::Vector2f aSecondPoint, CU::GrowingArray<CU::Triangle*> aTris)
{
	std::vector<CU::Edge*> splitThis;
	std::vector<CU::Vector2f> splitPoints;
	splitThis.reserve(1000);

	std::vector<CU::Edge*> splitOnlyThese;
	splitOnlyThese.reserve(5000);

	for(int triIndex = 0; triIndex < aTris.Count(); triIndex++)
	{
		bool addedAldry1 = false;
		bool addedAldry2 = false;
		bool addedAldry3 = false;
		for(unsigned int splitTri = 0; splitTri < splitOnlyThese.size(); splitTri++)
		{
			if(splitOnlyThese[splitTri] == aTris[triIndex]->myEdges[0])
			{
				addedAldry1 = true;
			}
			if(splitOnlyThese[splitTri] == aTris[triIndex]->myEdges[1])
			{
				addedAldry2 = true;
			}
			if(splitOnlyThese[splitTri] == aTris[triIndex]->myEdges[2])
			{
				addedAldry3 = true;
			}
		}
		if(addedAldry1 == false)
		{
			splitOnlyThese.push_back(aTris[triIndex]->myEdges[0]);
		}
		if(addedAldry2 == false)
		{
			splitOnlyThese.push_back(aTris[triIndex]->myEdges[1]);
		}
		if(addedAldry3 == false)
		{
			splitOnlyThese.push_back(aTris[triIndex]->myEdges[2]);
		}
	}

	for (unsigned int i = 0; i < splitOnlyThese.size();i++)
	{
		CU::Vector2f splitPoint;
		if(splitOnlyThese[i] != NULL)
		{
			if (splitOnlyThese[i]->LineIntersect(aFirstPoint, aSecondPoint, splitPoint))
			{
				splitThis.push_back(splitOnlyThese[i]);
				splitPoints.push_back(splitPoint);
			}
		}

	}

	for(unsigned int splitIndex = 0; splitIndex < splitThis.size(); splitIndex++)
	{
		Split(splitThis[splitIndex], splitPoints[splitIndex]);	
	}
}

void CU::NavMesh::Split(Edge* aSplitingEdge, CU::Vector2f aSplitPoint)
{
	CU::Vector2f p1 = aSplitingEdge->myPoints[0];
	CU::Vector2f p2 = aSplitingEdge->myPoints[1];
	CU::Vector2f p3 = aSplitPoint;
	p1.myX = Convert::AweRound(p1.myX);
	p1.myY = Convert::AweRound(p1.myY);

	p2.myX = Convert::AweRound(p2.myX);
	p2.myY = Convert::AweRound(p2.myY);

	p3.myX = Convert::AweRound(p3.myX);
	p3.myY = Convert::AweRound(p3.myY);

	if (p1 == p3)
	{
		return;
	}

	if(p2 == p3)
	{
		return;
	}

	if( aSplitingEdge->mySides[0] != NULL && aSplitingEdge->mySides[1] == NULL)
	{
		SplitOneSide(aSplitingEdge->mySides[0],aSplitingEdge,aSplitPoint);
	}
	else if ( aSplitingEdge->mySides[1] != NULL && aSplitingEdge->mySides[0] == NULL)
	{
		SplitOneSide(aSplitingEdge->mySides[1],aSplitingEdge,aSplitPoint);
	}
	else if(aSplitingEdge->mySides[0] != NULL && aSplitingEdge->mySides[1] != NULL)
	{
		SplitTwoSides(aSplitingEdge->mySides[0],aSplitingEdge->mySides[1],aSplitingEdge, aSplitPoint);
	}
	else
	{
		assert(0 && "Fail. Can't go here");
	}
}

void CU::NavMesh::SplitOneSide(Triangle* aOldTriangle, Edge* aSplitingEdge, CU::Vector2f aSplitPoint)
{
	CU::Triangle* oldTri1 = aOldTriangle;
	
	CU::Vector2f oldTriPoint1 = aSplitingEdge->myPoints[0];
	CU::Vector2f oldTriPoint2 = aSplitingEdge->myPoints[1];
	CU::Vector2f oldTriPoint3 = aOldTriangle->GetOpositePoint(aSplitingEdge);

	CU::Edge* oldEdge1 = oldTri1->GetEdgeWithPoints(oldTriPoint1,oldTriPoint3);
	CU::Edge* oldEdge2 = oldTri1->GetEdgeWithPoints(oldTriPoint2,oldTriPoint3);

	
	if(oldTriPoint1 == aSplitPoint)
	{
		return;
	}
	else if(aSplitPoint == oldTriPoint2)
	{
		return;
	}
	else if(aSplitPoint == oldTriPoint3)
	{
		return;
	}

	CU::Vector2f splittingPoint = aSplitPoint;

	CU::Edge* newEdge1 = new CU::Edge();
	CU::Edge* newEdge2 = new CU::Edge();
	CU::Edge* newEdge3 = new CU::Edge();

	myEdges.Add(newEdge1);
	myEdges.Add(newEdge2);
	myEdges.Add(newEdge3);

	newEdge1->myPoints[0] = oldTriPoint1;
	newEdge1->myPoints[1] = splittingPoint;

	newEdge2->myPoints[0] = splittingPoint;
	newEdge2->myPoints[1] = oldTriPoint2;

	newEdge3->myPoints[0] = splittingPoint;
	newEdge3->myPoints[1] = oldTriPoint3;

	CU::Triangle* newTriangle1 = new CU::Triangle();
	CU::Triangle* newTriangle2 = new CU::Triangle();

	oldEdge1->mySides[oldEdge1->GetTriangleIndex(aOldTriangle)] = newTriangle1;
	oldEdge2->mySides[oldEdge2->GetTriangleIndex(aOldTriangle)] = newTriangle2;

	myTriangles.Add(newTriangle1);
	myTriangles.Add(newTriangle2);

	newTriangle1->myEdges[0] = newEdge1;
	newTriangle1->myEdges[1] = newEdge3;
	newTriangle1->myEdges[2] = oldEdge1;

	newTriangle2->myEdges[0] = newEdge2;
	newTriangle2->myEdges[1] = oldEdge2;
	newTriangle2->myEdges[2] = newEdge3;

	newEdge1->mySides[0] = newTriangle1;

	newEdge2->mySides[0] = newTriangle2;

	newEdge3->mySides[0] = newTriangle1;
	newEdge3->mySides[1] = newTriangle2;

	for(int edgeIndex = 0; edgeIndex < myEdges.Count(); edgeIndex++)
	{
		if(myEdges[edgeIndex] == aSplitingEdge)
		{
			delete myEdges[edgeIndex];
			myEdges[edgeIndex] = NULL;
			myEdges.RemoveCyclicAtIndex(edgeIndex);
			break;
		}
	}

	for(int triangleIndex = 0; triangleIndex < myTriangles.Count(); triangleIndex++)
	{
		if(myTriangles[triangleIndex] == aOldTriangle)
		{
			delete myTriangles[triangleIndex];
			myTriangles[triangleIndex] = NULL;
			myTriangles.RemoveCyclicAtIndex(triangleIndex);
			break;
		}
	}
}

void CU::NavMesh::SplitTwoSides(Triangle* aFirstOldTriangle, Triangle* aSecondOldTriangle, Edge* aSplitingEdge, CU::Vector2f aSplitPoint)
{
	

	CU::Triangle* oldTriangle1 = aFirstOldTriangle;
	CU::Triangle* oldTriangle2 = aSecondOldTriangle;

	CU::Edge* oldEdge = aSplitingEdge;

	CU::Vector2f OT1P1 = oldTriangle1->GetOpositePoint(oldEdge);
	CU::Vector2f OT1P2 = oldEdge->myPoints[1];
	CU::Vector2f OT1P3 = oldEdge->myPoints[0];

	CU::Vector2f OT2P1 = oldTriangle2->GetOpositePoint(oldEdge);
	CU::Vector2f OT2P2 = oldEdge->myPoints[1];
	CU::Vector2f OT2P3 = oldEdge->myPoints[0];

	CU::Edge* OT1E1 = oldTriangle1->GetEdgeWithPoints(OT1P1,OT1P2);
	CU::Edge* OT1E2 = oldTriangle1->GetEdgeWithPoints(OT1P1,OT1P3);
	CU::Edge* OT2E1 = oldTriangle2->GetEdgeWithPoints(OT2P2,OT2P1);
	CU::Edge* OT2E2 = oldTriangle2->GetEdgeWithPoints(OT2P1,OT2P3);

	if(aSplitPoint == OT1P2)
	{
		return;
	}
	else if(aSplitPoint == OT1P3)
	{
		return;
	}
	else if(aSplitPoint == OT1P1)
	{
		return;
	}
	else if(aSplitPoint == OT2P1)
	{
		return;
	}

	CU::Edge* NE1 = new CU::Edge();
	CU::Edge* NE2 = new CU::Edge();
	CU::Edge* NE3 = new CU::Edge();
	CU::Edge* NE4 = new CU::Edge();

	CU::Triangle* NT1 = new CU::Triangle();
	CU::Triangle* NT2 = new CU::Triangle();
	CU::Triangle* NT3 = new CU::Triangle();
	CU::Triangle* NT4 = new CU::Triangle();

	myEdges.Add(NE1);
	myEdges.Add(NE2);
	myEdges.Add(NE3);
	myEdges.Add(NE4);

	myTriangles.Add(NT1);
	myTriangles.Add(NT2);
	myTriangles.Add(NT3);
	myTriangles.Add(NT4);

	NE1->myPoints[0] = OT1P2;
	NE1->myPoints[1] = aSplitPoint;
	NE1->mySides[0] = NT1;
	NE1->mySides[1] = NT4;

	NE2->myPoints[0] = aSplitPoint;
	NE2->myPoints[1] = OT1P3;
	NE2->mySides[0] = NT2;
	NE2->mySides[1] = NT3;

	NE3->myPoints[0] = aSplitPoint;
	NE3->myPoints[1] = OT1P1;
	NE3->mySides[0] = NT1;
	NE3->mySides[1] = NT2;

	NE4->myPoints[0] = aSplitPoint;
	NE4->myPoints[1] = OT2P1;
	NE4->mySides[0] = NT3;
	NE4->mySides[1] = NT4;

	OT2E1->mySides[OT2E1->GetTriangleIndex(oldTriangle2)] = NT4;
	OT2E2->mySides[OT2E2->GetTriangleIndex(oldTriangle2)] = NT3;

	OT1E1->mySides[OT1E1->GetTriangleIndex(oldTriangle1)] = NT1;
	OT1E2->mySides[OT1E2->GetTriangleIndex(oldTriangle1)] = NT2;

	NT1->myEdges[0] = OT1E1;
	NT1->myEdges[1] = NE3;
	NT1->myEdges[2] = NE1;

	NT2->myEdges[0] = OT1E2;
	NT2->myEdges[1] = NE2;
	NT2->myEdges[2] = NE3;

	NT3->myEdges[0] = NE2;
	NT3->myEdges[1] = OT2E2;
	NT3->myEdges[2] = NE4;

	NT4->myEdges[0] = NE1;
	NT4->myEdges[1] = NE4;
	NT4->myEdges[2] = OT2E1;

	for(int edgeIndex = 0; edgeIndex < myEdges.Count(); edgeIndex++)
	{
		if(myEdges[edgeIndex] == aSplitingEdge)
		{
			delete myEdges[edgeIndex];
			myEdges[edgeIndex] = NULL;
			myEdges.RemoveCyclicAtIndex(edgeIndex);
			break;
		}
	}

	for(int triangleIndex = 0; triangleIndex < myTriangles.Count(); triangleIndex++)
	{
		if(myTriangles[triangleIndex] == aFirstOldTriangle)
		{
			delete myTriangles[triangleIndex];
			myTriangles[triangleIndex] = NULL;
			myTriangles.RemoveCyclicAtIndex(triangleIndex);
			break;
		}
	}

	for(int triangleIndex = 0; triangleIndex < myTriangles.Count(); triangleIndex++)
	{
		if(myTriangles[triangleIndex] == aSecondOldTriangle)
		{
			delete myTriangles[triangleIndex];
			myTriangles[triangleIndex] = NULL;
			myTriangles.RemoveCyclicAtIndex(triangleIndex);
			break;
		}
	}
}



void CU::NavMesh::StencilOutAASquare(CU::Vector2f aSquareFirstPos, CU::Vector2f aSquareSecondPos)
{
	//palla göra icke axis aligend nu. sen.
	CU::Vector2f firstLineFirstPos;
	CU::Vector2f firstLineSecondPos;

	CU::Vector2f secondLineFirstPos;
	CU::Vector2f secondLineSecondPos;

	CU::Vector2f thirdLineFirstPos;
	CU::Vector2f thirdLineSecondPos;

	CU::Vector2f fourthLineFirstPos;
	CU::Vector2f fourthLineSecondPos;

	firstLineFirstPos.myY = myUppderLeftPos.myY;
	firstLineFirstPos.myX = aSquareFirstPos.myX;
	firstLineSecondPos.myY = myLowerRightPos.myY;
	firstLineSecondPos.myX = aSquareFirstPos.myX;
	CollideLine(firstLineFirstPos, firstLineSecondPos);

	secondLineFirstPos.myY = myUppderLeftPos.myY;
	secondLineFirstPos.myX = aSquareSecondPos.myX;
	secondLineSecondPos.myY = myLowerRightPos.myY;
	secondLineSecondPos.myX = aSquareSecondPos.myX;
	CollideLine(secondLineFirstPos, secondLineSecondPos);

	thirdLineFirstPos.myX = myUppderLeftPos.myX;
	thirdLineFirstPos.myY = aSquareFirstPos.myY;
	thirdLineSecondPos.myX = myLowerRightPos.myX;
	thirdLineSecondPos.myY = aSquareFirstPos.myY;
	CollideLine(thirdLineFirstPos, thirdLineSecondPos);

	fourthLineFirstPos.myX = myUppderLeftPos.myX;
	fourthLineFirstPos.myY = aSquareSecondPos.myY;
	fourthLineSecondPos.myX = myLowerRightPos.myX;
	fourthLineSecondPos.myY = aSquareSecondPos.myY;
	CollideLine(fourthLineFirstPos, fourthLineSecondPos);

	for (int i = 0; i < myTriangles.Count(); i++)
	{
		CU::Vector2f p1 = myTriangles[i]->myEdges[0]->myPoints[0];
		CU::Vector2f p2 = myTriangles[i]->myEdges[0]->myPoints[1];
		CU::Vector2f p3 = myTriangles[i]->GetOpositePoint(myTriangles[i]->myEdges[0]);


		if(Intersections::TriangleIsInsideSquare(p1, p2, p3, aSquareFirstPos, aSquareSecondPos))
		{
			myTriangles[i]->myIsBlocked = true;
			myBlockedEdges.Add(myTriangles[i]->myEdges[0]);
			myBlockedEdges.Add(myTriangles[i]->myEdges[1]);
			myBlockedEdges.Add(myTriangles[i]->myEdges[2]);
		}

	}
}

void CU::NavMesh::StencilOutTriangle(CU::Vector2f aTrianglePoint1, CU::Vector2f aTrianglePoint2, CU::Vector2f aTrianglePoint3)
{
	CU::GrowingArray<Triangle*> stencilThis;
	stencilThis.Init(5000,2500);
	for(int triIndex = 0; triIndex < myTriangles.Count(); triIndex++)
	{
		if(Intersections::TriangleTriangleIntersection(aTrianglePoint1,aTrianglePoint2,aTrianglePoint3,myTriangles[triIndex]->myEdges[0]->myPoints[0],myTriangles[triIndex]->myEdges[0]->myPoints[1],myTriangles[triIndex]->GetOpositePoint(myTriangles[triIndex]->myEdges[0])))
		{
			bool addedAlready = false;
			for(int stencilTriIndex = 0; stencilTriIndex < stencilThis.Count(); stencilTriIndex++)
			{
				if(stencilThis[stencilTriIndex] == myTriangles[triIndex])
				{
					addedAlready = true;
				}
			}
			if(addedAlready == false)
			{
				stencilThis.Add(myTriangles[triIndex]);
			}
		}
	}

	CU::Vector2f lin1 = aTrianglePoint1 - aTrianglePoint2;
	CU::Vector2f lin2 = aTrianglePoint1 - aTrianglePoint3;
	CU::Vector2f lin3 = aTrianglePoint2 - aTrianglePoint3;

	lin1.Normalize();
	lin2.Normalize();
	lin3.Normalize();

	CollideLineWithTheseTris(aTrianglePoint1 + lin1 * 1000.0f,aTrianglePoint1 + lin1 * -1000.0f,stencilThis);

	stencilThis.RemoveAll();
	for(int triIndex = 0; triIndex < myTriangles.Count(); triIndex++)
	{
		if(Intersections::TriangleTriangleIntersection(aTrianglePoint1,aTrianglePoint2,aTrianglePoint3,myTriangles[triIndex]->myEdges[0]->myPoints[0],myTriangles[triIndex]->myEdges[0]->myPoints[1],myTriangles[triIndex]->GetOpositePoint(myTriangles[triIndex]->myEdges[0])))
		{
			bool addedAlready = false;
			for(int stencilTriIndex = 0; stencilTriIndex < stencilThis.Count(); stencilTriIndex++)
			{
				if(stencilThis[stencilTriIndex] == myTriangles[triIndex])
				{
					addedAlready = true;
				}
			}
			if(addedAlready == false)
			{
				stencilThis.Add(myTriangles[triIndex]);
			}
		}
	}

	CollideLineWithTheseTris(aTrianglePoint1 + lin2 * 1000.0f,aTrianglePoint1 + lin2 * -1000.0f,stencilThis);

	stencilThis.RemoveAll();
	for(int triIndex = 0; triIndex < myTriangles.Count(); triIndex++)
	{
		if(Intersections::TriangleTriangleIntersection(aTrianglePoint1,aTrianglePoint2,aTrianglePoint3,myTriangles[triIndex]->myEdges[0]->myPoints[0],myTriangles[triIndex]->myEdges[0]->myPoints[1],myTriangles[triIndex]->GetOpositePoint(myTriangles[triIndex]->myEdges[0])))
		{
			bool addedAlready = false;
			for(int stencilTriIndex = 0; stencilTriIndex < stencilThis.Count(); stencilTriIndex++)
			{
				if(stencilThis[stencilTriIndex] == myTriangles[triIndex])
				{
					addedAlready = true;
				}
			}
			if(addedAlready == false)
			{
				stencilThis.Add(myTriangles[triIndex]);
			}
		}
	}

	CollideLineWithTheseTris(aTrianglePoint2 + lin3 * 1000.0f,aTrianglePoint1 + lin3 * -1000.0f,stencilThis);

	
}

CU::GrowingArray<CU::Vector2f> CU::NavMesh::GetPath(CU::Vector2f aStartPoint, CU::Vector2f aEndPoint)
{
	CU::GrowingArray<CU::Vector2f> returnVec;
	returnVec.Init(100,100);

	Node* startNode = NULL;
	Node* endNode = NULL;

	for(int triIndex = 0; triIndex < myTriangles.Count(); triIndex++)
	{
		CU::Vector2f p1 = myTriangles[triIndex]->myEdges[0]->myPoints[0];
		CU::Vector2f p2 = myTriangles[triIndex]->myEdges[0]->myPoints[1];
		CU::Vector2f p3 = myTriangles[triIndex]->GetOpositePoint(myTriangles[triIndex]->myEdges[0]);
		static int tempCheck = 0;
		if(Intersections::martinPointTriInterSect(aStartPoint,p1,p2,p3) == true)
		{
			startNode = &myGraph.myNodes[triIndex];
			tempCheck++;
		}

		if(Intersections::martinPointTriInterSect(aEndPoint,p1,p2,p3) == true)
		{
			endNode = &myGraph.myNodes[triIndex];
			tempCheck++;
			if(myTriangles[triIndex]->myIsBlocked == false)
			{
				returnVec.Add(aEndPoint);
			}
			else
			{
				return returnVec;
			}

			if(tempCheck == 2)
			{
				break;
			}
		}
	}
	if (startNode == NULL || endNode == NULL)
	{
		return returnVec;
	}

	CU::GrowingArray<Node*> nodePath = myAGraph.GetPath(startNode,endNode);


	for(int nodeIndex = 0; nodeIndex < nodePath.Count(); nodeIndex++)
	{
		//returnVec.Add(nodePath[nodeIndex]->myPosition); //TODO doesnt work with vector3
	}

	return returnVec;
}

std::vector<CU::Vector2f> CU::NavMesh::GetBlockedTriangles()
{
	std::vector<CU::Vector2f> returnPoss;
	for(int triIndex = 0; triIndex < myTriangles.Count(); triIndex++)
	{
		if(myTriangles[triIndex]->myIsBlocked == true)
		{
			returnPoss.push_back(myTriangles[triIndex]->GetMiddlePoint());
		}
	}
	assert(returnPoss.size() > 0);

	return returnPoss;
}

int CU::NavMesh::GetTriIndex(CU::Triangle* aTri)
{
	for(int triIndex = 0; triIndex < myTriangles.Count(); triIndex++)
	{
		if(myTriangles[triIndex] == aTri)
		{
			return triIndex;
		}
	}
	assert(0 && "fail no tri");
	return 0;
}

std::vector<CU::Vector2f> CU::NavMesh::GetAllTriPoints()
{
	std::vector<CU::Vector2f> returnVec;
	for(int triIndex = 0; triIndex < myTriangles.Count(); triIndex++)
	{
		CU::Vector2f p1 = myTriangles[triIndex]->myEdges[0]->myPoints[0];
		CU::Vector2f p2 = myTriangles[triIndex]->myEdges[0]->myPoints[1];
		CU::Vector2f p3 = myTriangles[triIndex]->GetOpositePoint(myTriangles[triIndex]->myEdges[0]);
		returnVec.push_back(p1);
		returnVec.push_back(p2);
		returnVec.push_back(p3);
	}
	return returnVec;
}

std::vector<CU::Vector2f> CU::NavMesh::GetAllBlockedTriPoints()
{
	std::vector<CU::Vector2f> returnVec;
	for(int triIndex = 0; triIndex < myTriangles.Count(); triIndex++)
	{
		if(myTriangles[triIndex]->myIsBlocked == true)
		{
			CU::Vector2f p1 = myTriangles[triIndex]->myEdges[0]->myPoints[0];
			CU::Vector2f p2 = myTriangles[triIndex]->myEdges[0]->myPoints[1];
			CU::Vector2f p3 = myTriangles[triIndex]->GetOpositePoint(myTriangles[triIndex]->myEdges[0]);
			returnVec.push_back(p1);
			returnVec.push_back(p2);
			returnVec.push_back(p3);
		}
	}
	return returnVec;
}

std::vector<CU::Vector2f> CU::NavMesh::GetAllNonBlockedPoints()
{
	std::vector<CU::Vector2f> returnVec;
	for(int triIndex = 0; triIndex < myTriangles.Count(); triIndex++)
	{
		if(myTriangles[triIndex]->myIsBlocked == false)
		{
			CU::Vector2f p1 = myTriangles[triIndex]->myEdges[0]->myPoints[0];
			CU::Vector2f p2 = myTriangles[triIndex]->myEdges[0]->myPoints[1];
			CU::Vector2f p3 = myTriangles[triIndex]->GetOpositePoint(myTriangles[triIndex]->myEdges[0]);
			returnVec.push_back(p1);
			returnVec.push_back(p2);
			returnVec.push_back(p3);
		}
	}
	return returnVec;
}

CU::GrowingArray<CU::Vector2f> CU::NavMesh::GetAllStarNodes()
{
	CU::GrowingArray<CU::Vector2f> returnVec;
	returnVec.Init(myGraph.myNodes.Count()+4,100);
	for(int nodeIndex = 0; nodeIndex < myGraph.myNodes.Count(); nodeIndex++)
	{
		if(myTriangles[nodeIndex]->myIsBlocked == false)
		{
			//returnVec.Add(myGraph.myNodes[nodeIndex].myPosition); // TODO: doesnt work with vector 3
		}
	}
	return returnVec;
}

const CU::GrowingArray<CU::SquareWrap>& CU::NavMesh::GetAllBlockedSquares()
{
	return myBlockedSquares;
}

const CU::GrowingArray<CU::Edge*>& CU::NavMesh::GetAllBlockedEdges()
{
	return myBlockedEdges;
}

void CU::NavMesh::BlockSquare(CU::Vector2f aFirstPoint,CU::Vector2f aSecondPoint)
{
	for (int i = 0; i < myTriangles.Count(); i++)
	{
		CU::Vector2f p1 = myTriangles[i]->myEdges[0]->myPoints[0];
		CU::Vector2f p2 = myTriangles[i]->myEdges[0]->myPoints[1];
		CU::Vector2f p3 = myTriangles[i]->GetOpositePoint(myTriangles[i]->myEdges[0]);

		if(Intersections::TriangleIsInsideSquare(p1, p2, p3, aFirstPoint, aSecondPoint))
		{
			myTriangles[i]->myIsBlocked = true;
			myBlockedEdges.Add(myTriangles[i]->myEdges[0]);
			myBlockedEdges.Add(myTriangles[i]->myEdges[1]);
			myBlockedEdges.Add(myTriangles[i]->myEdges[2]);
		}
	}
}

void CU::NavMesh::AddBlockedSquare(CU::Vector2f aFirstPoint,CU::Vector2f aSecondPoint)
{
	SquareWrap newSquare;
	newSquare.myFirstPoint = aFirstPoint;
	newSquare.mySecondPoint = aSecondPoint;
	myBlockedSquares.Add(newSquare);
}

void CU::NavMesh::BlockAllAddedSquares()
{
	for(int blockIndex = 0; blockIndex < myBlockedSquares.Count(); blockIndex++)
	{
		BlockSquare(myBlockedSquares[blockIndex].myFirstPoint,myBlockedSquares[blockIndex].mySecondPoint);
	}
	//myBlockedSquares.RemoveAll();
}