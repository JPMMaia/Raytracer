#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{		
	TEST_CLASS(PointLightTest)
	{
	private:
		PointLight m_pointLight;

	public:
		
		TEST_METHOD_INITIALIZE(PointLightTestInitialize)
		{
			m_pointLight = PointLight(Point<>(0.0f, 0.0f, 0.0f), Color<>(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.0f, 0.0f);
		}

		TEST_METHOD(CalculateLightColor1)
		{
			Point<> intersection = Point<>(1.0f, 0.0f, 0.0f);
			Vector<> normal = Vector<>(-1.0f, 0.0f, 0.0f);
			Vector<> viewDirection = Vector<>(-1.0f, 0.0f, 0.0f);
			Material diffuseMaterial = Material(Color<>(0.8f, 0.8f, 0.8f, 1.0f), Color<>(0.0f, 0.0f, 0.0f, 1.0f), 1.0f);
			Material specularMaterial = Material(Color<>(0.0f, 0.0f, 0.0f, 1.0f), Color<>(0.6f, 0.6f, 0.6f, 1.0f), 1.0f);
			Color<> calculatedColor;

			m_pointLight.CalculateLightColor(intersection, normal, viewDirection, diffuseMaterial, calculatedColor);
			Assert::AreEqual(calculatedColor.red, 0.8f, 0.01f);
			Assert::AreEqual(calculatedColor.green, 0.8f, 0.01f);
			Assert::AreEqual(calculatedColor.blue, 0.8f, 0.01f);

			m_pointLight.CalculateLightColor(intersection, normal, viewDirection, specularMaterial, calculatedColor);
			Assert::AreEqual(calculatedColor.red, 0.6f, 0.01f);
			Assert::AreEqual(calculatedColor.green, 0.6f, 0.01f);
			Assert::AreEqual(calculatedColor.blue, 0.6f, 0.01f);
		}
	};
}