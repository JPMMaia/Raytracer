#pragma once

#include "Vector.h"

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

	Point<T> operator+(const Vector<T>& other) const
	{
		return Point<T>(
			this->x + other.x,
			this->y + other.y,
			this->z + other.z
			);
	}

	Vector<T> operator-(const Point<T>& other) const
	{
		return Vector<T>(
			this->x - other.x,
			this->y - other.y,
			this->z - other.z
			);
	}
};