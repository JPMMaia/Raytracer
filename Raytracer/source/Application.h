#pragma once

#include "Graphics.h"

class Application 
{
public:
	bool Initialize();
	void Shutdown();

	void Render();

private:
	Graphics m_graphics;
};