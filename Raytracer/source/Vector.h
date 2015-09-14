#pragma once

#include <math.h>

template <class T = float>
struct Vector
{
	T x;
	T y;
	T z;

	Vector<T>()
	{
	}
	Vector<T>(T x, T y, T z) : x(x), y(y), z(z)
	{
	}

	inline T dot(const Vector<T> other) const
	{
		return
			this->x * other.x +
			this->y * other.y +
			this->z * other.z;
	}

	inline void normalize()
	{
		float length = this->length();

		this->x /= length;
		this->y /= length;
		this->z /= length;
	}

	inline float length() const
	{
		return sqrtf(this->x*this->x + this->y*this->y + this->z*this->z);
	}

	inline Vector<T> operator+(const Vector<T>& other) const
	{
		return Vector<T>(
			this->x + other.x,
			this->y + other.y,
			this->z + other.z
			);
	}
};

template<class T>
inline Vector<T> operator*(float scalar, const Vector<T>& vector)
{
	return Vector<T>(
		scalar * vector.x,
		scalar * vector.y,
		scalar * vector.z
		);
}
template<class T>
inline Vector<T> operator*(const Vector<T>& vector, float scalar)
{
	return scalar * vector;
}