#pragma once

#include "TestFileReader.h"
#include "Graphics.h"

class Application 
{
public:
	bool Initialize(const std::wstring& filename);
	void Shutdown();

	void Render();

private:
	Graphics m_graphics;
};