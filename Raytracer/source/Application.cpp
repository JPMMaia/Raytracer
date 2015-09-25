#include "Application.h"

bool Application::Initialize(const std::wstring& filename)
{
	m_scene.Initialize(10, 10);

	TestFileReader fileReader;
	if (!fileReader.Run(filename, m_scene))
		return false;

	const TestFileReader::FileData& fileData = fileReader.GetFileData();
	m_outputFilename = fileData.outputFilename;

	if (!m_graphics.Initialize(fileData.screenWidth, fileData.screenHeight, fileData.maxReflectionDepth, fileData.fieldOfViewY))
		return false;

	m_scene.SetCurrentCamera(1);

	return true;
}
void Application::Shutdown()
{
	m_graphics.Shutdown();
}

void Application::Render()
{
	m_graphics.Render(m_scene);

	m_graphics.SaveFrame(m_outputFilename.c_str());
}
