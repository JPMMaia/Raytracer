#pragma once

#include <glm\matrix.hpp>
#include <math.h>

#include "Vector2.h"

template <class T = float>
struct Vector3
{
	T x;
	T y;
	T z;

	Vector3<T>()
	{
	}
	Vector3<T>(T x, T y, T z) : x(x), y(y), z(z)
	{
	}

	inline T dot(const Vector3<T> other) const
	{
		return
			this->x * other.x +
			this->y * other.y +
			this->z * other.z;
	}

	inline Vector3<T> cross(const Vector3<T> other) const
	{
		/*
		i	j	k
		vx1	vy1	vz1
		vx2	vy2	vz2
		*/

		return Vector3<T>(
			this->y * other.z - this->z * other.y,
			this->z * other.x - this->x * other.z,
			this->x * other.y - this->y * other.x
			);
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

	inline Vector3<T> normalizedVector() const
	{
		float length = this->length();

		return Vector3<T>(
			this->x / length,
			this->y / length,
			this->z / length
			);
	}

	inline Vector3<T> operator+(const Vector3<T>& other) const
	{
		return Vector3<T>(
			this->x + other.x,
			this->y + other.y,
			this->z + other.z
			);
	}

	inline Vector3<T> operator-() const
	{
		return Vector3<T>(
			-this->x,
			-this->y,
			-this->z
			);
	}
};

template<class T>
inline Vector3<T> operator*(float scalar, const Vector3<T>& vector)
{
	return Vector3<T>(
		scalar * vector.x,
		scalar * vector.y,
		scalar * vector.z
		);
}
template<class T>
inline Vector3<T> operator*(const Vector3<T>& vector, float scalar)
{
	return scalar * vector;
}

template<class T>
Vector3<T> operator*(const Vector3<T>& vector, const glm::mat4& matrix)
{
	glm::vec4 result(vector.x, vector.y, vector.z, 0.0f);
	result = result * matrix;

	return Vector3<T>(result.x, result.y, result.z);
}
template<class T>
Vector3<T> operator*(const glm::mat4& matrix, const Vector3<T>& vector)
{
	glm::vec4 result(vector.x, vector.y, vector.z, 0.0f);
	result = matrix * result;

	return Vector3<T>(result.x, result.y, result.z);
}