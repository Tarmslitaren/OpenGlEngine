#ifndef COMMONUTILITIES_MATRIX33_HEADER
#define COMMONUTILITIES_MATRIX33_HEADER

#include <math.h>
#include "vector3.h"
#include "staticarray.h"
#include "CommonMacros.h"

namespace CommonUtilities
{
	template <class TYPE>
	class Matrix33
	{
	public:
		Matrix33();
		Matrix33(TYPE aX1, TYPE aY1, TYPE aZ1, TYPE aX2, TYPE aY2, TYPE aZ2, TYPE aX3, TYPE aY3, TYPE aZ3);
		Matrix33(Vector3<TYPE> aVector1, Vector3<TYPE> aVector2, Vector3<TYPE> aVector3);
		Matrix33(StaticArray<StaticArray<TYPE,3>,3> aStaticArray);
		~Matrix33();

		void Set(TYPE aX1, TYPE aY1, TYPE aZ1, TYPE aX2, TYPE aY2, TYPE aZ2, TYPE aX3, TYPE aY3, TYPE aZ3);
		void Set(Vector3<TYPE> aVector1, Vector3<TYPE> aVector2, Vector3<TYPE> aVector3);
		void Set(StaticArray<StaticArray<TYPE,3>,3> aStaticArray);
		
		Matrix33& operator+=(const Matrix33& aMatrix33);
		Matrix33& operator-=(const Matrix33& aMatrix33);

		Matrix33& operator*=(const Matrix33& aMatrix33);
		Matrix33& operator*=(const Vector3<TYPE>& aVector3);
		Matrix33& operator*=(const TYPE& aType);
		Matrix33& operator/=(const TYPE& aType);

		Matrix33& operator=(const Matrix33& aMatrix33);

		bool operator==(const Matrix33& aMatrix33) const;

		Matrix33<TYPE> Transpose();
		Matrix33<TYPE> Inverse();

		static Matrix33<TYPE> Identity();
		static Matrix33<TYPE> TransformationX(TYPE aRotationDegree);
		static Matrix33<TYPE> TransformationY(TYPE aRotationDegree);
		static Matrix33<TYPE> TransformationZ(TYPE aRotationDegree);




		StaticArray<StaticArray<TYPE,3>,3> myMatrix;
	};

	//OPERATORS
	template <class TYPE>
	Matrix33<TYPE> operator+(const Matrix33<TYPE>& aLeftSideMatrix33,const Matrix33<TYPE>& aRightSideMatrix33)
	{
		Matrix33<TYPE> returnValue(aLeftSideMatrix33);
		returnValue+=aRightSideMatrix33;
		return(returnValue);
	}
	template <class TYPE>
	Matrix33<TYPE> operator-(const Matrix33<TYPE>& aLeftSideMatrix33,const Matrix33<TYPE>& aRightSideMatrix33)
	{
		Matrix33<TYPE> returnValue(aLeftSideMatrix33);
		returnValue-=aRightSideMatrix33;
		return(returnValue);
	}

	template <class TYPE>
	Matrix33<TYPE> operator*(const Matrix33<TYPE>& aLeftSideMatrix33,const Matrix33<TYPE>& aRightSideMatrix33)
	{
		Matrix33<TYPE> returnValue(aLeftSideMatrix33);
		returnValue*=aRightSideMatrix33;
		return(returnValue);
	}
	template <class TYPE>
	Matrix33<TYPE> operator*(const Matrix33<TYPE>& aLeftSideMatrix33,const Vector3<TYPE>& aRightSideVector3)
	{
		Matrix33<TYPE> returnValue(aLeftSideMatrix33);
		returnValue*=aRightSideVector3;
		return(returnValue);
	}

	template <class TYPE>
	Matrix33<TYPE> operator*(const Matrix33<TYPE>& aLeftSideMatrix33,const TYPE& aRightSideType)
	{
		Matrix33<TYPE> returnValue(aLeftSideMatrix33);
		returnValue*=aRightSideType;
		return(returnValue);
	}
	template <class TYPE>
	Matrix33<TYPE> operator/(const Matrix33<TYPE>& aLeftSideMatrix33,const TYPE& aRightSideType)
	{
		Matrix33<TYPE> returnValue(aLeftSideMatrix33);
		returnValue/=aRightSideType;
		return(returnValue);
	}

	//CONSTRUCTORS / DESTRUCTORS
	template <class TYPE>
	Matrix33<TYPE>::Matrix33()
	{
		myMatrix[0][0] = 0;
		myMatrix[0][1] = 0;
		myMatrix[0][2] = 0;
		myMatrix[1][0] = 0;
		myMatrix[1][1] = 0;
		myMatrix[1][2] = 0;
		myMatrix[2][0] = 0;
		myMatrix[2][1] = 0;
		myMatrix[2][2] = 0;
	}

