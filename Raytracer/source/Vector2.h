#pragma once

#include <math.h>

template <class T = float>
struct Vector2
{
	T x;
	T y;

	Vector2<T>()
	{
	}
	Vector2<T>(T x, T y) : x(x), y(y)
	{
	}

	inline T dot(const Vector2<T> other) const
	{
		return
			this->x * other.x +
			this->y * other.y;
	}

	inline void normalize()
	{
		float length = this->length();

		this->x /= length;
		this->y /= length;
	}

	inline float length() const
	{
		return sqrtf(this->x*this->x + this->y*this->y);
	}

	inline Vector2<T> normalizedVector() const
	{
		float length = this->length();

		return Vector2<T>(
			this->x / length,
			this->y / length
			);
	}

	inline Vector2<T> operator+(const Vector2<T>& other) const
	{
		return Vector2<T>(
			this->x + other.x,
			this->y + other.y
			);
	}
};

template<class T>
inline Vector2<T> operator*(float scalar, const Vector2<T>& vector)
{
	return Vector2<T>(
		scalar * vector.x,
		scalar * vector.y
		);
}
template<class T>
inline Vector2<T> operator*(const Vector2<T>& vector, float scalar)
{
	return scalar * vector;
}