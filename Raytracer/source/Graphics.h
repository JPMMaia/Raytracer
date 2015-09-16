#pragma once

#include "Image.h"

class Graphics
{
public:
	bool Initialize();
	void Shutdown();

	bool Render();

private:
	Image m_renderBuffer;
	static const unsigned int s_WIDTH = 512;
	static const unsigned int s_HEIGHT = 512;
};