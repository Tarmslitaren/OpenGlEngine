#include "stdafx.h"
#include "Intersections.h"
#include "CommonMacros.h"

bool Intersections::GetIntersection( float fDst1, float fDst2, CU::Vector3f P1, CU::Vector3f P2, CU::Vector3f &Hit) {
	if ( (fDst1 * fDst2) >= 0.0f) return false;
	if ( fDst1 == fDst2) return false; 
	Hit = P1 + (P2-P1) * ( -fDst1/(fDst2-fDst1) );
	return true;
}

bool Intersections::InBox( CU::Vector3f Hit, CU::Vector3f B1, CU::Vector3f B2, const int Axis) {
	if ( Axis==1 && Hit.myZ > B1.myZ && Hit.myZ < B2.myZ && Hit.myY > B1.myY && Hit.myY < B2.myY) return true;
	if ( Axis==2 && Hit.myZ > B1.myZ && Hit.myZ < B2.myZ && Hit.myX > B1.myX && Hit.myX < B2.myX) return true;
	if ( Axis==3 && Hit.myX > B1.myX && Hit.myX < B2.myX && Hit.myY > B1.myY && Hit.myY < B2.myY) return true;
	return false;
}

// returns true if line (L1, L2) intersects with the box (B1, B2)
// returns intersection point in Hit
bool Intersections::LineBoxInterSect( CU::Vector3f B1, CU::Vector3f B2, CU::Vector3f L1, CU::Vector3f L2, CU::Vector3f &Hit)
{
	if (L2.myX < B1.myX && L1.myX < B1.myX) return false;
	if (L2.myX > B2.myX && L1.myX > B2.myX) return false;
	if (L2.myY < B1.myY && L1.myY < B1.myY) return false;
	if (L2.myY > B2.myY && L1.myY > B2.myY) return false;
	if (L2.myZ < B1.myZ && L1.myZ < B1.myZ) return false;
	if (L2.myZ > B2.myZ && L1.myZ > B2.myZ) return false;
	if (L1.myX > B1.myX && L1.myX < B2.myX &&
		L1.myY > B1.myY && L1.myY < B2.myY &&
		L1.myZ > B1.myZ && L1.myZ < B2.myZ) 
	{Hit = L1; 
	return true;}
	if ( (GetIntersection( L1.myX-B1.myX, L2.myX-B1.myX, L1, L2, Hit) && InBox( Hit, B1, B2, 1 ))
		|| (GetIntersection( L1.myY-B1.myY, L2.myY-B1.myY, L1, L2, Hit) && InBox( Hit, B1, B2, 2 )) 
		|| (GetIntersection( L1.myZ-B1.myZ, L2.myZ-B1.myZ, L1, L2, Hit) && InBox( Hit, B1, B2, 3 )) 
		|| (GetIntersection( L1.myX-B2.myX, L2.myX-B2.myX, L1, L2, Hit) && InBox( Hit, B1, B2, 1 )) 
		|| (GetIntersection( L1.myY-B2.myY, L2.myY-B2.myY, L1, L2, Hit) && InBox( Hit, B1, B2, 2 )) 
		|| (GetIntersection( L1.myZ-B2.myZ, L2.myZ-B2.myZ, L1, L2, Hit) && InBox( Hit, B1, B2, 3 )))
		return true;

	return false;
}

bool Intersections::LineSphereInterSect(CU::Vector3f aStart,CU::Vector3f aEnd,CU::Vector3f aCenterPoint,float aRadius,float aLineRadius)
{
	CU::Vector3f lineStartToSpheremid = aCenterPoint-aStart;
	CU::Vector3f lineVector=aEnd-aStart;

	CU::Vector3f projektedToLineVector=lineVector*(lineStartToSpheremid.Dot(lineVector)/lineVector.Length());

	CU::Vector3f closestPoint=aStart+projektedToLineVector;

	if (projektedToLineVector.Length() < lineVector.Length())
	{
		if (projektedToLineVector.Dot(lineVector) > 0)
		{
			CU::Vector3f lineToSphereMid=aCenterPoint-closestPoint;

			if (lineToSphereMid.Length() < aRadius+aLineRadius)
			{
				return true;
			}
		}
	}

	return false;

};

bool Intersections::SphereSphereIntersect(const CU::Vector3f& aSphereCenter, float aSphereRaduis, const CU::Vector3f& aSecondSphereCenter, float aSecondSphereRadius)
{
	if ((aSphereCenter-aSecondSphereCenter).Length() < (aSphereRaduis*aSphereRaduis+aSecondSphereRadius*aSecondSphereRadius))
	{
		return true;
	}
	return false;
}

