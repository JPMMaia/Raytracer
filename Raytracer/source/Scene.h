#pragma once

#include <vector>

#include "Camera.h"
#include "GenericMesh.h"
#include "Light.h"
#include "Model.h"
#include "Sphere.h"

class Scene
{
public:
	void Initialize(UINT maxSpheres, UINT maxGenericMeshes, UINT maxReflectionDepth = 5);

	bool CalculateColor(const Ray& ray, Point<float> cameraPosition, Color<float>& color) const;

	void AddCamera(const Camera& camera);
	void AddSphere(const Model<Sphere>& sphere);
	void AddGenericMesh(const Model<GenericMesh>& genericMesh);
	void AddLight(const Light& light);
	
	Camera& GetCurrentCamera() const;
	void SetCurrentCamera(UINT index);
	void SetMaxReflectionDepth(UINT maxReflectionDepth);

private:
	bool FindNearestIntersection(const Ray& ray, Point<float>& intersection, Vector3<float>& normal, const Material*& material) const;	
	void Scene::CalculateLight(const Point<float>& cameraPosition, const Point<float>& intersection, const Vector3<float>& normal, const Material& material, Color<float>& color) const;
	bool IsLightUnblocked(const Light& light, const Point<float>& point) const;

	template<class MeshType>
	bool IntersectMeshes(const std::vector<Model<MeshType>>& meshes, const Ray& ray, Point<>& intersection, Vector3<>& normal, const Material*& material, float& minDistance) const;

	template<class MeshType>
	bool IsLightUnblocked(const std::vector<Model<MeshType>>& meshes, const Light& light, float lightDistance, const Ray& ray) const;

	void CalculateReflection(const Ray& ray, const Point<float>& cameraPosition, const Point<float>& intersection, const Vector3<float>& normal, const Material& material, Color<float>& color, UINT depth) const;

private:
	std::vector<Model<Sphere>> m_spheres;
	std::vector<Model<GenericMesh>> m_genericMeshes;
	std::vector<Camera> m_cameras;
	std::vector<Light> m_lights;
	Camera* m_currentCamera;
	UINT m_maxReflectionDepth;
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

template<class MeshType>
inline bool Scene::IsLightUnblocked(const std::vector<Model<MeshType>>& meshes, const Light& light, float lightDistance, const Ray& ray) const
{
	float distance;
	Point<float> tempPoint;
	Vector3<float> tempVector;
	for (UINT i = 0; i < meshes.size(); i++)
	{
		// If there is an intersection:
		if (meshes[i].Intersect(ray, tempPoint, distance, tempVector))
		{
			// If there is an object between the light and the intersection:
			if (distance < lightDistance)
				return false;
		}
	}

	return true;
}