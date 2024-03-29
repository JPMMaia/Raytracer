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

bool Scene::CalculateColor(const Ray& ray, Point<float> cameraPosition, Color<float>& color, UINT depth) const
{
	color = Color<float>(0.0f, 0.0f, 0.0f, 1.0f);

	// Find the nearest object to the camera:
	Point<float> intersection;
	Vector3<float> normal;
	const Material* material;
	if (!FindNearestIntersection(ray, intersection, normal, material))
		return false;

	// Add ambient and emission colors:
	color = material->ambientColor + material->emissionColor;

	// Calculate color from lights:
	Color<float> lightColor;
	CalculateLight(cameraPosition, intersection, normal, *material, lightColor);

	color = color + lightColor;

	// Add reflection:
	if (depth > 0)
	{
		Ray reflectionRay;
		reflectionRay.direction = ray.direction - (2.0f * ray.direction.dot(normal) * normal);
		reflectionRay.direction.normalize();
		reflectionRay.origin = intersection + reflectionRay.direction * 0.0001f;

		Color<float> reflectionColor;
		CalculateColor(reflectionRay, intersection, reflectionColor, depth - 1);
		color = color + (material->specularColor * reflectionColor);
	}

	return  true;
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
void Scene::AddLight(const Light& light)
{
	m_lights.push_back(light);
}

Camera& Scene::GetCurrentCamera() const
{
	return *m_currentCamera;
}
void Scene::SetCurrentCamera(UINT index)
{
	m_currentCamera = &m_cameras[index];
}

bool Scene::FindNearestIntersection(const Ray& ray, Point<>& intersection, Vector3<>& normal, const Material*& material) const
{
	bool result = false;

	float minDistance = std::numeric_limits<float>::max();

	result |= IntersectMeshes<GenericMesh>(m_genericMeshes, ray, intersection, normal, material, minDistance);
	result |= IntersectMeshes<Sphere>(m_spheres, ray, intersection, normal, material, minDistance);
	
	return result;
}
void Scene::CalculateLight(const Point<float>& cameraPosition, const Point<float>& intersection, const Vector3<float>& normal, const Material& material, Color<float>& color) const
{
	color = Color<float>(0.0f, 0.0f, 0.0f, 1.0f);

	Color<float> lightColor;
	Vector3<float> viewDirection = cameraPosition - intersection;
	for (UINT i = 0; i < m_lights.size(); i++)
	{
		const Light& light = m_lights[i];

		// If there isn't any object blocking the light:
		if (IsLightUnblocked(light, intersection))
		{
			// Calculate light color from light:
			light.CalculateLightColor(intersection, normal, viewDirection, material, lightColor);

			// Add to the final color:
			color = color + lightColor;
		}
	}
}
bool Scene::IsLightUnblocked(const Light& light, const Point<float>& point) const
{
	Point<float> lightPosition = light.GetPosition();
	Vector3<float> lightDirection = light.IsDirectional() ? Vector3<>(lightPosition.x, lightPosition.y, lightPosition.z) : lightPosition - point;

	// Create a ray to cast at the direction of the light:
	Ray ray(point, lightDirection);

	// Add a little bit of offset to handle the numeric errors:
	ray.origin = ray.origin + ray.direction * 0.00001f;

	// Calculate distance between the light and the intersection point:
	float lightDistance = lightDirection.length();
	
	// Find if there is any object between the light and the object:
	if (!IsLightUnblocked<Sphere>(m_spheres, light, lightDistance, ray) ||
		!IsLightUnblocked<GenericMesh>(m_genericMeshes, light, lightDistance, ray)
		)
		return false;

	return true;
}