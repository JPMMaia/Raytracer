#include "Application.h"

bool Application::Initialize()
{
	if (!m_graphics.Initialize())
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
