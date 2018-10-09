#ifndef NODE_HEADER
#define NODE_HEADER



struct Link;
class Node
{
public:
	Node();
	Node(CU::Vector3f aPos);
	~Node();
	void UpdateCosts();

	CU::GrowingArray<Link> myLinks;
	float currDist;
	bool operator<(const Node& aNode);
	bool operator>(const Node& aNode);
	bool operator==(const Node& aNode);
	CU::Vector3f myPosition;
	bool isSelected;
	bool isStart;
	bool isEnd;
	bool isCover;

	bool isPassable;
	Node* myPredator;
};

struct Link
{
	Link()
	{
		myCost = 0;
		myDestination = NULL;
		myPredator = NULL;
	}
	float myCost;
	Node* myDestination;
	Node* myPredator;

	bool operator==(const Link& aLink) const
	{
		if(myCost!=aLink.myCost) return false;
		if(*myDestination==*aLink.myDestination) return false;
		if(*myPredator==*aLink.myPredator) return false;

		return false;
	};
};

#endif