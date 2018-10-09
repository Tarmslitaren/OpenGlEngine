#ifndef BINARY_HEAP_HEADER
#define BINARY_HEAP_HEADER


template<typename type>
class Heap
{
public:
	Heap();
	Heap(std::vector<type> aVector);
	~Heap();

	void ReInit(std::vector<type> aVector);
	void Enqueue(type aType);
	type Dequeue();
	bool IsEmpty();
	
	void Clear();
	int Size();
	type* Find(type aType);
	void Floyd();
private:
	void Balance(int aParentIndex);

	CU::GrowingArray<type> myElements;
};

template<typename type>
Heap<type>::Heap()
{
	myElements.Init(1024,1024);
}

template<typename type>
Heap<type>::Heap(std::vector<type> aVector)
{
	myElements = aVector;
	Floyd();
}

template<typename type>
void Heap<type>::ReInit(std::vector<type> aVector)
{
	myElements = aVector;
	Floyd();
}

template<typename type>
Heap<type>::~Heap()
{
}

template<typename type>
void Heap<type>::Enqueue(type aType)
{
	myElements.Add(aType);
	int pos = myElements.Count()-1;
	while(pos>0&&myElements[(pos-1)/2] > myElements[pos])
	{
		type temp=myElements[(pos-1)/2];
		myElements[(pos-1)/2]=myElements[pos];
		myElements[pos]=temp;

		pos=(pos-1)/2;
	}

}

template<typename type>
type Heap<type>::Dequeue()
{
	type returnValue = myElements[0];

	myElements[0] = myElements[myElements.Count() -1];
	myElements.RemoveCyclicAtIndex(myElements.Count()-1);;
	int pos = 0;

	while(pos*2+2 < myElements.Count())
	{
		if(myElements[pos]>myElements[pos*2+1] || myElements[pos] > myElements[pos*2+2])
		{
			if(myElements[pos*2+1] > myElements[pos*2+2])
			{
				type temp=myElements[pos*2+2];
				myElements[pos*2+2]=myElements[pos];
				myElements[pos]=temp;

				pos=pos*2+2;
			}
			else
			{
				type temp=myElements[pos*2+1];
				myElements[pos*2+1]=myElements[pos];
				myElements[pos]=temp;

				pos=pos*2+1;
			}
		}
		else
		{
			break;
		}
	}
	if(pos*2+1 < myElements.Count())
	{
		if(myElements[pos*2+1] > myElements[pos])
		{
			type temp=myElements[pos*2+1];
			myElements[pos*2+1]=myElements[pos];
			myElements[pos]=temp;
		}
	}
	return returnValue;
}

template<typename type>
bool Heap<type>::IsEmpty()
{
	if(myElements.Count() > 0)
	{
		return false;
	}
	return true;
}

template<typename type>
void Heap<type>::Floyd()
{
	if(myElements.size()>1)
	{
		unsigned int pos = (myElements.size()/ 2) - 1;
	
		Balance(pos);
	}
}

template<typename type>
void Heap<type>::Balance(int aParentIndex)
{
	int leftChildIndex = aParentIndex*2+1;
	int rightChildIndex = aParentIndex*2+2;
	if(rightChildIndex>=static_cast<int>(myElements.size()))
	{
		if(leftChildIndex<static_cast<int>(myElements.size()))
		{
			if(myElements[aParentIndex] > myElements[leftChildIndex])
			{
				type temp = myElements[leftChildIndex];
				myElements[leftChildIndex] = myElements[aParentIndex];
				myElements[aParentIndex] = temp;

				Balance(leftChildIndex);
			}
		}
	}
	else if(myElements[aParentIndex] > myElements[leftChildIndex] || myElements[aParentIndex] > myElements[rightChildIndex])
	{
		if(myElements[leftChildIndex] < myElements[rightChildIndex])
		{
			type temp = myElements[leftChildIndex];
			myElements[leftChildIndex] = myElements[aParentIndex];
			myElements[aParentIndex] = temp;

			Balance(leftChildIndex);
		}
		else
		{
			type temp = myElements[rightChildIndex];
			myElements[rightChildIndex] = myElements[aParentIndex];
			myElements[aParentIndex] = temp;

			Balance(rightChildIndex);
		}
	}
	if(aParentIndex>0)
	{
		Balance(aParentIndex-1);
	}

}

template<typename type>
void Heap<type>::Clear()
{
	myElements.clear();
}

template<typename type>
int Heap<type>::Size()
{
	return myElements.size();
}

template<typename type>
type* Heap<type>::Find(type aType)
{
	for(unsigned int elementsIndex = 0;elementsIndex < myElements.size() ; elementsIndex++)
	{
		if(myElements[elementsIndex] == aType)
		{
			return &myElements[elementsIndex];
		}
	}
	return NULL;
}
#endif
