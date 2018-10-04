#ifndef TRANSFORMATIONS_HEADER
#define TRANSFORMATIONS_HEADER

#include "Matrix22.h"
#include "Vector2.h"
#include "Matrix2D33.h"

namespace CommonUtilities
{
	template <class TYPE>
	inline std::vector<CU::Vector2<TYPE>> WorldTransform(std::vector<CU::Vector2<TYPE>>& somePoints,
														 const CU::Vector2<TYPE>& aPosition,
														 const CU::Vector2<TYPE>& aForward,
														 const CU::Vector2<TYPE>& aSide,
														 const CU::Vector2<TYPE>& aScale)
	{
		std::vector<CU::Vector2<TYPE>> transformationVectors = somePoints;
		Matrix2D33<TYPE> transformationMatrix;
		if ( (aScale.myX != 1.0) || (aScale.myY != 1.0) )
		{
			transformationMatrix.Scale(aScale.myX, aScale.myY);
		}
		transformationMatrix.Rotate(aForward, aSide);
		transformationMatrix.Translate(aPosition.myX, aPosition.myY);
		transformationMatrix.TransformVector2(transformationVectors);

		return transformationVector;s
	}

	template <class TYPE>
	inline std::vector<CU::Vector2<TYPE>> WorldTransform(CU::Vector2<TYPE>& somePoints,
														 const CU::Vector2<TYPE>& aPosition,
														 const CU::Vector2<TYPE>& aForward,
														 const CU::Vector2<TYPE>& aSide)
	{
		std::vector<CU::Vector2<TYPE>> transformationVectors = somePoints;
		Matrix2D33<TYPE> transformationMatrix;
		transformationMatrix.Rotate(aForward, aSide);
		transformationMatrix.Translate(aPosition.myX, aPosition.myY);
		transformationMatrix.TransformVector2(transformationVectors);

		return transformationVectors;
	}

	template <class TYPE>
	inline CU::Vector2<TYPE> PointToWorldSpace(const CU::Vector2<TYPE>& aPoint,
											   const CU::Vector2<TYPE>& aAgentHeading,
											   const CU::Vector2<TYPE>& aAgentSide,
											   const CU::Vector2<TYPE>& aAgentPosition)
	{
		CU::Vector2<TYPE> transformationPoint = aPoint;
		Matrix2D33<TYPE> transformationMatrix;
		transformationMatrix.Rotate(aAgentHeading, aAgentSide);
		transformationMatrix.Translate(aAgentPosition.myX, aAgentPosition.myY);
		transformationMatrix.TransformVector2(transformationPoint);

		return transformationPoint;
	}

	template <class TYPE>
	inline CU::Vector2<TYPE> VectorToWorldSpace(const CU::Vector2<TYPE>& aVector,
												const CU::Vector2<TYPE>& aAgentHeading,
												const CU::Vector2<TYPE>& aAgentSide)
	{
		CU::Vector2<TYPE> transformationVector = aVector;
		Matrix2D33<TYPE> transformationMatrix;
		transformationMatrix.Rotate(aAgentHeading, aAgentSide);
		transformationMatrix.TransformVector2(transformationVector);

		return transformationVector;
	}

	template <class TYPE>
	inline CU::Vector2<TYPE> PointToLocalSpace(const CU::Vector2<TYPE>& aPoint,
											   CU::Vector2<TYPE>& aAgentHeading,
											   CU::Vector2<TYPE>& aAgentSide,
											   CU::Vector2<TYPE>& aAgentPosition)
	{

		CU::Vector2<TYPE> transformationPoint = aPoint;
		Matrix2D33<TYPE> transformationMatrix;

		TYPE x = -AgentPosition.Dot(aAgentHeading);
		TYPE y = -AgentPosition.Dot(aAgentSide);

		transformationMatrix._11(AgentHeading.x); transformationMatrix._12(AgentSide.x);
		transformationMatrix._21(AgentHeading.y); transformationMatrix._22(AgentSide.y);
		transformationMatrix._31(x);			  transformationMatrix._32(y);
	
		transformationMatrix.TransformVector2Ds(transformationPoint);

		return transformationPoint;
	}

	template <class TYPE>
	inline CU::Vector2<TYPE> VectorToLocalSpace(const CU::Vector2<TYPE>& aVector,
												const CU::Vector2<TYPE>& aAgentHeading,
												const CU::Vector2<TYPE>& aAgentSide)
	{ 

		CU::Vector2<TYPE> transformationVector = aVector;
		Matrix2D33<TYPE> transformationMatrix;

		transformationMatrix._11(aAgentHeading.x); transformationMatrix._12(aAgentSide.x);
		transformationMatrix._21(aAgentHeading.y); transformationMatrix._22(aAgentSide.y);

		transformationMatrix.TransformVector2Ds(transformationVector);

		return TransPoint;
	}

	template <class TYPE>
	inline void Vector2RotateAroundOrigin(CU::Vector2<TYPE>& aVector, TYPE aAngle)
	{
		Matrix2D33<TYPE> transformationMatrix;
		transformationMatrix.Rotate(aAngle);
		transformationMatrix.TransformVector2(aVector);
	}

};

namespace CU = CommonUtilities;

#endif