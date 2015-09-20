#pragma once

#include <vector>

#include "Face.h"
#include "Point.h"
#include "Ray.h"

class GenericMesh
{
public:
	void Initialize(std::vector<Point<float>>& vertices, std::vector<UINT>& indices);

	bool Intersect(const Ray& ray, Point<float>& intersection, Vector3<float>& normal) const;

private:
	std::vector<Point<float>> m_vertices;
	std::vector<Face> m_faces;
};