#include "Scene.h"

void Scene::Initialize(UINT maxSpheres, UINT maxGenericMeshes)
{
	m_spheres.reserve(maxSpheres);
	m_genericMeshes.reserve(maxGenericMeshes);
}

bool Scene::Intersect(const Ray & ray, Point<>& intersection, Vector3<>& normal, const Material*& material) const
{
	bool result = false;

	float minDistance = std::numeric_limits<float>::max();

	result |= IntersectMeshes<Sphere>(m_spheres, ray, intersection, normal, material, minDistance);
	result |= IntersectMeshes<GenericMesh>(m_genericMeshes, ray, intersection, normal, material, minDistance);

	return result;
}

void Scene::AddSphere(const Model<Sphere>& sphere)
{
	m_spheres.push_back(sphere);
}

void Scene::AddGenericMesh(const Model<GenericMesh>& genericMesh)
{
	m_genericMeshes.push_back(genericMesh);
}