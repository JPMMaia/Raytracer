#include "Application.h"

int main()
{
	// TODO review normals
	// TODO review light calculation -> diffuse and specular
	Application application;
	if (!application.Initialize(L"resources/scene5.test"))
		return -1;

	application.Render();

	application.Shutdown();

	return 0;
}