#pragma once

#include <vector>

#include "Matrix2x2.h"
#include "Point.h"
#include "Ray.h"

typedef unsigned int UINT;

struct Face
{
	const Point<float>* vertex1;
	const Point<float>* vertex2;
	const Point<float>* vertex3;
	Vector3<float> normal;

	Face(const Point<float>& vertex1, const Point<float>& vertex2, const Point<float>& vertex3);

	bool Intersect(const Ray & ray, Point<>& intersection, Vector3<>& normal) const;
	
private:
	void CalculateNormal();
	void CalculateInverseMatrix();

private:
	Matrix2x2<float> m_inverseMatrix;
};