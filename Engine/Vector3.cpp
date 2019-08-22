#include "Vector3.h"

Engine::Vector3 Engine::Vector3::getNormalized() const
{
	float tmpMag = getMagnitudeSqr();
	if (tmpMag == 0.0f)
		return Vector3(0.0f, 0.0f, 0.0f);
	else
	{
		float tmpSqrtMag = sqrtf(tmpMag);

		if (tmpSqrtMag == 0)
			return Vector3(0.0f, 0.0f, 0.0f);

		return Vector3(_x / tmpSqrtMag, _y / tmpSqrtMag, _z / tmpSqrtMag);
	}
}

