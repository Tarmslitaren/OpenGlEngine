#ifndef OCT_TREE_NODE_HEADER
#define OCT_TREE_NODE_HEADER
#include "Intersections.h"
namespace CommonUtilities
{
	template <class Type>
	class OctTreeNode;

	struct OctLine
	{
		CU::Vector3f myStart;
		CU::Vector3f myEnd;
	};

	struct OctCubeLines
	{
		CU::StaticArray<CU::OctLine,4> myLines;
	};

	template <class Type>
	struct TreeDweller
	{
		Type* myObject;
		float myRadius;
		CU::Vector3f* myPosition;

		OctTreeNode<Type>* myRestingPlace;
	};

	template <class Type>
	class OctTreeNode
	{
	public:
		OctTreeNode()
		{
			myParent = NULL;
			myObjects.Init(50,50);
			//myChildrensObjects.Init(100,100);
		}
		~OctTreeNode()
		{
		}
		void BuildTree(CU::Vector3f aCenterPos, CU::Vector3f aHalfWidths, int aDepth);
		void AddObject(Type* anObject,CU::Vector3f& aPosition, float aRadius);
		CU::GrowingArray<Type*> GetObjectsInSphere(float aRadius, CU::Vector3f aPosition);
		void UpdateObjectsPos();

		void RemoveObject(Type* anObject, CU::Vector3f& anObjectPosition);

		void GetRenderLines(CU::GrowingArray<OctCubeLines>& myRenderCubes);

		
	private:
		void MoveObjectToItsNewHome(TreeDweller<Type>* aDweller, bool aMoveDownWards);
		void FindObjects(float aRadius, CU::Vector3f aPosition, CU::GrowingArray<Type*>& someObjectsToGet);

		void CreateCube();

		CU::Vector3f myCenter;
		CU::Vector3f myUpperLeftFront;
		CU::Vector3f myLowerRightBack;
		CU::Vector3f myHalfWidths;
		CU::GrowingArray< TreeDweller<Type>*> myObjects;
		//CU::GrowingArray< TreeDweller<Type>* > myChildrensObjects;
		CU::StaticArray<OctTreeNode*, 8> myChilds;
		OctTreeNode* myParent;

		OctCubeLines myCube;


		
	};

	template <class Type>
	void OctTreeNode<Type>::RemoveObject(Type* anObject, CU::Vector3f& anObjectPosition)
	{
		//FindObjects(

	}

	template <class Type>
	void OctTreeNode<Type>::MoveObjectToItsNewHome(TreeDweller<Type>* aDweller, bool aMoveDownWards)
	{
		if( aMoveDownWards == false)
		{
			if(myParent != NULL)
			{
				if( Intersections::SphereIsInBox(*(aDweller->myPosition), aDweller->myRadius, myUpperLeftFront, myLowerRightBack) == true)
				{
					myParent->MoveObjectToItsNewHome(aDweller, true);
				}
				else
				{
					myParent->MoveObjectToItsNewHome(aDweller, false);
				}
			}
			else
			{
				//if obj too big, still lay it in rootnode
				aDweller->myRestingPlace = this;
				myObjects.Add(aDweller);
			}
		}
		else
		{
			bool addObject = true;
			if(myChilds[0] != NULL)
			{
				for(int index = 0; index < 8; index++)
				{
					if( Intersections::SphereIsInBox( *(aDweller->myPosition), aDweller->myRadius, myUpperLeftFront, myLowerRightBack) == true)
					{
						myChilds[index]->MoveObjectToItsNewHome(aDweller, true);
						addObject = false;
						break;
					}
				}
			}
			if (addObject==true)
			{
				myObjects.Add(aDweller);
				aDweller->myRestingPlace = this;
			}
		}
	}

	template <class Type>
	void OctTreeNode<Type>::UpdateObjectsPos()
	{
		for (int objs = myObjects.Count()-1 ; objs >= 0;objs--)
		{
			if(Intersections::SphereIsInBox( *(myObjects[objs]->myPosition), myObjects[objs]->myRadius, myUpperLeftFront, myLowerRightBack) == false)
			{
					MoveObjectToItsNewHome(myObjects[objs], false);
					myObjects.RemoveCyclicAtIndex(objs);	
			}
			else
			{

					//MoveObjectToItsNewHome(myObjects[objs], true);
					//myObjects.RemoveCyclicAtIndex(objs);	

			}
		}
		if(myChilds[0] != NULL)
		{
			for(int index = 0; index < 8; index++)
			{
				myChilds[index]->UpdateObjectsPos();
			}
		}

	}


