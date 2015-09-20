#include <math.h>

#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::Sphere(const Point<> & center, float radius) : center(center), radius(radius)
{
}

bool Sphere::Intersect(const Ray& ray, Point<>& intersection, float& distance, Vector3<>& normal) const
{
	// O - C:
	Vector3<> centerOriginVector = ray.origin - this->center;

	// a = D . D:
	float a = ray.direction.dot(ray.direction);
	
	// b = 2D . (O - C):
	float b = 2.0f * ray.direction.dot(centerOriginVector);

	// c = (O - C) . (O - C) - r^2:
	float c = centerOriginVector.dot(centerOriginVector) - this->radius*this->radius;

	// Calculate delta (b^2 - 4ac):
	float delta = b*b - 4*a*c;

	// There isn't any real solution, therefore there isn't any intersection:
	if (delta < 0.0f)
		return false;

	// Find the smallest solution t:
	float t1 = (-b + sqrtf(delta)) / (2 * a);
	float t2 = (-b - sqrtf(delta)) / (2 * a);
	distance = fminf(t1, t2);

	// Find the point of intersection between the ray and the sphere:
	intersection = ray.origin + distance * ray.direction;

	// Calculate normal vector at the intersection:
	normal = intersection - this->center;

	return true;
}