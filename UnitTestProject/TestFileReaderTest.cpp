#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(TestFileReaderTest)
	{
	private:
		

	public:

		TEST_METHOD_INITIALIZE(TestFileReaderTestInitialize)
		{
			TestFileReader m_fileReader;
			m_fileReader.Initialize(L"ola");
		}

		TEST_METHOD(TestFileReaderTest1)
		{
		}
	};
}