#include "Application.h"

bool Application::Initialize(const std::wstring& filename)
{
	m_scene.Initialize(10, 10);

	TestFileReader fileReader;
	if (!fileReader.Run(filename, m_scene))
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
	m_graphics.Render(m_scene);
}
