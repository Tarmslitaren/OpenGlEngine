#include "stdafx.h"
#include "node.h"

Node::Node()
{
	currDist = 0;
	isSelected = false;
	isStart = false;
	isEnd = false;
	myPredator=NULL;
	isPassable = true;
	myLinks.Init(12,6);
}
Node::Node(CU::Vector3f aPos)
{
	currDist = 0;
	myPosition = aPos;
	isSelected = false;
	isStart = false;
	isEnd = false;
	isCover = false;
	myPredator=NULL;
	isPassable = true;
	myLinks.Init(12,6);
}
Node::~Node()
{
}

void Node::UpdateCosts()
{
	for(int i = 0; i < myLinks.Count(); i++)
	{
		myLinks[i].myCost = (myPosition - myLinks[i].myDestination->myPosition).Length();
	}
}
bool Node::operator<(const Node& aNode)
{
	if(currDist < aNode.currDist)
	{
		return true;
	}
	return false;
}
bool Node::operator>(const Node& aNode)
{
	if(currDist > aNode.currDist)
	{
		return true;
	}
	return false;
}
bool Node::operator==(const Node& aNode)
{
	if(currDist==aNode.currDist && myPosition==aNode.myPosition && isSelected==aNode.isSelected && myPredator==aNode.myPredator)
	{
		return true;
	}

	
	return false;
}