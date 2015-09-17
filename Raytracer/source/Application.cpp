#include "Application.h"

bool Application::Initialize(const std::wstring& filename)
{
	TestFileReader fileReader;
	if (!fileReader.Initialize(filename))
		return false;

	if (!m_graphics.Initialize(512, 512))
		return false;

	return true;
}
void Application::Shutdown()
{
	m_graphics.Shutdown();
}

void Application::Render()
{
	m_graphics.Render();
}
