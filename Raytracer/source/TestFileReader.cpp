#include "TestFileReader.h"

#include <sstream>

using namespace std;

bool TestFileReader::Initialize(const std::wstring& filename)
{
	// Open input file stream:
	m_fileStream.open(filename, ios::in);
	if (!m_fileStream.is_open())
		return false;

	while (!m_fileStream.eof())
		ReadLine();

	// Close input file stream:
	m_fileStream.close();

	return true;
}

void TestFileReader::ReadLine()
{
	string line;
	getline(m_fileStream, line);

	// Ignore empty lines:
	if (line.size() == 0)
		return;

	// If comment, ignore:
	if (line[0] == '#')
		return;

	// Create a string stream:
	stringstream ss(line);

	// Extract the command type, which is the first word of the line:
	string command;
	ss >> command;

	if (command == "size")
		ss >> m_fileData.screenWidth >> m_fileData.screenHeight;

	else if (command == "camera")
		ss
		>> m_fileData.eyeX >> m_fileData.eyeY >> m_fileData.eyeZ
		>> m_fileData.atX >> m_fileData.atY >> m_fileData.atZ
		>> m_fileData.upX >> m_fileData.upY >> m_fileData.upZ
		>> m_fileData.fieldOfViewY;
		
}
