#ifndef INTERSECTIONS_HEADER
#define INTERSECTIONS_HEADER

#include "stdafx.h"
#include "CU_Vector.h"

namespace Intersections
{
	bool LineBoxInterSect(CommonUtilities::Vector3f B1, CommonUtilities::Vector3f B2, CommonUtilities::Vector3f L1, CommonUtilities::Vector3f L2, CommonUtilities::Vector3f &Hit);
	bool LineSphereInterSect(CommonUtilities::Vector3f aStart,CommonUtilities::Vector3f aEnd,CommonUtilities::Vector3f aCenterPoint,float aRadius,float aLineRadius);

	bool SphereSphereIntersect(const CommonUtilities::Vector3f& aSphereCenter, float aSphereRaduis, const CommonUtilities::Vector3f& aSecondSphereCenter, float aSecondSphereRadius);
	bool SphereBoxIntersect(const CommonUtilities::Vector3f& aSphereCenter, float aSphereRaduis, const CommonUtilities::Vector3f& aBoxPosition, const CommonUtilities::Vector3f& aBoxSecondPosition);
	bool SphereIsInBox(const CommonUtilities::Vector3f& aSphereCenter, float aSphereRaduis, const CommonUtilities::Vector3f& aBoxPosition, const CommonUtilities::Vector3f& aBoxSecondPosition);

	bool BoxBoxIntersect(CommonUtilities::Vector3f aBoxPosition, CommonUtilities::Vector3f aBoxSecondPosition, CommonUtilities::Vector3f aSecondBoxPosition , CommonUtilities::Vector3f aSecondBoxSecondPosition);

	bool PointBoxIntersect(CommonUtilities::Vector3f aPoint,CommonUtilities::Vector3f aBoxPosition, CommonUtilities::Vector3f aBoxSecondPosition);

	bool GetIntersection( float fDst1, float fDst2, CommonUtilities::Vector3f P1, CommonUtilities::Vector3f P2, CommonUtilities::Vector3f &Hit);
	bool InBox( CommonUtilities::Vector3f Hit, CommonUtilities::Vector3f B1, CommonUtilities::Vector3f B2, const int Axis);
};

#endif