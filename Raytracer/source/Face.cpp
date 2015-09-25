#include "Face.h"
#include "Utils.h"

Face::Face(const Point<float>& vertex1, const Point<float>& vertex2, const Point<float>& vertex3)
	:
	vertex1(vertex1),
	vertex2(vertex2),
	vertex3(vertex3)
{
	CalculateNormal();
	CalculateInverseMatrix();
}

bool Face::Intersect(const Ray& ray, Point<float>& intersection, float& distance, Vector3<float>& normal) const
{	
	// If the ray is in the same plane as the triangle, consider that they don't intersect:
	float rayDotNormal = ray.direction.dot(this->normal);
	if (-0.00001f < rayDotNormal && rayDotNormal < 0.00001f)
		return false;

	// Calculate distance from the origin of the ray to the intersection with the plane of the triangle:
	distance = (this->vertex1 - ray.origin).dot(this->normal) / rayDotNormal;

	// If the distance is negative, then the triangle is in the oposite direction of the ray direction:
	if (distance < 0.00001f)
		return false;

	// Calculate the intersection of the ray and the plane of the triangle:
	intersection = ray.origin + distance * ray.direction;
	
	// Check if the intersection point is inside the triangle:

	Vector3<float> edge1 = this->vertex2 - this->vertex1;
	Vector3<float> cross1 = edge1.cross(intersection - this->vertex1);
	if (cross1.dot(this->normal) < 0.0f)
		return false;

	Vector3<float> edge2 = this->vertex3 - this->vertex2;
	Vector3<float> cross2 = edge2.cross(intersection - this->vertex2);
	if (cross2.dot(this->normal) < 0.0f)
		return false;

	Vector3<float> edge3 = this->vertex1 - this->vertex3;
	Vector3<float> cross3 = edge3.cross(intersection - this->vertex3);
	if (cross3.dot(this->normal) < 0.0f)
		return false;
	
	normal = this->normal;

	return true;
}

void Face::CalculateNormal()
{
	this->normal = (this->vertex2 - this->vertex1).cross(this->vertex3 - this->vertex1);
	this->normal.normalize();
}

void Face::CalculateInverseMatrix()
{
	float v00 = this->vertex2.x - this->vertex1.x;
	float v01 = this->vertex3.x - this->vertex1.x;
	float v10 = this->vertex2.y - this->vertex1.y;
	float v11 = this->vertex3.y - this->vertex1.y;

	m_inverseMatrix = Matrix2x2<float>(v00, v01, v10, v11).Inverse();
}
