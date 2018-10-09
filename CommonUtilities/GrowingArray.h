#ifndef CUSTOM_GROWINGARRAY_HEADER
#define CUSTOM_GROWINGARRAY_HEADER

#include "LoopMacros.h"
#include "CommonMacros.h"
#include "assert.h"
#include <iostream>

namespace CommonUtilities
{
	template <class Type,class CountType =int>
	class GrowingArray
	{
	public:
		GrowingArray();
		GrowingArray(int aNrOfRecomendedItems,int aItemIncreaseSize, bool aUseSafeModeFlag=true);
		GrowingArray(const GrowingArray& aGrowingArray);
		~GrowingArray();

		GrowingArray& operator=(const GrowingArray& aGrowingArray);


		void Init(int aNrOfRecomendedItems,int aItemIncreaseSize,bool aUseSafeModeFlag=true);
		void ReInit(int aNrOfRecomendedItems,int aItemIncreaseSize,bool aUseSafeModeFlag=true);

		inline Type& operator[](const int& aIndex) const;
		inline Type& operator[](const int& aIndex);
		inline Type& GetLast() const;
		inline void UnsafeAdd();

		inline void Add(const Type& aObject);
		inline void Insert(int aIndex,Type& aObject);
		inline void DeleteCyclic(Type& aObject);
		inline void DeleteCyclicAtIndex(int aItemNumber);
		inline void RemoveCyclic(const Type& aObject);
		inline void RemoveCyclicAtIndex(int aItemNumber);


		inline void RemoveAll();
		inline void DeleteAll();

		void Optimize();
		__forceinline int Count() const;

	protected:

		inline void ReSize(int aNewSize);

		Type* myItemList;
		Type* myLast;
		CountType myCurNrOfItems;
		CountType myMaxNrOfItems;
		CountType myItemIncreaseSize;
		bool myUseSafeModeFlag;

	};

	template <class Type,class CountType>
	GrowingArray<Type,CountType>::GrowingArray()
	{
		myItemList=NULL;
		myLast = myItemList;
		myCurNrOfItems=0;
		myMaxNrOfItems=0;
		myItemIncreaseSize=0;
		myUseSafeModeFlag=true;
	}

	template <class Type,class CountType>
	GrowingArray<Type,CountType>::GrowingArray(int aNrOfRecomendedItems,int aItemIncreaseSize,bool aUseSafeModeFlag)
	{
		myItemList=NULL;
		myLast = myItemList;
		myCurNrOfItems=0;
		myUseSafeModeFlag=aUseSafeModeFlag;
		Init(aNrOfRecomendedItems,aItemIncreaseSize);
	}

	template <class Type,class CountType>
	GrowingArray<Type,CountType>::GrowingArray(const GrowingArray<Type,CountType>& aGrowingArray)
	{
		myItemList=NULL;
		*this=aGrowingArray;
	}

	template <class Type,class CountType>

	GrowingArray<Type,CountType>& GrowingArray<Type,CountType>::operator=(const GrowingArray<Type,CountType>& aGrowingArray)
	{
		if(myItemList==NULL)
		{
			Init(aGrowingArray.myMaxNrOfItems,aGrowingArray.myItemIncreaseSize,aGrowingArray.myUseSafeModeFlag);
		}
		else
		{
			ReInit(aGrowingArray.myMaxNrOfItems,aGrowingArray.myItemIncreaseSize,aGrowingArray.myUseSafeModeFlag);
		}

 		if(myUseSafeModeFlag==true)
 		{
 			for(int i=0;i<aGrowingArray.Count();i++)
 			{
 				myItemList[i] = aGrowingArray[i];
 			}
 		}
 		else
		{
			memcpy(myItemList,&aGrowingArray[0],aGrowingArray.Count()*sizeof(Type));
		}
		myCurNrOfItems=static_cast<CountType>(aGrowingArray.Count());
		myLast = &myItemList[myCurNrOfItems];
		return(*this);
	}



	template <class Type,class CountType>
	GrowingArray<Type,CountType>::~GrowingArray()
	{
		RemoveAll();
		myLast=NULL;
		if(myItemList!=NULL)
		{
			delete [] myItemList;
		}
		myItemList=NULL;

	}


	template <class Type,class CountType>
	void GrowingArray<Type,CountType>::Init(int aNrOfRecomendedItems,int aItemIncreaseSize,bool aUseSafeModeFlag)
	{
		assert(myItemList==NULL && "CALLED INIT ON AN ALREADY INITED GROWINGARRAY PLEASE USE REINIT");

		myMaxNrOfItems=static_cast<CountType>(aNrOfRecomendedItems);
		myItemIncreaseSize=static_cast<CountType>(aItemIncreaseSize);
		myUseSafeModeFlag=aUseSafeModeFlag;
		myCurNrOfItems=0;

		myItemList = new Type [myMaxNrOfItems] ();
		myLast = myItemList;
	}

	template <class Type,class CountType>
	void GrowingArray<Type,CountType>::ReInit(int aNrOfRecomendedItems,int aItemIncreaseSize,bool aUseSafeModeFlag)
	{
		assert(myItemList!=NULL && "CALLED REINIT ON AN UNINITED GROWINGARRAY PLEASE USE INIT");

		delete [] (myItemList);

		myMaxNrOfItems=static_cast<CountType>(aNrOfRecomendedItems);
		myItemIncreaseSize=static_cast<CountType>(aItemIncreaseSize);
		myUseSafeModeFlag=aUseSafeModeFlag;
		myCurNrOfItems=0;

		myItemList = new Type [myMaxNrOfItems] ();
		myLast = myItemList;
	}



