#pragma once

#include <vector>

#include "Face.h"
#include "Point.h"
#include "Ray.h"

class GenericMesh
{
public:
	void Initialize(const std::vector<Point<float>>& vertices, const std::vector<UINT>& indices);

	bool Intersect(const Ray& ray, Point<float>& intersection, float& distance, Vector3<float>& normal) const;

private:
	std::vector<Face> m_faces;
};