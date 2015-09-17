#pragma once

#include <vector>

#include "Vector.h"

typedef unsigned int UINT;

class GenericMesh
{
public:
	struct Face
	{
		UINT index1, index2, index3;

		Face(UINT index1, UINT index2, UINT index3) : index1(index1), index2(index2), index3(index3) {}
	};
public:
	void Initialize(UINT maxNumVertex);
	void Shutdown();

	void AddTriangle(UINT index1, UINT index2, UINT index3);

private:
	std::vector<Vector<float>> m_vertices;
	std::vector<Face> m_indices;
};