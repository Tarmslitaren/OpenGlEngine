#include "StdAfx.h"
#include "AstarGraph.h"
#include "Graph.h"

AstarGraph::AstarGraph()
{
	myOpenList.Init(1024,512);
	myClosedList.Init(1024,512);
	myReturnVector.Init(1024,512);
	//myReturnVector.Init(1000,1000);

	myFoundPath = false;
}

AstarGraph::~AstarGraph()
{
}

const CU::GrowingArray<Node*>& AstarGraph::GetPath(Node* aStartNode, Node* aEndNode)
{
	myReturnVector.RemoveAll();
	myFoundPath = false;
	myOpenList.RemoveAll();
	myClosedList.RemoveAll();
	
	myStartNode = aStartNode;
	myEndNode = aEndNode;

	AstarNode tempNode;
	tempNode.F = 0;
	tempNode.G = 0;
	tempNode.H = 0;
	tempNode.myNode = aStartNode;
	myOpenList.Add(tempNode);

	while(myOpenList.Count() != 0)
	{
		unsigned int lowestFCostIndex = 0;
		for(int openIndex = 0; openIndex < myOpenList.Count(); openIndex++)
		{
			if(myOpenList[openIndex].F < myOpenList[lowestFCostIndex].F)
			{
				lowestFCostIndex = openIndex;
			}
		}
		AstarNode curNode = myOpenList[lowestFCostIndex];
		myClosedList.Add(curNode);

		if(curNode.myNode == aEndNode)
		{
			Node* tempNode = curNode.myNode;
			while(tempNode != aStartNode)
			{
				myReturnVector.Add(tempNode);
				tempNode = tempNode->myPredator;
			}
			myReturnVector.Add(tempNode);
			return myReturnVector;
		}

		myOpenList.RemoveCyclicAtIndex(lowestFCostIndex);
		CheckNode(curNode);	
	}
	return myReturnVector;
}


void AstarGraph::CheckNode(const AstarNode& aNode)
{
	for(int linkIndex = 0;linkIndex < aNode.myNode->myLinks.Count(); linkIndex++)
	{
		bool isInClosed = false;
		for(int closedIndex = 0; closedIndex < myClosedList.Count(); closedIndex++)
		{
			if(myClosedList[closedIndex].myNode == aNode.myNode->myLinks[linkIndex].myDestination)
			{
				isInClosed = true;
				break;
			}
		}
		if(isInClosed == false)
		{
			bool isInOpenList = false;
			for(int openIndex = 0; openIndex < myOpenList.Count(); openIndex++)
			{
				if(myOpenList[openIndex].myNode == aNode.myNode->myLinks[linkIndex].myDestination)
				{
					isInOpenList = true;
					if(myOpenList[openIndex].G > aNode.G + aNode.myNode->myLinks[linkIndex].myCost)
					{
						myOpenList[openIndex].myNode->myPredator = aNode.myNode;
						myOpenList[openIndex].G = aNode.G + static_cast<int>(aNode.myNode->myLinks[linkIndex].myCost);
						myOpenList[openIndex].H = static_cast<int>((myEndNode->myPosition - myOpenList[openIndex].myNode->myPosition).Length())*2;
						myOpenList[openIndex].F = myOpenList[openIndex].G + myOpenList[openIndex].H;
					}
					break;
				}
			}
			if(isInOpenList == false)
			{
				AstarNode tempANode;
				tempANode.myNode = aNode.myNode->myLinks[linkIndex].myDestination;
				tempANode.G = aNode.G + static_cast<int>(aNode.myNode->myLinks[linkIndex].myCost);
				tempANode.H = static_cast<int>((myEndNode->myPosition - tempANode.myNode->myPosition).Length())*2;
				tempANode.F = tempANode.G + tempANode.H;
				tempANode.myNode->myPredator = aNode.myNode;

				myOpenList.Add(tempANode);
			}
		}
	}
}