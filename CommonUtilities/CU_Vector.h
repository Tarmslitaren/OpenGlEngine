#ifndef COMMONUTILITIES_VECTOR_HEADER
#define COMMONUTILITIES_VECTOR_HEADER

#include "assert.h"
#include <math.h>

namespace CommonUtilities
{
	template <class TYPE>
	class Vector3;

	template <class TYPE>
	class Vector2
	{
	public:
		Vector2();
		Vector2(TYPE aX,TYPE aY);
		~Vector2();

		void Set(TYPE aX,TYPE aY);
		
		Vector2& operator+=(const Vector2& aVector);
		Vector2& operator-=(const Vector2& aVector);
		Vector2& operator*=(const Vector2& aVector);
		Vector2& operator/=(const Vector2& aVector);

		Vector2& operator*=(const TYPE& aType);
		Vector2& operator/=(const TYPE& aType);

		inline TYPE& operator[](const int& aIndex) const;
		inline TYPE& operator[](const int& aIndex);



		Vector2& operator=(const Vector2& aVector);

		bool operator==(const Vector2& aVector) const;

		TYPE Length() const;
		TYPE Length2() const;
		Vector2<TYPE>& Normalize();

		float Dot(const Vector2& aVector);
		float DotPerd(const Vector2& aVector);

		union
		{
			TYPE myX;
			TYPE x;
			TYPE u;
			TYPE width;
		};
		union
		{
			TYPE myY;
			TYPE y;
			TYPE v;
			TYPE height;
		};
	};


	template <class TYPE>
	Vector2<TYPE> operator+(const Vector2<TYPE>& aLeftSideVector,const Vector2<TYPE>& aRightSideVector)
	{
		Vector2<TYPE> returnValue(aLeftSideVector);
		returnValue+=aRightSideVector;
		return(returnValue);
	}

	template <class TYPE>
	Vector2<TYPE> operator-(const Vector2<TYPE>& aLeftSideVector,const Vector2<TYPE>& aRightSideVector)
	{
		Vector2<TYPE> returnValue(aLeftSideVector);
		returnValue-=aRightSideVector;
		return(returnValue);
	}

	template <class TYPE>
	Vector2<TYPE> operator*(const Vector2<TYPE>& aLeftSideVector,const Vector2<TYPE>& aRightSideVector)
	{
		Vector2<TYPE> returnValue(aLeftSideVector);
		returnValue*=aRightSideVector;
		return(returnValue);
	}
	template <class TYPE>
	Vector2<TYPE> operator/(const Vector2<TYPE>& aLeftSideVector,const Vector2<TYPE>& aRightSideVector)
	{
		Vector2<TYPE> returnValue(aLeftSideVector);
		returnValue/=aRightSideVector;
		return(returnValue);
	}
	template <class TYPE>
	Vector2<TYPE> operator*(const Vector2<TYPE>& aLeftSideVector,const TYPE& aRightSideType)
	{
		Vector2<TYPE> returnValue(aLeftSideVector);
		returnValue*=aRightSideType;
		return(returnValue);
	}
	template <class TYPE>
	Vector2<TYPE> operator/(const Vector2<TYPE>& aLeftSideVector,const TYPE& aRightSideType)
	{
		Vector2<TYPE> returnValue(aLeftSideVector);
		returnValue/=aRightSideType;
		return(returnValue);
	}




	template <class TYPE>
	Vector2<TYPE>::Vector2()
	{

	}

	template <class TYPE>
	Vector2<TYPE>::Vector2(const TYPE aX,const TYPE aY)
	{
		myX=aX;
		myY=aY;
	}
	
	template <class TYPE>
	Vector2<TYPE>::~Vector2()
	{
	}

	template <class TYPE>
	void Vector2<TYPE>::Set(const TYPE aX,const TYPE aY)
	{
		myX=aX;
		myY=aY;
	}

	template <class TYPE>
	Vector2<TYPE>& Vector2<TYPE>::operator+=(const Vector2<TYPE>& aVector)
	{
		myX+=aVector.myX;
		myY+=aVector.myY;
		return(*this);
	}
	template <class TYPE>
	Vector2<TYPE>& Vector2<TYPE>::operator-=(const Vector2<TYPE>& aVector)
	{
		myX-=aVector.myX;
		myY-=aVector.myY;
		return(*this);
	}

