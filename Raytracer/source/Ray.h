#pragma once

#include "Point.h"
#include "Vector3.h"

struct Ray
{
	Point<> origin;
	Vector3<> direction;

	Ray()
	{
	}
	Ray(const Point<>& origin, const Vector3<>& direction) : origin(origin), direction(direction)
	{
	}
};