#include "Graphics.h"
#include "Sphere.h"
#include "Property.h"
#include "Scene.h"

#include <iostream>

bool Graphics::Initialize(UINT screenWidth, UINT screenHeight, UINT maxReflectionDepth, float fieldOfViewY)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_maxReflectionDepth = maxReflectionDepth;

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
	Color<> color;

	Camera& camera = scene.GetCurrentCamera();
	const Point<>& cameraPosition = camera.GetPosition();
	const Vector3<>& cameraLeftDirection = camera.GetLeftDirection();
	const Vector3<>& cameraUpDirection = camera.GetUpDirection();
	const Vector3<>& cameraViewDirection = camera.GetViewDirection();
	
	for (UINT i = 0; i < m_screenHeight; i++)
	{
		std::cout << "line: " << i << std::endl; // To output some feedback about the progress

		for (UINT j = 0; j < m_screenWidth; j++)
		{
			Ray ray = m_raytracer.CalculatePixelRay(cameraPosition, cameraLeftDirection, cameraUpDirection, cameraViewDirection, i, j);

			if (scene.CalculateColor(ray, cameraPosition, color, m_maxReflectionDepth))
			{
				// Add color to pixel:
				m_renderBuffer.AddPixelColor(m_screenHeight - i - 1, j, color);
			}
		}
	}

	return true;
}

void Graphics::SaveFrame(const char* filename)
{
	m_renderBuffer.Save(filename);
}