	template <class TYPE>
	Matrix33<TYPE>::Matrix33(TYPE aX1, TYPE aY1, TYPE aZ1, TYPE aX2, TYPE aY2, TYPE aZ2, TYPE aX3, TYPE aY3, TYPE aZ3)
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
	}
	template <class TYPE>
	Matrix33<TYPE>::Matrix33(Vector3<TYPE> aVector1, Vector3<TYPE> aVector2, Vector3<TYPE> aVector3)
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
	}
	template <class TYPE>
	Matrix33<TYPE>::Matrix33(StaticArray<StaticArray<TYPE,3>,3> aStaticArray)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				myMatrix[i][j] = aStaticArray[i][j];
			}
		}
	}
	
	template <class TYPE>
	Matrix33<TYPE>::~Matrix33()
	{
	}

	//SET
	template <class TYPE>
	void Matrix33<TYPE>::Set(TYPE aX1, TYPE aY1, TYPE aZ1, TYPE aX2, TYPE aY2, TYPE aZ2, TYPE aX3, TYPE aY3, TYPE aZ3)
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
	}
	template <class TYPE>
	void Matrix33<TYPE>::Set(Vector3<TYPE> aVector1, Vector3<TYPE> aVector2, Vector3<TYPE> aVector3)
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
	}
	template <class TYPE>
	void Matrix33<TYPE>::Set(StaticArray<StaticArray<TYPE,3>,3> aStaticArray)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				myMatrix[i][j] = aStaticArray[i][j];
			}
		}
	}

	//OPERATORS
	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::operator+=(const Matrix33<TYPE>& aMatrix33)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				myMatrix[i][j] += aMatrix33.myMatrix[i][j];
			}
		}
		return(*this);
	}
	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::operator-=(const Matrix33<TYPE>& aMatrix33)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				myMatrix[i][j] -= aMatrix33.myMatrix[i][j];
			}
		}
		return(*this);
	}

	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::operator*=(const Matrix33<TYPE>& aMatrix33)
	{
		Matrix33<TYPE> resultMatrix;

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
		*this = resultMatrix;
		return(*this);
	}

	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::operator*=(const Vector3<TYPE>& aVector3)
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
	Matrix33<TYPE>& Matrix33<TYPE>::operator*=(const TYPE& aType)
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
	Matrix33<TYPE>& Matrix33<TYPE>::operator/=(const TYPE& aType)
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
	Matrix33<TYPE>& Matrix33<TYPE>::operator=(const Matrix33<TYPE>& aMatrix33)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				myMatrix[i][j] = aMatrix33.myMatrix[i][j];
			}
		}
		return(*this);
	}

	template <class TYPE>
	bool Matrix33<TYPE>::operator==(const Matrix33<TYPE>& aRightSideMatrix33) const
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(myMatrix[i][j] += aMatrix33.myMatrix[i][j]) return(false);
			}
		}
		return(true);
	}

	//FUNCTIONS

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::Transpose()
	{
		Matrix33<TYPE> transposedMatrix;

		transposedMatrix.myMatrix[0][0] = myMatrix[0][0];
		transposedMatrix.myMatrix[0][1] = myMatrix[1][0];
		transposedMatrix.myMatrix[0][2] = myMatrix[2][0];

		transposedMatrix.myMatrix[1][0] = myMatrix[0][1];
		transposedMatrix.myMatrix[1][1] = myMatrix[1][1];
		transposedMatrix.myMatrix[1][2] = myMatrix[2][1];

		transposedMatrix.myMatrix[2][0] = myMatrix[0][2];
		transposedMatrix.myMatrix[2][1] = myMatrix[1][2];
		transposedMatrix.myMatrix[2][2] = myMatrix[2][2];

		return(transposedMatrix);
	}
	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::Inverse()
	{
		return(this->Transpose());
	}

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::Identity()
	{
		Matrix33<TYPE> identityMatrix(1,0,0,0,1,0,0,0,1);
		return(identityMatrix);
	}

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::TransformationX(TYPE aRotationDegree)
	{
		double radian = 2 * PI * (aRotationDegree / 360.0);
		TYPE cosValue = static_cast<TYPE>(cos(radian));
		TYPE sinValue = static_cast<TYPE>(sin(radian));

		Matrix33<TYPE> transformationMatrix(1,0,0,0,cosValue,sinValue,0,-sinValue,cosValue);
		return(transformationMatrix);
	}
	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::TransformationY(TYPE aRotationDegree)
	{
		double radian = 2 * PI * (aRotationDegree / 360.0);
		TYPE cosValue = static_cast<TYPE>(cos(radian));
		TYPE sinValue = static_cast<TYPE>(sin(radian));

		Matrix33<TYPE> transformationMatrix(cosValue,0,-sinValue,0,1,0,sinValue,0,cosValue);
		return(transformationMatrix);
	}
	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::TransformationZ(TYPE aRotationDegree)
	{
		double radian = 2 * PI * (aRotationDegree / 360.0);
		TYPE cosValue = static_cast<TYPE>(cos(radian));
		TYPE sinValue = static_cast<TYPE>(sin(radian));

		Matrix33<TYPE> transformationMatrix(cosValue,sinValue,0,-sinValue,cosValue,0,0,0,1);
		return(transformationMatrix);
	}

};

namespace CU = CommonUtilities;

#endif