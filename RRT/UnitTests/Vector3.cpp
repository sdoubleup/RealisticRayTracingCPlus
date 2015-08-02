#include "stdafx.h"
#include "CppUnitTest.h"

#include "Vector3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(Vector3)
	{
	public:
		
		TEST_METHOD(Vector3IntLength)
		{
			RRT::Vector3<int> t(1, 1, 1);

			double l = t.Length();
			double e = 1.73205;
			double tol = 1e-5;

			Assert::IsTrue(std::fabs(l - e) < tol);
		}

		TEST_METHOD(Vector3IntAdd)
		{
			RRT::Vector3<int> a(1, 1, 1);
			RRT::Vector3<int> b(1, 1, 1);

			RRT::Vector3<int> c = a + b;
			Assert::AreEqual(2, c.x());
			Assert::AreEqual(2, c.y());
			Assert::AreEqual(2, c.z());

			c += a;
			Assert::AreEqual(3, c.x());
			Assert::AreEqual(3, c.y());
			Assert::AreEqual(3, c.z());
		}

	};
}