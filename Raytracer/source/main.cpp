#include "Application.h"

int main()
{
	Application application;
	if (!application.Initialize())
		return -1;

	application.Render();

	application.Shutdown();

	return 0;
}