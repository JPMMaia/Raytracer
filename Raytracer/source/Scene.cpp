#include "Scene.h"

void Scene::Initialize(UINT maxSpheres, UINT maxGenericMeshes)
{
	m_spheres.reserve(maxSpheres);
	m_genericMeshes.reserve(maxGenericMeshes);

	// Setup a default camera:
	Camera camera;
	camera.Initialize(Point<>(0.0f, 0.0f, 4.0f), Point<>(0.0f, 0.0f, -1.0f), Vector3<>(0.0f, 1.0f, 0.0f));
	AddCamera(camera);
	SetCurrentCamera(0);
}

bool Scene::Intersect(const Ray & ray, Point<>& intersection, Vector3<>& normal, const Material*& material) const
{
	bool result = false;

	float minDistance = std::numeric_limits<float>::max();

	result |= IntersectMeshes<Sphere>(m_spheres, ray, intersection, normal, material, minDistance);
	result |= IntersectMeshes<GenericMesh>(m_genericMeshes, ray, intersection, normal, material, minDistance);

	return result;
}

void Scene::AddCamera(const Camera& camera)
{
	m_cameras.push_back(camera);
}

void Scene::AddSphere(const Model<Sphere>& sphere)
{
	m_spheres.push_back(sphere);
}

void Scene::AddGenericMesh(const Model<GenericMesh>& genericMesh)
{
	m_genericMeshes.push_back(genericMesh);
}

Camera& Scene::GetCurrentCamera() const
{
	return *m_currentCamera;
}
void Scene::SetCurrentCamera(UINT index)
{
	m_currentCamera = &m_cameras[index];
}
