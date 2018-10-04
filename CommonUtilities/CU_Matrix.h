#ifndef I3M_MATRIX_HEADER
#define I3M_MATRIX_HEADER

#include <string.h>

// the standard myMatrix class to handle all myMatrix operations

namespace CommonUtilities
{
	template <class TYPE>
	class Matrix44;

	template <class TYPE>
	class Matrix33
	{
	public:
		Matrix33() 
		{
			myMatrix[0][0]=1;
			myMatrix[1][0]=0;
			myMatrix[2][0]=0;
			myMatrix[0][1]=0;
			myMatrix[1][1]=1;
			myMatrix[2][1]=0;
			myMatrix[0][2]=0;
			myMatrix[1][2]=0;
			myMatrix[2][2]=1;
		};

		Matrix33(	const TYPE aXX,const TYPE aXY,const TYPE aXZ,
					const TYPE aYX,const TYPE aYY,const TYPE aYZ,
					const TYPE aZX,const TYPE aZY,const TYPE aZZ);

		~Matrix33() 
		{
		};

		Matrix33 operator~() const;			// take the  inverse of the matrice

		Matrix33 operator*(const Matrix33& aMatrix);		// matrice multiplikation
		Matrix33 operator+(const Matrix33& aMatrix);		// matrice addition
		Matrix33 operator-(const Matrix33& aMatrix);		// matrice subtraction
		Matrix33& operator*=(const Matrix33& aMatrix);	// matrice multiplikation
		Matrix33& operator+=(const Matrix33& aMatrix);	// matrice addition
		Matrix33& operator-=(const Matrix33& aMatrix);	// matrice subtraction

		Matrix33& operator=(Matrix44<TYPE>& aMatrix) ;


		static Matrix33 RotateAroundXPI(const float aPIAngle);
		static Matrix33 RotateAroundYPI(const float aPIAngle);
		static Matrix33 RotateAroundZPI(const float aPIAngle);

		static Matrix33 Identity();
		void SetIdentity();
		Matrix33 Inverse() const;

		TYPE myMatrix[3][3]; 
	};

