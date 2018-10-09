#ifndef OCT_TREE_HEADER
#define OCT_TREE_HEADER

#include "octtreenode.h"
namespace CommonUtilities
{


	template <class Type>
	class OctTree
	{
	public:
		OctTree()
		{
		};
		~OctTree(){};
		void BuildTree(CU::Vector3f aCenter,float aSizeX, float aSizeY, float aSizeZ, short aDepth);
		void AddObject(Type* anObject, CU::Vector3f& aPosition, float aRadius);
		CU::GrowingArray<Type*> GetObjectsInSphere(float aRadius, CU::Vector3f aPosition);
		void UpdateObjectsPosition();
		void RemoveObject(Type* anObject, CU::Vector3f& anObjectPosition);

		void GetRenderLines(CU::GrowingArray<OctCubeLines>& myRenderCubes);
		
	private:
		OctTreeNode<Type>* myRoot;
	};

	template <class Type>
	void CommonUtilities::OctTree<Type>::GetRenderLines( CU::GrowingArray<OctCubeLines>& myRenderCubes )
	{
		myRoot->GetRenderLines(myRenderCubes);
	}
	template <class Type>
	void OctTree<Type>::UpdateObjectsPosition()
	{
		myRoot->UpdateObjectsPos();

	}

	template <class Type>
	void OctTree<Type>::RemoveObject(Type* anObject, CU::Vector3f& anObjectPosition)
	{
		myRoot->RemoveObject(anObject, anObjectPosition);

	}


	template <class Type>
	void OctTree<Type>::BuildTree(CU::Vector3f aCenter,float aSizeX, float aSizeY, float aSizeZ, short aDepth)
	{
		CU::Vector3f pos;
		pos.myX = aCenter.myX;
		pos.myY = aCenter.myY;
		pos.myZ = aCenter.myZ;
		CU::Vector3f halfWidth(aSizeX/ 2.0f,aSizeY/ 2.0f,aSizeZ/ 2.0f);
		myRoot = new OctTreeNode<Type>();
		myRoot->BuildTree(pos, halfWidth, aDepth);

	}

	template <class Type>
	void OctTree<Type>::AddObject(Type* anObject, CU::Vector3f& aPosition, float aRadius)
	{
		//assert if pos is not inside treespace

		myRoot->AddObject(anObject, aPosition, aRadius);
	}

	template <class Type>
	CU::GrowingArray<Type*> OctTree<Type>::GetObjectsInSphere(float aRadius, CU::Vector3f aPosition)
	{
		return myRoot->GetObjectsInSphere(aRadius, aPosition);

	}
};
#endif