	template <class Type>
	CU::GrowingArray<Type*> OctTreeNode<Type>::GetObjectsInSphere(float aRadius, CU::Vector3f aPosition)
	{
		//remember that octtree is not optimal for area effects like this
		CU::GrowingArray<Type*> returnObjs(10,10);

		FindObjects(aRadius, aPosition, returnObjs);
		return returnObjs;
	}

	template <class Type>
	void OctTreeNode<Type>::FindObjects(float aRadius, CU::Vector3f aPosition, CU::GrowingArray<Type*>& someObjectsToGet)
	{
		for (int objs =0; objs < myObjects.Count(); objs++)
		{
			someObjectsToGet.Add(myObjects[objs]->myObject);
		}
		if (myChilds[0] != NULL)
		{
			//short childIndex = -1;
			for (short i = 0; i < 8; i++)
			{
				if(Intersections::SphereBoxIntersect(aPosition, aRadius,myChilds[i]->myUpperLeftFront, myChilds[i]->myLowerRightBack) == true)
				{
					myChilds[i]->FindObjects(aRadius, aPosition, someObjectsToGet);
					//childIndex = i;
					//break;
				}
			}

		}

	}

	template <class Type>
	void OctTreeNode<Type>::AddObject(Type* anObject, CU::Vector3f& aPosition, float aRadius)
	{
		TreeDweller<Type>* dweller = new TreeDweller<Type>();
		dweller->myObject = anObject;
		dweller->myPosition = &aPosition;
		dweller->myRadius = aRadius;

		bool addObject = true;
		for (int i = 0; i < 8; i++)
		{
			if (myChilds[i] != NULL)
			{
				if(Intersections::SphereIsInBox(aPosition, aRadius,myChilds[i]->myUpperLeftFront, myChilds[i]->myLowerRightBack))
				{
					myChilds[i]->AddObject(anObject, aPosition, aRadius);
					//myChilds[i]->myChildrensObjects.Add(dweller);
					addObject = false;
					break;
				}
			}
		}
		if(addObject == true)
		{
			myObjects.Add(dweller);

		}
	}


	template <class Type>
	void OctTreeNode<Type>::BuildTree(CU::Vector3f aCenterPos, CU::Vector3f aHalfWidths, int aDepth)
	{
		myUpperLeftFront = aCenterPos - aHalfWidths;
		myLowerRightBack = aCenterPos + aHalfWidths;

		myCenter = aCenterPos;
		myHalfWidths = aHalfWidths;

		CreateCube();

		if(aDepth == 0)
		{
			for(int index = 0; index < 8; index++)
			{
				myChilds[index] = NULL;
			}
			return;
		}
		else
		{
			for(int index = 0; index < 8; index++)
			{
				OctTreeNode* newNode = new OctTreeNode();
				myChilds[index] = newNode;
				newNode->myParent = this;
			}
		}
		CU::Vector3f newHalfWidth = aHalfWidths / 2.0f;

		CU::Vector3f frontCenter = aCenterPos;
		CU::Vector3f backCenter = aCenterPos;

		frontCenter.myZ -= newHalfWidth.z;
		frontCenter.myX -= newHalfWidth.x;
		frontCenter.myY -= newHalfWidth.y;
		myChilds[0]->BuildTree(frontCenter, newHalfWidth, aDepth - 1);
		frontCenter.myX += aHalfWidths.x;
		myChilds[1]->BuildTree(frontCenter, newHalfWidth, aDepth - 1);
		frontCenter.myY += aHalfWidths.y;
		myChilds[2]->BuildTree(frontCenter, newHalfWidth, aDepth - 1);
		frontCenter.myX -= aHalfWidths.x;
		myChilds[3]->BuildTree(frontCenter, newHalfWidth, aDepth - 1);

		backCenter.myZ += newHalfWidth.z;
		backCenter.myX -= newHalfWidth.x;
		backCenter.myY -= newHalfWidth.y;
		myChilds[4]->BuildTree(backCenter, newHalfWidth, aDepth - 1);
		backCenter.myX += aHalfWidths.x;
		myChilds[5]->BuildTree(backCenter, newHalfWidth, aDepth - 1);
		backCenter.myY += aHalfWidths.y;
		myChilds[6]->BuildTree(backCenter, newHalfWidth, aDepth - 1);
		backCenter.myX -= aHalfWidths.x;
		myChilds[7]->BuildTree(backCenter, newHalfWidth, aDepth - 1);

	}

