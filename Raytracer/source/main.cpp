#include "Application.h"

int main()
{
	Application application;
	if (!application.Initialize(L"resources/scene2.test"))
		return -1;

	application.Render();

	application.Shutdown();

	return 0;
}