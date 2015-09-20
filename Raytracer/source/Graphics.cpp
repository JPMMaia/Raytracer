#include "Graphics.h"
#include "Sphere.h"
#include "PointLight.h"
#include "Property.h"
#include "Scene.h"

bool Graphics::Initialize(UINT screenWidth, UINT screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Initialize Free Image:
	FreeImage_Initialise();

	// Initialize image where the scene will be rendered:
	if (!m_renderBuffer.Initialize(screenWidth, screenHeight, 24))
		return false;

	// Initialize raytracer:
	if (!m_raytracer.Initialize(screenWidth, screenHeight))
		return false;

	// Initialize camera at the origin looking at -Z:
	m_camera.Initialize(Point<>(0.0f, 0.0f, 0.0f), Point<>(0.0f, 0.0f, 1.0f), Vector3<>(0.0f, 1.0f, 0.0f));

	return true;
}
void Graphics::Shutdown()
{
	m_raytracer.Shutdown();

	// Release Free Image resources: 
	FreeImage_DeInitialise();
}

bool Graphics::Render(const Scene& scene)
{
	Sphere sphere = Sphere(Point<>(0.0f, 0.0f, -4.0f), 1.0f);
	Point<> intersection;
	Vector3<> normal;
	PointLight pointLight = PointLight(Point<>(2.0f, 2.0f, -2.0f), Color<>(0.7f, 0.7f, 0.7f, 1.0f));
	Material material = Material(Color<>(0.0f, 0.0f, 0.0f, 0.0f), Color<>(0.0f, 0.4f, 0.7f, 1.0f), Color<>(0.0f, 0.4f, 0.7f, 1.0f), 20.0f);
	Color<> color;
	const Point<>& cameraPosition = Point<>(0.0f, 0.0f, 4.0f);
	
	for (UINT i = 0; i < m_screenWidth; i++)
	{
		for (UINT j = 0; j < m_screenHeight; j++)
		{
			Ray ray = m_raytracer.GetPixelRay(i, j);
			ray.origin = cameraPosition;

			/*if (scene.Intersect(ray, intersection, normal))
			{
				Vector3<> viewDirection = intersection - cameraPosition;

				// Calculate color:
				pointLight.CalculateLightColor(intersection, normal, viewDirection, material, color);

				// Add color to pixel:
				m_renderBuffer.AddPixelColor(m_screenHeight - i, j, color);
			}*/

			// If there is an intesection between the sphere and the ray:
			if (sphere.Intersect(ray, intersection, normal))
			{
				Vector3<> viewDirection = intersection - cameraPosition;

				// Calculate color:
				pointLight.CalculateLightColor(intersection, normal, viewDirection, material, color);

				// Add color to pixel:
				m_renderBuffer.AddPixelColor(m_screenHeight - i, j, color);
			}
		}
	}

	m_renderBuffer.Save("ResultImage.png");

	return true;
}