	template <class Type>
	void CommonUtilities::OctTreeNode<Type>::GetRenderLines( CU::GrowingArray<OctCubeLines>& myRenderCubes )
	{
		myRenderCubes.Add(myCube);

		for(int i = 0; i < 8; i++)
		{
			if(myChilds[i] == NULL)
			{
				return;
			}
			else
			{
				myChilds[i]->GetRenderLines(myRenderCubes);
			}

		}

	}


	template <class Type>
	void CommonUtilities::OctTreeNode<Type>::CreateCube()
	{
		CU::Vector3f TopFrontLeft = CU::Vector3f(myCenter.x-myHalfWidths.x, myCenter.y+myHalfWidths.y, myCenter.z-myHalfWidths.z);
		CU::Vector3f TopFrontRight = CU::Vector3f(myCenter.x+myHalfWidths.x,myCenter.y+myHalfWidths.y, myCenter.z-myHalfWidths.z);
		CU::Vector3f TopBackLeft = CU::Vector3f(myCenter.x-myHalfWidths.x, myCenter.y+myHalfWidths.y, myCenter.z+myHalfWidths.z);
		CU::Vector3f TopBackRight = CU::Vector3f(myCenter.x+myHalfWidths.x, myCenter.y+myHalfWidths.y, myCenter.z+myHalfWidths.z);
		CU::Vector3f BottomFrontLeft = CU::Vector3f(myCenter.x-myHalfWidths.x, myCenter.y-myHalfWidths.y, myCenter.z-myHalfWidths.z);
		CU::Vector3f BottomFrontRight = CU::Vector3f(myCenter.x+myHalfWidths.x, myCenter.y-myHalfWidths.y, myCenter.z-myHalfWidths.z);
		CU::Vector3f BottomBackLeft = CU::Vector3f(myCenter.x-myHalfWidths.x, myCenter.y-myHalfWidths.y, myCenter.z+myHalfWidths.z);
		CU::Vector3f BottomBackRight = CU::Vector3f(myCenter.x+myHalfWidths.x, myCenter.y-myHalfWidths.y, myCenter.z+myHalfWidths.z);

		for(int i = 0; i < 4; i++)
		{
			myCube.myLines[i] = OctLine();
		}
		
// 		myCube.myLines[0].myStart = TopFrontLeft;
// 		myCube.myLines[0].myEnd = TopFrontRight;
// 		myCube.myLines[1].myStart = TopBackLeft;
// 		myCube.myLines[1].myEnd = TopBackRight;
// 		myCube.myLines[2].myStart = BottomFrontLeft;
// 		myCube.myLines[2].myEnd = BottomFrontRight;
// 		myCube.myLines[3].myStart = BottomBackLeft;
// 		myCube.myLines[3].myEnd = BottomBackRight;

		myCube.myLines[0].myStart = TopFrontLeft;
		myCube.myLines[0].myEnd = TopBackLeft;
		myCube.myLines[1].myStart = TopFrontRight;
		myCube.myLines[1].myEnd = TopBackRight;
		myCube.myLines[2].myStart = BottomFrontLeft;
		myCube.myLines[2].myEnd = BottomBackLeft;
		myCube.myLines[3].myStart = BottomFrontRight;
		myCube.myLines[3].myEnd = BottomBackRight;


		/*myCube.myLines[8].myStart = TopFrontLeft;
		myCube.myLines[8].myEnd = BottomFrontLeft;
		myCube.myLines[9].myStart = TopFrontRight;
		myCube.myLines[9].myEnd = BottomFrontRight;
		myCube.myLines[10].myStart = TopBackLeft;
		myCube.myLines[10].myEnd = BottomBackLeft;
		myCube.myLines[11].myStart = TopBackRight;
		myCube.myLines[11].myEnd = BottomBackRight;*/



	}



};

#endif
