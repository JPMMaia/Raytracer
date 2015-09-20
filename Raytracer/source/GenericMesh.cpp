#include "GenericMesh.h"

void GenericMesh::Initialize(const std::vector<Point<float>>& vertices, const std::vector<UINT>& indices)
{
	UINT numFaces = indices.size() / 3;
	m_faces.reserve(numFaces);
	UINT indicesIndex = 0;
	for (UINT i = 0; i < numFaces; i++)
	{
		m_faces.push_back(
			Face(
				vertices[indices[indicesIndex++]],
				vertices[indices[indicesIndex++]],
				vertices[indices[indicesIndex++]]
				)
			);
	}
}

bool GenericMesh::Intersect(const Ray & ray, Point<float>& intersection, float& distance, Vector3<float>& normal) const
{
	// If the ray intersects any of the faces, return true:
	for (UINT i = 0; i < m_faces.size(); i++)
	{
		if (m_faces[i].Intersect(ray, intersection, distance, normal))
			return true;
	}

	return false;
}
