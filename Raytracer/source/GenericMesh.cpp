#include "GenericMesh.h"

void GenericMesh::Initialize(UINT maxNumVertex)
{
	// Reserve memory for vertices:
	m_vertices.reserve(maxNumVertex);
}

void GenericMesh::Shutdown()
{
}

void GenericMesh::AddTriangle(UINT index1, UINT index2, UINT index3)
{
	m_indices.push_back(Face(index1, index2, index3));
}
