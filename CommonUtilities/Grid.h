#ifndef GRID_HEADER
#define GRID_HEADER


namespace CommonUtilities
{

	template <class Type>
	struct GridCell;

	template <class Type>
	struct GridDweller
	{
		GridDweller()
		{
			myCells.Init(4, 4);
			myIsStatic = false;
		}
		~GridDweller()
		{
			for (int i =0; i < myCells.Count();i++)
			{
				for (int j = 0; j < myCells[i]->myObjects.Count(); j++)
				{
					if (myCells[i]->myObjects[j] == this)
					{
						myCells[i]->myObjects.RemoveCyclicAtIndex(j);

					}

				}
			}

		}

		CU::Vector2f* myPosition;
		CU::Vector2f* myDimensions;
		Type* myObject;
		bool myIsStatic;
		CU::GrowingArray< GridCell<Type>* >  myCells;
	};

	template <class Type>
	struct GridCell
	{
		GridCell()
		{
			myObjects.Init(5, 5);
		}
		CU::GrowingArray< GridDweller<Type>* > myObjects;
	};

	template <class Type, class SizeType = int>
	class Grid
	{
	public:
		Grid(SizeType aXSize, SizeType aYSize, SizeType aCellXSize, SizeType aCellYSize);
		~Grid(void);

		void UpdateAll();
		void AddObject(Type& anObject, CU::Vector2f& aDimension, CU::Vector2f& aUpperLeft, bool aIsStatic);
		CU::GrowingArray<Type*> GetObjects(const CU::Vector2f& aPosition) const;
		//CU::GrowingArray<Type*> GetObjectsInSphere(CU::Vector2f aPosition, CU::Vector2f aRadius);
		CU::GrowingArray<Type*> GetObjectsInBox(CU::Vector2f aUpperLeft, CU::Vector2f aDimension);
		//CU::GrowingArray<Type*> GetObjectsInUnalignedBox(CU::Vector2f aUpperLeft, CU::Vector2f aDimension);
		//CU::GrowingArray<Type*> GetObjectsInFrustrum(CU::Vector2f aCornerOne, CU::Vector2f aCornerTwo, CU::Vector2f aCornerThree, CU::Vector2f aCornerFour);
		void RemoveObject(Type* anObject, CU::Vector2f& aPosition);

	private:
		Grid& operator=(const Grid& Grid);
		void AddObject(GridDweller<Type>* anObject);
		void UpdateObjectPos(GridDweller<Type>* anObject);

		CU::GrowingArray<GridCell<Type> > myGrid;
		const CU::Vector2<SizeType> myGridSize;
		const SizeType myXSize;
		const SizeType myYSize;
		const SizeType myCellXSize;
		const SizeType myCellYSize;
	};


	template <class Type, class SizeType>
	void Grid<Type, SizeType>::RemoveObject(Type* anObject, CU::Vector2f& aPosition)
	{
		assert (aPosition.myX <= myXSize && "tried to look outside the grid");
		assert (aPosition.myY <= myYSize && "tried to look outside the grid");

		/*SizeType pos = static_cast<SizeType>(aPosition.myX/myCellXSize +aPosition.myY/(myCellYSize * myGridSize.myX));
		for (int i = 0; i < myGrid[pos].myObjects.Count();i++)
		{
			assert(myGrid[pos].myObjects.Count() > 0 && "object not at the specified position!");
			if (myGrid[pos].myObjects[i]->myObject == anObject)
			{
		
				myGrid[pos].myObjects.DeleteCyclicAtIndex(i);
				break;

			}
		}*/
		
		bool didDelete = false;
		for(int gridIndex = 0; gridIndex < myGrid.Count(); gridIndex++)
		{
			for (int i = 0; i < myGrid[gridIndex].myObjects.Count();i++)
			{
				if (myGrid[gridIndex].myObjects[i]->myObject == anObject)
				{
					myGrid[gridIndex].myObjects.RemoveCyclicAtIndex(i);
					i--;
					didDelete = true;
				}
			}
		}
		assert(didDelete && "Item not deleted");
	}



	template <class Type, class SizeType>
	Grid<Type, SizeType>::Grid(SizeType aXSize, SizeType aYSize, SizeType aCellXSize, SizeType aCellYSize)
		:myXSize(aXSize), 
		myYSize(aYSize), 
		myCellXSize(aCellXSize), 
		myCellYSize(aCellYSize),
		myGridSize(CU::Vector2<SizeType>(aXSize/aCellXSize, aYSize/aCellYSize))
	{

		myGrid.Init((myGridSize.myX*myGridSize.myY),100);
		for (SizeType index = 0; index < myGridSize.myY*myGridSize.myX; index++)
		{

			GridCell<Type> cell;
			myGrid.Add(cell);

		}
	}


	template <class Type, class SizeType>
	Grid<Type, SizeType>::~Grid()
	{
		for (SizeType index = 0; index < myGrid.Count(); index++)
		{
			myGrid[index].myObjects.DeleteAll();
		}
	}

	template <class Type, class SizeType>
	void Grid<Type, SizeType>::UpdateAll()
	{
		for (SizeType gridIndex = 0; gridIndex < myGrid.Count(); gridIndex++)
		{
			for (short objIndex = 0; objIndex < myGrid[gridIndex].myObjects.Count(); objIndex++)
			{
				if(myGrid[gridIndex].myObjects[objIndex]->myIsStatic == false)
				{
					UpdateObjectPos(myGrid[gridIndex].myObjects[objIndex]);
				}

			}

		}
		
	}

