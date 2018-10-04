#ifndef COMMONUTILITIES_MATRIX44_HEADER
#define COMMONUTILITIES_MATRIX44_HEADER

#include <math.h>
#include "StaticArray.h"

namespace CommonUtilities
{
	template <class TYPE>
	class Matrix44
	{
	public:
		Matrix44();
		Matrix44(const Matrix44& aMatrix);
		Matrix44(	
			const TYPE aXX,const TYPE aXY,const TYPE aXZ, const TYPE aXW,
			const TYPE aYX,const TYPE aYY,const TYPE aYZ, const TYPE aYW,
			const TYPE aZX,const TYPE aZY,const TYPE aZZ, const TYPE aZW,
			const TYPE aWX,const TYPE aWY,const TYPE aWZ, const TYPE aWW);
		~Matrix44();

		void Set(	
			const TYPE aXX,const TYPE aXY,const TYPE aXZ, const TYPE aXW,
			const TYPE aYX,const TYPE aYY,const TYPE aYZ, const TYPE aYW,
			const TYPE aZX,const TYPE aZY,const TYPE aZZ, const TYPE aZW,
			const TYPE aWX,const TYPE aWY,const TYPE aWZ, const TYPE aWW);

		Matrix44<TYPE>& operator*=(const Matrix44& aMatrix);

		Matrix44<TYPE>& operator*=(const TYPE& aType);


		Matrix44<TYPE>& operator=(const Matrix44& aMatirx);
		Matrix44<TYPE> Transpose();

		Matrix44<TYPE>& SetRotationX(float aAngle);
		Matrix44<TYPE>& SetRotationY(float aAngle);
		Matrix44<TYPE>& SetRotationZ(float aAngle);
		Matrix44<TYPE>& SetIdentity();

		Matrix44<TYPE>& Scale(const TYPE& aType);

		static Matrix44<TYPE> RotateX(float aAngle);
		static Matrix44<TYPE> RotateY(float aAngle);
		static Matrix44<TYPE> RotateZ(float aAngle);
		static Matrix44<TYPE> Identity();

		StaticArray<StaticArray<TYPE, 4>, 4> myMatrix;
	};

	template <class TYPE>
	Matrix44<TYPE> operator*(const Matrix44<TYPE>& aLeftSideVector,const Matrix44<TYPE>& aRightSideVector)
	{
		Matrix44<TYPE> returnValue(aLeftSideVector);
		returnValue*=aRightSideVector;
		return(returnValue);
	}

	template <class TYPE>
	Matrix44<TYPE> operator*(const Matrix44<TYPE>& aLeftSideVector,const TYPE& aRightSideType)
	{
		Matrix44<TYPE> returnValue(aLeftSideVector);
		returnValue*=aRightSideType;
		return(returnValue);
	}




	template <class TYPE>
	Matrix44<TYPE>::Matrix44()
	{
	}

	template <class TYPE>
	Matrix44<TYPE>::Matrix44(const Matrix44& aMatrix)
	{
		*this = aMatrix;
	}

	template <class TYPE>
	Matrix44<TYPE>::Matrix44(
		const TYPE aXX,const TYPE aXY,const TYPE aXZ, const TYPE aXW,
		const TYPE aYX,const TYPE aYY,const TYPE aYZ, const TYPE aYW,
		const TYPE aZX,const TYPE aZY,const TYPE aZZ, const TYPE aZW,
		const TYPE aWX,const TYPE aWY,const TYPE aWZ, const TYPE aWW)
	{
		myMatrix[0][0] = aXX;
		myMatrix[1][0] = aXY;
		myMatrix[2][0] = aXZ;
		myMatrix[3][0] = aXW;

		myMatrix[0][1] = aYX;
		myMatrix[1][1] = aYY;
		myMatrix[2][1] = aYZ;
		myMatrix[3][1] = aYW;

		myMatrix[0][2] = aZX;
		myMatrix[1][2] = aZY;
		myMatrix[2][2] = aZZ;
		myMatrix[3][2] = aZW;

		myMatrix[0][3] = aWX;
		myMatrix[1][3] = aWY;
		myMatrix[2][3] = aWZ;
		myMatrix[3][3] = aWW;
	}

	template <class TYPE>
	Matrix44<TYPE>::~Matrix44()
	{
	}

