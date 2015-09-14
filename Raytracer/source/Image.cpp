#include <string>

#include "Image.h"

using namespace std;

Image::Image()
{
}
Image::~Image()
{
}

bool Image::Initialize(int width, int height, int bitsPerPixel)
{
	m_bitmap = FreeImage_Allocate(width, height, bitsPerPixel);
	if (!m_bitmap)
		return false;

	return true;
}

bool Image::SetPixelColor(int line, int column, BYTE red, BYTE green, BYTE blue)
{
	RGBQUAD color;
	color.rgbRed = red;
	color.rgbGreen = green;
	color.rgbBlue = blue;

	if (!FreeImage_SetPixelColor(m_bitmap, column, line, &color))
		return false;

	return true;
}

bool Image::Save(const char* filename)
{
	if (!FreeImage_Save(FIF_PNG, m_bitmap, filename, 0))
		return false;

	return true;
}
