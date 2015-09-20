#pragma once

#include "Constants.h"
#include "Vector3.h"

struct Quartenion
{
	float w;
	float x;
	float y;
	float z;

	Quartenion& operator*=(const Quartenion& other)
	{
		w = w*other.w - x*other.x - y*other.y - z*other.z;
		x = w*other.x + x*other.w + y*other.z - z*other.y;
		y = w*other.y + y*other.w + z*other.x - x*other.z;
		z = w*other.z + z*other.w + x*other.y - y*other.x;

		return *this;
	}

	/*static Quartenion FromAxisAngle(const Vector3<float>& axis, float angle)
	{
		// Convert from degrees to radians:
		angle *= Constants::PI_OVER_180;

		Quartenion quartenion;

		Vector3<float> normalizedAxis = axis.normalizedVector();
		float halfAngle = angle * 0.5f;
		float sinAngle = sinf(halfAngle);
	
		quartenion.x = normalizedAxis.x * sinAngle;
		quartenion.y = normalizedAxis.y * sinAngle;
		quartenion.z = normalizedAxis.z * sinAngle;

		quartenion.w = cosf(halfAngle);

		return quartenion;
	}

	static Quartenion FromEulerAngles(float roll, float pitch, float yaw)
	{
		Quartenion rollQuartenion = FromAxisAngle(Vector3<float>(1.0f, 0.0f, 0.0f), roll);
		Quartenion pitchQuartenion = FromAxisAngle(Vector3<float>(0.0f, 1.0f, 0.0f), pitch);
		Quartenion yawQuartenion = FromAxisAngle(Vector3<float>(0.0f, 0.0f, 1.0f), yaw);

		return yawQuartenion * pitchQuartenion * rollQuartenion;
	}*/
};

inline Quartenion operator*(Quartenion lhs, const Quartenion& rhs)
{
	return lhs *= rhs;
}

inline Vector3<float> operator*(const Quartenion& quartenion, const Vector3<float>& vector)
{
	
}