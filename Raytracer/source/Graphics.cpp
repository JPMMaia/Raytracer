#include "Graphics.h"
#include "Sphere.h"
#include "PointLight.h"

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

	Point<> cameraPosition = Point<>(0.0f, 0.0f, 0.0f);
	Ray ray = Ray(cameraPosition, Vector<>(0.0f, 0.0f, -1.0f));
	Point<> intersection;
	Vector<> normal;
	PointLight pointLight = PointLight(Point<>(2.0f, 2.0f, -2.0f), Color<>(180, 180, 180, 255));
	Material material = Material(Color<>(0, 40, 180, 255), Color<>(0, 40, 180, 255), 20.0f);
	Color<> color;

	for (int i = 0; i < s_HEIGHT; i++)
	{
		float y = 2.0f * (pixelCenterY + static_cast<float>(i) / static_cast<float>(s_HEIGHT)) - 1.0f;
		ray.direction.y = -y;

		for (int j = 0; j < s_WIDTH; j++)
		{
			float x = 2.0f * (pixelCenterX + static_cast<float>(j) / static_cast<float>(s_WIDTH)) - 1.0f;
			ray.direction.x = x;

			// If there is an intesection between the sphere and the ray:
			if (sphere.Intersect(ray, intersection, normal))
			{
				Vector<> viewDirection = intersection - cameraPosition;

				// Calculate color:
				pointLight.CalculateLightColor(intersection, normal, viewDirection, material, color);

				// Add color to pixel:
				m_renderBuffer.AddPixelColor(s_HEIGHT - i, j, color.red, color.green, color.blue);
			}
		}
	}

	

	m_renderBuffer.Save("ResultImage.png");

	return true;
}
