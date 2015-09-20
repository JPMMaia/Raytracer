#pragma once

#include <fstream>
#include <string>

#include "GenericMesh.h"
#include "Model.h"
#include "Scene.h"
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
	bool Run(const std::wstring& filename, Scene& scene);

private:
	bool ReadLine(Scene& scene);

private:
	std::ifstream m_fileStream;
	FileData m_fileData;
	std::vector<Point<float>> m_vertices;
	Material m_material;
};