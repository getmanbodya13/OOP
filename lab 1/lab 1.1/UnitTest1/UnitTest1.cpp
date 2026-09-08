#include "pch.h"
#include "CppUnitTest.h"
#include "../lab 1.1/Point.h"
#include "../lab 1.1/Point.cpp"
#include "../lab 1.1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestInit)
        {
            Point p;

            bool result = p.Init(3, 4);

            Assert::IsTrue(result);
            Assert::AreEqual(3.0, p.GetFirst());
            Assert::AreEqual(4.0, p.GetSecond());
        }

         TEST_METHOD(TestDistance)
        {
            Point p;

            p.Init(3, 4);

            double result = p.Distance();

            Assert::AreEqual(5.0, result);
        }

        TEST_METHOD(TestValidCoordinates)
        {
            Point p;

            Assert::IsTrue(p.SetFirst(100));
            Assert::IsTrue(p.SetSecond(-100));

            Assert::AreEqual(100.0, p.GetFirst());
            Assert::AreEqual(-100.0, p.GetSecond());
        }

        TEST_METHOD(TestInvalidCoordinates)
        {
            Point p;

            Assert::IsFalse(p.SetFirst(101));
            Assert::IsFalse(p.SetSecond(-101));
        }

        TEST_METHOD(TestInvalidInit)
        {
            Point p;

            bool result = p.Init(150, 50);

            Assert::IsFalse(result);
        }
    };
}