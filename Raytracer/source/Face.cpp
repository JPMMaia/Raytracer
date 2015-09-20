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
		return(false);

	float f = 1 / a;
	Vector3<float> s = ray.origin - this->vertex1;
	float u = f * s.dot(h);

	if (u < 0.0 || u > 1.0)
		return(false);

	Vector3<float> q = s.cross(e1);
	float v = f * ray.direction.dot(q);

	if (v < 0.0 || u + v > 1.0)
		return(false);

	// at this stage we can compute t to find out where
	// the intersection point is on the line
	distance = f * e2.dot(q);

	if (distance > 0.00001) // ray intersection
	{
		intersection = ray.origin + ray.direction * distance;
		normal = this->normal;
		return(true);
	}
		

	else // this means that there is a line intersection
		 // but not a ray intersection
		return (false);



	/*// Check if ray direction is orthogonal to face normal:
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

	return true;*/
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
