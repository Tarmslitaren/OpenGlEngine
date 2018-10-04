#ifndef COMMONMACROS_HEADER
#define COMMONMACROS_HEADER

#include <sstream>
#include <assert.h>
#include <limits>

namespace CommonUtilities
{
	namespace Macros
	{
		const int     MaxInt    = (std::numeric_limits<int>::max)();
		const double  MaxDouble = (std::numeric_limits<double>::max)();
		const double  MinDouble = (std::numeric_limits<double>::min)();
		const float   MaxFloat  = (std::numeric_limits<float>::max)();
		const float   MinFloat  = (std::numeric_limits<float>::min)();

		#define PI 3.141592653f

		#define MIN(a,b)  ((a) < (b) ? (a) : (b))
		#define MAX(a,b)  ((a) > (b) ? (a) : (b))

		#define SAFE_DELETE(a) if (a!=NULL) {delete (a); a=NULL; }
		#define SAFE_DELETE_ARRAY(a) delete [] (a); a=NULL;

		#define RANDBETWEEN(min,max) min+rand()%(max-min)

		#define DEGREETORADIAN(a) (a/180.0) * PI
		#define RADIANTODEGREE(a) (a*(180/PI))

		template <typename T>
		_inline std::string ConvertToString(const T& t){std::stringstream ss; ss << t; return(ss.str());}

		template <class T, class U, class V>
		inline void Clamp(T& arg, const U& minVal, const V& maxVal)
		{
			assert ( ((double)minVal < (double)maxVal) && "<Clamp>MaxVal < MinVal!");

			if (arg < (T)minVal)
			{
				arg = (T)minVal;
			}

			if (arg > (T)maxVal)
			{
				arg = (T)maxVal;
			}
}
	};
};

namespace CU = CommonUtilities;

#endif
