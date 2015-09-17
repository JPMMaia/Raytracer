#include "Raytracer.h"

bool Raytracer::Initialize(int screenWidth, int screenHeight)
{
	if (screenWidth <= 0 || screenHeight <= 0)
		return false;

	float pixelCenterX = 0.5f / static_cast<float>(screenWidth);
	float pixelCenterY = 0.5f / static_cast<float>(screenHeight);

	int rayCount = screenWidth * screenHeight;
	m_rays = new Ray[rayCount];

	Ray ray;
	ray.direction.z = -1.0f;

	for (int i = 0; i < screenHeight; i++)
	{
		float y = 2.0f * (pixelCenterY + static_cast<float>(i) / static_cast<float>(screenHeight)) - 1.0f;
		ray.direction.y = -y;

		for (int j = 0; j < screenWidth; j++)
		{
			float x = 2.0f * (pixelCenterX + static_cast<float>(j) / static_cast<float>(screenWidth)) - 1.0f;
			ray.direction.x = x;

			m_rays[i * screenWidth + j] = ray;
		}
	}

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	return true;
}

void Raytracer::Shutdown()
{
	if (m_rays)
	{
		delete m_rays;
		m_rays = 0;
	}
}

const Ray& Raytracer::GetPixelRay(int line, int column)
{
	return m_rays[line * m_screenWidth + column];
}