#include <stdafx.h>
#include "Graph.h"

Graph::Graph()
{
	myNodes.Init(10000,1000);

}
Graph::~Graph()
{
}

void Graph::Reset()
{
	for(int i=0;i<myNodes.Count();i++)
	{
		myNodes[i].myPredator=NULL;
	}
}
void Graph::UpdateCosts()
{
	for(int i=0;i<myNodes.Count();i++)
	{
		myNodes[i].UpdateCosts();
	}
}
Node* Graph::AddNode(Node aNode)
{
	myNodes.Add(aNode);
	return(&myNodes[myNodes.Count() -1]);
}

void Graph::CreateLink(Node* Node1, Node* Node2)
{
	Link aLink;
	aLink.myCost = (Node1->myPosition - Node2->myPosition).Length();
	aLink.myDestination = Node1;
	aLink.myPredator = Node2;
	Node2->myLinks.Add(aLink);
	aLink.myDestination = Node2;
	aLink.myPredator = Node1;
	Node1->myLinks.Add(aLink);
}
Node* Graph::GetNodeAtPosition(CU::Vector3f aPos)
{
	for(int i = 0; i <myNodes.Count(); i++)
	{
		if(aPos.myX + 1.0f >= myNodes[i].myPosition.myX && aPos.myX <= myNodes[i].myPosition.myX + 1.0f)
		{
			if(aPos.myY + 1.0f >= myNodes[i].myPosition.myY && aPos.myY <= myNodes[i].myPosition.myY + 1.0f)
			{
				if(aPos.myZ + 1.0f >= myNodes[i].myPosition.myZ && aPos.myZ <= myNodes[i].myPosition.myZ + 1.0f)
				{
					return &myNodes[i];
				}
			}
		}
	}
	assert(0 && "Didnt find astar node at pospos");
	return(NULL);
}

Node* Graph::GetClosestNodeAtPosition(CU::Vector3f aPos)
{
	float closest = 2048.0f;
	int savedIndex = 0;
	for(int i = 0; i <myNodes.Count(); i++)
	{
		float lth = (aPos - myNodes[i].myPosition).Length();
		if(lth < closest)
		{
			savedIndex = i;
			closest = lth;
		}
	}
	return &myNodes[savedIndex];
}