#include "TestFileReader.h"

#include <sstream>

using namespace std;

bool TestFileReader::Run(const std::wstring& filename, Scene& scene)
{
	// Open input file stream:
	m_fileStream.open(filename, ios::in);
	if (!m_fileStream.is_open())
		return false;

	while (!m_fileStream.eof())
		if (!ReadLine(scene))
			return false;

	// Close input file stream:
	m_fileStream.close();

	return true;
}

bool TestFileReader::ReadLine(Scene& scene)
{
	string line;
	getline(m_fileStream, line);

	// Ignore empty lines:
	if (line.size() == 0)
		return true;

	// If comment, ignore:
	if (line[0] == '#')
		return true;

	// Create a string stream:
	stringstream ss(line);

	// Extract the command type, which is the first word of the line:
	string command;
	ss >> command;

	if (command == "size")
	{
		ss >> m_fileData.screenWidth >> m_fileData.screenHeight;
	}

	else if (command == "camera")
	{
		ss
			>> m_fileData.eyeX >> m_fileData.eyeY >> m_fileData.eyeZ
			>> m_fileData.atX >> m_fileData.atY >> m_fileData.atZ
			>> m_fileData.upX >> m_fileData.upY >> m_fileData.upZ
			>> m_fileData.fieldOfViewY;
	}
		
	else if (command == "maxverts")
	{
		UINT maxVertices;
		ss >> maxVertices;
		m_vertices.reserve(maxVertices);
	}
	
	else if (command == "vertex")
	{
		Point<float> vertex;
		ss >> vertex.x >> vertex.y >> vertex.z;
		m_vertices.push_back(vertex);
	}

	else if (command == "tri")
	{
		UINT index1, index2, index3;
		ss >> index1 >> index2 >> index3;

		vector<Point<float>> vertices(3);
		vertices[0] = m_vertices[index1];
		vertices[1] = m_vertices[index2];
		vertices[2] = m_vertices[index3];

		vector<UINT> indices(3);
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		
		GenericMesh triangleMesh;
		triangleMesh.Initialize(vertices, indices);

		Model<GenericMesh> triangleModel;
		triangleModel.Initialize(triangleMesh, m_material);
		scene.AddGenericMesh(triangleModel);
	}

	else if (command == "ambient")
		ss 
		>> m_material.ambientColor.red 
		>> m_material.ambientColor.green 
		>> m_material.ambientColor.blue;

	else if(command == "diffuse")
		ss
		>> m_material.diffuseColor.red
		>> m_material.diffuseColor.green
		>> m_material.diffuseColor.blue;

	else if(command == "specular")
		ss
		>> m_material.specularColor.red
		>> m_material.specularColor.green
		>> m_material.specularColor.blue;

	return true;
}