	template <class TYPE>
	void Matrix44<TYPE>::Set(
		const TYPE aXX,const TYPE aXY,const TYPE aXZ, const TYPE aXW,
		const TYPE aYX,const TYPE aYY,const TYPE aYZ, const TYPE aYW,
		const TYPE aZX,const TYPE aZY,const TYPE aZZ, const TYPE aZW,
		const TYPE aWX,const TYPE aWY,const TYPE aWZ, const TYPE aWW)
	{
		myMatrix[0][0] = aXX;
		myMatrix[1][0] = aXY;
		myMatrix[2][0] = aXZ;
		myMatrix[3][0] = aXW;

		myMatrix[0][1] = aYX;
		myMatrix[1][1] = aYY;
		myMatrix[2][1] = aYZ;
		myMatrix[3][1] = aYW;

		myMatrix[0][2] = aZX;
		myMatrix[1][2] = aZY;
		myMatrix[2][2] = aZZ;
		myMatrix[3][2] = aZW;

		myMatrix[0][3] = aWX;
		myMatrix[1][3] = aWY;
		myMatrix[2][3] = aWZ;
		myMatrix[3][3] = aWW;
	}

	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::operator*=(const Matrix44<TYPE>& aMatrix)
	{
		Matrix44<TYPE> tempMatrix;
		TYPE currentValue = 0;
		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				for(int k = 0; k < 5; k++)
				{
					currentValue += myMatrix[k][y] * aMatrix.myMatrix[x][k];
				}
				tempMatrix.myMatrix[x][y] = currentValue;
				currentValue = 0;
			}
		}
		*this = tempMatrix;
		return(*this);
	}

	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::operator=(const Matrix44<TYPE>& aMatrix)
	{
		this->myMatrix[0][0] = aMatrix.myMatrix[0][0];
		this->myMatrix[1][0] = aMatrix.myMatrix[1][0];
		this->myMatrix[2][0] = aMatrix.myMatrix[2][0];
		this->myMatrix[3][0] = aMatrix.myMatrix[3][0];

		this->myMatrix[0][1] = aMatrix.myMatrix[0][1];
		this->myMatrix[1][1] = aMatrix.myMatrix[1][1];
		this->myMatrix[2][1] = aMatrix.myMatrix[2][1];
		this->myMatrix[3][1] = aMatrix.myMatrix[3][1];

		this->myMatrix[0][2] = aMatrix.myMatrix[0][2];
		this->myMatrix[1][2] = aMatrix.myMatrix[1][2];
		this->myMatrix[2][2] = aMatrix.myMatrix[2][2];
		this->myMatrix[3][2] = aMatrix.myMatrix[3][2];

		this->myMatrix[0][3] = aMatrix.myMatrix[0][3];
		this->myMatrix[1][3] = aMatrix.myMatrix[1][3];
		this->myMatrix[2][3] = aMatrix.myMatrix[2][3];
		this->myMatrix[3][3] = aMatrix.myMatrix[3][3];
		return(*this);
	}

	template <class TYPE>
	Matrix44<TYPE> Matrix44<TYPE>::Transpose()
	{
		return Matrix44<TYPE>(	
			myMatrix[0][0],myMatrix[0][1],myMatrix[0][2],myMatrix[0][3],
			myMatrix[1][0],myMatrix[1][1],myMatrix[1][2],myMatrix[1][3],
			myMatrix[2][0],myMatrix[2][1],myMatrix[2][2],myMatrix[2][3],
			myMatrix[3][0],myMatrix[3][1],myMatrix[3][2],myMatrix[3][3]);	
	}

	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::SetRotationX(float aAngle)
	{
		return *this *= RotateX(aAngle);
	}

	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::SetRotationY(float aAngle)
	{
		return *this *= RotateY(aAngle);
	}

	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::SetRotationZ(float aAngle)
	{
		return *this *= RotateZ(aAngle);
	}

	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::SetIdentity()
	{
		return *this = Identity();
	}

	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::Scale(const TYPE& aType)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				myMatrix[x][y] *= aType;
			}
		}
		return(*this);
	}

	template <class TYPE>
	Matrix44<TYPE> Matrix44<TYPE>::RotateX(float aAngle)
	{
		aAngle = (aAngle*2*3.14159265f)/360;
		Matrix44<TYPE> transformationMatrix;

		transformationMatrix.SetIdentity();
		transformationMatrix[1][1] = cos(aAngle);
		transformationMatrix[1][2] = -sin(aAngle);
		transformationMatrix[2][1] = sin(aAngle);
		transformationMatrix[2][2] = cos(aAngle);


		return(transformationMatrix);
	}

	template <class TYPE>
	Matrix44<TYPE> Matrix44<TYPE>::RotateY(float aAngle)
	{
		aAngle = (aAngle*2*3.14159265f)/360;
		Matrix44<TYPE> transformationMatrix;
		transformationMatrix.SetIdentity();
		transformationMatrix[0][0] = cos(aAngle);
		transformationMatrix[0][2] = sin(aAngle);
		transformationMatrix[2][0] = -sin(aAngle);
		transformationMatrix[2][2] = cos(aAngle);


		return(transformationMatrix);
	}

	template <class TYPE>
	Matrix44<TYPE> Matrix44<TYPE>::RotateZ(float aAngle)
	{
		aAngle = (aAngle*2*3.14159265f)/360;
		Matrix44<TYPE> transformationMatrix;

		transformationMatrix.SetIdentity();

		transformationMatrix[1][1] = cos(aAngle);
		transformationMatrix[1][2] = -sin(aAngle);
		transformationMatrix[2][1] = sin(aAngle);
		transformationMatrix[2][2] = cos(aAngle);

		return(transformationMatrix);
	}

	template <class TYPE>
	Matrix44<TYPE> Matrix44<TYPE>::Identity()
	{
		Matrix44<TYPE> identityMatrix(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		return(identityMatrix);
	}


	typedef Matrix44<float> Matrix44f;
	typedef Matrix44<double> Matrix44d;
	typedef Matrix44<int> Matrix44i;
};
namespace CU = CommonUtilities;

#endif