#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1.2/Time.h"
#include "../lab1.2/Time.cpp"
#include "../lab1.2/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TimeUnitTests
{
    TEST_CLASS(TimeTests)
    {
    public:

        TEST_METHOD(SetHour_ValidValue)
        {
            Time t;

            bool result = t.setHour(16);

            Assert::IsTrue(result);
            Assert::AreEqual(16, t.getHour());
        }

        TEST_METHOD(SetHour_MinValue)
        {
            Time t;

            bool result = t.setHour(0);

            Assert::IsTrue(result);
            Assert::AreEqual(0, t.getHour());
        }

        TEST_METHOD(SetHour_MaxValue)
        {
            Time t;

            bool result = t.setHour(23);

            Assert::IsTrue(result);
            Assert::AreEqual(23, t.getHour());
        }

        TEST_METHOD(SetHour_InvalidValue)
        {
            Time t;

            bool result = t.setHour(24);

            Assert::IsFalse(result);
        }

        TEST_METHOD(SetMinute_ValidValue)
        {
            Time t;

            bool result = t.setMinute(18);

            Assert::IsTrue(result);
            Assert::AreEqual(18, t.getMinute());
        }

        TEST_METHOD(SetMinute_MinValue)
        {
            Time t;

            bool result = t.setMinute(0);

            Assert::IsTrue(result);
            Assert::AreEqual(0, t.getMinute());
        }

        TEST_METHOD(SetMinute_MaxValue)
        {
            Time t;

            bool result = t.setMinute(59);

            Assert::IsTrue(result);
            Assert::AreEqual(59, t.getMinute());
        }

        TEST_METHOD(SetMinute_InvalidValue)
        {
            Time t;

            bool result = t.setMinute(60);

            Assert::IsFalse(result);
        }

        TEST_METHOD(SetSecond_ValidValue)
        {
            Time t;

            bool result = t.setSecond(3);

            Assert::IsTrue(result);
            Assert::AreEqual(3, t.getSecond());
        }

        TEST_METHOD(SetSecond_MinValue)
        {
            Time t;

            bool result = t.setSecond(0);

            Assert::IsTrue(result);
            Assert::AreEqual(0, t.getSecond());
        }

        TEST_METHOD(SetSecond_MaxValue)
        {
            Time t;

            bool result = t.setSecond(59);

            Assert::IsTrue(result);
            Assert::AreEqual(59, t.getSecond());
        }

        TEST_METHOD(SetSecond_InvalidValue)
        {
            Time t;

            bool result = t.setSecond(60);

            Assert::IsFalse(result);
        }

        TEST_METHOD(Init_ValidValues)
        {
            Time t;

            bool result = t.Init(16, 18, 3);

            Assert::IsTrue(result);
            Assert::AreEqual(16, t.getHour());
            Assert::AreEqual(18, t.getMinute());
            Assert::AreEqual(3, t.getSecond());
        }

        TEST_METHOD(Init_InvalidHour)
        {
            Time t;

            bool result = t.Init(24, 18, 3);

            Assert::IsFalse(result);
        }

        TEST_METHOD(Init_InvalidMinute)
        {
            Time t;

            bool result = t.Init(16, 60, 3);

            Assert::IsFalse(result);
        }

        TEST_METHOD(Init_InvalidSecond)
        {
            Time t;

            bool result = t.Init(16, 18, 60);

            Assert::IsFalse(result);
        }

        TEST_METHOD(Init_BoundaryValues)
        {
            Time t;

            bool result = t.Init(23, 59, 59);

            Assert::IsTrue(result);
            Assert::AreEqual(23, t.getHour());
            Assert::AreEqual(59, t.getMinute());
            Assert::AreEqual(59, t.getSecond());
        }

        TEST_METHOD(Init_MinimumValues)
        {
            Time t;

            bool result = t.Init(0, 0, 0);

            Assert::IsTrue(result);
            Assert::AreEqual(0, t.getHour());
            Assert::AreEqual(0, t.getMinute());
            Assert::AreEqual(0, t.getSecond());
        }

        TEST_METHOD(MakeTime_ValidValues)
        {
            Time t = makeTime(16, 18, 3);

            Assert::AreEqual(16, t.getHour());
            Assert::AreEqual(18, t.getMinute());
            Assert::AreEqual(3, t.getSecond());
        }
    };
}