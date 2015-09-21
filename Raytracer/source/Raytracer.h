#pragma once

#include <vector>

#include "Ray.h"
#include "Sphere.h"

class Raytracer
{
public:
	bool Initialize(int screenWidth, int screenHeight, float zNear);

	Ray CalculatePixelRay(const Point<float>& origin, const Vector3<float>& leftDirection, const Vector3<float>& upDirection, const Vector3<float>& viewDirection, int line, int column);

private:
	int m_screenWidth;
	int m_screenHeight;
	float m_aspectRatio;
	float m_pixelCenterX;
	float m_pixelCenterY;
	float m_zNear;
};