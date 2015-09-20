#pragma once

#include "Camera.h"
#include "Image.h"
#include "Raytracer.h"
#include "Scene.h"

typedef unsigned int UINT;

class Graphics
{
public:
	bool Initialize(UINT screenWidth, UINT screenHeight);
	void Shutdown();

	bool Render(const Scene& scene);

private:
	Camera m_camera;
	Image m_renderBuffer;
	Raytracer m_raytracer;

	UINT m_screenWidth;
	UINT m_screenHeight;
};