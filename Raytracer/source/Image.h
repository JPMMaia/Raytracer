#pragma once

#include <FreeImage.h>

#include "Color.h"

class Image
{
public:
	Image();
	~Image();

	bool Initialize(int width, int height, int bitsPerPixel);

	bool GetPixelColor(int line, int column, Color<BYTE>& color) const;
	bool SetPixelColor(int line, int column, const Color<BYTE>& color);
	bool AddPixelColor(int line, int column, const Color<BYTE>& color);
	bool Save(const char* filename) const;

private:
	FIBITMAP* m_bitmap;
};