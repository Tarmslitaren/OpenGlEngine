#ifndef INTERSECTIONS_KID_HEADER
#define INTERSECTIONS_KID_HEADER

#include "stdafx.h"


namespace Intersections
{
	bool PointBoxIntersect(CU::Vector3f aPoint,CU::Vector3f aBoxPosition, CU::Vector3f aBoxSecondPosition);
	bool PointInSquare(CU::Vector2f aPoint, CU::Vector2f aSquarePos1, CU::Vector2f aSquarePos2);
	bool PointTriangleIntersect(CU::Vector2f aPoint, CU::Vector2f aTrianglePoint1, CU::Vector2f aTrianglePoint2, CU::Vector2f aTrianglePoint3 );
	bool PointCircleIntersection(CU::Vector2f aPoint,CU::Vector2f aCenterPoint,float aRadius);
	bool PointInSquareWarpInclusive(CU::Vector2f aPoint, CU::Vector2f aSquarePos1, CU::Vector2f aSquarePos2);
	bool martinPointTriInterSect(CU::Vector2f aPoint, CU::Vector2f aTrianglePoint1, CU::Vector2f aTrianglePoint2, CU::Vector2f aTrianglePoint3 );

	bool LineBoxInterSect(CU::Vector3f B1, CU::Vector3f B2, CU::Vector3f L1, CU::Vector3f L2, CU::Vector3f &Hit);
	bool LineSphereInterSect(CU::Vector3f aStart,CU::Vector3f aEnd,CU::Vector3f aCenterPoint,float aRadius,float aLineRadius);
	bool LineSigmentLineSigmentIntersection(const CU::Vector2f& aLineStart,const CU::Vector2f& aLineEnd,const CU::Vector2f& aSecondLineStart,const CU::Vector2f& aSecondLineEnd,CU::Vector2f& anIntersectionPoint );
	bool LineSphereIntersection( CU::Vector3f aPoint, CU::Vector3f aDirection, CU::Vector3f aCenterPos, float aRadius, CU::Vector3f& aHit);
	bool LineLineIntersection(const CU::Vector2f& aLineStart,const CU::Vector2f& aLineEnd,const CU::Vector2f& aSecondLineStart,const CU::Vector2f& aSecondLineEnd,CU::Vector2f& anIntersectionPoint);
	bool LineTriangleIntersection(CU::Vector2f aLineStart,CU::Vector2f aLineEnd,CU::Vector2f aTrianglePoint1, CU::Vector2f aTrianglePoint2, CU::Vector2f aTrianglePoint3);
	bool LineSquareIntersection(const CU::Vector2f& B1,const CU::Vector2f& B2,const CU::Vector2f& L1,const CU::Vector2f& L2, CU::Vector2f &Hit);
	bool GetIntersection2D( float fDst1, float fDst2, CU::Vector2f P1, CU::Vector2f P2, CU::Vector2f &Hit);
	bool InBox2D( CU::Vector2f Hit, CU::Vector2f B1, CU::Vector2f B2, const int Axis);

	bool SphereSphereIntersect(const CU::Vector3f& aSphereCenter, float aSphereRaduis, const CU::Vector3f& aSecondSphereCenter, float aSecondSphereRadius);
	bool SphereBoxIntersect(const CU::Vector3f& aSphereCenter, float aSphereRaduis, const CU::Vector3f& aBoxPosition, const CU::Vector3f& aBoxSecondPosition);
	bool SphereIsInBox(const CU::Vector3f& aSphereCenter, float aSphereRaduis, const CU::Vector3f& aBoxPosition, const CU::Vector3f& aBoxSecondPosition);
	
	bool BoxBoxIntersect(CU::Vector3f aBoxPosition, CU::Vector3f aBoxSecondPosition, CU::Vector3f aSecondBoxPosition , CU::Vector3f aSecondBoxSecondPosition);
	bool InBox( CU::Vector3f Hit, CU::Vector3f B1, CU::Vector3f B2, const int Axis);
	bool GetIntersection( float fDst1, float fDst2, CU::Vector3f P1, CU::Vector3f P2, CU::Vector3f &Hit);

	bool TriangleIsInsideSquare(CU::Vector2f aTrianglePoint1, CU::Vector2f aTrianglePoint2, CU::Vector2f aTrianglePoint3, CU::Vector2f asquarePos1, CU::Vector2f asquarePos2);
	bool TriangleTriangleIntersection(CU::Vector2f aTrianglePoint1, CU::Vector2f aTrianglePoint2, CU::Vector2f aTrianglePoint3,CU::Vector2f aSecondTrianglePoint1, CU::Vector2f aSecondTrianglePoint2, CU::Vector2f aSecondTrianglePoint3);

	bool RaySphereIntersection(CU::Vector3f aPoint, CU::Vector3f aDirection, CU::Vector3f aCenterPos, float aRadius);
	bool RayPlaneIntersection(CU::Vector3f& aReturnPoint, CU::Vector3f aStartPoint, CU::Vector3f aEndPoint, CU::Vector3f aPlane,  CU::Vector3f aNormal);

	bool CircleInSquare(CU::Vector2f aCirclePoint,float aRadius, CU::Vector2f aSquarePos1, CU::Vector2f aSquarePos2);
	
	bool SameSide(const CU::Vector2f& aPoint1, const CU::Vector2f& aPoint2, const CU::Vector2f& aPoint3, const CU::Vector2f& aPoint4);
};

#endif