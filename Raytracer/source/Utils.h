#pragma once

#include <limits>
#include <math.h>

namespace Utils
{
	bool AreNearlyEqual(float a, float b, float epsilon)
	{
		float absA = fabs(a);
		float absB = fabs(b);
		float difference = fabs(a - b);

		// Handle infinity:
		if (a == b)
			return true;

		// A or B is 0, or both are extremely close to it:
		else if (a == 0.0f || b == 0.0f || difference < std::numeric_limits<float>::denorm_min())
			return difference < (epsilon * std::numeric_limits<float>::denorm_min());

		// Use relative error:
		return difference / fmin((absA + absB), std::numeric_limits<float>::max()) < epsilon;
	}
}