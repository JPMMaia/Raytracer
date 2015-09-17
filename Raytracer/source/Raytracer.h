#pragma once

#include "Ray.h"
#include "Sphere.h"

class Raytracer
{
public:
	bool Initialize(int screenWidth, int screenHeight);
	void Shutdown();

	const Ray& GetPixelRay(int line, int column);

private:
	Ray* m_rays;
	int m_screenWidth;
	int m_screenHeight;
};