#include "Face.h"

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
	Vector3<float> e1 = this->vertex2 - this->vertex1;
	Vector3<float> e2 = this->vertex3 - this->vertex1;

	Vector3<float> h = ray.direction.cross(e2);
	float a = e1.dot(h);

	if (a > -0.00001 && a < 0.00001)
		return false;

	float f = 1 / a;
	Vector3<float> s = ray.origin - this->vertex1;
	float u = f * s.dot(h);

	if (u < 0.0 || u > 1.0)
		return false;

	Vector3<float> q = s.cross(e1);
	float v = f * ray.direction.dot(q);

	if (v < 0.0 || u + v > 1.0)
		return false;

	distance = f * e2.dot(q);

	// Ray intersection:
	if (distance > 0.00001) 
	{
		intersection = ray.origin + ray.direction * distance;
		normal = this->normal;
		return true;
	}
	
	return false;
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
