#ifndef RANDOMIZER_HEADER
#define RANDOMIZER_HEADER

#include <iostream>

namespace CommonUtilities
{
	namespace Randomizer
	{
		double randDouble(double low, double high)
		{
			/*double temp;

			if (low > high)
			{
				temp = low;
				low = high;
				high = temp;
			}

			temp = (rand() / (static_cast<double>(RAND_MAX) + 1.0)) * (high - low) + low;
			return temp;*/

			return (rand() / (static_cast<double>(RAND_MAX) + 1.0)) * (high - low) + low;
		}

		float randFloat(float low, float high)
		{
			/*float temp;

			if (low > high)
			{
				temp = low;
				low = high;
				high = temp;
			}

			temp = static_cast<float>((rand() / (static_cast<float>(RAND_MAX) + 1.0)) * (high - low) + low);
			return temp;*/

			return static_cast<float>((rand() / (static_cast<float>(RAND_MAX) + 1.0)) * (high - low) + low);
		}

		inline float RandomFloatClamped()
		{
			return(randFloat(0.0f,1.0f) - randFloat(0.0f,1.0f));
		}
	};
};

#endif