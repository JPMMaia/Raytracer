#include "GenericMesh.h"

void GenericMesh::Initialize(std::vector<Point<float>>& vertices, std::vector<UINT>& indices)
{
	m_vertices.swap(vertices);

	UINT numFaces = indices.size() / 3;
	m_faces.reserve(numFaces);
	UINT indicesIndex = 0;
	for (UINT i = 0; i < numFaces; i++)
	{
		m_faces.push_back(
			Face(
				m_vertices[indices[indicesIndex++]],
				m_vertices[indices[indicesIndex++]],
				m_vertices[indices[indicesIndex++]]
				)
			);
	}
}

bool GenericMesh::Intersect(const Ray & ray, Point<float>& intersection, Vector3<float>& normal) const
{
	// If the ray intersects any of the faces, return true:
	for (UINT i = 0; i < m_faces.size(); i++)
	{
		if (m_faces[i].Intersect(ray, intersection, normal))
			return true;
	}

	return false;
}