	template <class TYPE>
	Vector2<TYPE>& Vector2<TYPE>::operator*=(const Vector2<TYPE>& aVector)
	{
		myX*=aVector.myX;
		myY*=aVector.myY;
		return(*this);
	}
	template <class TYPE>
	Vector2<TYPE>& Vector2<TYPE>::operator/=(const Vector2<TYPE>& aVector)
	{
		myX/=aVector.myX;
		myY/=aVector.myY;
		return(*this);
	}

	template <class TYPE>
	Vector2<TYPE>& Vector2<TYPE>::operator*=(const TYPE& aType)
	{
		myX*=aType;
		myY*=aType;
		return(*this);
	}

	template <class TYPE>
	Vector2<TYPE>& Vector2<TYPE>::operator/=(const TYPE& aType)
	{
		myX/=aType;
		myY/=aType;
		return(*this);
	}

	template <class TYPE>
	Vector2<TYPE>& Vector2<TYPE>::operator=(const Vector2<TYPE>& aVector)
	{
		myX=aVector.myX;
		myY=aVector.myY;
		return(*this);
	}

	template <class TYPE>
	bool Vector2<TYPE>::operator==(const Vector2<TYPE>& aRightSideVector) const 
	{
		if(myX!=aRightSideVector.myX) return(false);
		if(myY!=aRightSideVector.myY) return(false);
		return(true);
	}


	template <class TYPE>
	Vector2<TYPE>& Vector2<TYPE>::Normalize()
	{
		float length=Length();
		myX/=length;
		myY/=length;
		return *this;
	}

	template <class TYPE>
	float Vector2<TYPE>::Dot(const Vector2& aVector)
	{
		return(aVector.x*myX+aVector.y*myY);
	}

	template <class TYPE>
	float Vector2<TYPE>::DotPerd(const Vector2& aVector)
	{
		return(myX*aVector.myY - myY*aVector.myX);
	}

	template <class TYPE>
	TYPE Vector2<TYPE>::Length() const 
	{
		return(sqrt(myX*myX+myY*myY));
	}

	template <class TYPE>
	TYPE Vector2<TYPE>::Length2() const 
	{
		return(myX*myX+myY*myY);
	}

	typedef Vector2<float> Vector2f;
	typedef Vector2<double> Vector2d;
	typedef Vector2<int> Vector2i;




	template <class TYPE>
	class Vector3
	{
	public:
		Vector3();
		Vector3(TYPE aX,TYPE aY,TYPE aZ);
		~Vector3();

		void Set(TYPE aX,TYPE aY,TYPE aZ);
		
		Vector3& operator+=(const Vector3& aVector);
		Vector3& operator-=(const Vector3& aVector);
		Vector3& operator*=(const Vector3& aVector);
		Vector3& operator/=(const Vector3& aVector);

		Vector3& operator*=(const TYPE& aType);
		Vector3& operator/=(const TYPE& aType);

		inline TYPE& operator[](const int& aIndex) const;
		inline TYPE& operator[](const int& aIndex);

		float Dot(const Vector3& aVector);
		float DotPerp(const Vector3& aVector);
		static Vector3<TYPE> Cross(const Vector3<TYPE>& aLeftSideVector,const Vector3<TYPE>& aRightSideVector); //Cross Product
		Vector3<TYPE> Cross(const Vector3 &aVector);

		Vector3& operator=(const Vector3& aVector);

		bool operator==(const Vector3& aVector) const;
		bool operator!=(const Vector3& aVector) const;

		TYPE Length() const;
		TYPE Length2() const;
		Vector3<TYPE>& Normalize();
		Vector3<TYPE> GetNormalized();

		union
		{
			TYPE myX;
			TYPE x;
			TYPE r;
		};
		union
		{
			TYPE myY;
			TYPE y;
			TYPE g;

		};
		union
		{
			TYPE myZ;
			TYPE z;
			TYPE b;

		};
	};


	template <class TYPE>
	float Vector3<TYPE>::Dot(const Vector3& aVector)
	{
		return(aVector.x*x+aVector.y*y+aVector.z*z);
	}


	template <typename TYPE>
	Vector3<TYPE> Vector3<TYPE>::Cross(const Vector3& aVector)
	{
		return Vector3<TYPE>(
			myY*aVector.myZ - myZ*aVector.myY,
			myZ*aVector.myX - myX*aVector.myZ,
			myX*aVector.myY - myY*aVector.myX);
	}

	template <class TYPE>
	Vector3<TYPE> operator+(const Vector3<TYPE>& aLeftSideVector,const Vector3<TYPE>& aRightSideVector)
	{
		Vector3<TYPE> returnValue(aLeftSideVector);
		returnValue+=aRightSideVector;
		return(returnValue);
	}
	template <class TYPE>
	Vector3<TYPE> operator-(const Vector3<TYPE>& aLeftSideVector,const Vector3<TYPE>& aRightSideVector)
	{
		Vector3<TYPE> returnValue(aLeftSideVector);
		returnValue-=aRightSideVector;
		return(returnValue);
	}

