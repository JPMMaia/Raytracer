#pragma once

#include "Point.h"
#include "Vector.h"

struct Ray
{
	Point<> origin;
	Vector<> direction;

	Ray(const Point<>& origin, const Vector<>& direction) : origin(origin), direction(direction)
	{
	}
};