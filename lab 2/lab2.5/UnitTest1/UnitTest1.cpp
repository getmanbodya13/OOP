#include "CppUnitTest.h"
#include "../lab2.5/Number.h"
#include "../lab2.5/Real.h"

#include <stdexcept>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(NumberTests)
    {
    public:

        TEST_METHOD(DefaultConstructorTest)
        {
            Number n;
            Assert::AreEqual(0.0f, n.getValue());
        }

        TEST_METHOD(InitializationConstructorTest)
        {
            Number n(5.5f);
            Assert::AreEqual(5.5f, n.getValue());
        }

        TEST_METHOD(CopyConstructorTest)
        {
            Number first(10.0f);
            Number second(first);

            Assert::AreEqual(10.0f, second.getValue());
        }

        TEST_METHOD(SetValueTest)
        {
            Number n;
            n.setValue(12.5f);

            Assert::AreEqual(12.5f, n.getValue());
        }

        TEST_METHOD(InitTest)
        {
            Number n;
            n.Init(7.5f);

            Assert::AreEqual(7.5f, n.getValue());
        }

        TEST_METHOD(AdditionTest)
        {
            Number a(5.0f);
            Number b(3.0f);

            Number result = a.add(b);

            Assert::AreEqual(8.0f, result.getValue());
        }

        TEST_METHOD(DivisionTest)
        {
            Number a(10.0f);
            Number b(2.0f);

            Number result = a.divide(b);

            Assert::AreEqual(5.0f, result.getValue());
        }

        TEST_METHOD(DivisionByZeroTest)
        {
            Number a(10.0f);
            Number b(0.0f);

            Assert::ExpectException<std::invalid_argument>(
                [&]() { a.divide(b); }
            );
        }

        TEST_METHOD(AssignmentOperatorTest)
        {
            Number a(15.0f);
            Number b;

            b = a;

            Assert::AreEqual(15.0f, b.getValue());
        }

        TEST_METHOD(IncrementOperatorTest)
        {
            Number n(5.0f);
            ++n;

            Assert::AreEqual(6.0f, n.getValue());
        }

        TEST_METHOD(DecrementOperatorTest)
        {
            Number n(5.0f);
            --n;

            Assert::AreEqual(4.0f, n.getValue());
        }

        TEST_METHOD(PostIncrementOperatorTest)
        {
            Number n(5.0f);
            Number old = n++;

            Assert::AreEqual(5.0f, old.getValue());
            Assert::AreEqual(6.0f, n.getValue());
        }

        TEST_METHOD(PostDecrementOperatorTest)
        {
            Number n(5.0f);
            Number old = n--;

            Assert::AreEqual(5.0f, old.getValue());
            Assert::AreEqual(4.0f, n.getValue());
        }

    };

    TEST_CLASS(RealTests)
    {
    public:

        TEST_METHOD(DefaultConstructorTest)
        {
            Real r;
            Assert::AreEqual(0.0f, r.getNumber().getValue());
        }

        TEST_METHOD(InitializationConstructorTest)
        {
            Real r(5.0f);
            Assert::AreEqual(5.0f, r.getNumber().getValue());
        }

        TEST_METHOD(NumberConstructorTest)
        {
            Number n(8.0f);
            Real r(n);

            Assert::AreEqual(8.0f, r.getNumber().getValue());
        }

        TEST_METHOD(CopyConstructorTest)
        {
            Real first(12.0f);
            Real second(first);

            Assert::AreEqual(12.0f, second.getNumber().getValue());
        }

        TEST_METHOD(SetNumberTest)
        {
            Real r;
            Number n(9.0f);

            r.setNumber(n);

            Assert::AreEqual(9.0f, r.getNumber().getValue());
        }

        TEST_METHOD(AssignmentOperatorTest)
        {
            Real first(15.0f);
            Real second;

            second = first;

            Assert::AreEqual(15.0f, second.getNumber().getValue());
        }

        TEST_METHOD(IncrementOperatorTest)
        {
            Real r(5.0f);
            ++r;

            Assert::AreEqual(6.0f, r.getNumber().getValue());
        }

        TEST_METHOD(DecrementOperatorTest)
        {
            Real r(5.0f);
            --r;

            Assert::AreEqual(4.0f, r.getNumber().getValue());
        }

        TEST_METHOD(PostIncrementOperatorTest)
        {
            Real r(5.0f);
            Real old = r++;

            Assert::AreEqual(5.0f, old.getNumber().getValue());
            Assert::AreEqual(6.0f, r.getNumber().getValue());
        }

        TEST_METHOD(PostDecrementOperatorTest)
        {
            Real r(5.0f);
            Real old = r--;

            Assert::AreEqual(5.0f, old.getNumber().getValue());
            Assert::AreEqual(4.0f, r.getNumber().getValue());
        }

        TEST_METHOD(PowerTest)
        {
            Real r(5.0f);

            Assert::AreEqual(125.0f, r.power(3.0f));
        }

        TEST_METHOD(PowerZeroExponentTest)
        {
            Real r(5.0f);

            Assert::AreEqual(1.0f, r.power(0.0f));
        }

        TEST_METHOD(PowerNegativeExponentTest)
        {
            Real r(2.0f);

            Assert::AreEqual(0.25f, r.power(-2.0f));
        }

        TEST_METHOD(PowerInvalidOperationTest)
        {
            Real r(-5.0f);

            Assert::ExpectException<std::invalid_argument>(
                [&]() { r.power(0.5f); }
            );
        }

        TEST_METHOD(LogarithmTest)
        {
            Real r(1.0f);

            Assert::AreEqual(0.0f, r.logarithm(), 0.0001f);
        }

        TEST_METHOD(LogarithmOfNegativeNumberTest)
        {
            Real r(-5.0f);

            Assert::ExpectException<std::invalid_argument>(
                [&]() { r.logarithm(); }
            );
        }

        TEST_METHOD(LogarithmOfZeroTest)
        {
            Real r(0.0f);

            Assert::ExpectException<std::invalid_argument>(
                [&]() { r.logarithm(); }
            );
        }
    };
}