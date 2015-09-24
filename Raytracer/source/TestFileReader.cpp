#include "TestFileReader.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <sstream>

using namespace glm;
using namespace std;

bool TestFileReader::Run(const std::wstring& filename, Scene& scene)
{
	m_transforms.push(mat4());
	m_fileData.constantAttenuation = 1.0f;
	m_fileData.linearAttenuation = 0.0f;
	m_fileData.quadraticAttenuation = 0.0f;

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

const TestFileReader::FileData& TestFileReader::GetFileData() const
{
	return m_fileData;
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

	if (command == "output")
		ss >> m_fileData.outputFilename;

	else if (command == "size")
	{
		ss >> m_fileData.screenWidth >> m_fileData.screenHeight;
	}

	else if (command == "maxdepth")
	{
		UINT maxDepth;
		ss >> maxDepth;
		scene.SetMaxReflectionDepth(maxDepth);
	}

	else if (command == "camera")
	{
		float eyeX, eyeY, eyeZ;
		float atX, atY, atZ;
		float upX, upY, upZ;
		ss
			>> eyeX >> eyeY >> eyeZ
			>> atX >> atY >> atZ
			>> upX >> upY >> upZ
			>> m_fileData.fieldOfViewY;

		Camera camera;
		camera.Initialize(
			Point<>(eyeX, eyeY, eyeZ),
			Point<>(atX, atY, atZ),
			Vector3<>(upX, upY, upZ)
			);
		scene.AddCamera(camera);
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

		glm::mat4 transform = m_transforms.top();
		Model<GenericMesh> triangleModel;
		triangleModel.Initialize(triangleMesh, m_material, transform);
		scene.AddGenericMesh(triangleModel);
	}

	else if (command == "sphere")
	{
		float x, y, z, radius;
		ss >> x >> y >> z >> radius;

		Sphere sphereMesh(Point<float>(x, y, z), radius);
		Model<Sphere> sphere;
		sphere.Initialize(sphereMesh, m_material, m_transforms.top());
		scene.AddSphere(sphere);
	}

	else if (command == "ambient")
		ss
		>> m_material.ambientColor.red
		>> m_material.ambientColor.green
		>> m_material.ambientColor.blue;

	else if (command == "emission")
		ss
		>> m_material.emissionColor.red
		>> m_material.emissionColor.green
		>> m_material.emissionColor.blue;

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

	else if (command == "shininess")
		ss >> m_material.shininess;

	else if (command == "translate")
	{
		float tX, tY, tZ;
		ss >> tX >> tY >> tZ;
		MultiplyTransform(translate(vec3(tX, tY, tZ)));
	}

	else if (command == "rotate")
	{
		float rX, rY, rZ, angle;
		ss >> rX >> rY >> rZ >> angle;
		MultiplyTransform(rotate(angle * Constants::DEGREES_TO_RADIANS, vec3(rX, rY, rZ)));
	}

	else if (command == "scale")
	{
		float sX, sY, sZ;
		ss >> sX >> sY >> sZ;
		MultiplyTransform(scale(vec3(sX, sY, sZ)));
	}

	else if (command == "pushTransform")
		PushTransform();

	else if (command == "popTransform")
		PopTransform();

	else if (command == "point")
	{
		float x, y, z, r, g, b;
		ss >> x >> y >> z >> r >> g >> b;

		Light light;
		light.Initialize(
			Point<float>(x, y, z),
			Color<float>(r, g, b, 1.0f),
			false,
			m_fileData.constantAttenuation,
			m_fileData.linearAttenuation,
			m_fileData.quadraticAttenuation
			);
		scene.AddLight(light);
	}

	else if (command == "directional")
	{
		float x, y, z, r, g, b;
		ss >> x >> y >> z >> r >> g >> b;

		Light light;
		light.Initialize(
			Point<float>(x, y, z), 
			Color<float>(r, g, b, 1.0f), 
			true
			);
		scene.AddLight(light);
	}

	else if (command == "attenuation")
		ss
		>> m_fileData.constantAttenuation
		>> m_fileData.linearAttenuation
		>> m_fileData.quadraticAttenuation;

	return true;
}

void TestFileReader::PushTransform()
{
	m_transforms.push(m_transforms.top());
}

void TestFileReader::PopTransform()
{
	m_transforms.pop();
}

void TestFileReader::MultiplyTransform(const glm::mat4& transform)
{
	mat4& result = m_transforms.top();

	result = result * transform;
}
