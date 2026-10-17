#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab2.3\Complex.h"
#include "..\lab2.3\Complex.cpp"

#include <string>
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ComplexTests
{
    TEST_CLASS(ComplexUnitTests)
    {
    public:

        TEST_METHOD(DefaultConstructor)
        {
            Complex c;

            Assert::AreEqual(0.0, c.GetX(), 1e-9);
            Assert::AreEqual(0.0, c.GetY(), 1e-9);
        }

        TEST_METHOD(InitializationConstructor)
        {
            Complex c(3.0, 4.0);

            Assert::AreEqual(3.0, c.GetX(), 1e-9);
            Assert::AreEqual(4.0, c.GetY(), 1e-9);
        }

        TEST_METHOD(CopyConstructor)
        {
            Complex original(5.0, -2.0);
            Complex copy(original);

            Assert::AreEqual(5.0, copy.GetX(), 1e-9);
            Assert::AreEqual(-2.0, copy.GetY(), 1e-9);
        }

        TEST_METHOD(AssignmentOperator)
        {
            Complex a(2.0, 3.0);
            Complex b;

            b = a;

            Assert::AreEqual(2.0, b.GetX(), 1e-9);
            Assert::AreEqual(3.0, b.GetY(), 1e-9);
        }

        TEST_METHOD(SelfAssignment)
        {
            Complex a(7.0, -1.0);

            a = a;

            Assert::AreEqual(7.0, a.GetX(), 1e-9);
            Assert::AreEqual(-1.0, a.GetY(), 1e-9);
        }

        TEST_METHOD(SettersAndGetters)
        {
            Complex c;

            c.SetX(8.5);
            c.SetY(-3.5);

            Assert::AreEqual(8.5, c.GetX(), 1e-9);
            Assert::AreEqual(-3.5, c.GetY(), 1e-9);
        }

        TEST_METHOD(InitMethod)
        {
            Complex c;
            c.Init(6.0, 9.0);

            Assert::AreEqual(6.0, c.GetX(), 1e-9);
            Assert::AreEqual(9.0, c.GetY(), 1e-9);
        }

        TEST_METHOD(SubtractionMethod)
        {
            Complex a(8.0, 6.0);
            Complex b(2.0, 3.0);

            Complex result = a.sub(b);

            Assert::AreEqual(6.0, result.GetX(), 1e-9);
            Assert::AreEqual(3.0, result.GetY(), 1e-9);
        }

        TEST_METHOD(SubtractionOperator)
        {
            Complex a(8.0, 6.0);
            Complex b(2.0, 3.0);

            Complex result = a - b;

            Assert::AreEqual(6.0, result.GetX(), 1e-9);
            Assert::AreEqual(3.0, result.GetY(), 1e-9);
        }

        TEST_METHOD(DivisionByZeroThrowsException)
        {
            Complex a(5.0, 2.0);
            Complex zero(0.0, 0.0);

            bool exceptionThrown = false;

            try
            {
                a.div(zero);
            }
            catch (const std::domain_error&)
            {
                exceptionThrown = true;
            }

            Assert::IsTrue(exceptionThrown);
        }

        TEST_METHOD(ConjugateMethod)
        {
            Complex c(3.0, 4.0);
            Complex result = c.conj();

            Assert::AreEqual(3.0, result.GetX(), 1e-9);
            Assert::AreEqual(-4.0, result.GetY(), 1e-9);
        }

        TEST_METHOD(PrefixIncrement)
        {
            Complex c(3.0, 4.0);

            Complex result = ++c;

            Assert::AreEqual(4.0, c.GetX(), 1e-9);
            Assert::AreEqual(4.0, c.GetY(), 1e-9);
            Assert::AreEqual(4.0, result.GetX(), 1e-9);
        }

        TEST_METHOD(PrefixDecrement)
        {
            Complex c(3.0, 4.0);

            Complex result = --c;

            Assert::AreEqual(2.0, c.GetX(), 1e-9);
            Assert::AreEqual(4.0, c.GetY(), 1e-9);
            Assert::AreEqual(2.0, result.GetX(), 1e-9);
        }

        TEST_METHOD(PostfixIncrement)
        {
            Complex c(3.0, 4.0);

            Complex old = c++;

            Assert::AreEqual(3.0, old.GetX(), 1e-9);
            Assert::AreEqual(4.0, old.GetY(), 1e-9);

            Assert::AreEqual(3.0, c.GetX(), 1e-9);
            Assert::AreEqual(5.0, c.GetY(), 1e-9);
        }

        TEST_METHOD(PostfixDecrement)
        {
            Complex c(3.0, 4.0);

            Complex old = c--;

            Assert::AreEqual(3.0, old.GetX(), 1e-9);
            Assert::AreEqual(4.0, old.GetY(), 1e-9);

            Assert::AreEqual(3.0, c.GetX(), 1e-9);
            Assert::AreEqual(3.0, c.GetY(), 1e-9);
        }

        TEST_METHOD(StringConversion)
        {
            Complex c(3.0, 4.0);

            std::string result = c.toString();

            Assert::AreEqual(
                std::string("3.00 + 4.00i"),
                result);
        }

        TEST_METHOD(StringConversionNegativeImaginary)
        {
            Complex c(3.0, -4.0);

            Assert::AreEqual(
                std::string("3.00 - 4.00i"),
                c.toString());
        }

        TEST_METHOD(InvalidRealPartThrowsException)
        {
            Complex c;
            bool exceptionThrown = false;

            try
            {
                c.SetX(
                    std::numeric_limits<double>::infinity());
            }
            catch (const std::invalid_argument&)
            {
                exceptionThrown = true;
            }

            Assert::IsTrue(exceptionThrown);
        }

        TEST_METHOD(InvalidImaginaryPartThrowsException)
        {
            Complex c;
            bool exceptionThrown = false;

            try
            {
                c.SetY(
                    std::numeric_limits<double>::quiet_NaN());
            }
            catch (const std::invalid_argument&)
            {
                exceptionThrown = true;
            }

            Assert::IsTrue(exceptionThrown);
        }

        TEST_METHOD(ArrayOfComplexObjects)
        {
            Complex arr[3] = {
                Complex(),
                Complex(1.0, 2.0),
                Complex(3.0, 4.0)
            };

            Assert::AreEqual(0.0, arr[0].GetX(), 1e-9);
            Assert::AreEqual(2.0, arr[1].GetY(), 1e-9);
            Assert::AreEqual(3.0, arr[2].GetX(), 1e-9);
        }
    };
}
