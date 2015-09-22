#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{		
	TEST_CLASS(LightTest)
	{
	public:
	
		TEST_METHOD(CalculateLightColor1)
		{
			Light light;
			light.Initialize(Point<>(0.0f, 0.0f, 0.0f), Color<>(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.0f, 0.0f);

			Point<> intersection = Point<>(1.0f, 0.0f, 0.0f);
			Vector3<> normal = Vector3<>(-1.0f, 0.0f, 0.0f);
			Vector3<> viewDirection = Vector3<>(-1.0f, 0.0f, 0.0f);
			Material diffuseMaterial = Material(Color<>(0.0f, 0.0f, 0.0f, 0.0f), Color<>(0.8f, 0.8f, 0.8f, 1.0f), Color<>(0.0f, 0.0f, 0.0f, 1.0f), 1.0f);
			Material specularMaterial = Material(Color<>(0.0f, 0.0f, 0.0f, 0.0f), Color<>(0.0f, 0.0f, 0.0f, 1.0f), Color<>(0.6f, 0.6f, 0.6f, 1.0f), 1.0f);
			Color<> calculatedColor;

			light.CalculateLightColor(intersection, normal, viewDirection, diffuseMaterial, calculatedColor);
			Assert::AreEqual(calculatedColor.red, 0.8f, 0.01f);
			Assert::AreEqual(calculatedColor.green, 0.8f, 0.01f);
			Assert::AreEqual(calculatedColor.blue, 0.8f, 0.01f);

			light.CalculateLightColor(intersection, normal, viewDirection, specularMaterial, calculatedColor);
			Assert::AreEqual(calculatedColor.red, 0.6f, 0.01f);
			Assert::AreEqual(calculatedColor.green, 0.6f, 0.01f);
			Assert::AreEqual(calculatedColor.blue, 0.6f, 0.01f);
		}

		TEST_METHOD(CalculateLightColor2)
		{
			Light light;
			light.Initialize(Point<>(0.0f, 1.0f, 0.0f), Color<>(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.0f, 0.0f);

			Point<> intersection = Point<>(1.0f, 0.0f, 0.0f);
			Vector3<> normal = Vector3<>(-1.0f, 0.0f, 0.0f);
			Vector3<> viewDirection = Vector3<>(-1.0f, 0.0f, 0.0f);
			Material specularMaterial = Material(Color<>(0.0f, 0.0f, 0.0f, 0.0f), Color<>(0.0f, 0.0f, 0.0f, 1.0f), Color<>(0.6f, 0.6f, 0.6f, 1.0f), 2.0f);
			Color<> calculatedColor;

			light.CalculateLightColor(intersection, normal, viewDirection, specularMaterial, calculatedColor);
			Assert::AreEqual(calculatedColor.red, 0.51213f, 0.001f);
			Assert::AreEqual(calculatedColor.green, 0.51213f, 0.001f);
			Assert::AreEqual(calculatedColor.blue, 0.51213f, 0.001f);
		}
	};
}