	template <class Type, class SizeType>
	void Grid<Type, SizeType>::AddObject(Type& anObject, CU::Vector2f& aDimension, CU::Vector2f& aPosition, bool aIsStatic)
	{
		CU::GridDweller<Type>* objwrapper = new CU::GridDweller<Type>();
		objwrapper->myObject = &anObject;
		objwrapper->myPosition = &aPosition;

		objwrapper->myDimensions =  &aDimension;
		objwrapper->myIsStatic = aIsStatic;
		AddObject(objwrapper);
	}


	template <class Type, class SizeType>
	void Grid<Type, SizeType>::AddObject(GridDweller<Type>* anObject)
	{
		
		short firstXCell = static_cast<short>(anObject->myPosition->myX / myCellXSize);
		short firstYCell = static_cast<short>(anObject->myPosition->myY / myCellYSize);
		short lastXCell = static_cast<short>((anObject->myPosition->myX + anObject->myDimensions->myX) / myCellXSize);
		short lastYCell = static_cast<short>((anObject->myPosition->myY + anObject->myDimensions->myY) / myCellXSize);
		
		if(firstXCell < 0 || firstXCell > myGridSize.myX - 1 )
		{
			return;
		}
		if(firstYCell < 0 || firstYCell > myGridSize.myY - 1 )
		{
			return;
		}
		if(lastXCell < 0 || lastXCell > myGridSize.myX - 1 )
		{
			return;
		}
		if(lastYCell < 0 || lastYCell > myGridSize.myY - 1 )
		{
			return;
		}
		

		//to fix warping:
		if(lastXCell > myGridSize.myX)
		{
			lastXCell = static_cast<short>(myGridSize.myX);
		}
		if(lastYCell > myGridSize.myY)
		{
			lastYCell = static_cast<short>(myGridSize.myY);
		} 

		for (short currentYCell = firstYCell; currentYCell <= lastYCell; currentYCell++)
		{
			for (short currentXCell = firstXCell; currentXCell <= lastXCell; currentXCell++)
			{
				short currentGridIndex = static_cast<short>(currentXCell + currentYCell*myGridSize.myX);
				if (currentGridIndex < myGrid.Count())
				{
					myGrid[currentGridIndex].myObjects.Add(anObject);
					anObject->myCells.Add(&myGrid[currentGridIndex]);
				}
			}
		}

	}

	template <class Type, class SizeType>
	void Grid<Type, SizeType>::UpdateObjectPos(GridDweller<Type>* anObject)
	{
		//if has moved:
		while ( anObject->myCells.Count() > 0)
		{
			anObject->myCells[0]->myObjects.RemoveCyclic(anObject);
			anObject->myCells.RemoveCyclicAtIndex(0);
		} 
		//unopted:
		AddObject(anObject);
	}

	template <class Type, class SizeType>
	CU::GrowingArray<Type*> Grid<Type, SizeType>::GetObjects(const CU::Vector2f& aPosition) const
	{
		assert (aPosition.myX <= myXSize && "tried to look outside the grid");
		assert (aPosition.myY <= myYSize && "tried to look outside the grid");

		CU::GrowingArray<Type*> objs(10,5);
		SizeType pos = static_cast<int>(aPosition.myX/myCellXSize) + static_cast<int>(aPosition.myY/myCellYSize) * myGridSize.myX;
		
		
		for (int i = 0; i < myGrid[pos].myObjects.Count();i++)
		{
			objs.Add(myGrid[pos].myObjects[i]->myObject);

		}
		return objs;
	}


	/*
	template <class Type, class SizeType>
	CU::GrowingArray<Type*> Grid<Type, SizeType>::GetObjectsInSphere(CU::Vector2f aPosition, CU::Vector2f aRadius)
	{
		assert (aPosition.myX <= myXSize && "tried to look outside the grid");
		assert (aPosition.myY <= myYSize && "tried to look outside the grid");


	}
	*/

	template <class Type, class SizeType>
	CU::GrowingArray<Type*> Grid<Type, SizeType>::GetObjectsInBox(CU::Vector2f aPosition, CU::Vector2f aDimension)
	{
		assert (aPosition.myX <= myXSize && "tried to look outside the grid");
		assert (aPosition.myY <= myYSize && "tried to look outside the grid");

		short firstXCell = aPosition.myX / myCellXSize;
		short firstYCell = aPosition.myY / myCellYSize;
		short lastXCell = (aPosition.myX + aDimension.myX) / myCellXSize;
		short lastYCell = (aPosition.myY + aDimension.myY) / myCellYSize;
		
		//to fix warping:
		if(lastXCell > myGridSize.myX)
		{
			lastXCell = myGridSize.myX;
		}
		if(lastYCell > myGridSize.myY)
		{
			lastYCell = myGridSize.myY;
		} 


		CU::GrowingArray<Type*> objs(10,5);
		for (short currentYCell = firstYCell; currentYCell <= lastYCell; currentYCell++)
		{
			for (short currentXCell = firstXCell; currentXCell <= lastXCell; currentXCell++)
			{
				short currentGridIndex = currentXCell + currentYCell*myGridSize.myX;
				if (currentGridIndex < myGrid.Count())
				{
					for (int i = 0; i < myGrid[currentGridIndex].myObjects.Count();i++)
					{
						bool alreadyExists = false;
						for(int objsIndex = 0; objsIndex < objs.Count();  objsIndex++)
						{
							if (objs[objsIndex] == myGrid[currentGridIndex].myObjects[i]->myObject)
							{
								alreadyExists = true;
								break;
							}
						}
						if (alreadyExists == false)
						{
							objs.Add(myGrid[currentGridIndex].myObjects[i]->myObject);
						}
					}
				}
			}
		}
		return objs;


	}

};
#endif
