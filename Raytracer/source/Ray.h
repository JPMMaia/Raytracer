#pragma once

#include "Point.h"
#include "Vector.h"

struct Ray
{
	Point<> origin;
	Vector<> direction;

	Ray()
	{
	}
	Ray(const Point<>& origin, const Vector<>& direction) : origin(origin), direction(direction)
	{
	}
};