	template <class TYPE>
	Vector3<TYPE> operator*(const Vector3<TYPE>& aLeftSideVector,const Vector3<TYPE>& aRightSideVector)
	{
		Vector3<TYPE> returnValue(aLeftSideVector);
		returnValue*=aRightSideVector;
		return(returnValue);
	}
	template <class TYPE>
	Vector3<TYPE> operator/(const Vector3<TYPE>& aLeftSideVector,const Vector3<TYPE>& aRightSideVector)
	{
		Vector3<TYPE> returnValue(aLeftSideVector);
		returnValue/=aRightSideVector;
		return(returnValue);
	}
	template <class TYPE>
	Vector3<TYPE> operator*(const Vector3<TYPE>& aLeftSideVector,const TYPE& aRightSideType)
	{
		Vector3<TYPE> returnValue(aLeftSideVector);
		returnValue*=aRightSideType;
		return(returnValue);
	}
	template <class TYPE>
	Vector3<TYPE> operator/(const Vector3<TYPE>& aLeftSideVector,const TYPE& aRightSideType)
	{
		Vector3<TYPE> returnValue(aLeftSideVector);
		returnValue/=aRightSideType;
		return(returnValue);
	}


	template <class TYPE>
	Vector3<TYPE>::Vector3()
	{
		

	}

	template <class TYPE>
	Vector3<TYPE> Vector3<TYPE>::Cross(const Vector3<TYPE>& aLeftSideVector,const Vector3<TYPE>& aRightSideVector)
	{
		Vector3<TYPE> returnValue;
		returnValue.myX = (aLeftSideVector.myY*aRightSideVector.myZ)-(aLeftSideVector.myZ*aRightSideVector.myY);
		returnValue.myY = -((aLeftSideVector.myX*aRightSideVector.myZ)-(aLeftSideVector.myZ*aRightSideVector.myX));
		returnValue.myZ = (aLeftSideVector.myX*aRightSideVector.myY)-(aLeftSideVector.myY*aRightSideVector.myX);
		return(returnValue);
	}

	template <class TYPE>
	Vector3<TYPE>::Vector3(const TYPE aX,const TYPE aY,const TYPE aZ)
	{
		myX=aX;
		myY=aY;
		myZ=aZ;
	}
	
	template <class TYPE>
	Vector3<TYPE>::~Vector3()
	{
	}

	template <class TYPE>
	void Vector3<TYPE>::Set(const TYPE aX,const TYPE aY,const TYPE aZ)
	{
		myX=aX;
		myY=aY;
		myZ=aZ;
	}

	template <class TYPE>
	Vector3<TYPE>& Vector3<TYPE>::operator+=(const Vector3<TYPE>& aVector)
	{
		myX+=aVector.myX;
		myY+=aVector.myY;
		myZ+=aVector.myZ;
		return(*this);
	}
	template <class TYPE>
	Vector3<TYPE>& Vector3<TYPE>::operator-=(const Vector3<TYPE>& aVector)
	{
		myX-=aVector.myX;
		myY-=aVector.myY;
		myZ-=aVector.myZ;
		return(*this);
	}

	template <class TYPE>
	Vector3<TYPE>& Vector3<TYPE>::operator*=(const Vector3<TYPE>& aVector)
	{
		myX*=aVector.myX;
		myY*=aVector.myY;
		myZ*=aVector.myZ;

		return(*this);
	}
	template <class TYPE>
	Vector3<TYPE>& Vector3<TYPE>::operator/=(const Vector3<TYPE>& aVector)
	{
		myX/=aVector.myX;
		myY/=aVector.myY;
		myZ/=aVector.myZ;
		return(*this);
	}

	template <class TYPE>
	Vector3<TYPE>& Vector3<TYPE>::operator*=(const TYPE& aType)
	{
		myX*=aType;
		myY*=aType;
		myZ*=aType;
		return(*this);
	}

	template <class TYPE>
	Vector3<TYPE>& Vector3<TYPE>::operator/=(const TYPE& aType)
	{
		myX/=aType;
		myY/=aType;
		myZ/=aType;
		return(*this);
	}

	template <class TYPE>
	Vector3<TYPE>& Vector3<TYPE>::operator=(const Vector3<TYPE>& aVector)
	{
		myX=aVector.myX;
		myY=aVector.myY;
		myZ=aVector.myZ;

		return(*this);
	}

