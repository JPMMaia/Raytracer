#pragma once

#include "Point.h"
#include "Ray.h"

struct Sphere
{
	Point<> center;
	float radius;


	Sphere(const Point<>& center, float radius);

	bool Intersect(const Ray& ray);
};