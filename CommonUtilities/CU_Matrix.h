#pragma once
#ifndef COMMONUTILITIES_MATRIX44_HEADER
#define COMMONUTILITIES_MATRIX44_HEADER

#include <math.h>
#include <algorithm>
//#include <xmmintrin.h>
//#include <intrin.h>

//#pragma intrinsic ( _mm_hadd_ps )





namespace CommonUtilities
{
	template <class TYPE>
	class Vector3;
	template <class TYPE>
	class Matrix44;

	template <class TYPE>
	class Matrix33
	{
	public:
		Matrix33();
		Matrix33(const Matrix33& aMatrix);
		Matrix33(	const TYPE aXX,const TYPE aXY,const TYPE aXZ,
			const TYPE aYX,const TYPE aYY,const TYPE aYZ,
			const TYPE aZX,const TYPE aZY,const TYPE aZZ);
		~Matrix33();

		void Set(	const TYPE aXX,const TYPE aXY,const TYPE aXZ,
			const TYPE aYX,const TYPE aYY,const TYPE aYZ,
			const TYPE aZX,const TYPE aZY,const TYPE aZZ);

		Matrix33<TYPE>& operator*=(const Matrix33& aMatrix);

		Matrix33<TYPE>& operator*=(const TYPE& aType);

		Matrix33<TYPE>& operator=(const Matrix33& aMatirx);
		Matrix33<TYPE>& operator=(Matrix44<TYPE>& aMatrix);
		Matrix33<TYPE> Transpose();


		//todo: these functions are all poorly named, none of these adds a rotation to the current matrix, 
		//the 
		Matrix33<TYPE>& SetRotationX(float aAngle);
		Matrix33<TYPE>& SetRotationY(float aAngle);
		Matrix33<TYPE>& SetRotationZ(float aAngle);

		Matrix33<TYPE>& RotateAroundX(float aAngle);
		Matrix33<TYPE>& RotateAroundY(float aAngle);
		Matrix33<TYPE>& RotateAroundZ(float aAngle);
		static Matrix33<TYPE> RotateAroundXPI(const float aPIAngle);
		static Matrix33<TYPE> RotateAroundYPI(const float aPIAngle);
		static Matrix33<TYPE> RotateAroundZPI(const float aPIAngle);
		Matrix33<TYPE>& SetIdentity();

		Matrix33<TYPE>& Scale(const TYPE& aType);

		static Matrix33<TYPE> RotateX(float aAngle);
		static Matrix33<TYPE> RotateY(float aAngle);
		static Matrix33<TYPE> RotateZ(float aAngle);
		static Matrix33<TYPE> Identity();

		TYPE myMatrix[3][3];
		void SwapPerformanceHax(Matrix33<TYPE>& aMatrix);
	};

	template <class TYPE>
	Matrix33<TYPE>& CommonUtilities::Matrix33<TYPE>::operator=( Matrix44<TYPE>& aMatrix )
	{
		myMatrix[0][0]=aMatrix.myMatrix[0][0];
		myMatrix[0][1]=aMatrix.myMatrix[0][1];
		myMatrix[0][2]=aMatrix.myMatrix[0][2];
		myMatrix[1][0]=aMatrix.myMatrix[1][0];
		myMatrix[1][1]=aMatrix.myMatrix[1][1];
		myMatrix[1][2]=aMatrix.myMatrix[1][2];
		myMatrix[2][0]=aMatrix.myMatrix[2][0];
		myMatrix[2][1]=aMatrix.myMatrix[2][1];
		myMatrix[2][2]=aMatrix.myMatrix[2][2];
		return(*this);
	}
	template <class TYPE>
	Matrix33<TYPE> operator*(const Matrix33<TYPE>& aLeftSideVector,const Matrix33<TYPE>& aRightSideVector)
	{
		Matrix33<TYPE> returnValue(aLeftSideVector);
		returnValue*=aRightSideVector;
		return(returnValue);
	}

	template <class TYPE>
	Matrix33<TYPE> operator*(const Matrix33<TYPE>& aLeftSideVector,const TYPE& aRightSideType)
	{
		Matrix33<TYPE> returnValue(aLeftSideVector);
		returnValue*=aRightSideType;
		return(returnValue);
	}




	template <class TYPE>
	Matrix33<TYPE>::Matrix33()
	{
	}

	template <class TYPE>
	Matrix33<TYPE>::Matrix33(const Matrix33& aMatrix)
	{
		*this = aMatrix;
	}

