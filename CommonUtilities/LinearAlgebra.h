#ifndef COMMONUTILITIES_LINEAR_ALGEBRA_HEADER
#define COMMONUTILITIES_LINEAR_ALGEBRA_HEADER

#include <math.h>

#include "CU_Vector2.h"
#include "CU_Vector3.h"
#include "CU_Matrix33.h"
#include "CU_Matrix34.h"

namespace CommonUtilities
{
	template <class TYPE>
	Vector3<TYPE> operator*(const Vector3<TYPE>& aVector, const Matrix33<TYPE>& aMatrix)
	{
		Vector3<TYPE> returnValue(aVector);
		returnValue*=aMatrix;
		return(returnValue);
	}

	template <class TYPE>	
	Matrix33<TYPE> operator*(const Matrix33<TYPE>& aMatrix, const Vector3<TYPE>& aVector)
	{
		Matrix33<TYPE> returnValue(aMatrix);
		returnValue*=aVector;
		return(returnValue);
	}

	template <class TYPE>
	void operator*=(Vector3<TYPE>& aVector, const Matrix33<TYPE>& aMatrix)
	{
		TYPE tempX = aVector.myX;
		TYPE tempY = aVector.myY;
		TYPE tempZ = aVector.myZ;
		aVector.myX = (tempX*aMatrix.myMatrix[0][0]) + (tempY*aMatrix.myMatrix[1][0]) + (tempZ*aMatrix.myMatrix[2][0]);
		aVector.myY = (tempX*aMatrix.myMatrix[0][1]) + (tempY*aMatrix.myMatrix[1][1]) + (tempZ*aMatrix.myMatrix[2][1]);
		aVector.myZ = (tempX*aMatrix.myMatrix[0][2]) + (tempY*aMatrix.myMatrix[1][2]) + (tempZ*aMatrix.myMatrix[2][2]);
	}

	template <class TYPE>	
	void operator*=(Matrix33<TYPE>& aMatrix, const Vector3<TYPE>& aVector)
	{
		for (int column = 0; column < 3; column++)
		{
			aMatrix.myMatrix[column][0] = aMatrix.myMatrix[column][0] * aVector.myX;
			aMatrix.myMatrix[column][1] = aMatrix.myMatrix[column][1] * aVector.myY;
			aMatrix.myMatrix[column][2] = aMatrix.myMatrix[column][2] * aVector.myZ;
		}
	}

	template <class TYPE>
	Vector3<TYPE> operator*(const Vector3<TYPE>& aVector, const Matrix34<TYPE>& aMatrix)
	{
		Vector3<TYPE> returnValue(aVector);
		returnValue*=aMatrix;
		return(returnValue);
	}

	template <class TYPE>	
	Matrix34<TYPE> operator*(const Matrix34<TYPE>& aMatrix, const Vector3<TYPE>& aVector)
	{
		Matrix34<TYPE> returnValue(aMatrix);
		returnValue*=aVector;
		return(returnValue);
	}

	template <class TYPE>
	void operator*=(Vector3<TYPE>& aVector, const Matrix34<TYPE>& aMatrix)
	{
		TYPE tempX = aVector.myX;
		TYPE tempY = aVector.myY;
		TYPE tempZ = aVector.myZ;
		aVector.myX = (tempX*aMatrix.myMatrix[0][0]) + (tempY*aMatrix.myMatrix[1][0]) + (tempZ*aMatrix.myMatrix[2][0]);
		aVector.myY = (tempX*aMatrix.myMatrix[0][1]) + (tempY*aMatrix.myMatrix[1][1]) + (tempZ*aMatrix.myMatrix[2][1]);
		aVector.myZ = (tempX*aMatrix.myMatrix[0][2]) + (tempY*aMatrix.myMatrix[1][2]) + (tempZ*aMatrix.myMatrix[2][2]);
	}

	template <class TYPE>	
	void operator*=(Matrix34<TYPE>& aMatrix, const Vector3<TYPE>& aVector)
	{
		for (int column = 0; column < 3; column++)
		{
			aMatrix.myMatrix[column][0] = aMatrix.myMatrix[column][0] * aVector.myX;
			aMatrix.myMatrix[column][1] = aMatrix.myMatrix[column][1] * aVector.myY;
			aMatrix.myMatrix[column][2] = aMatrix.myMatrix[column][2] * aVector.myZ;
		}
	}

	template <class TYPE>	
	Matrix34<TYPE> operator*(const Matrix34<TYPE>& aMatrix34, const Matrix33<TYPE>& aMatrix33)
	{
		Matrix34<TYPE> returnValue(aMatrix);
		returnValue*=aVector;
		return(returnValue);
	}

	template <class TYPE>	
	void operator*=(Matrix34<TYPE>& aMatrix34, const Matrix33<TYPE>& aMatrix33)
	{
		Matrix34<TYPE> tempMatrix(	aMatrix33[0][0],aMatrix33[1][0],aMatrix33[2][0],
									aMatrix33[0][1],aMatrix33[1][1],aMatrix33[2][1],
									aMatrix33[0][2],aMatrix33[1][2],aMatrix33[2][2],
									aMatrix34[0][3],aMatrix34[1][3],aMatrix34[2][3]);
		tempMatrix * aMatrix34;
		return tempMatrix;
	}

	template <class TYPE>	
	Matrix33<TYPE> operator*(const Matrix33<TYPE>& aMatrix33, const Matrix34<TYPE>& aMatrix34)
	{
		Matrix34<TYPE> returnValue(aMatrix);
		returnValue*=aVector;
		return(returnValue);
	}

	template <class TYPE>	
	void operator*=(Matrix33<TYPE>& aMatrix33, const Matrix34<TYPE>& aMatrix34)
	{
		Matrix34<TYPE> tempMatrix(	aMatrix34[0][0],aMatrix34[1][0],aMatrix34[2][0],
									aMatrix34[0][1],aMatrix34[1][1],aMatrix34[2][1],
									aMatrix34[0][2],aMatrix34[1][2],aMatrix34[2][2]);
		tempMatrix * aMatrix33;
		return tempMatrix;
	}
};

#endif