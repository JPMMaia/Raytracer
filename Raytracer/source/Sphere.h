#pragma once

#include "Vector3.h"
#include "Point.h"
#include "Ray.h"

struct Sphere
{
	Point<> center;
	float radius;

	Sphere();
	Sphere(const Point<>& center, float radius);

	bool Intersect(const Ray& ray, Point<>& intersection, float& distance, Vector3<>& normal) const;
};