	template <class TYPE>
	void Matrix33<TYPE>::SetIdentity()
	{
		myMatrix[0][0]=1;
		myMatrix[1][0]=0;
		myMatrix[2][0]=0;
		myMatrix[0][1]=0;
		myMatrix[1][1]=1;
		myMatrix[2][1]=0;
		myMatrix[0][2]=0;
		myMatrix[1][2]=0;
		myMatrix[2][2]=1;
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
	Matrix33<TYPE> Matrix33<TYPE>::operator~() const			// take the  inverse of the matrice
	{
	  return Matrix33(myMatrix[0][0] , myMatrix[0][1], myMatrix[0][2],  
						 myMatrix[1][0] , myMatrix[1][1], myMatrix[1][2],
						 myMatrix[2][0] , myMatrix[2][1], myMatrix[2][2]);  
	}

	template <class TYPE>	
	Matrix33<TYPE>& Matrix33<TYPE>::operator=(Matrix44<TYPE>& aMatrix) 
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
	Matrix33<TYPE> Matrix33<TYPE>::operator*(const Matrix33& aMatrix)	// matrice multiplikation
	{
	  return Matrix33
		  (myMatrix[0][0]*aMatrix.myMatrix[0][0]+myMatrix[1][0]*aMatrix.myMatrix[0][1]+myMatrix[2][0]*aMatrix.myMatrix[0][2],
		   myMatrix[0][0]*aMatrix.myMatrix[1][0]+myMatrix[1][0]*aMatrix.myMatrix[1][1]+myMatrix[2][0]*aMatrix.myMatrix[1][2],
		   myMatrix[0][0]*aMatrix.myMatrix[2][0]+myMatrix[1][0]*aMatrix.myMatrix[2][1]+myMatrix[2][0]*aMatrix.myMatrix[2][2],
		   myMatrix[0][1]*aMatrix.myMatrix[0][0]+myMatrix[1][1]*aMatrix.myMatrix[0][1]+myMatrix[2][1]*aMatrix.myMatrix[0][2],
		   myMatrix[0][1]*aMatrix.myMatrix[1][0]+myMatrix[1][1]*aMatrix.myMatrix[1][1]+myMatrix[2][1]*aMatrix.myMatrix[1][2],
		   myMatrix[0][1]*aMatrix.myMatrix[2][0]+myMatrix[1][1]*aMatrix.myMatrix[2][1]+myMatrix[2][1]*aMatrix.myMatrix[2][2],
		   myMatrix[0][2]*aMatrix.myMatrix[0][0]+myMatrix[1][2]*aMatrix.myMatrix[0][1]+myMatrix[2][2]*aMatrix.myMatrix[0][2],
		   myMatrix[0][2]*aMatrix.myMatrix[1][0]+myMatrix[1][2]*aMatrix.myMatrix[1][1]+myMatrix[2][2]*aMatrix.myMatrix[1][2],
		   myMatrix[0][2]*aMatrix.myMatrix[2][0]+myMatrix[1][2]*aMatrix.myMatrix[2][1]+myMatrix[2][2]*aMatrix.myMatrix[2][2]);
	}

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::operator-(const Matrix33& aMatrix)	// matrice subtraction
	{
		return Matrix33(
						 myMatrix[0][0] - aMatrix.myMatrix[0][0] , myMatrix[1][0] - aMatrix.myMatrix[1][0]
						,myMatrix[2][0] - aMatrix.myMatrix[2][0] , myMatrix[0][1] - aMatrix.myMatrix[0][1]  
						,myMatrix[1][1] - aMatrix.myMatrix[1][1] , myMatrix[2][1] - aMatrix.myMatrix[2][1] 
						,myMatrix[0][2] - aMatrix.myMatrix[0][2] , myMatrix[1][2] - aMatrix.myMatrix[1][2] 
						,myMatrix[2][2] - aMatrix.myMatrix[2][2] );  

	}


	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::operator+(const Matrix33& aMatrix)	// matrice addition
	{
		return Matrix33(
						 myMatrix[0][0] + aMatrix.myMatrix[0][0] , myMatrix[1][0] + aMatrix.myMatrix[1][0]
						,myMatrix[2][0] + aMatrix.myMatrix[2][0] , myMatrix[0][1] + aMatrix.myMatrix[0][1]  
						,myMatrix[1][1] + aMatrix.myMatrix[1][1] , myMatrix[2][1] + aMatrix.myMatrix[2][1] 
						,myMatrix[0][2] + aMatrix.myMatrix[0][2] , myMatrix[1][2] + aMatrix.myMatrix[1][2] 
						,myMatrix[2][2] + aMatrix.myMatrix[2][2] );  

	}


	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::operator*=(const Matrix33& aMatrix)	// matrice multiplikation
	{
		Matrix33 temp;
	
	
		temp.myMatrix[0][0]=myMatrix[0][0]*aMatrix.myMatrix[0][0]+myMatrix[0][1]*aMatrix.myMatrix[1][0]+myMatrix[0][2]*aMatrix.myMatrix[2][0];
		temp.myMatrix[0][1]=myMatrix[0][0]*aMatrix.myMatrix[0][1]+myMatrix[0][1]*aMatrix.myMatrix[1][1]+myMatrix[0][2]*aMatrix.myMatrix[2][1];
		temp.myMatrix[0][2]=myMatrix[0][0]*aMatrix.myMatrix[0][2]+myMatrix[0][1]*aMatrix.myMatrix[1][2]+myMatrix[0][2]*aMatrix.myMatrix[2][2];

		temp.myMatrix[1][0]=myMatrix[1][0]*aMatrix.myMatrix[0][0]+myMatrix[1][1]*aMatrix.myMatrix[1][0]+myMatrix[1][2]*aMatrix.myMatrix[2][0];
		temp.myMatrix[1][1]=myMatrix[1][0]*aMatrix.myMatrix[0][1]+myMatrix[1][1]*aMatrix.myMatrix[1][1]+myMatrix[1][2]*aMatrix.myMatrix[2][1];
		temp.myMatrix[1][2]=myMatrix[1][0]*aMatrix.myMatrix[0][2]+myMatrix[1][1]*aMatrix.myMatrix[1][2]+myMatrix[1][2]*aMatrix.myMatrix[2][2];

		temp.myMatrix[2][0]=myMatrix[2][0]*aMatrix.myMatrix[0][0]+myMatrix[2][1]*aMatrix.myMatrix[1][0]+myMatrix[2][2]*aMatrix.myMatrix[2][0];
		temp.myMatrix[2][1]=myMatrix[2][0]*aMatrix.myMatrix[0][1]+myMatrix[2][1]*aMatrix.myMatrix[1][1]+myMatrix[2][2]*aMatrix.myMatrix[2][1];
		temp.myMatrix[2][2]=myMatrix[2][0]*aMatrix.myMatrix[0][2]+myMatrix[2][1]*aMatrix.myMatrix[1][2]+myMatrix[2][2]*aMatrix.myMatrix[2][2];

		memcpy(myMatrix,temp.myMatrix,sizeof(Matrix33<TYPE>));

		
	
		return *this;
	}

	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::operator+=(const Matrix33& aMatrix)	// matrice addition
	{
		myMatrix[0][0]+=aMatrix.myMatrix[0][0];
		myMatrix[1][0]+=aMatrix.myMatrix[1][0];
		myMatrix[2][0]+=aMatrix.myMatrix[2][0];
		myMatrix[0][1]+=aMatrix.myMatrix[0][1];
		myMatrix[1][1]+=aMatrix.myMatrix[1][1];
		myMatrix[2][1]+=aMatrix.myMatrix[2][1];
		myMatrix[0][2]+=aMatrix.myMatrix[0][2];
		myMatrix[1][2]+=aMatrix.myMatrix[1][2];
		myMatrix[2][2]+=aMatrix.myMatrix[2][2];

		return *this;

	}

	template <class TYPE>
	Matrix33<TYPE>& Matrix33<TYPE>::operator-=(const Matrix33& aMatrix)	// matrice subtraction
	{
		myMatrix[0][0]-=aMatrix.myMatrix[0][0];
		myMatrix[1][0]-=aMatrix.myMatrix[1][0];
		myMatrix[2][0]-=aMatrix.myMatrix[2][0];
		myMatrix[0][1]-=aMatrix.myMatrix[0][1];
		myMatrix[1][1]-=aMatrix.myMatrix[1][1];
		myMatrix[2][1]-=aMatrix.myMatrix[2][1];
		myMatrix[0][2]-=aMatrix.myMatrix[0][2];
		myMatrix[1][2]-=aMatrix.myMatrix[1][2];
		myMatrix[2][2]-=aMatrix.myMatrix[2][2];
		
		return *this;
	}

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::RotateAroundXPI(const float aPIAngle)
	{
		Matrix33 temp;
		float Sin,Cos;

		Sin=(float)sin(aPIAngle);
		Cos=(float)cos(aPIAngle);
		
		temp.myMatrix[1][1]=Cos;
		temp.myMatrix[2][1]=Sin;
		temp.myMatrix[2][2]=Cos;
		temp.myMatrix[1][2]=-Sin;


		return(temp);
	}

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::RotateAroundYPI(const float aPIAngle)
	{
		Matrix33 temp;
		float Sin,Cos;

		Sin=(float)sin(aPIAngle);
		Cos=(float)cos(aPIAngle);

		temp.myMatrix[0][0]=Cos;
		temp.myMatrix[2][0]=-Sin;
		temp.myMatrix[2][2]=Cos;
		temp.myMatrix[0][2]=Sin;

		return(temp);

	}

	template <class TYPE>
	Matrix33<TYPE> Matrix33<TYPE>::RotateAroundZPI(const float aPIAngle)
	{
		Matrix33 temp;
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
		Matrix33 temp;
		return(temp);
	}


	template <class TYPE>
	class Matrix44
	{
	public:
		Matrix44(TYPE* aMatrix) 
		{
			myMatrix[0][0]=aMatrix[0];
			myMatrix[1][0]=aMatrix[1];
			myMatrix[2][0]=aMatrix[2];
			myMatrix[3][0]=aMatrix[3];
			myMatrix[0][1]=aMatrix[4];
			myMatrix[1][1]=aMatrix[5];
			myMatrix[2][1]=aMatrix[6];
			myMatrix[3][1]=aMatrix[7];
			myMatrix[0][2]=aMatrix[8];
			myMatrix[1][2]=aMatrix[9];
			myMatrix[2][2]=aMatrix[10];
			myMatrix[3][2]=aMatrix[11];
			myMatrix[0][3]=aMatrix[12];
			myMatrix[1][3]=aMatrix[13];
			myMatrix[2][3]=aMatrix[14];
			myMatrix[3][3]=aMatrix[15];
		}


		void ConvertD3D(TYPE* aMatrix) 
		{
			myMatrix[0][0]=aMatrix[0];
			myMatrix[0][1]=aMatrix[1];
			myMatrix[0][2]=aMatrix[2];
			myMatrix[0][3]=aMatrix[3];
			myMatrix[1][0]=aMatrix[4];
			myMatrix[1][1]=aMatrix[5];
			myMatrix[1][2]=aMatrix[6];
			myMatrix[1][3]=aMatrix[7];
			myMatrix[2][0]=aMatrix[8];
			myMatrix[2][1]=aMatrix[9];
			myMatrix[2][2]=aMatrix[10];
			myMatrix[2][3]=aMatrix[11];
			myMatrix[3][0]=aMatrix[12];
			myMatrix[3][1]=aMatrix[13];
			myMatrix[3][2]=aMatrix[14];
			myMatrix[3][3]=aMatrix[15];
		}


		Matrix44(float m1,float m2,float m3,float m4,float m5,float m6,float m7,float m8,float m9,float m10,float m11,float m12,float m13,float m14,float m15,float m16) 
		{
			myMatrix[0][0]=m1;
			myMatrix[1][0]=m2;
			myMatrix[2][0]=m3;
			myMatrix[3][0]=m4;
			myMatrix[0][1]=m5;
			myMatrix[1][1]=m6;
			myMatrix[2][1]=m7;
			myMatrix[3][1]=m8;
			myMatrix[0][2]=m9;
			myMatrix[1][2]=m10;
			myMatrix[2][2]=m11;
			myMatrix[3][2]=m12;
			myMatrix[0][3]=m13;
			myMatrix[1][3]=m14;
			myMatrix[2][3]=m15;
			myMatrix[3][3]=m16;
		}

		Matrix44() 
		{
			myMatrix[0][0]=1;
			myMatrix[1][0]=0;
			myMatrix[2][0]=0;
			myMatrix[3][0]=0;
			myMatrix[0][1]=0;
			myMatrix[1][1]=1;
			myMatrix[2][1]=0;
			myMatrix[3][1]=0;
			myMatrix[0][2]=0;
			myMatrix[1][2]=0;
			myMatrix[2][2]=1;
			myMatrix[3][2]=0;
			myMatrix[0][3]=0;
			myMatrix[1][3]=0;
			myMatrix[2][3]=0;
			myMatrix[3][3]=1;
		};

		~Matrix44() 
		{
		};

		Matrix44 operator~() const;			// take the  inverse of the matrice
		Matrix44 EpicInverse() const;

		Matrix44 operator*(const Matrix44& aSecondMatrix) const;		// matrice multiplikation
		Matrix44& operator*=(const Matrix44& aMatrix);	// matrice multiplikation

		Matrix44 operator*(const Matrix33<TYPE>& aMatrix);		// matrice multiplikation
		Matrix44& operator*=(const Matrix33<TYPE>& aMatrix);	// matrice multiplikation

		Matrix44<TYPE>& operator=(const Matrix33<TYPE>& aMatirx);


		static Matrix44 RotateAroundXPI(const float aPIAngle);
		static Matrix44 RotateAroundYPI(const float aPIAngle);
		static Matrix44 RotateAroundZPI(const float aPIAngle);

		static Matrix44 Identity();
		void SetIdentity();
		Matrix33<TYPE> GetMatrix33() const;

		TYPE myMatrix[4][4]; 
	};


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




	template <class TYPE>
	void Matrix44<TYPE>::SetIdentity()
	{
			myMatrix[0][0]=1;
			myMatrix[1][0]=0;
			myMatrix[2][0]=0;
			myMatrix[3][0]=0;
			myMatrix[0][1]=0;
			myMatrix[1][1]=1;
			myMatrix[2][1]=0;
			myMatrix[3][1]=0;
			myMatrix[0][2]=0;
			myMatrix[1][2]=0;
			myMatrix[2][2]=1;
			myMatrix[3][2]=0;
			myMatrix[0][3]=0;
			myMatrix[1][3]=0;
			myMatrix[2][3]=0;
			myMatrix[3][3]=1;
	}


	template <class TYPE>
	Matrix44<TYPE> Matrix44<TYPE>::operator~() const			// take the  inverse of the matrice
	{
	  return Matrix44(myMatrix[0][0] , myMatrix[0][1], myMatrix[0][2],  myMatrix[0][3],
						 myMatrix[1][0] , myMatrix[1][1], myMatrix[1][2] ,myMatrix[1][3],
						 myMatrix[2][0] , myMatrix[2][1], myMatrix[2][2] ,myMatrix[2][3],
						 myMatrix[3][0] , myMatrix[3][1], myMatrix[3][2] ,myMatrix[3][3]);  
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
	Matrix44<TYPE> Matrix44<TYPE>::EpicInverse() const
	{
		/*
		Matrix44<TYPE> returnMatrix;
		returnMatrix.SetIdentity();
		Matrix33<TYPE> tempMatrix;
		
		tempMatrix = this->~GetMatrix33();

		TYPE tempX =  -myMatrix[3][0];
		TYPE tempY =  -myMatrix[3][1];
		TYPE tempZ =  -myMatrix[3][2];

		returnMatrix.myMatrix[3][0] = tempX * tempMatrix.myMatrix[0][0] + tempY * tempMatrix.myMatrix[1][0] + tempZ * tempMatrix.myMatrix[2][0];
		returnMatrix.myMatrix[3][1] = tempX * tempMatrix.myMatrix[1][0] + tempY * tempMatrix.myMatrix[1][1] + tempZ * tempMatrix.myMatrix[2][1];
		returnMatrix.myMatrix[3][2] = tempX * tempMatrix.myMatrix[2][0] + tempY * tempMatrix.myMatrix[1][2] + tempZ * tempMatrix.myMatrix[2][2];

		returnMatrix.myMatrix[0][0]= tempMatrix.myMatrix[0][0];
		returnMatrix.myMatrix[0][1]= tempMatrix.myMatrix[0][1];
		returnMatrix.myMatrix[0][2]= tempMatrix.myMatrix[0][2];
		returnMatrix.myMatrix[1][0]= tempMatrix.myMatrix[1][0];
		returnMatrix.myMatrix[1][1]= tempMatrix.myMatrix[1][1];
		returnMatrix.myMatrix[1][2]= tempMatrix.myMatrix[1][2];
		returnMatrix.myMatrix[2][0]= tempMatrix.myMatrix[2][0];
		returnMatrix.myMatrix[2][1]= tempMatrix.myMatrix[2][1];
		returnMatrix.myMatrix[2][2]= tempMatrix.myMatrix[2][2];

		return returnMatrix;
		*/
		TYPE tempX = -myMatrix[3][0];
		TYPE tempY = -myMatrix[3][1];
		TYPE tempZ = -myMatrix[3][2];

		Matrix44<TYPE> returnMatrix;
		returnMatrix.SetIdentity();

		returnMatrix.myMatrix[3][0]=tempX*myMatrix[0][0]+tempY*myMatrix[0][1]+tempZ*myMatrix[0][2];
		returnMatrix.myMatrix[3][1]=tempX*myMatrix[1][0]+tempY*myMatrix[1][1]+tempZ*myMatrix[1][2];
		returnMatrix.myMatrix[3][2]=tempX*myMatrix[2][0]+tempY*myMatrix[2][1]+tempZ*myMatrix[2][2];

		returnMatrix = ~GetMatrix33();

		return returnMatrix;
	}

	template <class TYPE>
	Matrix44<TYPE> Matrix44<TYPE>::operator*(const Matrix44& aSecondMatrix) const	// matrice multiplikation
	{
		Matrix44 temp;

		return(Matrix44(
		myMatrix[0][0]*aSecondMatrix.myMatrix[0][0]+myMatrix[0][1]*aSecondMatrix.myMatrix[1][0]+myMatrix[0][2]*aSecondMatrix.myMatrix[2][0]+myMatrix[0][3]*aSecondMatrix.myMatrix[3][0],
		myMatrix[1][0]*aSecondMatrix.myMatrix[0][0]+myMatrix[1][1]*aSecondMatrix.myMatrix[1][0]+myMatrix[1][2]*aSecondMatrix.myMatrix[2][0]+myMatrix[1][3]*aSecondMatrix.myMatrix[3][0],
		myMatrix[2][0]*aSecondMatrix.myMatrix[0][0]+myMatrix[2][1]*aSecondMatrix.myMatrix[1][0]+myMatrix[2][2]*aSecondMatrix.myMatrix[2][0]+myMatrix[2][3]*aSecondMatrix.myMatrix[3][0],
		myMatrix[3][0]*aSecondMatrix.myMatrix[0][0]+myMatrix[3][1]*aSecondMatrix.myMatrix[1][0]+myMatrix[3][2]*aSecondMatrix.myMatrix[2][0]+myMatrix[3][3]*aSecondMatrix.myMatrix[3][0],

		myMatrix[0][0]*aSecondMatrix.myMatrix[0][1]+myMatrix[0][1]*aSecondMatrix.myMatrix[1][1]+myMatrix[0][2]*aSecondMatrix.myMatrix[2][1]+myMatrix[0][3]*aSecondMatrix.myMatrix[3][1],
		myMatrix[1][0]*aSecondMatrix.myMatrix[0][1]+myMatrix[1][1]*aSecondMatrix.myMatrix[1][1]+myMatrix[1][2]*aSecondMatrix.myMatrix[2][1]+myMatrix[1][3]*aSecondMatrix.myMatrix[3][1],
		myMatrix[2][0]*aSecondMatrix.myMatrix[0][1]+myMatrix[2][1]*aSecondMatrix.myMatrix[1][1]+myMatrix[2][2]*aSecondMatrix.myMatrix[2][1]+myMatrix[2][3]*aSecondMatrix.myMatrix[3][1],
		myMatrix[3][0]*aSecondMatrix.myMatrix[0][1]+myMatrix[3][1]*aSecondMatrix.myMatrix[1][1]+myMatrix[3][2]*aSecondMatrix.myMatrix[2][1]+myMatrix[3][3]*aSecondMatrix.myMatrix[3][1],

		myMatrix[0][0]*aSecondMatrix.myMatrix[0][2]+myMatrix[0][1]*aSecondMatrix.myMatrix[1][2]+myMatrix[0][2]*aSecondMatrix.myMatrix[2][2]+myMatrix[0][3]*aSecondMatrix.myMatrix[3][2],
		myMatrix[1][0]*aSecondMatrix.myMatrix[0][2]+myMatrix[1][1]*aSecondMatrix.myMatrix[1][2]+myMatrix[1][2]*aSecondMatrix.myMatrix[2][2]+myMatrix[1][3]*aSecondMatrix.myMatrix[3][2],
		myMatrix[2][0]*aSecondMatrix.myMatrix[0][2]+myMatrix[2][1]*aSecondMatrix.myMatrix[1][2]+myMatrix[2][2]*aSecondMatrix.myMatrix[2][2]+myMatrix[2][3]*aSecondMatrix.myMatrix[3][2],
		myMatrix[3][0]*aSecondMatrix.myMatrix[0][2]+myMatrix[3][1]*aSecondMatrix.myMatrix[1][2]+myMatrix[3][2]*aSecondMatrix.myMatrix[2][2]+myMatrix[3][3]*aSecondMatrix.myMatrix[3][2],

		myMatrix[0][0]*aSecondMatrix.myMatrix[0][3]+myMatrix[0][1]*aSecondMatrix.myMatrix[1][3]+myMatrix[0][2]*aSecondMatrix.myMatrix[2][3]+myMatrix[0][3]*aSecondMatrix.myMatrix[3][3],
		myMatrix[1][0]*aSecondMatrix.myMatrix[0][3]+myMatrix[1][1]*aSecondMatrix.myMatrix[1][3]+myMatrix[1][2]*aSecondMatrix.myMatrix[2][3]+myMatrix[1][3]*aSecondMatrix.myMatrix[3][3],
		myMatrix[2][0]*aSecondMatrix.myMatrix[0][3]+myMatrix[2][1]*aSecondMatrix.myMatrix[1][3]+myMatrix[2][2]*aSecondMatrix.myMatrix[2][3]+myMatrix[2][3]*aSecondMatrix.myMatrix[3][3],
		myMatrix[3][0]*aSecondMatrix.myMatrix[0][3]+myMatrix[3][1]*aSecondMatrix.myMatrix[1][3]+myMatrix[3][2]*aSecondMatrix.myMatrix[2][3]+myMatrix[3][3]*aSecondMatrix.myMatrix[3][3]));
	}


	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::operator*=(const Matrix44& aMatrix)	// matrice multiplikation
	{
		Matrix44 temp;

		temp.myMatrix[0][0]=myMatrix[0][0]*aMatrix.myMatrix[0][0]+myMatrix[0][1]*aMatrix.myMatrix[1][0]+myMatrix[0][2]*aMatrix.myMatrix[2][0]+myMatrix[0][3]*aMatrix.myMatrix[3][0];
		temp.myMatrix[0][1]=myMatrix[0][0]*aMatrix.myMatrix[0][1]+myMatrix[0][1]*aMatrix.myMatrix[1][1]+myMatrix[0][2]*aMatrix.myMatrix[2][1]+myMatrix[0][3]*aMatrix.myMatrix[3][1];
		temp.myMatrix[0][2]=myMatrix[0][0]*aMatrix.myMatrix[0][2]+myMatrix[0][1]*aMatrix.myMatrix[1][2]+myMatrix[0][2]*aMatrix.myMatrix[2][2]+myMatrix[0][3]*aMatrix.myMatrix[3][2];
		temp.myMatrix[0][3]=myMatrix[0][0]*aMatrix.myMatrix[0][3]+myMatrix[0][1]*aMatrix.myMatrix[1][3]+myMatrix[0][2]*aMatrix.myMatrix[2][3]+myMatrix[0][3]*aMatrix.myMatrix[3][3];

		temp.myMatrix[1][0]=myMatrix[1][0]*aMatrix.myMatrix[0][0]+myMatrix[1][1]*aMatrix.myMatrix[1][0]+myMatrix[1][2]*aMatrix.myMatrix[2][0]+myMatrix[1][3]*aMatrix.myMatrix[3][0];
		temp.myMatrix[1][1]=myMatrix[1][0]*aMatrix.myMatrix[0][1]+myMatrix[1][1]*aMatrix.myMatrix[1][1]+myMatrix[1][2]*aMatrix.myMatrix[2][1]+myMatrix[1][3]*aMatrix.myMatrix[3][1];
		temp.myMatrix[1][2]=myMatrix[1][0]*aMatrix.myMatrix[0][2]+myMatrix[1][1]*aMatrix.myMatrix[1][2]+myMatrix[1][2]*aMatrix.myMatrix[2][2]+myMatrix[1][3]*aMatrix.myMatrix[3][2];
		temp.myMatrix[1][3]=myMatrix[1][0]*aMatrix.myMatrix[0][3]+myMatrix[1][1]*aMatrix.myMatrix[1][3]+myMatrix[1][2]*aMatrix.myMatrix[2][3]+myMatrix[1][3]*aMatrix.myMatrix[3][3];

		temp.myMatrix[2][0]=myMatrix[2][0]*aMatrix.myMatrix[0][0]+myMatrix[2][1]*aMatrix.myMatrix[1][0]+myMatrix[2][2]*aMatrix.myMatrix[2][0]+myMatrix[2][3]*aMatrix.myMatrix[3][0];
		temp.myMatrix[2][1]=myMatrix[2][0]*aMatrix.myMatrix[0][1]+myMatrix[2][1]*aMatrix.myMatrix[1][1]+myMatrix[2][2]*aMatrix.myMatrix[2][1]+myMatrix[2][3]*aMatrix.myMatrix[3][1];
		temp.myMatrix[2][2]=myMatrix[2][0]*aMatrix.myMatrix[0][2]+myMatrix[2][1]*aMatrix.myMatrix[1][2]+myMatrix[2][2]*aMatrix.myMatrix[2][2]+myMatrix[2][3]*aMatrix.myMatrix[3][2];
		temp.myMatrix[2][3]=myMatrix[2][0]*aMatrix.myMatrix[0][3]+myMatrix[2][1]*aMatrix.myMatrix[1][3]+myMatrix[2][2]*aMatrix.myMatrix[2][3]+myMatrix[2][3]*aMatrix.myMatrix[3][3];

		temp.myMatrix[3][0]=myMatrix[3][0]*aMatrix.myMatrix[0][0]+myMatrix[3][1]*aMatrix.myMatrix[1][0]+myMatrix[3][2]*aMatrix.myMatrix[2][0]+myMatrix[3][3]*aMatrix.myMatrix[3][0];
		temp.myMatrix[3][1]=myMatrix[3][0]*aMatrix.myMatrix[0][1]+myMatrix[3][1]*aMatrix.myMatrix[1][1]+myMatrix[3][2]*aMatrix.myMatrix[2][1]+myMatrix[3][3]*aMatrix.myMatrix[3][1];
		temp.myMatrix[3][2]=myMatrix[3][0]*aMatrix.myMatrix[0][2]+myMatrix[3][1]*aMatrix.myMatrix[1][2]+myMatrix[3][2]*aMatrix.myMatrix[2][2]+myMatrix[3][3]*aMatrix.myMatrix[3][2];
		temp.myMatrix[3][3]=myMatrix[3][0]*aMatrix.myMatrix[0][3]+myMatrix[3][1]*aMatrix.myMatrix[1][3]+myMatrix[3][2]*aMatrix.myMatrix[2][3]+myMatrix[3][3]*aMatrix.myMatrix[3][3];

		memcpy(myMatrix,temp.myMatrix,4*4*4);

		return *this;
	}



	template <class TYPE>
	Matrix44<TYPE>& Matrix44<TYPE>::operator*=(const Matrix33<TYPE>& aMatrix)	// matrice multiplikation
	{
		Matrix44 temp;



		temp.myMatrix[0][0]=myMatrix[0][0]*aMatrix.myMatrix[0][0]+myMatrix[0][1]*aMatrix.myMatrix[1][0]+myMatrix[0][2]*aMatrix.myMatrix[2][0];
		temp.myMatrix[0][1]=myMatrix[0][0]*aMatrix.myMatrix[0][1]+myMatrix[0][1]*aMatrix.myMatrix[1][1]+myMatrix[0][2]*aMatrix.myMatrix[2][1];
		temp.myMatrix[0][2]=myMatrix[0][0]*aMatrix.myMatrix[0][2]+myMatrix[0][1]*aMatrix.myMatrix[1][2]+myMatrix[0][2]*aMatrix.myMatrix[2][2];
		temp.myMatrix[0][3]=myMatrix[0][3];

		temp.myMatrix[1][0]=myMatrix[1][0]*aMatrix.myMatrix[0][0]+myMatrix[1][1]*aMatrix.myMatrix[1][0]+myMatrix[1][2]*aMatrix.myMatrix[2][0];
		temp.myMatrix[1][1]=myMatrix[1][0]*aMatrix.myMatrix[0][1]+myMatrix[1][1]*aMatrix.myMatrix[1][1]+myMatrix[1][2]*aMatrix.myMatrix[2][1];
		temp.myMatrix[1][2]=myMatrix[1][0]*aMatrix.myMatrix[0][2]+myMatrix[1][1]*aMatrix.myMatrix[1][2]+myMatrix[1][2]*aMatrix.myMatrix[2][2];
		temp.myMatrix[1][3]=myMatrix[1][3];

		temp.myMatrix[2][0]=myMatrix[2][0]*aMatrix.myMatrix[0][0]+myMatrix[2][1]*aMatrix.myMatrix[1][0]+myMatrix[2][2]*aMatrix.myMatrix[2][0];
		temp.myMatrix[2][1]=myMatrix[2][0]*aMatrix.myMatrix[0][1]+myMatrix[2][1]*aMatrix.myMatrix[1][1]+myMatrix[2][2]*aMatrix.myMatrix[2][1];
		temp.myMatrix[2][2]=myMatrix[2][0]*aMatrix.myMatrix[0][2]+myMatrix[2][1]*aMatrix.myMatrix[1][2]+myMatrix[2][2]*aMatrix.myMatrix[2][2];
		temp.myMatrix[2][3]=myMatrix[2][3];

		temp.myMatrix[3][0]=myMatrix[3][0];
		temp.myMatrix[3][1]=myMatrix[3][1];
		temp.myMatrix[3][2]=myMatrix[3][2];
		temp.myMatrix[3][3]=myMatrix[3][3];


		memcpy(myMatrix,temp.myMatrix,4*4*4);

		return *this;
	}


	template <class TYPE>
	Matrix44<TYPE> Matrix44<TYPE>::RotateAroundXPI(const float aPIAngle)
	{
		Matrix44 temp;
		float Sin,Cos;

		Sin=(float)sin(aPIAngle);
		Cos=(float)cos(aPIAngle);
		
		temp.myMatrix[1][1]=Cos;
		temp.myMatrix[2][1]=Sin;
		temp.myMatrix[2][2]=Cos;
		temp.myMatrix[1][2]=-Sin;
		temp.myMatrix[3][3]=1;


		return(temp);
	}

	template <class TYPE>
	 Matrix44<TYPE> Matrix44<TYPE>::RotateAroundYPI(const float aPIAngle)
	{
		Matrix44 temp;
		float Sin,Cos;

		Sin=(float)sin(aPIAngle);
		Cos=(float)cos(aPIAngle);

		temp.myMatrix[0][0]=Cos;
		temp.myMatrix[2][0]=-Sin;
		temp.myMatrix[2][2]=Cos;
		temp.myMatrix[0][2]=Sin;
		temp.myMatrix[3][3]=1;

		return(temp);

	}

	template <class TYPE>
	 Matrix44<TYPE> Matrix44<TYPE>::RotateAroundZPI(const float aPIAngle)
	{
		Matrix44 temp;
		float Sin,Cos;

		Sin=(float)sin(aPIAngle);
		Cos=(float)cos(aPIAngle);

		temp.myMatrix[0][0]=Cos;
		temp.myMatrix[1][0]=Sin;
		temp.myMatrix[1][1]=Cos;
		temp.myMatrix[0][1]=-Sin;
		temp.myMatrix[3][3]=1;


		
		return(temp);
	}

	template <class TYPE>
	Matrix44<TYPE> Matrix44<TYPE>::Identity()
	{
		Matrix44 temp;
		return(temp);
	}


	typedef Matrix33<float> Matrix33f;
	typedef Matrix33<double> Matrix33d;
	typedef Matrix33<int> Matrix33i;

	typedef Matrix44<float> Matrix44f;
	typedef Matrix44<double> Matrix44d;
	typedef Matrix44<int> Matrix44i;
};

#endif