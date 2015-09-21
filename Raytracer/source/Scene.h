#pragma once

#include <vector>

#include "Camera.h"
#include "GenericMesh.h"
#include "Model.h"
#include "Sphere.h"

class Scene
{
public:
	void Initialize(UINT maxSpheres, UINT maxGenericMeshes);

	bool Intersect(const Ray& ray, Point<>& intersection, Vector3<>& normal, const Material*& material) const;

	void AddCamera(const Camera& camera);
	void AddSphere(const Model<Sphere>& sphere);
	void AddGenericMesh(const Model<GenericMesh>& genericMesh);
	
	Camera& GetCurrentCamera() const;
	void SetCurrentCamera(UINT index);

private:
	template<class MeshType>
	bool IntersectMeshes(const std::vector<Model<MeshType>>& meshes, const Ray& ray, Point<>& intersection, Vector3<>& normal, const Material*& material, float& minDistance) const;

private:
	std::vector<Model<Sphere>> m_spheres;
	std::vector<Model<GenericMesh>> m_genericMeshes;
	std::vector<Camera> m_cameras;
	Camera* m_currentCamera;
};

template<class MeshType>
inline bool Scene::IntersectMeshes(const std::vector<Model<MeshType>>& meshes, const Ray & ray, Point<>& intersection, Vector3<>& normal, const Material*& material, float& minDistance) const
{
	bool result = false;

	Point<> tempIntersection;
	Vector3<> tempNormal;
	float distance;
	for (UINT i = 0; i < meshes.size(); i++)
	{
		if (meshes[i].Intersect(ray, tempIntersection, distance, tempNormal))
		{
			result = true;
			if (distance < minDistance)
			{
				minDistance = distance;
				intersection = tempIntersection;
				normal = tempNormal;
				material = &meshes[i].GetMaterial();
			}
		}
	}

	return result;
}