	template <class TYPE>
	bool Vector3<TYPE>::operator==(const Vector3<TYPE>& aRightSideVector) const 
	{
		if(myX!=aRightSideVector.myX) return(false);
		if(myY!=aRightSideVector.myY) return(false);
		if(myZ!=aRightSideVector.myZ) return(false);
		return(true);
	}

	template <class TYPE>
	bool Vector3<TYPE>::operator!=(const Vector3<TYPE>& aRightSideVector) const 
	{
		if(myX==aRightSideVector.myX && myY==aRightSideVector.myY && myZ==aRightSideVector.myZ)
		{
			return(false);
		}
		return(true);
	}


	template <class TYPE>
	Vector3<TYPE>& Vector3<TYPE>::Normalize()
	{
		
		float length=Length();
		if (length > 0.0f)
		{
			myX/=length;
			myY/=length;
			myZ/=length;
		}
	
		return *this;
	}

	template <class TYPE>
	Vector3<TYPE> Vector3<TYPE>::GetNormalized()
	{
		
		float length=Length();
		if (length > 0.0f)
		{
			return CU::Vector3f(myX/length,myY/length,myZ/length);
		}
	
		return CU::Vector3f(0,0,0);
	}

	template <class TYPE>
	TYPE Vector3<TYPE>::Length() const 
	{
		return(sqrtf(myX*myX+myY*myY+myZ*myZ));
	}

	template <class TYPE>
	TYPE Vector3<TYPE>::Length2() const 
	{
		return(myX*myX+myY*myY+myZ*myZ);
	}

	typedef Vector3<float> Vector3f;
	typedef Vector3<double> Vector3d;
	typedef Vector3<int> Vector3i;


	template <class TYPE>
	class Vector4
	{
	public:
		Vector4();
		Vector4(TYPE aX,TYPE aY,TYPE aZ,TYPE aAlpha);
		~Vector4();

		void Set(TYPE aX,TYPE aY,TYPE aZ,TYPE aAlpha);
		
		Vector4& operator+=(const Vector4& aVector);
		Vector4& operator-=(const Vector4& aVector);
		Vector4& operator*=(const Vector4& aVector);
		Vector4& operator/=(const Vector4& aVector);

		Vector4& operator*=(const TYPE& aType);
		Vector4& operator/=(const TYPE& aType);
		
		inline TYPE& operator[](const int& aIndex) const;
		inline TYPE& operator[](const int& aIndex);

		float Dot(const Vector4& aVector);
	

		Vector4& operator=(const Vector4& aVector);

		bool operator==(const Vector4& aVector) const;

		TYPE Length() const;
		TYPE Length2() const;
		Vector4<TYPE>& Normalize();

		union
		{
			TYPE myX;
			TYPE x;
			TYPE r;
		};
		union
		{
			TYPE myY;
			TYPE y;
			TYPE g;

		};
		union
		{
			TYPE myZ;
			TYPE z;
			TYPE b;

		};
		union
		{
			TYPE myW;
			TYPE w;
			TYPE myAlpha;
			TYPE a;

		};
	};

	template <class TYPE>
	float Vector4<TYPE>::Dot(const Vector4& aVector)
	{
		return(aVector.x*x+aVector.y*y+aVector.z*z+aVector.w*w);
	}

	template <class TYPE>
	Vector4<TYPE> operator+(const Vector4<TYPE>& aLeftSideVector,const Vector4<TYPE>& aRightSideVector)
	{
		Vector4<TYPE> returnValue(aLeftSideVector);
		returnValue+=aRightSideVector;
		return(returnValue);
	}
	template <class TYPE>
	Vector4<TYPE> operator-(const Vector4<TYPE>& aLeftSideVector,const Vector4<TYPE>& aRightSideVector)
	{
		Vector4<TYPE> returnValue(aLeftSideVector);
		returnValue-=aRightSideVector;
		return(returnValue);
	}

