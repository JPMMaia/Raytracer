#pragma once

#include <fstream>
#include <glm\matrix.hpp>
#include <stack>
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
		std::string outputFilename;
		int screenWidth, screenHeight;
		float fieldOfViewY;
		float constantAttenuation, linearAttenuation, quadraticAttenuation;
	};

public:
	bool Run(const std::wstring& filename, Scene& scene);

	const FileData& GetFileData() const;

private:
	bool ReadLine(Scene& scene);
	
	void PushTransform();
	void PopTransform();
	void MultiplyTransform(const glm::mat4& transform);

private:
	std::ifstream m_fileStream;
	FileData m_fileData;
	std::vector<Point<float>> m_vertices;
	Material m_material;

	std::stack<glm::mat4> m_transforms;
};