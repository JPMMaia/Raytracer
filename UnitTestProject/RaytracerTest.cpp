#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(RaytracerTest)
	{
	private:
		static const float s_TOLERANCE;

	private:
		void CompareVector3s(const Vector3<float>& expected, const Vector3<float>& actual)
		{
			Assert::AreEqual(expected.x, actual.x, s_TOLERANCE);
			Assert::AreEqual(expected.y, actual.y, s_TOLERANCE);
			Assert::AreEqual(expected.z, actual.z, s_TOLERANCE);
		}

	public:

		TEST_METHOD(RaytracerTest1)
		{
			Raytracer raytracer;
			raytracer.Initialize(9, 9, 1.0f);

			Point<float> origin(0.0f, 0.0f, 0.0f);
			Vector3<float> xDirection(-1.0f, 0.0f, 0.0f);
			Vector3<float> yDirection(0.0f, 1.0f, 0.0f);
			Vector3<float> zDirection(0.0f, 0.0f, -1.0f);

			Ray ray = raytracer.CalculatePixelRay(
				origin,
				xDirection,
				yDirection,
				zDirection,
				4,
				4
				);
			
			CompareVector3s(Vector3<float>(0.0f, 0.0f, -1.0f), ray.direction);
		}

		TEST_METHOD(RaytracerTest2)
		{
			Raytracer raytracer;
			raytracer.Initialize(9, 9, 1.0f);

			Camera camera;
			camera.Initialize(Point<float>(-4.0f, -4.0f, 4.0f), Point<float>(1.0f, 0.0f, 0.0f), Vector3<float>(0.0f, 1.0f, 0.0f));

			Point<float> origin(0.0f, 0.0f, 0.0f);

			Ray ray = raytracer.CalculatePixelRay(
				origin,
				camera.GetLeftDirection(),
				camera.GetUpDirection(),
				camera.GetViewDirection(),
				4,
				4
				);

			CompareVector3s(Vector3<float>(5.0f, 4.0f, -4.0f).normalizedVector(), ray.direction);
		}
	};

	/*
	for (int i = 0; i < 9; i++)
	{
	for (int j = 0; j < 9; j++)
	{
	Ray ray = raytracer.CalculatePixelRay(
	origin,
	xDirection,
	yDirection,
	zDirection,
	i,
	j
	);
	}
	}*/

	const float RaytracerTest::s_TOLERANCE = 0.0001f;
}