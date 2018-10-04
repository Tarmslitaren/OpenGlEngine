#ifndef COMMONUTILITIES_MATRIX22_HEADER
#define COMMONUTILITIES_MATRIX22_HEADER

#include <math.h>
#include "vector2.h"
#include "staticarray.h"
#include "CommonMacros.h"

namespace CommonUtilities
{
	template <class TYPE>
	class Matrix22
	{
	public:
		Matrix22();
		Matrix22(TYPE aX1, TYPE aY1, TYPE aX2, TYPE aY2);
		Matrix22(Vector2<TYPE> aVector1, Vector2<TYPE> aVector2);
		Matrix22(StaticArray<StaticArray<TYPE,2>,2> aStaticArray);
		~Matrix22();

		void Set(TYPE aX1, TYPE aY1, TYPE aX2, TYPE aY2);
		void Set(Vector2<TYPE> aVector1, Vector2<TYPE> aVector2);
		void Set(StaticArray<StaticArray<TYPE,2>,2> aStaticArray);
		
		Matrix22& operator+=(const Matrix22& aMatrix22);
		Matrix22& operator-=(const Matrix22& aMatrix22);

		Matrix22& operator*=(const Matrix22& aMatrix22);
		Matrix22& operator*=(const Vector2<TYPE>& aVector2);
		Matrix22& operator*=(const TYPE& aType);
		Matrix22& operator/=(const TYPE& aType);

		Matrix22& operator=(const Matrix22& aMatrix22);

		bool operator==(const Matrix22& aMatrix22) const;

		Matrix22<TYPE> Transpose();
		Matrix22<TYPE> Inverse();
		void Rotate(TYPE aRotationDegree);
		Matrix22<TYPE> Rotate(const CU::Vector2<TYPE>& aFacing, const CU::Vector2<TYPE>& aSide);

		static Matrix22<TYPE> Identity();
		static Matrix22<TYPE> Transformation(TYPE aRotationDegree);
		static void Transform(Vector2<TYPE>& aVector2);



		StaticArray<StaticArray<TYPE,2>,2> myMatrix;
	};






		//OPERATORS
	template <class TYPE>
	Matrix22<TYPE> operator+(const Matrix22<TYPE>& aLeftSideMatrix22,const Matrix22<TYPE>& aRightSideMatrix22)
	{
		Matrix22<TYPE> returnValue(aLeftSideMatrix22);
		returnValue+=aRightSideMatrix22;
		return(returnValue);
	}
	template <class TYPE>
	Matrix22<TYPE> operator-(const Matrix22<TYPE>& aLeftSideMatrix22,const Matrix22<TYPE>& aRightSideMatrix22)
	{
		Matrix22<TYPE> returnValue(aLeftSideMatrix22);
		returnValue-=aRightSideMatrix22;
		return(returnValue);
	}

	template <class TYPE>
	Matrix22<TYPE> operator*(const Matrix22<TYPE>& aLeftSideMatrix22,const Matrix22<TYPE>& aRightSideMatrix22)
	{
		Matrix22<TYPE> returnValue(aLeftSideMatrix22);
		returnValue*=aRightSideMatrix22;
		return(returnValue);
	}
	template <class TYPE>
	Matrix22<TYPE> operator*(const Matrix22<TYPE>& aLeftSideMatrix22,const Vector2<TYPE>& aRightSideVector2)
	{
		Matrix22<TYPE> returnValue(aLeftSideMatrix22);
		returnValue*=aRightSideVector2;
		return(returnValue);
	}

	template <class TYPE>
	Matrix22<TYPE> operator*(const Matrix22<TYPE>& aLeftSideMatrix22,const TYPE& aRightSideType)
	{
		Matrix22<TYPE> returnValue(aLeftSideMatrix22);
		returnValue*=aRightSideType;
		return(returnValue);
	}
	template <class TYPE>
	Matrix22<TYPE> operator/(const Matrix22<TYPE>& aLeftSideMatrix22,const TYPE& aRightSideType)
	{
		Matrix22<TYPE> returnValue(aLeftSideMatrix22);
		returnValue/=aRightSideType;
		return(returnValue);
	}



