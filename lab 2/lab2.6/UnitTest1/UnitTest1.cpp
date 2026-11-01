#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab2.6/Real.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{
    TEST_CLASS(NumberTests)
    {
    public:

        TEST_METHOD(TestDefaultConstructor)
        {
            Real::Number n;

            Assert::AreEqual(0.0f, n.getValue());
        }

        TEST_METHOD(TestInitializationConstructor)
        {
            Real::Number n(15.5f);

            Assert::AreEqual(15.5f, n.getValue());
        }

        TEST_METHOD(TestCopyConstructor)
        {
            Real::Number n1(10.0f);
            Real::Number n2(n1);

            Assert::AreEqual(n1.getValue(), n2.getValue());
        }

        TEST_METHOD(TestSetAndGetValue)
        {
            Real::Number n;

            n.setValue(25.0f);

            Assert::AreEqual(25.0f, n.getValue());
        }

        TEST_METHOD(TestAssignmentOperator)
        {
            Real::Number n1(12.0f);
            Real::Number n2;

            n2 = n1;

            Assert::AreEqual(12.0f, n2.getValue());
        }

        TEST_METHOD(TestAddition)
        {
            Real::Number n1(10.0f);
            Real::Number n2(5.0f);

            Real::Number result = n1 + n2;

            Assert::AreEqual(15.0f, result.getValue());
        }

        TEST_METHOD(TestDivision)
        {
            Real::Number n1(20.0f);
            Real::Number n2(4.0f);

            Real::Number result = n1 / n2;

            Assert::AreEqual(5.0f, result.getValue());
        }

        TEST_METHOD(TestDivisionByZero)
        {
            Real::Number n1(10.0f);
            Real::Number n2(0.0f);

            Assert::ExpectException<invalid_argument>([&]()
                {
                    n1 / n2;
                });
        }

        TEST_METHOD(TestAddMethod)
        {
            Real::Number n1(7.0f);
            Real::Number n2(3.0f);

            Real::Number result = n1.add(n2);

            Assert::AreEqual(10.0f, result.getValue());
        }

        TEST_METHOD(TestDivideMethod)
        {
            Real::Number n1(18.0f);
            Real::Number n2(3.0f);

            Real::Number result = n1.divide(n2);

            Assert::AreEqual(6.0f, result.getValue());
        }

        TEST_METHOD(TestPrefixIncrement)
        {
            Real::Number n(5.0f);

            ++n;

            Assert::AreEqual(6.0f, n.getValue());
        }

        TEST_METHOD(TestPostfixIncrement)
        {
            Real::Number n(5.0f);

            Real::Number old = n++;

            Assert::AreEqual(5.0f, old.getValue());
            Assert::AreEqual(6.0f, n.getValue());
        }

        TEST_METHOD(TestPrefixDecrement)
        {
            Real::Number n(5.0f);

            --n;

            Assert::AreEqual(4.0f, n.getValue());
        }

        TEST_METHOD(TestPostfixDecrement)
        {
            Real::Number n(5.0f);

            Real::Number old = n--;

            Assert::AreEqual(5.0f, old.getValue());
            Assert::AreEqual(4.0f, n.getValue());
        }

        TEST_METHOD(TestStringConversion)
        {
            Real::Number n(10.0f);

            string result = static_cast<string>(n);

            Assert::AreEqual(string("10"), result);
        }

        TEST_METHOD(TestNumberCounter)
        {
            int initialCount = Real::Number::getCounter();

            {
                Real::Number n1;
                Real::Number n2(5.0f);

                Assert::AreEqual(initialCount + 2,
                    Real::Number::getCounter());
            }

            Assert::AreEqual(initialCount,
                Real::Number::getCounter());
        }
    };


    TEST_CLASS(RealTests)
    {
    public:

        TEST_METHOD(TestDefaultConstructor)
        {
            Real r;

            Assert::AreEqual(0.0f, r.getValue());
        }

        TEST_METHOD(TestInitializationConstructor)
        {
            Real r(16.0f);

            Assert::AreEqual(16.0f, r.getValue());
        }

        TEST_METHOD(TestCopyConstructor)
        {
            Real r1(25.0f);
            Real r2(r1);

            Assert::AreEqual(r1.getValue(), r2.getValue());
        }

        TEST_METHOD(TestSetAndGetValue)
        {
            Real r;

            r.setValue(30.0f);

            Assert::AreEqual(30.0f, r.getValue());
        }

        TEST_METHOD(TestAssignmentOperator)
        {
            Real r1(40.0f);
            Real r2;

            r2 = r1;

            Assert::AreEqual(40.0f, r2.getValue());
        }

        TEST_METHOD(TestPower)
        {
            Real r(2.0f);

            float result = r.power(3.0f);

            Assert::AreEqual(8.0f, result);
        }

        TEST_METHOD(TestFractionalPower)
        {
            Real r(9.0f);

            float result = r.power(0.5f);

            Assert::AreEqual(3.0f, result, 0.0001f);
        }

        TEST_METHOD(TestLogarithm)
        {
            Real r(1.0f);

            float result = r.logarithm();

            Assert::AreEqual(0.0f, result);
        }

        TEST_METHOD(TestLogarithmOfNegativeNumber)
        {
            Real r(-5.0f);

            Assert::ExpectException<invalid_argument>([&]()
                {
                    r.logarithm();
                });
        }

        TEST_METHOD(TestLogarithmOfZero)
        {
            Real r(0.0f);

            Assert::ExpectException<invalid_argument>([&]()
                {
                    r.logarithm();
                });
        }

        TEST_METHOD(TestPrefixIncrement)
        {
            Real r(5.0f);

            ++r;

            Assert::AreEqual(6.0f, r.getValue());
        }

        TEST_METHOD(TestPostfixIncrement)
        {
            Real r(5.0f);

            Real old = r++;

            Assert::AreEqual(5.0f, old.getValue());
            Assert::AreEqual(6.0f, r.getValue());
        }

        TEST_METHOD(TestPrefixDecrement)
        {
            Real r(5.0f);

            --r;

            Assert::AreEqual(4.0f, r.getValue());
        }

        TEST_METHOD(TestPostfixDecrement)
        {
            Real r(5.0f);

            Real old = r--;

            Assert::AreEqual(5.0f, old.getValue());
            Assert::AreEqual(4.0f, r.getValue());
        }

        TEST_METHOD(TestStringConversion)
        {
            Real r(12.0f);

            string result = static_cast<string>(r);

            Assert::AreEqual(
                string("Real number = 12"), result);
        }

        TEST_METHOD(TestRealCounter)
        {
            int initialCount = Real::getCounter();

            {
                Real r1;
                Real r2(10.0f);

                Assert::AreEqual(initialCount + 2,
                    Real::getCounter());
            }

            Assert::AreEqual(initialCount,
                Real::getCounter());
        }

        TEST_METHOD(TestNestedNumberCounter)
        {
            int initialCount = Real::Number::getCounter();

            {
                Real r1(10.0f);

                Assert::AreEqual(initialCount + 1,
                    Real::Number::getCounter());
            }

            Assert::AreEqual(initialCount,
                Real::Number::getCounter());
        }
    };
}
