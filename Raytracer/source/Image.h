#pragma once

#include <FreeImage.h>

class Image
{
public:
	Image();
	~Image();

	bool Initialize(int width, int height, int bitsPerPixel);

	bool SetPixelColor(int line, int column, BYTE red, BYTE green, BYTE blue);
	bool Save(const char* filename);

private:
	FIBITMAP* m_bitmap;
};