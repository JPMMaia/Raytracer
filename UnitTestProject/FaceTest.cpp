#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(FaceTest)
	{
	public:

		TEST_METHOD(FaceTest1)
		{
			Face face = Face(
				Point<>(-0.5f, -0.5f, -1.0f),
				Point<>(0.5f, -0.5f, -1.0f),
				Point<>(0.0f, 0.5f, -1.0f)
				);

			Point<> intersection;
			Vector3<> normal;
			float distance;
			Assert::IsTrue(
				face.Intersect(
					Ray(Point<>(0.0f, 0.0f, 0.0f), Vector3<>(0.0f, 0.0f, -1.0f)),
					intersection,
					distance,
					normal
					)
				);

			Assert::IsFalse(
				face.Intersect(
					Ray(Point<>(-0.5f, 0.4f, 0.0f), Vector3<>(0.0f, 0.0f, -1.0f)),
					intersection,
					distance,
					normal
					)
				);
		}
	};
}