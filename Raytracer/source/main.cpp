#include "Application.h"

int main()
{
	Application application;
	if (!application.Initialize(L"resources/scene6.test"))
		return -1;

	application.Render();

	application.Shutdown();

	return 0;
}