#include "StdAfx.h"
#include "Random.h"

double CommonUtilities::RandDouble(double low, double high)
{
	double temp;

	/* swap low & high around if the user makes no sense */
	if (low > high)
	{
		temp = low;
		low = high;
		high = temp;
	}

	/* calculate the random number & return it */
	temp = (rand() / (static_cast<double>(RAND_MAX) + 1.0))
		* (high - low) + low;
	return temp;
}

float CommonUtilities::RandFloat(float low, float high)
{
	float temp;

	/* swap low & high around if the user makes no sense */
	if (low > high)
	{
		temp = low;
		low = high;
		high = temp;
	}

	/* calculate the random number & return it */
	temp = (rand() / (static_cast<float>(RAND_MAX) + 1.0f))
		* (high - low) + low;
	return temp;
}