	template <class TYPE>
	Vector4<TYPE> operator*(const Vector4<TYPE>& aLeftSideVector,const Vector4<TYPE>& aRightSideVector)
	{
		Vector4<TYPE> returnValue(aLeftSideVector);
		returnValue*=aRightSideVector;
		return(returnValue);
	}
	template <class TYPE>
	Vector4<TYPE> operator/(const Vector4<TYPE>& aLeftSideVector,const Vector4<TYPE>& aRightSideVector)
	{
		Vector4<TYPE> returnValue(aLeftSideVector);
		returnValue/=aRightSideVector;
		return(returnValue);
	}
	template <class TYPE>
	Vector4<TYPE> operator*(const Vector4<TYPE>& aLeftSideVector,const TYPE& aRightSideType)
	{
		Vector4<TYPE> returnValue(aLeftSideVector);
		returnValue*=aRightSideType;
		return(returnValue);
	}
	template <class TYPE>
	Vector4<TYPE> operator/(const Vector4<TYPE>& aLeftSideVector,const TYPE& aRightSideType)
	{
		Vector4<TYPE> returnValue(aLeftSideVector);
		returnValue/=aRightSideType;
		return(returnValue);
	}




	template <class TYPE>
	Vector4<TYPE>::Vector4()
	{
	}

	template <class TYPE>
	Vector4<TYPE>::Vector4(const TYPE aX,const TYPE aY,const TYPE aZ,const TYPE aW)
	{
		myX=aX;
		myY=aY;
		myZ=aZ;
		myW=aW;
	}
	
	template <class TYPE>
	Vector4<TYPE>::~Vector4()
	{
	}

	template <class TYPE>
	void Vector4<TYPE>::Set(const TYPE aX,const TYPE aY,const TYPE aZ,const TYPE aW)
	{
		myX=aX;
		myY=aY;
		myZ=aZ;
		myW=aW;
	}

	template <class TYPE>
	Vector4<TYPE>& Vector4<TYPE>::operator+=(const Vector4<TYPE>& aVector)
	{
		myX+=aVector.myX;
		myY+=aVector.myY;
		myZ+=aVector.myZ;
		myW+=aVector.myW;
		return(*this);
	}
	template <class TYPE>
	Vector4<TYPE>& Vector4<TYPE>::operator-=(const Vector4<TYPE>& aVector)
	{
		myX-=aVector.myX;
		myY-=aVector.myY;
		myZ-=aVector.myZ;
		myW-=aVector.myW;
		return(*this);
	}

	template <class TYPE>
	Vector4<TYPE>& Vector4<TYPE>::operator*=(const Vector4<TYPE>& aVector)
	{
		myX*=aVector.myX;
		myY*=aVector.myY;
		myZ*=aVector.myZ;
		myW*=aVector.myW;

		return(*this);
	}
	template <class TYPE>
	Vector4<TYPE>& Vector4<TYPE>::operator/=(const Vector4<TYPE>& aVector)
	{
		myX/=aVector.myX;
		myY/=aVector.myY;
		myZ/=aVector.myZ;
		myW/=aVector.myW;
		return(*this);
	}

	template <class TYPE>
	Vector4<TYPE>& Vector4<TYPE>::operator*=(const TYPE& aType)
	{
		myX*=aType;
		myY*=aType;
		myZ*=aType;
		myW*=aType;
		return(*this);
	}

	template <class TYPE>
	Vector4<TYPE>& Vector4<TYPE>::operator/=(const TYPE& aType)
	{
		myX/=aType;
		myY/=aType;
		myZ/=aType;
		myW/=aType;
		return(*this);
	}

	template <class TYPE>
	Vector4<TYPE>& Vector4<TYPE>::operator=(const Vector4<TYPE>& aVector)
	{
		myX=aVector.myX;
		myY=aVector.myY;
		myZ=aVector.myZ;
		myW=aVector.myW;

		return(*this);
	}

	template <class TYPE>
	bool Vector4<TYPE>::operator==(const Vector4<TYPE>& aRightSideVector) const 
	{
		if(myX!=aRightSideVector.myX) return(false);
		if(myY!=aRightSideVector.myY) return(false);
		if(myZ!=aRightSideVector.myZ) return(false);
		if(myW!=aRightSideVector.myW) return(false);
		return(true);
	}


	template <class TYPE>
	Vector4<TYPE>& Vector4<TYPE>::Normalize()
	{
		float length=Length();
		myX/=length;
		myY/=length;
		myZ/=length;
		myW/=length;
		return *this;
	}

	template <class TYPE>
	TYPE Vector4<TYPE>::Length() const 
	{
		return(sqrt(myX*myX+myY*myY+myZ*myZ+myW*myW));
	}

	template <class TYPE>
	TYPE Vector4<TYPE>::Length2() const 
	{
		return(myX*myX+myY*myY+myZ*myZ+myW*myW);
	}

	typedef Vector4<float> Vector4f;
	typedef Vector4<double> Vector4d;
	typedef Vector4<int> Vector4i;

};

namespace CU = CommonUtilities;

#endif