#ifndef GEOMETRY_HEADER
#define GEOMETRY_HEADER

#include "Vector2.h"

namespace CommonUtilities
{
	template <class TYPE>
	inline bool LineIntersection2D(	CU::Vector2<TYPE>   A,
									CU::Vector2<TYPE>   B,
									CU::Vector2<TYPE>   C, 
									CU::Vector2<TYPE>   D,
									TYPE&				aDist,
									CU::Vector2<TYPE>&  aPointOfIntersection)
	{
		TYPE rTop = (A.myY-C.myY)*(D.myX-C.myX)-(A.myX-C.myX)*(D.myY-C.myY);
		TYPE rBot = (B.myX-A.myX)*(D.myY-C.myY)-(B.myY-A.myY)*(D.myX-C.myX);

		TYPE sTop = (A.myY-C.myY)*(B.myX-A.myX)-(A.myX-C.myX)*(B.myY-A.myY);
		TYPE sBot = (B.myX-A.myX)*(D.myY-C.myY)-(B.myY-A.myY)*(D.myX-C.myX);

		if ( (rBot == 0) || (sBot == 0))
		{
			//lines are parallel
			return false;
		}

		TYPE r = rTop/rBot;
		TYPE s = sTop/sBot;

		if( (r > 0) && (r < 1) && (s > 0) && (s < 1) )
		{
  			//dist = Vec2DDistance(A,B) * r;
			CU::Vector2<TYPE> tmp = A - B;
			aDist = tmp.Length();
			aPointOfIntersection = A + ((B - A) * r);
			return(true);
		}
		else
		{
			aDist = 0;
			return(false);
		}	
	}
};

namespace CU = CommonUtilities;

#endif