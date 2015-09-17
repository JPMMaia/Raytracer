#pragma once

#include "Vector.h"
#include "Point.h"
#include "Ray.h"

struct Sphere
{
	Point<> center;
	float radius;

	Sphere();
	Sphere(const Point<>& center, float radius);

	bool Intersect(const Ray& ray, Point<>& intersection, Vector<>& normal) const;
};