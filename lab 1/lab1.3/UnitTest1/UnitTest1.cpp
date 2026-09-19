#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1.3/Complex.h"
#include "../lab1.3/Complex.cpp"
#include "../lab1.3/main.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ComplexTests
{
    TEST_CLASS(ComplexClassTests)
    {
    public:

        TEST_METHOD(TestDefaultConstructor)
        {
            Complex c;

            Assert::AreEqual(
                std::string("0.00 + 0.00i"),
                c.toString()
            );
        }

        TEST_METHOD(TestParameterizedConstructor)
        {
            Complex c(5.0, -3.0);

            Assert::AreEqual(
                std::string("5.00 - 3.00i"),
                c.toString()
            );
        }

        TEST_METHOD(TestInit)
        {
            Complex c;

            c.Init(7.0, 4.0);

            Assert::AreEqual(
                std::string("7.00 + 4.00i"),
                c.toString()
            );
        }

        TEST_METHOD(TestToStringPositiveImaginary)
        {
            Complex c(3.5, 2.5);

            Assert::AreEqual(
                std::string("3.50 + 2.50i"),
                c.toString()
            );
        }

        TEST_METHOD(TestToStringNegativeImaginary)
        {
            Complex c(3.5, -2.5);

            Assert::AreEqual(
                std::string("3.50 - 2.50i"),
                c.toString()
            );
        }

        TEST_METHOD(TestSubtraction)
        {
            Complex c1(5.0, 7.0);
            Complex c2(2.0, 3.0);

            Complex result = c1.sub(c2);

            Assert::AreEqual(
                std::string("3.00 + 4.00i"),
                result.toString()
            );
        }

        TEST_METHOD(TestSubtractionNegativeValues)
        {
            Complex c1(-4.0, 6.0);
            Complex c2(2.0, -3.0);

            Complex result = c1.sub(c2);

            Assert::AreEqual(
                std::string("-6.00 + 9.00i"),
                result.toString()
            );
        }

        TEST_METHOD(TestDivision)
        {
            Complex c1(5.0, 3.0);
            Complex c2(2.0, -4.0);

            Complex result = c1.div(c2);

            Assert::AreEqual(
                std::string("-0.10 + 1.30i"),
                result.toString()
            );
        }

        TEST_METHOD(TestDivisionByZero)
        {
            Complex c1(5.0, 3.0);
            Complex zero(0.0, 0.0);

            bool exceptionThrown = false;

            try
            {
                c1.div(zero);
            }
            catch (const std::invalid_argument&)
            {
                exceptionThrown = true;
            }

            Assert::IsTrue(exceptionThrown);
        }

        TEST_METHOD(TestConjugate)
        {
            Complex c(5.0, 3.0);

            Complex result = c.conj();

            Assert::AreEqual(
                std::string("5.00 - 3.00i"),
                result.toString()
            );
        }

        TEST_METHOD(TestConjugateNegativeImaginary)
        {
            Complex c(5.0, -3.0);

            Complex result = c.conj();

            Assert::AreEqual(
                std::string("5.00 + 3.00i"),
                result.toString()
            );
        }

        TEST_METHOD(TestZeroRealPart)
        {
            Complex c(0.0, 5.0);

            Complex result = c.conj();

            Assert::AreEqual(
                std::string("0.00 - 5.00i"),
                result.toString()
            );
        }
    };
}