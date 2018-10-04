#ifndef MATRIX2D33_HEADER
#define MATRIX2D33_HEADER

#include <math.h>
#include <vector>

#include "Vector2.h"

namespace CommonUtilities
{
	template <typename TYPE>
	class Matrix2D33
	{

	private:
	  
		template <typename TYPE>
		struct Matrix2D
		{
			Matrix2D()
			{
				_11=NULL; _12=NULL; _13=NULL;
				_21=NULL; _22=NULL; _23=NULL;
				_31=NULL; _32=NULL; _33=NULL;
			}

			TYPE _11, _12, _13;
			TYPE _21, _22, _23;
			TYPE _31, _32, _33;

		};

	 public:

		Matrix2D33()
		{
			Identity();
		}

	  //create an identity matrix
		inline void Identity();
	  
	  //create a transformation matrix
		inline void Translate(TYPE aX, TYPE aY);

	  //create a scale matrix
		inline void Scale(TYPE aScaleX, TYPE aScaleY);

	  //create a rotation matrix
		inline void  Rotate(TYPE aRotation);

	  //create a rotation matrix from a fwd and side 2D vector
		inline void  Rotate(const Vector2<TYPE>& aForward, const Vector2<TYPE>& aSide);

	   //applys a transformation matrix to a std::vector of points
		inline void TransformVector2(std::vector<Vector2<TYPE>>& someVectors);

	  //applys a transformation matrix to a point
		inline void TransformVector2(Vector2<TYPE>& aVector);

	  //accessors to the matrix elements
		inline void _11(TYPE aValue){myMatrix._11 = aValue;}
		inline void _12(TYPE aValue){myMatrix._12 = aValue;}
		inline void _13(TYPE aValue){myMatrix._13 = aValue;}

		inline void _21(TYPE aValue){myMatrix._21 = aValue;}
		inline void _22(TYPE aValue){myMatrix._22 = aValue;}
		inline void _23(TYPE aValue){myMatrix._23 = aValue;}

		inline void _31(TYPE aValue){myMatrix._31 = aValue;}
		inline void _32(TYPE aValue){myMatrix._32 = aValue;}
		inline void _33(TYPE aValue){myMatrix._33 = aValue;}

	private:

		inline void  MatrixMultiply(Matrix2D<TYPE>& aMatrix2D);

	private:
	  
		Matrix2D<TYPE> myMatrix;

	};



	//multiply two matrices together
	template <typename TYPE>
	inline void Matrix2D33<TYPE>::MatrixMultiply(Matrix2D<TYPE>& aMatrix2D)
	{
		Matrix2D33<TYPE>::Matrix2D<TYPE> tempMatrix;
	  
		tempMatrix._11 = (myMatrix._11*aMatrix2D._11) + (myMatrix._12*aMatrix2D._21) + (myMatrix._13*aMatrix2D._31);
		tempMatrix._12 = (myMatrix._11*aMatrix2D._12) + (myMatrix._12*aMatrix2D._22) + (myMatrix._13*aMatrix2D._32);
		tempMatrix._13 = (myMatrix._11*aMatrix2D._13) + (myMatrix._12*aMatrix2D._23) + (myMatrix._13*aMatrix2D._33);

		tempMatrix._21 = (myMatrix._21*aMatrix2D._11) + (myMatrix._22*aMatrix2D._21) + (myMatrix._23*aMatrix2D._31);
		tempMatrix._22 = (myMatrix._21*aMatrix2D._12) + (myMatrix._22*aMatrix2D._22) + (myMatrix._23*aMatrix2D._32);
		tempMatrix._23 = (myMatrix._21*aMatrix2D._13) + (myMatrix._22*aMatrix2D._23) + (myMatrix._23*aMatrix2D._33);

		tempMatrix._31 = (myMatrix._31*aMatrix2D._11) + (myMatrix._32*aMatrix2D._21) + (myMatrix._33*aMatrix2D._31);
		tempMatrix._32 = (myMatrix._31*aMatrix2D._12) + (myMatrix._32*aMatrix2D._22) + (myMatrix._33*aMatrix2D._32);
		tempMatrix._33 = (myMatrix._31*aMatrix2D._13) + (myMatrix._32*aMatrix2D._23) + (myMatrix._33*aMatrix2D._33);

		myMatrix = tempMatrix;
	}

