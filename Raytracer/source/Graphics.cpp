#include "Graphics.h"
#include "Sphere.h"

bool Graphics::Initialize()
{
	// Initialize Free Image:
	FreeImage_Initialise();

	// Initialize image where the scene will be rendered:
	if (!m_renderBuffer.Initialize(s_WIDTH, s_HEIGHT, 24))
		return false;

	return true;
}
void Graphics::Shutdown()
{
	// Release Free Image resources: 
	FreeImage_DeInitialise();
}

bool Graphics::Render()
{
	Sphere sphere = Sphere(Point<>(0.0f, 0.0f, -4.0f), 1.0f);

	float pixelCenterX = 0.5f / static_cast<float>(s_WIDTH);
	float pixelCenterY = 0.5f / static_cast<float>(s_HEIGHT);

	Ray ray = Ray(Point<>(0.0f, 0.0f, 0.0f), Vector<>(0.0f, 0.0f, -1.0f));

	for (int i = 0; i < s_HEIGHT; i++)
	{
		float y = 2.0f * (pixelCenterY + static_cast<float>(i) / static_cast<float>(s_HEIGHT)) - 1.0f;
		ray.direction.y = -y;

		for (int j = 0; j < s_WIDTH; j++)
		{
			float x = 2.0f * (pixelCenterX + static_cast<float>(j) / static_cast<float>(s_WIDTH)) - 1.0f;
			ray.direction.x = x;

			if (sphere.Intersect(ray))
				m_renderBuffer.SetPixelColor(s_HEIGHT - i, j, 255, 0, 0);
			else
				m_renderBuffer.SetPixelColor(s_HEIGHT - i, j, 0, 0, 0);
		}
	}

	m_renderBuffer.Save("Output\Result.png");

	return true;
}
