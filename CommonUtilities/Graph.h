#ifndef GRAPH_HEADER
#define GRAPH_HEADER


#include "Node.h"

class Graph
{
public:
	Graph();
	~Graph();
	void Reset();
	void UpdateCosts();

	Node* AddNode(Node aNode);
	void CreateLink(Node* Node1, Node* Node2);
	Node* GetNodeAtPosition(CU::Vector3f aPos);
	Node* GetClosestNodeAtPosition(CU::Vector3f aPos);
	

	CU::GrowingArray<Node> myNodes;

};

#endif