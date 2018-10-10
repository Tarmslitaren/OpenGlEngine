#pragma once
#ifndef COMMONMACROS_HEADER
#define COMMONMACROS_HEADER
#include <sstream>
namespace CommonUtilities
{
	constexpr float PI = 3.14159265f;

	namespace Macros
	{
		#define MIN(a,b)  ((a) < (b) ? (a) : (b))
		#define MAX(a,b)  ((a) > (b) ? (a) : (b))
		#define RANDBETWEEN(min,max) min+rand()%(max-min)


		#ifndef SAFE_DELETE
		#define SAFE_DELETE(a) if (a!=NULL) {delete (a); a=NULL; }
		#define SAFE_DELETE_ARRAY(a) delete [] (a); a=NULL;
		#endif
		#ifndef SAFE_RELEASE
		#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
		#endif



	};

	constexpr int     MaxInt = (std::numeric_limits<int>::max)();
	constexpr double  MaxDouble = (std::numeric_limits<double>::max)();
	constexpr double  MinDouble = (std::numeric_limits<double>::min)();
	constexpr float   MaxFloat = (std::numeric_limits<float>::max)();
	constexpr float   MinFloat = (std::numeric_limits<float>::min)();




	template <typename T>
	_inline std::string ConvertToString(const T& t) { std::stringstream ss; ss << t; return(ss.str()); }

	template <class T, class U, class V>
	inline void Clamp(T& arg, const U& minVal, const V& maxVal)
	{
		assert(((double)minVal < (double)maxVal) && "<Clamp>MaxVal < MinVal!");

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

namespace CU = CommonUtilities;

#endif
