#pragma once

namespace CommonUtilities
{
	template <class Type>
	class SmartPointer
	{
	public:
		SmartPointer(Type *aPointer = NULL);
		~SmartPointer();
		

		SmartPointer& operator=(const SmartPointer& aSmartPointer);
		bool operator!=(const SmartPointer& aSmartPointer);
		bool operator==(const SmartPointer& aSmartPointer);
		Type &operator*();
		Type* operator->();
		void ForceDelete();

	private:
		void Dispose();



		Type *myPointer;
		int myNumberOfOwners;
	};

	template <class Type>
	SmartPointer<Type>::SmartPointer(Type *aPointer)
	{
		myPointer = aPointer;
		myNumberOfOwners = 1;
	}

	template <class Type>
	SmartPointer<Type>& SmartPointer<Type>::operator=(const SmartPointer<Type>& aSmartPointer)
	{
		if (this != &aSmartPointer)
		{
			Dispose();
			myPointer = aSmartPointer.myPointer;
			myNumberOfOwners = aSmartPointer.myNumberOfOwners;
			myNumberOfOwners++;
		}
		return *this;
	}

	template <class Type>
	bool SmartPointer<Type>::operator!=(const SmartPointer<Type>& aSmartPointer)
	{
		if (this != aSmartPointer)
		{
			return true;
		}
		return false;
	}

	template <class Type>
	bool SmartPointer<Type>::operator==(const SmartPointer<Type>& aSmartPointer)
	{
		if (this == aSmartPointer)
		{
			return true;
		}
		return false;
	}
	template <class Type>
	SmartPointer<Type>::~SmartPointer()
	{
		Dispose();
	}


	template <class Type>
	Type &SmartPointer<Type>::operator*() 
	{
		return *myPointer;
	}

	template <class Type>
	Type *SmartPointer<Type>::operator->()
	{
		assert(myPointer != NULL && "pointer is NULL" );
		return myPointer;
	}


	template <class Type>
	void SmartPointer<Type>::Dispose()
	{
		if (--myNumberOfOwners == 0)
		{
			if (myPointer != NULL)
			{
				delete myPointer;
				myPointer = NULL;
			}
		}
	}

	template <class Type>
	void SmartPointer<Type>::ForceDelete()
	{
		delete myPointer;
		myPointer = NULL;
	}
}

