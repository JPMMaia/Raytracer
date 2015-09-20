#pragma once

#include <vector>

#include "GenericMesh.h"
#include "Model.h"
#include "Sphere.h"

class Scene
{
public:
	void Initialize(UINT maxSpheres, UINT maxGenericMeshes)
	{
		m_spheres.reserve(maxSpheres);
		m_genericMeshes.reserve(maxGenericMeshes);
	}

	bool Intersect(const Ray& ray, Point<>& intersection, Vector3<>& normal) const
	{
		// TODO

		for (UINT i = 0; i < m_spheres.size(); i++)
			if (m_spheres[i].Intersect(ray, intersection, normal))
				return true;

		for (UINT i = 0; i < m_genericMeshes.size(); i++)
			if (m_genericMeshes[i].Intersect(ray, intersection, normal))
				return true;

		return false;
	}

	void AddSphere(const Model<Sphere>& sphere)
	{
		m_spheres.push_back(sphere);
	}
	void AddGenericMesh(const Model<GenericMesh>& genericMesh)
	{
		m_genericMeshes.push_back(genericMesh);
	}

private:
	std::vector<Model<Sphere>> m_spheres;
	std::vector<Model<GenericMesh>> m_genericMeshes;
};