	//applies a 2D transformation matrix to a std::vector of Vector2Ds
	template <typename TYPE>
	inline void Matrix2D33<TYPE>::TransformVector2(std::vector<Vector2<TYPE>>& someVectors)
	{
	  for (unsigned int index = 0; index < someVectors.size(); ++index)
	  {
			TYPE tempX = (myMatrix._11*someVectors[i].myX) + (myMatrix._21*someVectors[i].myY) + (myMatrix._31);
			TYPE tempY = (myMatrix._12*someVectors[i].myX) + (myMatrix._22*someVectors[i].myY) + (myMatrix._32);
	  
			someVectors[i].myX = tempX;
			someVectors[i].myY = tempY;
	  }
	}

	//applies a 2D transformation matrix to a single Vector2D
	template <typename TYPE>
	inline void Matrix2D33<TYPE>::TransformVector2(Vector2<TYPE>& aVector)
	{
		TYPE tempX = (myMatrix._11*aVector.myX) + (myMatrix._21*aVector.myY) + (myMatrix._31);
		TYPE tempY = (myMatrix._12*aVector.myX) + (myMatrix._22*aVector.myY) + (myMatrix._32);
	  
		aVector.myX = tempX;
		aVector.myY = tempY;
	}

	//create an identity matrix
	template <typename TYPE>
	inline void Matrix2D33<TYPE>::Identity()
	{
		myMatrix._11 = 1; myMatrix._12 = 0; myMatrix._13 = 0;
		myMatrix._21 = 0; myMatrix._22 = 1; myMatrix._23 = 0;
		myMatrix._31 = 0; myMatrix._32 = 0; myMatrix._33 = 1;
	}

	//create a transformation matrix
	template <typename TYPE>
	inline void Matrix2D33<TYPE>::Translate(TYPE aX, TYPE aY)
	{
		Matrix2D<TYPE> matrix;
	  
		matrix._11 = 1;  matrix._12 = 0;  matrix._13 = 0;
		matrix._21 = 0;  matrix._22 = 1;  matrix._23 = 0;
		matrix._31 = aX; matrix._32 = aY; matrix._33 = 1;
	  
		MatrixMultiply(matrix);
	}

	//create a scale matrix
	template <typename TYPE>
	inline void Matrix2D33<TYPE>::Scale(TYPE aScaleX, TYPE aScaleY)
	{
		Matrix2D33<TYPE>::Matrix2D<TYPE> matrix;
	  
		matrix._11 = aScaleX; matrix._12 = 0;		matrix._13 = 0;
		matrix._21 = 0;		  matrix._22 = aScaleY; matrix._23 = 0;
		matrix._31 = 0;		  matrix._32 = 0;		matrix._33 = 1;
	  
		MatrixMultiply(matrix);
	}


	//create a rotation matrix
	template <typename TYPE>
	inline void Matrix2D33<TYPE>::Rotate(TYPE aRotation)
	{
		Matrix2D33<TYPE>::Matrix2D<TYPE> matrix;

		TYPE Sin = sin(aRotation);
		TYPE Cos = cos(aRotation);
	  
		matrix._11 = Cos;  matrix._12 = Sin; matrix._13 = 0;
		matrix._21 = -Sin; matrix._22 = Cos; matrix._23 = 0;
		matrix._31 = 0;	   matrix._32 = 0;	 matrix._33 = 1;
	  
		MatrixMultiply(matrix);
	}


	//create a rotation matrix from a 2D vector
	template <typename TYPE>
	inline void Matrix2D33<TYPE>::Rotate(const Vector2<TYPE>& aForward, const Vector2<TYPE>& aSide)
	{
		Matrix2D33<TYPE>::Matrix2D<TYPE> matrix;
	  
		matrix._11 = aForward.myX;  matrix._12 = aForward.myY;  matrix._13 = 0; 
		matrix._21 = aSide.myX;		matrix._22 = aSide.myY;		matrix._23 = 0;	  
		matrix._31 = 0;				matrix._32 = 0;				matrix._33 = 1;

		MatrixMultiply(matrix);
	}


};


#endif
