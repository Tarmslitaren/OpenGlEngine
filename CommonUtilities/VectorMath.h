#ifndef COMMONUTILITIES_VECTORMATH_HEADER
#define COMMONUTILITIES_VECTORMATH_HEADER

#include "CU_vector.h"
#include "CU_Matrix.h"

namespace CommonUtilities
{


	template <class TYPE>
	CU::Matrix33<TYPE> GenerateMatrix(CU::Vector3<TYPE> aDirection)
	{
		CU::Vector3<TYPE> zAxis(aDirection);
		aDirection.Normalize();

		CU::Vector3<TYPE>  yAxis;

		if (!zAxis.myX && !zAxis.myZ)
		{
			yAxis = CU::Vector3<TYPE>(-zAxis.myY, 0.0f, 0.0f );
		}
		else
		{
			yAxis = CU::Vector3<TYPE>(0.0f, 1.0f, 0.0f);
		}

		CU::Vector3<TYPE> xAxis = yAxis.Cross( zAxis );
		xAxis.Normalize();
		yAxis = xAxis.Cross( zAxis );
		yAxis.Normalize();
		//yAxis.myX = -yAxis.myX;
		//yAxis.myY = -yAxis.myY;
		//yAxis.myZ = -yAxis.myZ;

		CU::Matrix33<TYPE> rot(xAxis.myX, xAxis.myY, xAxis.myZ, yAxis.myX, yAxis.myY, yAxis.myZ, zAxis.myX, zAxis.myY, zAxis.myZ);

		return rot;
	}

	template <class TYPE>
	Vector3<TYPE> GetVector(const Matrix44<TYPE>& aMatrix)
	{
		Vector3<TYPE> returnValue;
		returnValue.myX = aMatrix.myMatrix[3][0];
		returnValue.myY = aMatrix.myMatrix[3][1]; 
		returnValue.myZ = aMatrix.myMatrix[3][2];
		return returnValue;
	}


	//set vector in 44matrix
	template <class TYPE>
	void SetVectorOfMatrix(Matrix44<TYPE>& aMatrix, const CU::Vector3f& aVector)
	{
		aMatrix.myMatrix[3][0] = aVector.myX;
		aMatrix.myMatrix[3][1] = aVector.myY;
		aMatrix.myMatrix[3][2] = aVector.myZ;
	}


	template <class TYPE>
	Vector3<TYPE> operator*(const Vector3<TYPE>& aVector,const Matrix33<TYPE>& aMatrix)
	{
		Vector3<TYPE> returnValue;

		returnValue.x=aVector.myX*aMatrix.myMatrix[0][0]+aVector.myY*aMatrix.myMatrix[1][0]+aVector.myZ*aMatrix.myMatrix[2][0];
		returnValue.y=aVector.myX*aMatrix.myMatrix[0][1]+aVector.myY*aMatrix.myMatrix[1][1]+aVector.myZ*aMatrix.myMatrix[2][1];
		returnValue.z=aVector.myX*aMatrix.myMatrix[0][2]+aVector.myY*aMatrix.myMatrix[1][2]+aVector.myZ*aMatrix.myMatrix[2][2];

		return(returnValue);
	}

	template <class TYPE>
	Vector3<TYPE> operator*(const Vector3<TYPE>& aVector,const Matrix44<TYPE>& aMatrix)
	{
		Vector3<TYPE> returnValue;

		returnValue.x = aVector.myX*aMatrix.myMatrix[0][0]+aVector.myY*aMatrix.myMatrix[1][0]+aVector.myZ*aMatrix.myMatrix[2][0];
		returnValue.y = aVector.myX*aMatrix.myMatrix[0][1]+aVector.myY*aMatrix.myMatrix[1][1]+aVector.myZ*aMatrix.myMatrix[2][1];
		returnValue.z = aVector.myX*aMatrix.myMatrix[0][2]+aVector.myY*aMatrix.myMatrix[1][2]+aVector.myZ*aMatrix.myMatrix[2][2];

		return(returnValue);
	}


	template <class TYPE>
	Vector4<TYPE> operator*(const Vector4<TYPE>& aVector,const Matrix44<TYPE>& aMatrix)
	{
		Vector4<TYPE> returnValue;

		returnValue.x=aVector.myX*aMatrix.myMatrix[0][0]+aVector.myY*aMatrix.myMatrix[1][0]+aVector.myZ*aMatrix.myMatrix[2][0]+aVector.myW*aMatrix.myMatrix[3][0];
		returnValue.y=aVector.myX*aMatrix.myMatrix[0][1]+aVector.myY*aMatrix.myMatrix[1][1]+aVector.myZ*aMatrix.myMatrix[2][1]+aVector.myW*aMatrix.myMatrix[3][1];
		returnValue.z=aVector.myX*aMatrix.myMatrix[0][2]+aVector.myY*aMatrix.myMatrix[1][2]+aVector.myZ*aMatrix.myMatrix[2][2]+aVector.myW*aMatrix.myMatrix[3][2];
		returnValue.w=aVector.myX*aMatrix.myMatrix[0][3]+aVector.myY*aMatrix.myMatrix[1][3]+aVector.myZ*aMatrix.myMatrix[2][3]+aVector.myW*aMatrix.myMatrix[3][3];

		return(returnValue);
	}

}

#endif