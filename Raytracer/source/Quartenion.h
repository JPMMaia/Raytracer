#pragma once

#include "Constants.h"
#include "Vector3.h"

struct Quartenion
{
	float w;
	float x;
	float y;
	float z;

	Quartenion();
	Quartenion(float w, float x, float y, float z);

	Quartenion Conjugate() const;
	inline float Norm() const;
	inline float NormSquared() const;
	Quartenion& Normalize();
	Quartenion Inverse() const;

	Quartenion operator+(const Quartenion& other) const;
	Quartenion operator*(const Quartenion& other) const;
	Quartenion& operator+=(const Quartenion& other);
	Quartenion& operator*=(const Quartenion& other);

	Quartenion operator*(float value) const;
	Quartenion operator/(float value) const;
	Quartenion& operator*=(float value);
	Quartenion& operator/=(float value);

	static Vector3<float> Rotate(const Vector3<float>& vector, const Vector3<float>& axis, float angle);
	static Quartenion FromAxisAngle(const Vector3<float>& axis, float angle);
	static Quartenion FromEulerAngles(float roll, float pitch, float yaw);
};

inline Vector3<float> operator*(const Quartenion& quartenion, const Vector3<float>& vector);