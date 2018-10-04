#ifndef COMMONUTILITIES_MATRIX34_HEADER
#define COMMONUTILITIES_MATRIX34_HEADER

#include <math.h>
#include "vector3.h"
#include "matrix33.h"
#include "staticarray.h"
#include "CommonMacros.h"

namespace CommonUtilities
{
	template <class TYPE>
	class Matrix34
	{
	public:
		Matrix34();
		Matrix34(TYPE aX1, TYPE aY1, TYPE aZ1, TYPE aX2, TYPE aY2, TYPE aZ2, TYPE aX3, TYPE aY3, TYPE aZ3, TYPE aPosX, TYPE aPosY, TYPE aPosZ);
		Matrix34(Vector3<TYPE> aVector1, Vector3<TYPE> aVector2, Vector3<TYPE> aVector3, Vector3<TYPE> aPositionVector);
		Matrix34(Matrix33<TYPE> aMatrix33, Vector3<TYPE> aPositionVector);
		Matrix34(StaticArray<StaticArray<TYPE,4>,3> aStaticArray);
		~Matrix34();

		void Set(TYPE aX1, TYPE aY1, TYPE aZ1, TYPE aX2, TYPE aY2, TYPE aZ2, TYPE aX3, TYPE aY3, TYPE aZ3, TYPE aPosX, TYPE aPosY, TYPE aPosZ);
		void Set(Vector3<TYPE> aVector1, Vector3<TYPE> aVector2, Vector3<TYPE> aVector3, Vector3<TYPE> aPositionVector);
		void Set(Matrix33<TYPE>, Vector3<TYPE> aPositionVector);
		void Set(StaticArray<StaticArray<TYPE,4>,3> aStaticArray);

		void SetPosition(TYPE aPosX, TYPE aPosY, TYPE aPosZ);
		Vector3<TYPE> GetPosition();

		Matrix34& operator*=(const Matrix34& aMatrix34);
		Matrix34& operator*=(const Matrix33<TYPE>& aMatrix33);
		Matrix34& operator*=(const Vector3<TYPE>& aVector3);
		Matrix34& operator*=(const TYPE& aType);
		Matrix34& operator/=(const TYPE& aType);

		Matrix34& operator=(const Matrix34& aMatrix34);

		bool operator==(const Matrix34& aMatrix34) const;




		StaticArray<StaticArray<TYPE,3>,4> myMatrix;
	};

	//OPERATORS
	template <class TYPE>
	Matrix34<TYPE> operator*(const Matrix34<TYPE>& aLeftSideMatrix34,const Matrix34<TYPE>& aRightSideMatrix34)
	{
		Matrix34<TYPE> returnValue(aLeftSideMatrix34);
		returnValue*=aRightSideMatrix34;
		return(returnValue);
	}

	template <class TYPE>
	Matrix34<TYPE> operator*(const Matrix34<TYPE>& aLeftSideMatrix34,const Matrix33<TYPE>& aRightSideMatrix33)
	{
		Matrix34<TYPE> returnValue(aLeftSideMatrix34);
		returnValue*=aRightSideMatrix33;
		return(returnValue);
	}
	template <class TYPE>
	Matrix34<TYPE> operator*(const Matrix34<TYPE>& aLeftSideMatrix33,const Vector3<TYPE>& aRightSideVector3)
	{
		Matrix34<TYPE> returnValue(aLeftSideMatrix33);
		returnValue*=aRightSideVector3;
		return(returnValue);
	}

	template <class TYPE>
	Matrix34<TYPE> operator*(const Matrix34<TYPE>& aLeftSideMatrix34,const TYPE& aRightSideType)
	{
		Matrix34<TYPE> returnValue(aLeftSideMatrix34);
		returnValue*=aRightSideType;
		return(returnValue);
	}
	template <class TYPE>
	Matrix34<TYPE> operator/(const Matrix34<TYPE>& aLeftSideMatrix34,const TYPE& aRightSideType)
	{
		Matrix34<TYPE> returnValue(aLeftSideMatrix34);
		returnValue/=aRightSideType;
		return(returnValue);
	}

	//CONSTRUCTORS / DESTRUCTORS
	template <class TYPE>
	Matrix34<TYPE>::Matrix34()
	{
	}

