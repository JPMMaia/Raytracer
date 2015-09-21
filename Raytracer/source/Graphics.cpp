#include "Graphics.h"
#include "Sphere.h"
#include "PointLight.h"
#include "Property.h"
#include "Scene.h"

bool Graphics::Initialize(UINT screenWidth, UINT screenHeight, float fieldOfViewY)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Initialize Free Image:
	FreeImage_Initialise();

	// Initialize image where the scene will be rendered:
	if (!m_renderBuffer.Initialize(screenWidth, screenHeight, 24))
		return false;

	// Initialize raytracer:
	if (!m_raytracer.Initialize(screenWidth, screenHeight, 1.0f / tanf(fieldOfViewY * Constants::DEGREES_TO_RADIANS * 0.5f)))
		return false;

	return true;
}
void Graphics::Shutdown()
{
	// Release Free Image resources: 
	FreeImage_DeInitialise();
}

bool Graphics::Render(const Scene& scene)
{
	Point<> intersection;
	Vector3<> normal;
	PointLight pointLight = PointLight(Point<>(2.0f, 2.0f, -2.0f), Color<>(0.7f, 0.7f, 0.7f, 1.0f));
	const Material* material;
	Color<> color;

	Camera& camera = scene.GetCurrentCamera();
	const Point<>& cameraPosition = camera.GetPosition();
	const Vector3<>& cameraLeftDirection = camera.GetLeftDirection();
	const Vector3<>& cameraUpDirection = camera.GetUpDirection();
	const Vector3<>& cameraViewDirection = camera.GetViewDirection();
	
	for (UINT i = 0; i < m_screenHeight; i++)
	{
		for (UINT j = 0; j < m_screenWidth; j++)
		{
			Ray ray = m_raytracer.CalculatePixelRay(cameraPosition, cameraLeftDirection, cameraUpDirection, cameraViewDirection, i, j);

			if (scene.Intersect(ray, intersection, normal, material))
			{
				Vector3<> viewDirection = intersection - cameraPosition;

				// Calculate color:
				pointLight.CalculateLightColor(intersection, normal, viewDirection, *material, color);

				// Add ambient color:
				color = color + material->ambientColor;

				// Add color to pixel:
				m_renderBuffer.AddPixelColor(m_screenHeight - i, j, color);
			}
		}
	}

	m_renderBuffer.Save("ResultImage.png");

	return true;
}
