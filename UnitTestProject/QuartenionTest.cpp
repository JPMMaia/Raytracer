#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(QuartenionTest)
	{
	private:
		static const float s_TOLERANCE;
	public:

		TEST_METHOD(QuartenionTest1)
		{
			Quartenion quartenion1(4.0f, -3.0f, 2.0f, -1.0);
			Quartenion quartenion2(-1.0f, 2.0f, -3.0f, 4.0);

			Quartenion sum = quartenion1 + quartenion2;
			Assert::AreEqual(3.0f, sum.w, s_TOLERANCE);
			Assert::AreEqual(-1.0f, sum.x, s_TOLERANCE);
			Assert::AreEqual(-1.0f, sum.y, s_TOLERANCE);
			Assert::AreEqual(3.0f, sum.z, s_TOLERANCE);

			quartenion1 += quartenion2;
			Assert::AreEqual(sum.w, quartenion1.w, s_TOLERANCE);
			Assert::AreEqual(sum.x, quartenion1.x, s_TOLERANCE);
			Assert::AreEqual(sum.y, quartenion1.y, s_TOLERANCE);
			Assert::AreEqual(sum.z, quartenion1.z, s_TOLERANCE);
		}

		TEST_METHOD(QuartenionTest2)
		{
			Quartenion quartenion1(4.0f, -3.0f, 2.0f, -1.0);
			Quartenion quartenion2(-1.0f, 2.0f, -3.0f, 4.0);

			Quartenion multiplication12 = quartenion1 * quartenion2;
			Assert::AreEqual(12.0f, multiplication12.w, s_TOLERANCE);
			Assert::AreEqual(16.0f, multiplication12.x, s_TOLERANCE);
			Assert::AreEqual(-4.0f, multiplication12.y, s_TOLERANCE);
			Assert::AreEqual(22.0f, multiplication12.z, s_TOLERANCE);

			Quartenion multiplication21 = quartenion2 * quartenion1;
			Assert::AreEqual(12.0f, multiplication21.w, s_TOLERANCE);
			Assert::AreEqual(6.0f, multiplication21.x, s_TOLERANCE);
			Assert::AreEqual(-24.0f, multiplication21.y, s_TOLERANCE);
			Assert::AreEqual(12.0f, multiplication21.z, s_TOLERANCE);

			quartenion1 *= quartenion2;
			Assert::AreEqual(multiplication12.w, quartenion1.w, s_TOLERANCE);
			Assert::AreEqual(multiplication12.x, quartenion1.x, s_TOLERANCE);
			Assert::AreEqual(multiplication12.y, quartenion1.y, s_TOLERANCE);
			Assert::AreEqual(multiplication12.z, quartenion1.z, s_TOLERANCE);
		}

		TEST_METHOD(QuartenionTest3)
		{
			Quartenion quartenion(1.0f, 4.0f, 4.0f, -4.0f);
			float expectedNorm = 7.0f;

			Quartenion conjugate = quartenion.Conjugate();
			Assert::AreEqual(quartenion.w, conjugate.w, s_TOLERANCE);
			Assert::AreEqual(-quartenion.x, conjugate.x, s_TOLERANCE);
			Assert::AreEqual(-quartenion.y, conjugate.y, s_TOLERANCE);
			Assert::AreEqual(-quartenion.z, conjugate.z, s_TOLERANCE);

			float norm = quartenion.Norm();
			Assert::AreEqual(expectedNorm, norm, s_TOLERANCE);

			Quartenion normalizedQuartenion(quartenion);
			normalizedQuartenion.Normalize();
			Assert::AreEqual(quartenion.w / expectedNorm, normalizedQuartenion.w, s_TOLERANCE);
			Assert::AreEqual(quartenion.x / expectedNorm, normalizedQuartenion.x, s_TOLERANCE);
			Assert::AreEqual(quartenion.y / expectedNorm, normalizedQuartenion.y, s_TOLERANCE);
			Assert::AreEqual(quartenion.z / expectedNorm, normalizedQuartenion.z, s_TOLERANCE);

			// Test the inverse:
			quartenion *= quartenion.Inverse();
			Assert::AreEqual(1.0f, quartenion.w, s_TOLERANCE);
			Assert::AreEqual(0.0f, quartenion.x, s_TOLERANCE);
			Assert::AreEqual(0.0f, quartenion.y, s_TOLERANCE);
			Assert::AreEqual(0.0f, quartenion.z, s_TOLERANCE);
		}

		TEST_METHOD(QuartenionTest4)
		{
			Quartenion quartenion(0.0f, 2.0f, 0.0f, 0.0f);
			Quartenion rotation = Quartenion::FromAxisAngle(Vector3<>(0.0f, 0.0f, 1.0f), 45.0f);

			quartenion = rotation * quartenion * rotation.Conjugate();
			Assert::AreEqual(2.0f, quartenion.Norm(), s_TOLERANCE);
			Assert::AreEqual(0.0f, quartenion.w, s_TOLERANCE);
			Assert::AreEqual(sqrtf(2.0f), quartenion.x, s_TOLERANCE);
			Assert::AreEqual(sqrtf(2.0f), quartenion.y, s_TOLERANCE);
			Assert::AreEqual(0.0f, quartenion.z, s_TOLERANCE);

			Vector3<float> rotatedVector = Quartenion::Rotate(Vector3<float>(2.0f, 0.0f, 0.0f), Vector3<>(0.0f, 0.0f, 1.0f), 45.0f);
			Assert::AreEqual(sqrtf(2.0f), rotatedVector.x, s_TOLERANCE);
			Assert::AreEqual(sqrtf(2.0f), rotatedVector.y, s_TOLERANCE);
			Assert::AreEqual(0.0f, rotatedVector.z, s_TOLERANCE);
		}
	};

	const float QuartenionTest::s_TOLERANCE = 0.0001f;
}