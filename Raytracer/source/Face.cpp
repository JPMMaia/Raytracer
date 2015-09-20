#include "Face.h"

Face::Face(const Point<float>& vertex1, const Point<float>& vertex2, const Point<float>& vertex3)
	:
	vertex1(&vertex1),
	vertex2(&vertex2),
	vertex3(&vertex3)
{
	CalculateNormal();
	CalculateInverseMatrix();
}

bool Face::Intersect(const Ray& ray, Point<float>& intersection, Vector3<float>& normal) const
{
	// Check if ray direction is orthogonal to face normal:
	float directionDotNormal = ray.direction.dot(this->normal);
	if (directionDotNormal == 0.0f)
		return false;

	// Check intersection with triangle plane:
	float t = (*this->vertex1 - ray.origin).dot(this->normal) / directionDotNormal;

	// Calculate intersection point:
	intersection = ray.origin + ray.direction * t;

	Vector2<float> p = Vector2<float>(intersection.x - this->vertex1->x, intersection.y - this->vertex1->y);
	Vector2<float> lambda = m_inverseMatrix * p;

	if (lambda.x < 0.0f || lambda.x > 1.0f)
		return false;

	if (lambda.y < 0.0f || lambda.y > 1.0f)
		return false;

	normal = this->normal;

	return true;
}

void Face::CalculateNormal()
{
	this->normal = (*this->vertex2 - *this->vertex1).cross(*this->vertex3 - *this->vertex1);
	this->normal.normalize();
}

void Face::CalculateInverseMatrix()
{
	float v00 = this->vertex2->x - this->vertex1->x;
	float v01 = this->vertex3->x - this->vertex1->x;
	float v10 = this->vertex2->y - this->vertex1->y;
	float v11 = this->vertex3->y - this->vertex1->y;

	m_inverseMatrix = Matrix2x2<float>(v00, v01, v10, v11).Inverse();
}