	//CONSTRUCTORS / DESTRUCTORS
	template <class TYPE>
	Matrix22<TYPE>::Matrix22()
	{
		myMatrix[0][0] = 0;
		myMatrix[0][1] = 0;
		myMatrix[1][0] = 0;
		myMatrix[1][1] = 0;
	}

	template <class TYPE>
	Matrix22<TYPE>::Matrix22(TYPE aX1, TYPE aY1, TYPE aX2, TYPE aY2)
	{
		myMatrix[0][0] = aX1;
		myMatrix[0][1] = aY1;
		myMatrix[1][0] = aX2;
		myMatrix[1][1] = aY2;
	}
	template <class TYPE>
	Matrix22<TYPE>::Matrix22(Vector2<TYPE> aVector1, Vector2<TYPE> aVector2)
	{
		myMatrix[0][0] = aVector1.myX;
		myMatrix[0][1] = aVector1.myY;
		myMatrix[1][0] = aVector2.myX;
		myMatrix[1][1] = aVector2.myY;
	}
	template <class TYPE>
	Matrix22<TYPE>::Matrix22(StaticArray<StaticArray<TYPE,2>,2> aStaticArray)
	{
		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < 2; j++)
			{
				myMatrix[i][j] = aStaticArray[i][j];
			}
		}
	}

	template <class TYPE>
	Matrix22<TYPE>::~Matrix22()
	{
	}

	//SET
	template <class TYPE>
	void Matrix22<TYPE>::Set(TYPE aX1, TYPE aY1, TYPE aX2, TYPE aY2)
	{
		myMatrix[0][0] = aX1;
		myMatrix[0][1] = aY1;
		myMatrix[1][0] = aX2;
		myMatrix[1][1] = aY2;
	}
	template <class TYPE>
	void Matrix22<TYPE>::Set(Vector2<TYPE> aVector1, Vector2<TYPE> aVector2)
	{
		myMatrix[0][0] = aVector1.myX;
		myMatrix[0][1] = aVector1.myY;
		myMatrix[1][0] = aVector2.myX;
		myMatrix[1][1] = aVector2.myY;
	}
	template <class TYPE>
	void Matrix22<TYPE>::Set(StaticArray<StaticArray<TYPE,2>,2> aStaticArray)
	{
		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < 2; j++)
			{
				myMatrix[i][j] = aStaticArray[i][j];
			}
		}
	}

	//OPERATORS
	template <class TYPE>
	Matrix22<TYPE>& Matrix22<TYPE>::operator+=(const Matrix22<TYPE>& aMatrix22)
	{
		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < 2; j++)
			{
				myMatrix[i][j] += aMatrix22.myMatrix[i][j];
			}
		}
		return(*this);
	}
	template <class TYPE>
	Matrix22<TYPE>& Matrix22<TYPE>::operator-=(const Matrix22<TYPE>& aMatrix22)
	{
		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < 2; j++)
			{
				myMatrix[i][j] -= aMatrix22.myMatrix[i][j];
			}
		}
		return(*this);
	}


	template <class TYPE>
	Matrix22<TYPE>& Matrix22<TYPE>::operator*=(const Matrix22<TYPE>& aMatrix22)
	{
		Matrix22<TYPE> resultMatrix;
		
		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < 2; j++)
			{
				resultMatrix.myMatrix[i][j] = 0;
				for(int k = 0; k < 2; k++)
				{
					resultMatrix.myMatrix[i][j] += myMatrix[i][k] * aMatrix22.myMatrix[k][j];
				}
			}
		}
		*this = resultMatrix;
		return(*this);
	}

	template <class TYPE>
	Matrix22<TYPE>& Matrix22<TYPE>::operator*=(const Vector2<TYPE>& aVector2)
	{
		myMatrix[0][0] *= aVector2.myX;
		myMatrix[0][1] *= aVector2.myX;
		myMatrix[1][0] *= aVector2.myY;
		myMatrix[1][1] *= aVector2.myY;

		return(*this);
	}

	template <class TYPE>
	Matrix22<TYPE>& Matrix22<TYPE>::operator*=(const TYPE& aType)
	{
		myMatrix[0][0] *= aType;
		myMatrix[0][1] *= aType;
		myMatrix[1][0] *= aType;
		myMatrix[1][1] *= aType;

		return(*this);
	}
	template <class TYPE>
	Matrix22<TYPE>& Matrix22<TYPE>::operator/=(const TYPE& aType)
	{
		myMatrix[0][0] /= aType;
		myMatrix[0][1] /= aType;
		myMatrix[1][0] /= aType;
		myMatrix[1][1] /= aType;

		return(*this);
	}

	template <class TYPE>
	Matrix22<TYPE>& Matrix22<TYPE>::operator=(const Matrix22<TYPE>& aMatrix22)
	{
		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < 2; j++)
			{
				myMatrix[i][j] = aMatrix22.myMatrix[i][j];
			}
		}
		return(*this);
	}

	template <class TYPE>
	bool Matrix22<TYPE>::operator==(const Matrix22<TYPE>& aRightSideMatrix22) const
	{
		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < 2; j++)
			{
				if(myMatrix[i][j] += aMatrix22.myMatrix[i][j]) return(false);
			}
		}
		return(true);
	}

	//FUNCTIONS

	template <class TYPE>
	Matrix22<TYPE> Matrix22<TYPE>::Transpose()
	{
		Matrix22<TYPE> transposedMatrix;

		transposedMatrix.myMatrix[0][0] = myMatrix[0][0];
		transposedMatrix.myMatrix[0][1] = myMatrix[1][0];

		transposedMatrix.myMatrix[1][0] = myMatrix[0][1];
		transposedMatrix.myMatrix[1][1] = myMatrix[1][1];

		return(transposedMatrix);
	}
	template <class TYPE>
	Matrix22<TYPE> Matrix22<TYPE>::Inverse()
	{
		return(this->Transpose());
	}

	template <class TYPE>
	Matrix22<TYPE> Matrix22<TYPE>::Identity()
	{
		Matrix22<TYPE> identityMatrix(1,0,0,1);
		return(identityMatrix);
	}

	template <class TYPE>
	void Matrix22<TYPE>::Rotate(TYPE aRotationDegree)
	{
		Matrix22<TYPE> tmp = Transformation(aRotationDegree);

		myMatrix = myMatrix * tmp;
	}

	template <class TYPE>
	Matrix22<TYPE> Matrix22<TYPE>::Rotate(const CU::Vector2<TYPE>& aFacing, const CU::Vector2<TYPE>& aSide)
	{
		Matrix22<TYPE> tmp(aFacing.myX,aFacing.myY,aSide.myX,aSide.myY);
  
		return(tmp);
	}

	template <class TYPE>
	Matrix22<TYPE> Matrix22<TYPE>::Transformation(TYPE aRotationDegree)
	{
		//2 * PI * (aRotationDegree / 360.0);
		TYPE cosValue = static_cast<TYPE>(cos(aRotationDegree));
		TYPE sinValue = static_cast<TYPE>(sin(aRotationDegree));

		Matrix22<TYPE> transformationMatrix(cosValue,-sinValue,sinValue,cosValue);
		return(transformationMatrix);
	}

	/*template <class TYPE>
	void Matrix22<TYPE>::Transform(Vector2<TYPE>& aVector2)
	{
		double tempX =(myMatrix[0][0] * aVector2.myX) + (myMatrix[1][0] * aVector2.myX);
		double tempY = (myMatrix[0][1] * aVector2.myY) + (myMatrix[1][1] * aVector2.myY);
  
		aVector2.myX = tempX;
		aVector2.myY = tempY;
	}*/


};

namespace CU = CommonUtilities;

#endif