bool Intersections::BoxBoxIntersect(CU::Vector3f aBoxPosition, CU::Vector3f aBoxSecondPosition, CU::Vector3f aSecondBoxPosition , CU::Vector3f aSecondBoxSecondPosition)
{
	CU::Vector3f halfDimensions(abs(aBoxSecondPosition.myX-aBoxPosition.myX)/2.0f
		,abs(aBoxSecondPosition.myY-aBoxPosition.myY)/2.0f
		,abs(aBoxSecondPosition.myZ-aBoxPosition.myZ)/2.0f);
	if(PointBoxIntersect((aBoxPosition+halfDimensions),(aSecondBoxPosition-halfDimensions),(aSecondBoxSecondPosition+halfDimensions)))
	{
		return true;
	}
	return false;
}

bool Intersections::SphereBoxIntersect(const CU::Vector3f& aSphereCenter, float aSphereRaduis,const CU::Vector3f& aBoxPosition,const CU::Vector3f& aBoxSecondPosition)
{
	CU::Vector3f firstEdge(aBoxPosition);
	CU::Vector3f secondEdge(aBoxSecondPosition);
	firstEdge.myX -= aSphereRaduis;
	firstEdge.myY -= aSphereRaduis;
	firstEdge.myZ -= aSphereRaduis;
	secondEdge.myX += aSphereRaduis;
	secondEdge.myY += aSphereRaduis;
	secondEdge.myZ += aSphereRaduis;
	if(PointBoxIntersect(aSphereCenter,firstEdge,secondEdge))
	{
		return true;
	}
	/*else
	{
	CU::Vector3f closestBoxPoint = aBoxPosition;

	if (abs(aSphereCenter.myX-aBoxPosition.myX) > abs(aSphereCenter.myX-aBoxSecondPosition.myX))
	{
	closestBoxPoint.myX = aBoxSecondPosition.myX;
	}
	if (abs(aSphereCenter.myY-aBoxPosition.myY) > abs(aSphereCenter.myY-aBoxSecondPosition.myY))
	{
	closestBoxPoint.myY = aBoxSecondPosition.myY;
	}
	if (abs(aSphereCenter.myZ-aBoxPosition.myZ) > abs(aSphereCenter.myZ-aBoxSecondPosition.myZ))
	{
	closestBoxPoint.myZ = aBoxSecondPosition.myZ;
	}
	if ((closestBoxPoint-aSphereCenter).LengthSquared() < aSphereRaduis*aSphereRaduis)
	{
	return true;
	}*/
	return false;

}

bool Intersections::SphereIsInBox(const CU::Vector3f& aSphereCenter, float aSphereRaduis, const CU::Vector3f& aBoxPosition, const CU::Vector3f& aBoxSecondPosition)
{
	if(PointBoxIntersect(aSphereCenter,aBoxPosition,aBoxSecondPosition))
	{
		CU::Vector3f closestBoxPoint = aBoxPosition;
		if (abs(aSphereCenter.myX-aBoxPosition.myX) > abs(aSphereCenter.myX-aBoxSecondPosition.myX))
		{
			closestBoxPoint.myX = aBoxSecondPosition.myX;
		}
		if (abs(aSphereCenter.myY-aBoxPosition.myY) > abs(aSphereCenter.myY-aBoxSecondPosition.myY))
		{
			closestBoxPoint.myY = aBoxSecondPosition.myY;
		}
		if (abs(aSphereCenter.myZ-aBoxPosition.myZ) > abs(aSphereCenter.myZ-aBoxSecondPosition.myZ))
		{
			closestBoxPoint.myZ = aBoxSecondPosition.myZ;
		}
		if ((closestBoxPoint-aSphereCenter).Length() >= aSphereRaduis)
		{
			return true;
		}
	}
	return false;
}

bool Intersections::PointBoxIntersect(CU::Vector3f aPoint,CU::Vector3f aBoxPosition, CU::Vector3f aBoxSecondPosition)
{
	if(aPoint.myX < aBoxPosition.myX || aPoint.myX > aBoxSecondPosition.myX) return false;
	if(aPoint.myY < aBoxPosition.myY || aPoint.myY > aBoxSecondPosition.myY) return false;
	if(aPoint.myZ < aBoxPosition.myZ || aPoint.myZ > aBoxSecondPosition.myZ) return false;

	return true;
}