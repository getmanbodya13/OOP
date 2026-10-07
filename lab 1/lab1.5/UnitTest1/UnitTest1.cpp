#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1.5/Number.h"
#include "../lab1.5/Real.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(NumberTests)
    {
    public:

        TEST_METHOD(Number_InitAndGetValue)
        {
            Number number;

            number.Init(15.5f);

            Assert::AreEqual(15.5f, number.getValue(), 0.001f);
        }


        TEST_METHOD(Number_SetValue)
        {
            Number number;

            number.Init(10.0f);
            number.setValue(25.5f);

            Assert::AreEqual(25.5f, number.getValue(), 0.001f);
        }

        TEST_METHOD(Number_ToString)
        {
            Number number;

            number.Init(12.345f);

            Assert::AreEqual(
                std::string("12.35"),
                number.toString()
            );
        }

        TEST_METHOD(Number_Add)
        {
            Number first;
            Number second;

            first.Init(10.0f);
            second.Init(5.0f);

            Number result = first.add(second);

            Assert::AreEqual(
                15.0f,
                result.getValue(),
                0.001f
            );
        }

        TEST_METHOD(Number_AddNegative)
        {
            Number first;
            Number second;

            first.Init(-10.0f);
            second.Init(4.0f);

            Number result = first.add(second);

            Assert::AreEqual(
                -6.0f,
                result.getValue(),
                0.001f
            );
        }

        TEST_METHOD(Number_Divide)
        {
            Number first;
            Number second;

            first.Init(20.0f);
            second.Init(5.0f);

            Number result = first.divide(second);

            Assert::AreEqual(
                4.0f,
                result.getValue(),
                0.001f
            );
        }

        TEST_METHOD(Number_DivideFraction)
        {
            Number first;
            Number second;

            first.Init(7.5f);
            second.Init(2.5f);

            Number result = first.divide(second);

            Assert::AreEqual(
                3.0f,
                result.getValue(),
                0.001f
            );
        }

        TEST_METHOD(Number_DivideByZero)
        {
            Number first;
            Number zero;

            first.Init(10.0f);
            zero.Init(0.0f);

            Assert::ExpectException<std::invalid_argument>(
                [&]()
                {
                    first.divide(zero);
                }
            );
        }
    };


    TEST_CLASS(RealTests)
    {
    public:

        TEST_METHOD(Real_InitAndGetNumber)
        {
            Number number;
            number.Init(25.0f);

            Real real;
            real.Init(number);

            Number result = real.getNumber();

            Assert::AreEqual(
                25.0f,
                result.getValue(),
                0.001f
            );
        }

        TEST_METHOD(Real_SetNumber)
        {
            Number first;
            Number second;

            first.Init(10.0f);
            second.Init(50.0f);

            Real real;
            real.Init(first);

            real.setNumber(second);

            Assert::AreEqual(
                50.0f,
                real.getNumber().getValue(),
                0.001f
            );
        }


        TEST_METHOD(Real_Power)
        {
            Number number;
            number.Init(5.0f);

            Real real;
            real.Init(number);

            float result = real.power(3.0f);

            Assert::AreEqual(
                125.0f,
                result,
                0.001f
            );
        }

        TEST_METHOD(Real_PowerFraction)
        {
            Number number;
            number.Init(16.0f);

            Real real;
            real.Init(number);

            float result = real.power(0.5f);

            Assert::AreEqual(
                4.0f,
                result,
                0.001f
            );
        }

        TEST_METHOD(Real_PowerZero)
        {
            Number number;
            number.Init(10.0f);

            Real real;
            real.Init(number);

            float result = real.power(0.0f);

            Assert::AreEqual(
                1.0f,
                result,
                0.001f
            );
        }

        TEST_METHOD(Real_Logarithm)
        {
            Number number;
            number.Init(1.0f);

            Real real;
            real.Init(number);

            float result = real.logarithm();

            Assert::AreEqual(
                0.0f,
                result,
                0.001f
            );
        }

        TEST_METHOD(Real_LogarithmPositive)
        {
            Number number;
            number.Init(2.7182818f);

            Real real;
            real.Init(number);

            float result = real.logarithm();

            Assert::AreEqual(
                1.0f,
                result,
                0.001f
            );
        }

        TEST_METHOD(Real_LogarithmZero)
        {
            Number number;
            number.Init(0.0f);

            Real real;
            real.Init(number);

            Assert::ExpectException<std::invalid_argument>(
                [&]()
                {
                    real.logarithm();
                }
            );
        }

        TEST_METHOD(Real_LogarithmNegative)
        {
            Number number;
            number.Init(-10.0f);

            Real real;
            real.Init(number);

            Assert::ExpectException<std::invalid_argument>(
                [&]()
                {
                    real.logarithm();
                }
            );
        }

        TEST_METHOD(Real_NegativeFractionalPower)
        {
            Number number;
            number.Init(-4.0f);

            Real real;
            real.Init(number);

            Assert::ExpectException<std::invalid_argument>(
                [&]()
                {
                    real.power(0.5f);
                }
            );
        }

        TEST_METHOD(Real_ToString)
        {
            Number number;
            number.Init(25.678f);

            Real real;
            real.Init(number);

            Assert::AreEqual(
                std::string("25.68"),
                real.toString()
            );
        }
    };
}