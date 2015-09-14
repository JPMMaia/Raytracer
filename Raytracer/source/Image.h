#pragma once

#include <FreeImage.h>

class Image
{
public:
	Image();
	~Image();

	bool Initialize(int width, int height, int bitsPerPixel);

	bool GetPixelColor(int line, int column, BYTE& red, BYTE& green, BYTE& blue) const;
	bool SetPixelColor(int line, int column, BYTE red, BYTE green, BYTE blue);
	bool AddPixelColor(int line, int column, BYTE red, BYTE green, BYTE blue);
	bool Save(const char* filename) const;

private:
	FIBITMAP* m_bitmap;
};