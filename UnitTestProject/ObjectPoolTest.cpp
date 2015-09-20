#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(ObjectPoolTest)
	{
	private:
		struct TestObject
		{
			static UINT staticCount;
			int id;

			/*TestObject()
			{
				id = staticCount++;
			}*/
		};
		//UINT TestObject::staticCount = 0;

	public:
		TEST_METHOD(ObjectPoolTest1)
		{
			ObjectPool<TestObject> pool;
			pool.Initialize(1);

			TestObject::staticCount = 0;
			TestObject* object1, * object2;
			Assert::IsTrue(pool.Create(object1));
			Assert::AreEqual(0, object1->id);
			
			Assert::IsFalse(pool.Create(object2));
		}
	};
}