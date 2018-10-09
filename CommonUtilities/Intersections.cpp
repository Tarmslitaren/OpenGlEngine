#include "stdafx.h"
#include "Intersections.h"
#include "CommonMacros.h"
#include "converters.h"

bool Intersections::GetIntersection( float fDst1, float fDst2, CU::Vector3f P1, CU::Vector3f P2, CU::Vector3f &Hit) {
	if ( (fDst1 * fDst2) >= 0.0f) return false;
	if ( fDst1 == fDst2) return false; 
	Hit = P1 + (P2-P1) * ( -fDst1/(fDst2-fDst1) );
	return true;
}

bool Intersections::GetIntersection2D( float fDst1, float fDst2, CU::Vector2f P1, CU::Vector2f P2, CU::Vector2f &Hit) {
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

bool Intersections::InBox2D( CU::Vector2f Hit, CU::Vector2f B1, CU::Vector2f B2, const int Axis)
{
	if ( Axis==1 && Hit.myY > B1.myY && Hit.myY < B2.myY) return true;
	if ( Axis==2 && Hit.myX > B1.myX && Hit.myX < B2.myX) return true;
	//if ( Axis==3 && Hit.myX > B1.myX && Hit.myX < B2.myX) return true;
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
	{
		Hit = L1; 
		return true;
	}
	if ( (GetIntersection( L1.myX-B1.myX, L2.myX-B1.myX, L1, L2, Hit) && InBox( Hit, B1, B2, 1 ))
		|| (GetIntersection( L1.myY-B1.myY, L2.myY-B1.myY, L1, L2, Hit) && InBox( Hit, B1, B2, 2 )) 
		|| (GetIntersection( L1.myZ-B1.myZ, L2.myZ-B1.myZ, L1, L2, Hit) && InBox( Hit, B1, B2, 3 )) 
		|| (GetIntersection( L1.myX-B2.myX, L2.myX-B2.myX, L1, L2, Hit) && InBox( Hit, B1, B2, 1 )) 
		|| (GetIntersection( L1.myY-B2.myY, L2.myY-B2.myY, L1, L2, Hit) && InBox( Hit, B1, B2, 2 )) 
		|| (GetIntersection( L1.myZ-B2.myZ, L2.myZ-B2.myZ, L1, L2, Hit) && InBox( Hit, B1, B2, 3 )))
		return true;

	return false;
}

bool Intersections::LineSquareIntersection(const CU::Vector2f& B1,const CU::Vector2f& B2,const CU::Vector2f& L1,const CU::Vector2f& L2, CU::Vector2f &Hit)
{
	if (L2.myX < B1.myX && L1.myX < B1.myX) return false;
	if (L2.myX > B2.myX && L1.myX > B2.myX) return false;
	if (L2.myY < B1.myY && L1.myY < B1.myY) return false;
	if (L2.myY > B2.myY && L1.myY > B2.myY) return false;
	if (L1.myX > B1.myX && L1.myX < B2.myX &&
		L1.myY > B1.myY && L1.myY < B2.myY) 
	{Hit = L1; 
	return true;}
	if ( (GetIntersection2D( L1.myX-B1.myX, L2.myX-B1.myX, L1, L2, Hit) && InBox2D( Hit, B1, B2, 1 ))
		|| (GetIntersection2D( L1.myY-B1.myY, L2.myY-B1.myY, L1, L2, Hit) && InBox2D( Hit, B1, B2, 2 ))
		|| (GetIntersection2D( L1.myX-B2.myX, L2.myX-B2.myX, L1, L2, Hit) && InBox2D( Hit, B1, B2, 1 )) 
		|| (GetIntersection2D( L1.myY-B2.myY, L2.myY-B2.myY, L1, L2, Hit) && InBox2D( Hit, B1, B2, 2 )))
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

bool Intersections::RaySphereIntersection( CU::Vector3f aPoint, CU::Vector3f aDirection, CU::Vector3f aCenterPos, float aRadius)
{
	CU::Vector3f pontToSphere = aCenterPos - aPoint;	
	float s = pontToSphere.Dot(aDirection);
	float l2 = pontToSphere.Dot(pontToSphere);
	float r2 = (aRadius*aRadius);
	
	if(s < 0 && l2 > r2 )
	{
		return false;
	}

	float m2 = l2-(s*s);
	if(m2 > r2)
	{
		return false;
	}

	return true;

}

bool Intersections::LineSphereIntersection( CU::Vector3f aPoint, CU::Vector3f aDirection, CU::Vector3f aCenterPos, float aRadius, CU::Vector3f& aHit)
{
	CU::Vector3f d = aDirection;
	d.Normalize();
	CU::Vector3f pontToSphere = aCenterPos - aPoint;	
	float s = pontToSphere.Dot(d);
	float l2 = pontToSphere.Dot(pontToSphere);
	float r2 = (aRadius*aRadius);

	if(s < 0 && l2 > r2 )
	{
		return false;
	}

	float m2 = l2-(s*s);
	if(m2 > r2)
	{
		return false;
	}

	float q = sqrt(r2-m2);
	float t = 0;

	if(l2 > r2)
	{
		t = s-q;
	}
	else
	{
		t = s+q;
	}

	CU::Vector3f length = aDirection - aPoint;

	if(t > length.Length())
	{
		return false;
	}

	aHit = aPoint + (d*t);

	return true;

}





bool Intersections::PointTriangleIntersect(CU::Vector2f aPoint, CU::Vector2f aTrianglePoint1, CU::Vector2f aTrianglePoint2, CU::Vector2f aTrianglePoint3 )
{
	//warning not tested thouroughly, seems to work though.
	bool isInside = true;

	CU::Vector2f p1ToP2 = aTrianglePoint2 - aTrianglePoint1;
	CU::Vector2f p1ToP3 = aTrianglePoint3 - aTrianglePoint1;
	CU::Vector2f p1ToCheckPoint = aPoint - aTrianglePoint1;
	float toCheckDot = p1ToP2.Dot(p1ToCheckPoint);
	float toReferenceDot = p1ToP2.Dot(p1ToP3);
	if (toCheckDot > toReferenceDot)
	{
		isInside = false;
	}


	CU::Vector2f p2ToP1 = aTrianglePoint1 - aTrianglePoint2;
	CU::Vector2f p2ToP3 = aTrianglePoint3 - aTrianglePoint2;
	CU::Vector2f p2ToCheckPoint = aPoint - aTrianglePoint2;
	toCheckDot = p2ToP3.Dot(p1ToCheckPoint);
	toReferenceDot = p2ToP3.Dot(p2ToP1);
	if (toCheckDot > toReferenceDot)
	{
		isInside = false;
	}

	CU::Vector2f p3ToP1 = aTrianglePoint1 - aTrianglePoint3;
	CU::Vector2f p3ToP2 = aTrianglePoint2 - aTrianglePoint3;
	CU::Vector2f p3ToCheckPoint = aPoint - aTrianglePoint3;
	toCheckDot = p3ToP1.Dot(p1ToCheckPoint);
	toReferenceDot = p3ToP1.Dot(p3ToP2);
	if (toCheckDot > toReferenceDot)
	{
		isInside = false;
	}
	
	return isInside;

}


bool Intersections::TriangleIsInsideSquare(CU::Vector2f aTrianglePoint1, CU::Vector2f aTrianglePoint2, CU::Vector2f aTrianglePoint3, CU::Vector2f asquarePos1, CU::Vector2f asquarePos2)
{
	CU::Vector2f temp1;
	CU::Vector2f temp2;
	CU::Vector2f temp3;
	temp1.myX = Convert::AweRound(aTrianglePoint1.myX);
	temp1.myY = Convert::AweRound(aTrianglePoint1.myY);
	temp2.myX = Convert::AweRound(aTrianglePoint2.myX);
	temp2.myY = Convert::AweRound(aTrianglePoint2.myY);
	temp3.myX = Convert::AweRound(aTrianglePoint3.myX);
	temp3.myY = Convert::AweRound(aTrianglePoint3.myY);


	if (PointInSquare(temp1, asquarePos1, asquarePos2) == true &&
		PointInSquare(temp2, asquarePos1, asquarePos2) == true &&
		PointInSquare(temp3, asquarePos1, asquarePos2) == true)
	{
		return true;
	}
	return false;

	
}

bool Intersections::PointInSquare(CU::Vector2f aPoint, CU::Vector2f aSquarePos1, CU::Vector2f aSquarePos2)
{
	CU::Vector2f temp1;
	CU::Vector2f temp2;
	CU::Vector2f temp3;

	temp1.myX = Convert::AweRound(aPoint.myX);
	temp1.myY = Convert::AweRound(aPoint.myY);

	temp2.myX = Convert::AweRound(aSquarePos1.myX);
	temp2.myY = Convert::AweRound(aSquarePos1.myY);

	temp3.myX = Convert::AweRound(aSquarePos2.myX);
	temp3.myY = Convert::AweRound(aSquarePos2.myY);

	if(temp1.myX < temp2.myX || temp1.myX > temp3.myX) return false;
	if(temp1.myY < temp2.myY || temp1.myY > temp3.myY) return false;
	return true;

}

bool Intersections::PointInSquareWarpInclusive(CU::Vector2f aPoint, CU::Vector2f aSquarePos1, CU::Vector2f aSquarePos2)
{
	CU::Vector2f temp1;
	CU::Vector2f temp2;
	CU::Vector2f temp3;

	temp1.myX = aPoint.myX;
	temp1.myY = aPoint.myY;


	if(aSquarePos1.myX > aSquarePos2.myX)
	{
		temp2.myX = aSquarePos2.myX;
		temp3.myX = aSquarePos1.myX;


	}
	else
	{
		temp2.myX = aSquarePos1.myX;
		temp3.myX = aSquarePos2.myX;

	}

	if(aSquarePos1.myY > aSquarePos2.myY)
	{
		temp2.myY = aSquarePos2.myY;
		temp3.myY = aSquarePos1.myY;


	}
	else
	{
		temp2.myY = aSquarePos1.myY;
		temp3.myY = aSquarePos2.myY;

	}



	if(temp1.myX < temp2.myX || temp1.myX > temp3.myX) return false;
	if(temp1.myY < temp2.myY || temp1.myY > temp3.myY) return false;
	return true;

}

bool Intersections::CircleInSquare(CU::Vector2f aCirclePoint,float aRadius, CU::Vector2f aSquarePos1, CU::Vector2f aSquarePos2)
{
	if(aCirclePoint.myX < aSquarePos1.myX + aRadius || aCirclePoint.myX > aSquarePos2.myX - aRadius) return false;
	if(aCirclePoint.myY < aSquarePos1.myY + aRadius || aCirclePoint.myY > aSquarePos2.myY - aRadius) return false;
	return true;
}

bool Intersections::RayPlaneIntersection( CU::Vector3f& aReturnPoint, CU::Vector3f aStartPoint, CU::Vector3f aEndPoint, CU::Vector3f aPlane,  CU::Vector3f aNormal)
{
	CU::Vector3f u = aEndPoint - aStartPoint;
	CU::Vector3f w = aStartPoint - aPlane;

	float D = aNormal.Dot(u);
	float N = -aNormal.Dot(w);

	/*if (fabs(D) < SMALL_NUM) {          // segment is parallel to plane
		if (N == 0)                     // segment lies in plane
			return 2;
		else
			return 0;                   // no intersection
	}*/
	// they are not parallel
	// compute intersect param
	float sI = N / D;
	if (sI < 0 || sI > 1)
	{
		return false;  
	}// no intersection

	aReturnPoint = aStartPoint + u * sI;                 // compute segment intersect point
	return true;
}

bool Intersections::martinPointTriInterSect(CU::Vector2f aPoint, CU::Vector2f aTrianglePoint1, CU::Vector2f aTrianglePoint2, CU::Vector2f aTrianglePoint3 )
{
	if(SameSide(aPoint, aTrianglePoint1, aTrianglePoint2, aTrianglePoint3) == false) return false;
	if(SameSide(aPoint, aTrianglePoint2, aTrianglePoint1, aTrianglePoint3) == false) return false;
	if(SameSide(aPoint, aTrianglePoint3, aTrianglePoint1, aTrianglePoint2) == false) return false;
	
	return true;
}

bool Intersections::SameSide(const CU::Vector2f& aPoint1, const CU::Vector2f& aPoint2, const CU::Vector2f& aPoint3, const CU::Vector2f& aPoint4)
{
	CU::Vector2f vec1 = aPoint4 - aPoint3;
	CU::Vector2f vec2(vec1);

	float dot1 = vec1.DotPerd(aPoint1 - aPoint3);
	float dot2 = vec2.DotPerd(aPoint2 - aPoint3);

	if( (dot1 >= 0.0f && dot2 >= 0.0f) || (dot1 < 0.0f && dot2 < 0.0f) )
		return true;

	return false;
}

bool Intersections::LineLineIntersection(const CU::Vector2f& aLineStart,const CU::Vector2f& aLineEnd,const CU::Vector2f& aSecondLineStart,const CU::Vector2f& aSecondLineEnd,CU::Vector2f& anIntersectionPoint)
{
	CU::Vector2f kDiff = aSecondLineStart - aLineStart;
	CU::Vector2f myDir = aSecondLineEnd - aSecondLineStart;
	CU::Vector2f lineDir = aLineEnd - aLineStart;

	float fD0DotPerpD1 = lineDir.DotPerd(myDir);
	if (abs(fD0DotPerpD1) > 0.001f)
	{
		// lines intersect in a single point
		float fInvD0DotPerpD1 = (1.0f)/fD0DotPerpD1;
		float fDiffDotPerpD0 = kDiff.DotPerd(lineDir);
		float fDiffDotPerpD1 = kDiff.DotPerd(myDir);
		float as[2];
		as[0]= fDiffDotPerpD0*fInvD0DotPerpD1;
		as[1]= fDiffDotPerpD1*fInvD0DotPerpD1;
		if((as[0]<0) || (as[0]>1)) return(false); 
		if((as[1]<0) || (as[1]>1)) return(false); 
		anIntersectionPoint=aSecondLineStart+myDir*as[0];
		return true;
	}
	return false;
}

bool Intersections::LineTriangleIntersection(CU::Vector2f aLineStart,CU::Vector2f aLineEnd,CU::Vector2f aTrianglePoint1, CU::Vector2f aTrianglePoint2, CU::Vector2f aTrianglePoint3)
{
	if(martinPointTriInterSect(aLineStart,aTrianglePoint1,aTrianglePoint2,aTrianglePoint3) == true)
	{
		return true;
	}
	if(martinPointTriInterSect(aLineEnd,aTrianglePoint1,aTrianglePoint2,aTrianglePoint3) == true)
	{
		return true;
	}

	CU::Vector2f tempThrowAway;
	if(LineLineIntersection(aLineStart,aLineEnd,aTrianglePoint1,aTrianglePoint2,tempThrowAway) == true)
	{
		return true;
	}
	if(LineLineIntersection(aLineStart,aLineEnd,aTrianglePoint1,aTrianglePoint3,tempThrowAway) == true)
	{
		return true;
	}
	if(LineLineIntersection(aLineStart,aLineEnd,aTrianglePoint2,aTrianglePoint3,tempThrowAway) == true)
	{
		return true;
	}
	return false;
}

bool Intersections::TriangleTriangleIntersection(CU::Vector2f aTrianglePoint1, CU::Vector2f aTrianglePoint2, CU::Vector2f aTrianglePoint3,CU::Vector2f aSecondTrianglePoint1, CU::Vector2f aSecondTrianglePoint2, CU::Vector2f aSecondTrianglePoint3)
{
	if(LineTriangleIntersection(aTrianglePoint1,aTrianglePoint2,aSecondTrianglePoint1,aSecondTrianglePoint2,aSecondTrianglePoint3) == true)
	{
		return true;
	}
	if(LineTriangleIntersection(aTrianglePoint1,aTrianglePoint3,aSecondTrianglePoint1,aSecondTrianglePoint2,aSecondTrianglePoint3) == true)
	{
		return true;
	}
	if(LineTriangleIntersection(aTrianglePoint2,aTrianglePoint3,aSecondTrianglePoint1,aSecondTrianglePoint2,aSecondTrianglePoint3) == true)
	{
		return true;
	}

	return false;
}

bool Intersections::PointCircleIntersection(CU::Vector2f aPoint,CU::Vector2f aCenterPoint,float aRadius)
{
	CU::Vector2f tempVec = aPoint - aCenterPoint;
	if(tempVec.Length() < aRadius)
	{
		return true;
	}
	return false;
}

bool Intersections::LineSigmentLineSigmentIntersection( const CU::Vector2f& aLineStart,const CU::Vector2f& aLineEnd,const CU::Vector2f& aSecondLineStart,const CU::Vector2f& aSecondLineEnd,CU::Vector2f& anIntersectionPoint )
{
	const float tinyNum = 0.001f;

	float firstValue = ((aSecondLineEnd.myX - aSecondLineStart.myX) * (aLineStart.myY-aSecondLineStart.myY)) -((aSecondLineEnd.myY- aSecondLineStart.myY) * (aLineStart.myX-aSecondLineStart.myX));
	float secondValue = ((aSecondLineEnd.myY - aSecondLineStart.myY) * (aLineEnd.myX - aLineStart.myX))- ((aSecondLineEnd.myX - aSecondLineStart.myX) * (aLineEnd.myY -aLineStart.myY));
	float magicValue = firstValue/secondValue;

	if(magicValue == 0)
	{
		return false;	
	}

	float x = aLineStart.myX + magicValue *(aLineEnd.myX - aLineStart.myX);
	float y = aLineStart.myY + magicValue *(aLineEnd.myY -  aLineStart.myY);

	if (x < min(aSecondLineStart.myX, aSecondLineEnd.myX)-tinyNum || x > max(aSecondLineStart.myX, aSecondLineEnd.myX)+tinyNum ) 
	{
		return false;
	}
	if (y < min(aSecondLineStart.myY,aSecondLineEnd.myY)-tinyNum || y > max(aSecondLineStart.myY,aSecondLineEnd.myY)+tinyNum )
	{
		return false;
	}

	if (x < min(aLineStart.myX, aLineEnd.myX)-tinyNum || x > max(aLineStart.myX, aLineEnd.myX)+tinyNum ) 
	{
		return false;
	}
	if (y < min(aLineStart.myY,aLineEnd.myY)-tinyNum || y > max(aLineStart.myY, aLineEnd.myY)+tinyNum )
	{
		return false;
	}


	
	anIntersectionPoint.Set(x,y);

	return true;

}