#include <FreeImage.h>
#include <iostream>

void main()
{
	FreeImage_Initialise();

	std::cout << FreeImage_GetVersion();

	FreeImage_DeInitialise();
}