	template <class TYPE>
	Matrix33<TYPE>::Matrix33(	const TYPE aXX,const TYPE aXY,const TYPE aXZ,
		const TYPE aYX,const TYPE aYY,const TYPE aYZ,
		const TYPE aZX,const TYPE aZY,const TYPE aZZ)
	{
		myMatrix[0][0] = aXX;
		myMatrix[1][0] = aXY;
		myMatrix[2][0] = aXZ;
		myMatrix[0][1] = aYX;
		myMatrix[1][1] = aYY;
		myMatrix[2][1] = aYZ;
		myMatrix[0][2] = aZX;
		myMatrix[1][2] = aZY;
		myMatrix[2][2] = aZZ;
	}

	template <class TYPE>
	Matrix33<TYPE>::~Matrix33()
	{
	}

	template <class TYPE>
	void Matrix33<TYPE>::Set(	const TYPE aXX,const TYPE aXY,const TYPE aXZ,
		const TYPE aYX,const TYPE aYY,const TYPE aYZ,
		const TYPE aZX,const TYPE aZY,const TYPE aZZ)
	{
		myMatrix[0][0] = aXX;
		myMatrix[1][0] = aXY;
		myMatrix[2][0] = aXZ;
		myMatrix[0][1] = aYX;
		myMatrix[1][1] = aYY;
		myMatrix[2][1] = aYZ;
		myMatrix[0][2] = aZX;
		myMatrix[1][2] = aZY;
		myMatrix[2][2] = aZZ;
	}
	/*
	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::operator*=(const Matrix33<TYPE>& aMatrix)
	{
		Matrix33<TYPE> tempMatrix;
		TYPE currentValue = 0;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				for(int k = 0; k < 3; k++)
				{
					currentValue += myMatrix[k][y] * aMatrix.myMatrix[x][k];
				}
				tempMatrix.myMatrix[x][y] = currentValue;
				currentValue = 0;
			}
		}
		*this = tempMatrix;
		return(*this);
	}*/

