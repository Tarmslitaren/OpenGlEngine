#ifndef ASTARGRAPH_HEADER
#define ASTARGRAPH_HEADER



class Graph;
class Node;
struct AstarNode
{
	int F;
	int G;
	int H;
	Node* myNode;
};
class AstarGraph
{
public:
	AstarGraph();
	~AstarGraph();

	const CU::GrowingArray<Node*>& GetPath(Node* aStartNode, Node* aEndNode);

private:
	AstarGraph& operator=(AstarGraph&);



	void CheckNode(const AstarNode& aNode);



	

	Node* myStartNode;
	Node* myEndNode;

	CU::GrowingArray<AstarNode> myOpenList;
	CU::GrowingArray<AstarNode> myClosedList;
	CU::GrowingArray<Node*> myReturnVector;
	bool myFoundPath;
};
#endif