#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <sstream>
#include "../lab3.1/Number.h"
#include "../lab3.1/Real.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab3_1_Tests
{
    TEST_CLASS(NumberTests)
    {
    public:
        TEST_METHOD(TestNumberDefaultConstructor)
        {
            Number number;

            Assert::AreEqual(0.0f, number.getValue(), 0.0001f);
        }

        TEST_METHOD(TestNumberParameterizedConstructor)
        {
            Number number(15.5f);

            Assert::AreEqual(15.5f, number.getValue(), 0.0001f);
        }

        TEST_METHOD(TestNumberCopyConstructor)
        {
            Number original(25.0f);
            Number copy(original);

            Assert::AreEqual(25.0f, copy.getValue(), 0.0001f);
        }

        TEST_METHOD(TestNumberSetterAndGetter)
        {
            Number number;

            number.setValue(42.5f);

            Assert::AreEqual(42.5f, number.getValue(), 0.0001f);
        }

        TEST_METHOD(TestNumberAddition)
        {
            Number a(10.0f);
            Number b(5.0f);

            Number result = a.add(b);

            Assert::AreEqual(15.0f, result.getValue(), 0.0001f);
        }

        TEST_METHOD(TestNumberDivision)
        {
            Number a(20.0f);
            Number b(4.0f);

            Number result = a.divide(b);

            Assert::AreEqual(5.0f, result.getValue(), 0.0001f);
        }

        TEST_METHOD(TestNumberStringConversion)
        {
            Number number(12.5f);

            std::string result = (std::string)number;

            Assert::AreEqual(
                std::string("12.5"),
                result
            );
        }

        TEST_METHOD(TestNumberOutputOperator)
        {
            Number number(15.0f);

            std::stringstream ss;
            ss << number;

            Assert::AreEqual(
                std::string("15"),
                ss.str()
            );
        }
    };

    TEST_CLASS(RealTests)
    {
    public:
        TEST_METHOD(TestRealDefaultConstructor)
        {
            Real number;

            Assert::AreEqual(0.0f, number.getValue(), 0.0001f);
        }

        TEST_METHOD(TestRealParameterizedConstructor)
        {
            Real number(16.0f);

            Assert::AreEqual(16.0f, number.getValue(), 0.0001f);
        }

        TEST_METHOD(TestRealCopyConstructor)
        {
            Real original(25.0f);
            Real copy(original);

            Assert::AreEqual(25.0f, copy.getValue(), 0.0001f);
        }

        TEST_METHOD(TestRealPower)
        {
            Real number(2.0f);

            Real result = number.power(3.0f);

            Assert::AreEqual(8.0f, result.getValue(), 0.0001f);
        }

        TEST_METHOD(TestRealFractionalPower)
        {
            Real number(16.0f);

            Real result = number.power(0.5f);

            Assert::AreEqual(4.0f, result.getValue(), 0.0001f);
        }

        TEST_METHOD(TestRealNaturalLogarithm)
        {
            Real number(1.0f);

            Real result = number.logarithm();

            Assert::AreEqual(0.0f, result.getValue(), 0.0001f);
        }

        TEST_METHOD(TestRealNaturalLogarithmOfE)
        {
            Real number(2.7182818f);

            Real result = number.logarithm();

            Assert::AreEqual(1.0f, result.getValue(), 0.0001f);
        }

        TEST_METHOD(TestRealLogarithmWithBase)
        {
            Real number(8.0f);

            Real result = number.logarithm(2.0f);

            Assert::AreEqual(3.0f, result.getValue(), 0.0001f);
        }

        TEST_METHOD(TestRealStringConversion)
        {
            Real number(16.0f);

            std::string result = (std::string)number;

            Assert::AreEqual(
                std::string("Real number: 16"),
                result
            );
        }

        TEST_METHOD(TestRealInheritedAddition)
        {
            Real a(10.0f);
            Real b(20.0f);

            Number result = a.add(b);

            Assert::AreEqual(30.0f, result.getValue(), 0.0001f);
        }

        TEST_METHOD(TestRealInheritedDivision)
        {
            Real a(30.0f);
            Real b(5.0f);

            Number result = a.divide(b);

            Assert::AreEqual(6.0f, result.getValue(), 0.0001f);
        }

        TEST_METHOD(TestRealInheritedSetter)
        {
            Real number;

            number.setValue(50.0f);

            Assert::AreEqual(50.0f, number.getValue(), 0.0001f);
        }
    };
}
