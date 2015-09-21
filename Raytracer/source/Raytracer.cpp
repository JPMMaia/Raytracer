#include "Raytracer.h"

bool Raytracer::Initialize(int screenWidth, int screenHeight, float zNear)
{
	if (screenWidth <= 0 || screenHeight <= 0)
		return false;

	m_pixelCenterX = 0.5f / static_cast<float>(screenWidth);
	m_pixelCenterY = 0.5f / static_cast<float>(screenHeight);

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
	m_zNear = zNear;

	return true;
}

Ray Raytracer::CalculatePixelRay(const Point<float>& origin, const Vector3<float>& leftDirection, const Vector3<float>& upDirection, const Vector3<float>& viewDirection, int line, int column)
{
	Ray output;

	output.origin = origin;

	float s = (2.0f * (m_pixelCenterX + static_cast<float>(column) / static_cast<float>(m_screenWidth)) - 1.0f) * m_aspectRatio;
	float t = -(2.0f * (m_pixelCenterY + static_cast<float>(line) / static_cast<float>(m_screenHeight)) - 1.0f);
	
	output.direction = (s * -leftDirection) + (t * upDirection) + (m_zNear * viewDirection);

	return output;
}