	template<class TYPE>
	void Matrix33<TYPE>::SwapPerformanceHax(Matrix33<TYPE>& aMatrix)
	{
		for (int i = 0; i < 3; i++) {
			for (int j = i + 1; j < 3; j++) 
			{
				std::swap(aMatrix.myMatrix[i][j], aMatrix.myMatrix[j][i]);
			}
		}
	}

	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::operator*=(const Matrix33<TYPE>& aMatrix)
	{
		//assert (TYPE == float && "not a float matrix... Doom!");
		Matrix33<TYPE> tempMatrix;
		SwapPerformanceHax(const_cast<Matrix33<TYPE>&>(aMatrix));
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				//__m128 currentValue = _mm_setzero_ps();
				TYPE currentValue = 0;
				for(int k = 0; k < 3; k++) 
				{
					//currentValue = _mm_add_ps(currentValue, _mm_mul_ps(_mm_load_ps(&myMatrix[i][0]),_mm_load_ps(&aMatrix.myMatrix[j][0])));
					currentValue += myMatrix[k][i] * aMatrix.myMatrix[k][j];
				}
				//currentValue = _mm_hadd_ps(currentValue, currentValue);
				//currentValue = _mm_hadd_ps(currentValue, currentValue);
				//_mm_store_ss(&tempMatrix.myMatrix[i][j], currentValue);

				tempMatrix.myMatrix[j][i] = currentValue;
			}
		}
		SwapPerformanceHax(const_cast<Matrix33<TYPE>&>(aMatrix));
		*this = tempMatrix;
		return(*this);
	}

	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::operator=(const Matrix33<TYPE>& aMatrix)
	{
		this->myMatrix[0][0] = aMatrix.myMatrix[0][0];
		this->myMatrix[1][0] = aMatrix.myMatrix[1][0];
		this->myMatrix[2][0] = aMatrix.myMatrix[2][0];
		this->myMatrix[0][1] = aMatrix.myMatrix[0][1];
		this->myMatrix[1][1] = aMatrix.myMatrix[1][1];
		this->myMatrix[2][1] = aMatrix.myMatrix[2][1];
		this->myMatrix[0][2] = aMatrix.myMatrix[0][2];
		this->myMatrix[1][2] = aMatrix.myMatrix[1][2];
		this->myMatrix[2][2] = aMatrix.myMatrix[2][2];
		return(*this);
	}

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::Transpose()
	{
		return Matrix33<TYPE>(	myMatrix[0][0],myMatrix[0][1],myMatrix[0][2],
			myMatrix[1][0],myMatrix[1][1],myMatrix[1][2],
			myMatrix[2][0],myMatrix[2][1],myMatrix[2][2]);	
	}

	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::SetRotationX(float aAngle)
	{
		return *this = RotateX(aAngle);
	}

	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::SetRotationY(float aAngle)
	{
		return *this = RotateY(aAngle);
	}

	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::SetRotationZ(float aAngle)
	{
		return *this = RotateZ(aAngle);
	}



	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::RotateAroundX(float aAngle)
	{
		return *this *= RotateX(aAngle);
	}

	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::RotateAroundY(float aAngle)
	{
		return *this *= RotateY(aAngle);
	}

	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::RotateAroundZ(float aAngle)
	{
		return *this *= RotateZ(aAngle);
	}


	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::SetIdentity()
	{
		return *this = Identity();
	}

	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::Scale(const TYPE& aType)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				myMatrix[x][y] *= aType;
			}
		}
		return(*this);
	}

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::RotateX(float aAngle)
	{
		aAngle = (aAngle*2*3.14159265f)/360;
		Matrix33<TYPE> transformationMatrix(1, 0, 0, 
											0, cos(aAngle), sin(aAngle),
											0, -sin(aAngle), cos(aAngle));
		return(transformationMatrix);
	}

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::RotateY(float aAngle)
	{
		aAngle = (aAngle*2*3.14159265f)/360;
		Matrix33<TYPE> transformationMatrix(cos(aAngle), 0, -sin(aAngle), 0, 1, 0, sin(aAngle), 0, cos(aAngle));
		return(transformationMatrix);
	}

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::RotateZ(float aAngle)
	{
		aAngle = (aAngle*2*3.14159265f)/360;
		Matrix33<TYPE> transformationMatrix(cos(aAngle), sin(aAngle), 0, -sin(aAngle), cos(aAngle), 0, 0, 0, 1);
		return(transformationMatrix);
	}

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::RotateAroundXPI(const float aPIAngle)
	{
		Matrix33<TYPE> transformationMatrix(1, 0, 0, 
											0, cos(aPIAngle), sin(aPIAngle),
											0, -sin(aPIAngle), cos(aPIAngle));
		return(transformationMatrix);
		/*
		Matrix33f temp;
		float Sin,Cos;

		Sin=(float)sin(aPIAngle);
		Cos=(float)cos(aPIAngle);

		temp.myMatrix[1][1]=Cos;
		temp.myMatrix[2][1]=Sin;
		temp.myMatrix[2][2]=Cos;
		temp.myMatrix[1][2]=-Sin;


		return(temp);*/
	}

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::RotateAroundYPI(const float aPIAngle)
	{
		Matrix33<TYPE> transformationMatrix(cos(aPIAngle), 0, -sin(aPIAngle), 0, 1, 0, sin(aPIAngle), 0, cos(aPIAngle));
		return(transformationMatrix);
		/*
		Matrix33f temp;
		float Sin,Cos;

		Sin=(float)sin(aPIAngle);
		Cos=(float)cos(aPIAngle);

		temp.myMatrix[0][0]=Cos;
		temp.myMatrix[2][0]=-Sin;
		temp.myMatrix[2][2]=Cos;
		temp.myMatrix[0][2]=Sin;

		return(temp);*/

	}

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::RotateAroundZPI(const float aPIAngle)
	{
		Matrix33<TYPE> temp;
		float Sin,Cos;

		Sin=(float)sin(aPIAngle);
		Cos=(float)cos(aPIAngle);

		temp.myMatrix[0][0]=Cos;
		temp.myMatrix[1][0]=Sin;
		temp.myMatrix[1][1]=Cos;
		temp.myMatrix[0][1]=-Sin;


		return(temp);
	}

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::Identity()
	{
		Matrix33<TYPE> identityMatrix(1, 0, 0, 0, 1, 0, 0, 0, 1);
		return(identityMatrix);
	}

	typedef Matrix33<float> Matrix33f;
	typedef Matrix33<double> Matrix33d;
	typedef Matrix33<int> Matrix33i;

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

		Matrix44<TYPE>& operator*=(const Matrix44<TYPE>& aMatrix);
		//Matrix44<float>& operator*=(const Matrix44<float>& aMatrix);
		Matrix44<TYPE>& operator*=(const Matrix33<TYPE>& aMatrix);

		Matrix44<TYPE>& operator*(const float aValue);



		Matrix44<TYPE>& operator*=(TYPE& aType);


		Matrix44<TYPE>& operator=(const Matrix44<TYPE>& aMatirx);
		Matrix44<TYPE>& operator=(const Matrix33<TYPE>& aMatrix);
		Matrix44<TYPE> Transpose();

		void Inverse(Matrix44<TYPE>& aReturnMatrix);

		//all these rotations are badly named. RotateX should multiply current matrix with a rotation matrix and not return anything,
		//setRotationx should cancel all current rotation and set the rotation to desired value on current matrix
		//RotateAroundX might be better to rename nad make static (to be like RotateX is now)
		Matrix44<TYPE>& SetRotationX(float aAngle);
		Matrix44<TYPE>& SetRotationY(float aAngle);
		Matrix44<TYPE>& SetRotationZ(float aAngle);

		Matrix44<TYPE>& RotateAroundX(float aAngle);
		Matrix44<TYPE>& RotateAroundY(float aAngle);
		Matrix44<TYPE>& RotateAroundZ(float aAngle);

		Matrix44<TYPE>& SetIdentity();

		Matrix44<TYPE>& Scale(TYPE aType);
		void SetScaling(const TYPE& aXScale, const TYPE& aYScale, const TYPE& aZScale);

		Vector3<TYPE> GetScaling();

		static Matrix44<TYPE> RotateX(float aAngle);
		static Matrix44<TYPE> RotateY(float aAngle);
		static Matrix44<TYPE> RotateZ(float aAngle);
		static Matrix44<TYPE> Identity();
		static Matrix44<TYPE> Convert(float *SomeFloats);

		Matrix33<TYPE> GetMatrix33() const;

		Vector3<TYPE> GetPosition() const;
		void SetPosition(const Vector3<TYPE>& aPosition);
		void Translate(const Vector3<TYPE>& aPosition);
		

		TYPE myMatrix[4][4];
	private:
		void SwapPerformanceHax(Matrix44<TYPE>& aMatrix);

	};

	template <class TYPE>
	Matrix44<TYPE>& CommonUtilities::Matrix44<TYPE>::operator*( const float aValue )
	{
		myMatrix[0][0] *= aValue;
		myMatrix[0][1] *= aValue;
		myMatrix[0][2] *= aValue;
		myMatrix[0][3] *= aValue;

		myMatrix[1][0] *= aValue;
		myMatrix[1][1] *= aValue;
		myMatrix[1][2] *= aValue;
		myMatrix[1][3] *= aValue;

		myMatrix[2][0] *= aValue;
		myMatrix[2][1] *= aValue;
		myMatrix[2][2] *= aValue;
		myMatrix[2][3] *= aValue;

		myMatrix[3][0] *= aValue;
		myMatrix[3][1] *= aValue;
		myMatrix[3][2] *= aValue;
		myMatrix[3][3] *= aValue;

	}

	template <class TYPE>
	void CommonUtilities::Matrix44<TYPE>::Translate(const Vector3<TYPE>& aPosition)
	{
		//translation is just setting the position in the world
		SetPosition(aPosition);
	}

	template <class TYPE>
	void CommonUtilities::Matrix44<TYPE>::SetPosition( const Vector3<TYPE>& aPosition ) 
	{
		myMatrix[3][0] = aPosition.x;
		myMatrix[3][1] = aPosition.y;
		myMatrix[3][2] = aPosition.z;
	}
	template <class TYPE>
	Vector3<TYPE> CommonUtilities::Matrix44<TYPE>::GetPosition() const
	{
		return Vector3<TYPE>(myMatrix[3][0],myMatrix[3][1],myMatrix[3][2]);
	}
	template <class TYPE>
	Matrix44<TYPE> operator*(const Matrix44<TYPE>& aLeftSideMatrix,Matrix44<TYPE>& aRightSideMatrix)
	{
		Matrix44<TYPE> returnValue(aLeftSideMatrix);
		returnValue*=aRightSideMatrix;
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
	Matrix44<TYPE> Matrix44<TYPE>::Convert(float *someFloats)
	{
		Matrix44<TYPE> convertMatrix(
			someFloats[0], someFloats[4], someFloats[8], someFloats[12],
			someFloats[1], someFloats[5], someFloats[9], someFloats[13],
			someFloats[2], someFloats[6], someFloats[10], someFloats[14],
			someFloats[3], someFloats[7], someFloats[11], someFloats[15]);
		return(convertMatrix);
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
		tempMatrix = tempMatrix.Identity();
		TYPE currentValue = 0;
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				for(int k = 0; k < 4; k++)
				{
					currentValue += myMatrix[x][k] * aMatrix.myMatrix[k][y];
				}
				tempMatrix.myMatrix[x][y] = currentValue;
				currentValue = 0;
			}
		}
		*this = tempMatrix;
		return(*this);
	}

	template<class TYPE>
	void Matrix44<TYPE>::SwapPerformanceHax(Matrix44<TYPE>& aMatrix)
	{
		for (int i = 0; i < 4; i++) {
			for (int j = i + 1; j < 4; j++) 
			{
				std::swap(aMatrix.myMatrix[i][j], aMatrix.myMatrix[j][i]);
			}
		}
	}

	//template <class TYPE>
	//Matrix44<TYPE>& Matrix44<TYPE>::operator*=(const Matrix44<TYPE>& aMatrix)
	//{
	//	//assert (TYPE == float && "not a float matrix... Doom!");
	//	Matrix44<TYPE> tempMatrix;
	//	SwapPerformanceHax(const_cast<Matrix44<TYPE>&>(aMatrix));
	//	for (int i = 0; i < 4; i++)
	//	{
	//		for (int j = 0; j < 4; j++)
	//		{
	//			//__m128 currentValue = _mm_setzero_ps();
	//			float currentValue = 0.0f;
	//			for(int k = 0; k < 4; k++) 
	//			{
	//				//currentValue = _mm_add_ps(currentValue, _mm_mul_ps(_mm_load_ps(&myMatrix[i][0]),_mm_load_ps(&aMatrix.myMatrix[j][0])));
	//				currentValue += myMatrix[i][k] * aMatrix.myMatrix[j][k];
	//			}
	//			//currentValue = _mm_hadd_ps(currentValue, currentValue);
	//			//currentValue = _mm_hadd_ps(currentValue, currentValue);
	//			//_mm_store_ss(&tempMatrix.myMatrix[i][j], currentValue);

	//			tempMatrix.myMatrix[i][j] = currentValue;
	//		}
	//	}
	//	SwapPerformanceHax(const_cast<Matrix44<TYPE>&>(aMatrix));
	//	*this = tempMatrix;
	//	return(*this);
	//}
	


	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::operator*=(const Matrix33<TYPE>& aMatrix)
	{
		Matrix33<TYPE> tempMatrix = this->GetMatrix33();

		tempMatrix *= aMatrix;

		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				this->myMatrix[i][j] = tempMatrix.myMatrix[i][j];
			}
		}
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
	Matrix44<TYPE>& Matrix44<TYPE>::operator=(const Matrix33<TYPE>& aMatrix)
	{
		this->myMatrix[0][0] = aMatrix.myMatrix[0][0];
		this->myMatrix[1][0] = aMatrix.myMatrix[1][0];
		this->myMatrix[2][0] = aMatrix.myMatrix[2][0];

		this->myMatrix[0][1] = aMatrix.myMatrix[0][1];
		this->myMatrix[1][1] = aMatrix.myMatrix[1][1];
		this->myMatrix[2][1] = aMatrix.myMatrix[2][1];

		this->myMatrix[0][2] = aMatrix.myMatrix[0][2];
		this->myMatrix[1][2] = aMatrix.myMatrix[1][2];
		this->myMatrix[2][2] = aMatrix.myMatrix[2][2];

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
	void Matrix44<TYPE>::Inverse(Matrix44<TYPE> &aReturnMatrix)
	{

		aReturnMatrix = this->GetMatrix33().Transpose();

		Vector3<TYPE> tempVec(-myMatrix[3][0], -myMatrix[3][1], -myMatrix[3][2]);


		Vector3<TYPE> tempVec2 = tempVec;

		tempVec.x=tempVec2.myX*aReturnMatrix.myMatrix[0][0]+tempVec2.myY*aReturnMatrix.myMatrix[1][0]+tempVec2.myZ*aReturnMatrix.myMatrix[2][0];
		tempVec.y=tempVec2.myX*aReturnMatrix.myMatrix[0][1]+tempVec2.myY*aReturnMatrix.myMatrix[1][1]+tempVec2.myZ*aReturnMatrix.myMatrix[2][1];
		tempVec.z=tempVec2.myX*aReturnMatrix.myMatrix[0][2]+tempVec2.myY*aReturnMatrix.myMatrix[1][2]+tempVec2.myZ*aReturnMatrix.myMatrix[2][2];

		aReturnMatrix.myMatrix[3][0] = tempVec.myX;
		aReturnMatrix.myMatrix[3][1] = tempVec.myY;
		aReturnMatrix.myMatrix[3][2] = tempVec.myZ;

	}


	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::SetRotationX(float aAngle)
	{
		return *this = Matrix33<TYPE>::RotateX(aAngle);
	}

	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::SetRotationY(float aAngle)
	{
		return *this = Matrix33<TYPE>::RotateY(aAngle);
	}

	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::SetRotationZ(float aAngle)
	{
		return *this = Matrix33<TYPE>::RotateZ(aAngle);
	}

	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::RotateAroundX(float aAngle)
	{
		return *this *= RotateX(aAngle);
	}

	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::RotateAroundY(float aAngle)
	{
		return *this *= RotateY(aAngle);
	}

	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::RotateAroundZ(float aAngle)
	{
		return *this *= RotateZ(aAngle);
	}

	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::SetIdentity()
	{
		return *this = Identity();
	}

	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::Scale(TYPE aType)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				myMatrix[x][y] *= aType;
			}
		}
		return(*this);
	}

	template <typename TYPE>
	void Matrix44<TYPE>::SetScaling(const TYPE& aXScale, const TYPE& aYScale, const TYPE& aZScale)
	{
		myMatrix[0][0] = aXScale;
		myMatrix[1][1] = aYScale;
		myMatrix[2][2] = aZScale;
	}

	template <typename TYPE>
	Vector3<TYPE> Matrix44<TYPE>::GetScaling()
	{
		return(Vector3<TYPE>(myMatrix[0][0], myMatrix[1][1], myMatrix[2][2]));
	}

	template <class TYPE>
	Matrix44<TYPE> Matrix44<TYPE>::RotateX(float aAngle)
	{
		aAngle = (aAngle*2*3.14159265f)/360;
		Matrix44<float> transformationMatrix;

		transformationMatrix.SetIdentity();
		transformationMatrix.myMatrix[1][1] = cos(aAngle);
		transformationMatrix.myMatrix[1][2] = -sin(aAngle);
		transformationMatrix.myMatrix[2][1] = sin(aAngle);
		transformationMatrix.myMatrix[2][2] = cos(aAngle);


		return(transformationMatrix);
	}

	template <class TYPE>
	Matrix44<TYPE> Matrix44<TYPE>::RotateY(float aAngle)
	{
		aAngle = (aAngle*2.0f*3.141f)/360.0f;
		Matrix44<TYPE> transformationMatrix;
		transformationMatrix.SetIdentity();
		transformationMatrix.myMatrix[0][0] = cos(aAngle);
		transformationMatrix.myMatrix[0][2] = sin(aAngle);
		transformationMatrix.myMatrix[2][0] = -sin(aAngle);
		transformationMatrix.myMatrix[2][2] = cos(aAngle);


		return(transformationMatrix);
	}

	template <class TYPE>
	Matrix44<TYPE> Matrix44<TYPE>::RotateZ(float aAngle)
	{
		aAngle = (aAngle*2*3.14159265f)/360;
		Matrix44<TYPE> transformationMatrix;

		transformationMatrix.SetIdentity();

		transformationMatrix.myMatrix[0][0] = cos(aAngle);
		transformationMatrix.myMatrix[0][1] = -sin(aAngle);
		transformationMatrix.myMatrix[1][0] = sin(aAngle);
		transformationMatrix.myMatrix[1][1] = cos(aAngle);

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

	template <class TYPE>
	Matrix33<TYPE> Matrix44<TYPE>::GetMatrix33() const
	{
		Matrix33<TYPE> aResultMatrix;

		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				aResultMatrix.myMatrix[i][j] = this->myMatrix[i][j];
			}
		}
		return(aResultMatrix);
	}


	typedef Matrix44<float> Matrix44f;
	typedef Matrix44<double> Matrix44d;
	typedef Matrix44<int> Matrix44i;
};
namespace CU = CommonUtilities;

#endif