	template <class Type,class CountType>
	Type& GrowingArray<Type,CountType>::operator[](const int& aIndex) const 
	{
		assert((aIndex>=0) && (aIndex<static_cast<int>(myCurNrOfItems)) && "OUT OF BOUNDS ERROR");
		return(myItemList[aIndex]);
	}

	template <class Type,class CountType>
	Type& GrowingArray<Type,CountType>::operator[](const int& aIndex)
	{
		assert((aIndex>=0) && (aIndex<static_cast<int>(myCurNrOfItems)) && "OUT OF BOUNDS ERROR");
		return(myItemList[aIndex]);
	}

	template <class Type,class CountType>
	void GrowingArray<Type,CountType>::Add(const Type& aItem)
	{
		if(myCurNrOfItems==myMaxNrOfItems) ReSize(myMaxNrOfItems+myItemIncreaseSize);
		myItemList[myCurNrOfItems]=aItem;
		myCurNrOfItems++;
		myLast = &myItemList[myCurNrOfItems];
	}


	template <class Type,class CountType>
	void GrowingArray<Type,CountType>::DeleteCyclic(Type& aItem)
	{
		For_Count_i(myCurNrOfItems)
		{
			if(myItemList[i]==aItem)
			{
				delete(myItemList[i]);
				myItemList[i]=myItemList[myCurNrOfItems-1];
				myCurNrOfItems--;
				myLast = &myItemList[myCurNrOfItems];
				return;
			}
		}

	}

	template <class Type,class CountType>
	void GrowingArray<Type,CountType>::DeleteCyclicAtIndex(int aItemNumber)
	{
		delete(myItemList[aItemNumber]);
		myItemList[aItemNumber] = NULL;
		myItemList[aItemNumber]=myItemList[myCurNrOfItems-1];
		myCurNrOfItems--;
		myLast = &myItemList[myCurNrOfItems];
	}

	template <class Type,class CountType>
	void GrowingArray<Type,CountType>::RemoveCyclic(const Type& aItem) 
	{
		For_Count_i(myCurNrOfItems)
		{
			if(myItemList[i]==aItem)
			{
				myItemList[i]=myItemList[myCurNrOfItems-1];
				myCurNrOfItems--;
				myLast = &myItemList[myCurNrOfItems];
				return;
			}
		}
	}

	template <class Type,class CountType>
	void GrowingArray<Type,CountType>::RemoveCyclicAtIndex(int aItemNumber)
	{
		myItemList[aItemNumber]=myItemList[myCurNrOfItems-1];
		myCurNrOfItems--;
		myLast = &myItemList[myCurNrOfItems];
	}

	template <class Type,class CountType>
	void GrowingArray<Type,CountType>::Insert(int aIndex,Type& aObject)
	{
		if(myCurNrOfItems==myMaxNrOfItems) 
		{
			ReSize(myMaxNrOfItems+myItemIncreaseSize);
		}
		for(int i=myCurNrOfItems-1;i>=aIndex;i--)
		{
			myItemList[i+1]=myItemList[i];
		}
		myItemList[aIndex]=aObject;
		myCurNrOfItems++;
		myLast = &myItemList[myCurNrOfItems];
	}

	template <class Type,class CountType>
	void GrowingArray<Type,CountType>::RemoveAll()
	{
		myCurNrOfItems=0;
		myLast = myItemList;
	}

	template <class Type,class CountType>
	void GrowingArray<Type,CountType>::DeleteAll()
	{
		For_Count_i(myCurNrOfItems)
		{
			delete myItemList[i];
			myItemList[i]=NULL;
		}
		myCurNrOfItems=0;
		myLast = myItemList;

	}

	template <class Type,class CountType>
	void GrowingArray<Type,CountType>::Optimize()
	{
		ReSize(myCurNrOfItems);
	}

	template <class Type,class CountType>
	int GrowingArray<Type,CountType>::Count() const
	{

		return(myCurNrOfItems);
	}

	template <class Type,class CountType>
	void GrowingArray<Type,CountType>::ReSize(int aNewSize)
	{
		assert(aNewSize != 0 && "NEW SIZE IS ZERO");
		assert(myMaxNrOfItems < aNewSize);
		Type* tempList=new Type [aNewSize] ();
		if(myUseSafeModeFlag==true)
		{
			for(int i=0;i<static_cast<int>(myCurNrOfItems);i++)
			{
				tempList[i]=myItemList[i];
			}
		}
		else
		{
			memcpy(tempList,myItemList,myCurNrOfItems*sizeof(Type*));
		}
		delete [] (myItemList);
		myMaxNrOfItems=static_cast<CountType>(aNewSize);
		myItemList=tempList;
		myLast = &myItemList[myCurNrOfItems];
	}

	template <class Type,class CountType>
	Type& GrowingArray<Type,CountType>::GetLast() const
	{
		return myItemList[myCurNrOfItems-1];
	}

	template <class Type,class CountType>
	void GrowingArray<Type,CountType>::UnsafeAdd()
	{
		if(myCurNrOfItems==myMaxNrOfItems) ReSize(myMaxNrOfItems+myItemIncreaseSize);
		myCurNrOfItems++;
		myLast = &myItemList[myCurNrOfItems];
	}

}

namespace CU = CommonUtilities;	


#endif