	template <class TYPE>
	Matrix34<TYPE>::Matrix34(TYPE aX1, TYPE aY1, TYPE aZ1, TYPE aX2, TYPE aY2, TYPE aZ2, TYPE aX3, TYPE aY3, TYPE aZ3, TYPE aPosX, TYPE aPosY, TYPE aPosZ)
	{
		myMatrix[0][0] = aX1;
		myMatrix[0][1] = aY1;
		myMatrix[0][2] = aZ1;
		myMatrix[1][0] = aX2;
		myMatrix[1][1] = aY2;
		myMatrix[1][2] = aZ2;
		myMatrix[2][0] = aX3;
		myMatrix[2][1] = aY3;
		myMatrix[2][2] = aZ3;
		myMatrix[3][0] = aPosX;
		myMatrix[3][1] = aPosY;
		myMatrix[3][2] = aPosZ;
	}
	template <class TYPE>
	Matrix34<TYPE>::Matrix34(Vector3<TYPE> aVector1, Vector3<TYPE> aVector2, Vector3<TYPE> aVector3, Vector3<TYPE> aPositionVector)
	{
		myMatrix[0][0] = aVector1.myX;
		myMatrix[0][1] = aVector1.myY;
		myMatrix[0][2] = aVector1.myZ;
		myMatrix[1][0] = aVector2.myX;
		myMatrix[1][1] = aVector2.myY;
		myMatrix[1][2] = aVector2.myZ;
		myMatrix[2][0] = aVector3.myX;
		myMatrix[2][1] = aVector3.myY;
		myMatrix[2][2] = aVector3.myZ;
		myMatrix[3][0] = aPositionVector.myX;
		myMatrix[3][1] = aPositionVector.myY;
		myMatrix[3][2] = aPositionVector.myZ;
	}
	template <class TYPE>
	Matrix34<TYPE>::Matrix34(Matrix33<TYPE> aMatrix33, Vector3<TYPE> aPositionVector)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				myMatrix[i][j] = aMatrix33.myMatrix[i][j];
			}
		}
		myMatrix[3][0] = aPositionVector.myX;
		myMatrix[3][1] = aPositionVector.myY;
		myMatrix[3][2] = aPositionVector.myZ;
	}
	template <class TYPE>
	Matrix34<TYPE>::Matrix34(StaticArray<StaticArray<TYPE,4>,3> aStaticArray)
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				myMatrix[i][j] = aStaticArray[i][j];
			}
		}
	}
	
	template <class TYPE>
	Matrix34<TYPE>::~Matrix34()
	{
	}

	//SET
	template <class TYPE>
	void Matrix34<TYPE>::Set(TYPE aX1, TYPE aY1, TYPE aZ1, TYPE aX2, TYPE aY2, TYPE aZ2, TYPE aX3, TYPE aY3, TYPE aZ3, TYPE aPosX, TYPE aPosY, TYPE aPosZ)
	{
		myMatrix[0][0] = aX1;
		myMatrix[0][1] = aY1;
		myMatrix[0][2] = aZ1;
		myMatrix[1][0] = aX2;
		myMatrix[1][1] = aY2;
		myMatrix[1][2] = aZ2;
		myMatrix[2][0] = aX3;
		myMatrix[2][1] = aY3;
		myMatrix[2][2] = aZ3;
		myMatrix[3][0] = aPosX;
		myMatrix[3][1] = aPosY;
		myMatrix[3][2] = aPosZ;
	}
	template <class TYPE>
	void Matrix34<TYPE>::Set(Vector3<TYPE> aVector1, Vector3<TYPE> aVector2, Vector3<TYPE> aVector3, Vector3<TYPE> aPositionVector)
	{
		myMatrix[0][0] = aVector1.myX;
		myMatrix[0][1] = aVector1.myY;
		myMatrix[0][2] = aVector1.myZ;
		myMatrix[1][0] = aVector2.myX;
		myMatrix[1][1] = aVector2.myY;
		myMatrix[1][2] = aVector2.myZ;
		myMatrix[2][0] = aVector3.myX;
		myMatrix[2][1] = aVector3.myY;
		myMatrix[2][2] = aVector3.myZ;
		myMatrix[3][0] = aPositionVector.myX;
		myMatrix[3][1] = aPositionVector.myY;
		myMatrix[3][2] = aPositionVector.myZ;
	}
	template <class TYPE>
	void Matrix34<TYPE>::Set(Matrix33<TYPE> aMatrix33, Vector3<TYPE> aPositionVector)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				myMatrix[i][j] = aMatrix33.myMatrix[i][j];
			}
		}
		myMatrix[3][0] = aPositionVector.myX;
		myMatrix[3][1] = aPositionVector.myY;
		myMatrix[3][2] = aPositionVector.myZ;
	}
	template <class TYPE>
	void Matrix34<TYPE>::Set(StaticArray<StaticArray<TYPE,4>,3> aStaticArray)
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				myMatrix[i][j] = aStaticArray[i][j];
			}
		}
	}

	template <class TYPE>
	void Matrix34<TYPE>::SetPosition(TYPE aPosX, TYPE aPosY, TYPE aPosZ)
	{
		myMatrix[3][0] = aPosX;
		myMatrix[3][1] = aPosY;
		myMatrix[3][2] = aPosZ;
	}
	template <class TYPE>
	Vector3<TYPE> Matrix34<TYPE>::GetPosition()
	{
		Vector3<TYPE> positionVector(myMatrix[3][0], myMatrix[3][1], myMatrix[3][2]);
	}

	//OPERATORS
	template <class TYPE>
	Matrix34<TYPE>& Matrix34<TYPE>::operator*=(const Matrix34<TYPE>& aMatrix34)
	{
		Matrix34<TYPE> resultMatrix;

		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				resultMatrix.myMatrix[i][j] = 0;
				for(int k = 0; k < 3; k++)
				{
					resultMatrix.myMatrix[i][j] += myMatrix[i][k] * aMatrix34.myMatrix[k][j];
				}
			}
		}
		*this = resultMatrix;
		return(*this);
	}

	template <class TYPE>
	Matrix34<TYPE>& Matrix34<TYPE>::operator*=(const Matrix33<TYPE>& aMatrix33)
	{
		Matrix34<TYPE> resultMatrix;

		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				resultMatrix.myMatrix[i][j] = 0;
				for(int k = 0; k < 3; k++)
				{
					resultMatrix.myMatrix[i][j] += myMatrix[i][k] * aMatrix33.myMatrix[k][j];
				}
			}
		}

		resultMatrix.myMatrix[3][0] = myMatrix[3][0];
		resultMatrix.myMatrix[3][1] = myMatrix[3][1];
		resultMatrix.myMatrix[3][2] = myMatrix[3][2];

		*this = resultMatrix;
		return(*this);
	}

	template <class TYPE>
	Matrix34<TYPE>& Matrix34<TYPE>::operator*=(const Vector3<TYPE>& aVector3)
	{
		myMatrix[0][0] *= aVector3.myX;
		myMatrix[0][1] *= aVector3.myX;
		myMatrix[0][2] *= aVector3.myX;
		myMatrix[1][0] *= aVector3.myY;
		myMatrix[1][1] *= aVector3.myY;
		myMatrix[1][2] *= aVector3.myY;
		myMatrix[2][0] *= aVector3.myZ;
		myMatrix[2][1] *= aVector3.myZ;
		myMatrix[2][2] *= aVector3.myZ;

		return(*this);
	}

	template <class TYPE>
	Matrix34<TYPE>& Matrix34<TYPE>::operator*=(const TYPE& aType)
	{
		myMatrix[0][0] *= aType;
		myMatrix[0][1] *= aType;
		myMatrix[0][2] *= aType;
		myMatrix[1][0] *= aType;
		myMatrix[1][1] *= aType;
		myMatrix[1][2] *= aType;
		myMatrix[2][0] *= aType;
		myMatrix[2][1] *= aType;
		myMatrix[2][2] *= aType;

		return(*this);
	}
	template <class TYPE>
	Matrix34<TYPE>& Matrix34<TYPE>::operator/=(const TYPE& aType)
	{
		myMatrix[0][0] /= aType;
		myMatrix[0][1] /= aType;
		myMatrix[0][2] /= aType;
		myMatrix[1][0] /= aType;
		myMatrix[1][1] /= aType;
		myMatrix[1][2] /= aType;
		myMatrix[2][0] /= aType;
		myMatrix[2][1] /= aType;
		myMatrix[2][2] /= aType;

		return(*this);
	}

	template <class TYPE>
	Matrix34<TYPE>& Matrix34<TYPE>::operator=(const Matrix34<TYPE>& aMatrix34)
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				myMatrix[i][j] = aMatrix34.myMatrix[i][j];
			}
		}

		return(*this);
	}

	template <class TYPE>
	bool Matrix34<TYPE>::operator==(const Matrix34<TYPE>& aRightSideMatrix34) const
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(myMatrix[i][j] += aMatrix33.myMatrix[i][j]) return(false);
			}
		}
		return(true);
	}
};

namespace CU = CommonUtilities;

#endif