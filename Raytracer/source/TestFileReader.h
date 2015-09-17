#pragma once

#include <fstream>
#include <string>

#include "Model.h"
#include "Sphere.h"

class TestFileReader
{
public:
	struct FileData
	{
		int screenWidth, screenHeight;
		float eyeX, eyeY, eyeZ, atX, atY, atZ, upX, upY, upZ, fieldOfViewY;
	};

public:
	bool Initialize(const std::wstring& filename);

private:
	void ReadLine();

private:
	std::ifstream m_fileStream;
	FileData m_fileData;
};