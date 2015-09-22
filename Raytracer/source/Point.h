#pragma once

#include "Vector3.h"

template <class T = float>
struct Point
{
	float x;
	float y;
	float z;

	Point<T>()
	{
	}
	Point<T>(float x, float y, float z) : x(x), y(y), z(z)
	{
	}
	~Point<T>()
	{
	}

	Point<T> operator+(const Vector3<T>& other) const
	{
		return Point<T>(
			this->x + other.x,
			this->y + other.y,
			this->z + other.z
			);
	}

	Vector3<T> operator-(const Point<T>& other) const
	{
		return Vector3<T>(
			this->x - other.x,
			this->y - other.y,
			this->z - other.z
			);
	}
};

template<class T>
Point<T> operator*(const Point<T>& point, const glm::mat4& matrix)
{
	glm::vec4 result(point.x, point.y, point.z, 1.0f);
	result = result * matrix;

	return Point<T>(result.x, result.y, result.z);
}
template<class T>
Point<T> operator*(const glm::mat4& matrix, const Point<T>& point)
{
	glm::vec4 result(point.x, point.y, point.z, 1.0f);
	result = matrix * result;

	return Point<T>(result.x, result.y, result.z);
}