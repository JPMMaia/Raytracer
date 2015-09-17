#include <math.h>
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

bool Image::GetPixelColor(int line, int column, Color<BYTE>& color) const
{
	RGBQUAD pixelColor;
	if (!FreeImage_GetPixelColor(m_bitmap, column, line, &pixelColor))
		return false;

	color.red = pixelColor.rgbRed;
	color.green = pixelColor.rgbGreen;
	color.blue = pixelColor.rgbBlue;

	return true;
}

bool Image::SetPixelColor(int line, int column, const Color<BYTE>& color)
{
	RGBQUAD pixelColor;
	pixelColor.rgbRed = color.red;
	pixelColor.rgbGreen = color.green;
	pixelColor.rgbBlue = color.blue;

	if (!FreeImage_SetPixelColor(m_bitmap, column, line, &pixelColor))
		return false;

	return true;
}

bool Image::AddPixelColor(int line, int column, const Color<BYTE>& color)
{
	Color<BYTE> pixelColor;
	if (!GetPixelColor(line, column, pixelColor))
		return false;

	pixelColor = pixelColor + color;

	if (!SetPixelColor(line, column, pixelColor))
		return false;

	return true;
}

bool Image::Save(const char* filename) const
{
	if (!FreeImage_Save(FIF_PNG, m_bitmap, filename, 0))
		return false;

	return true;
}
