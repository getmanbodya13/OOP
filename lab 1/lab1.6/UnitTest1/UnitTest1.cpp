#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1.6/Real.h" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab16
{
    TEST_CLASS(RealAndNumberTests)
    {
    public:

        TEST_METHOD(TestNumberInitAndAccessors)
        {
            Real::Number num;
            num.Init(25.5f);
            Assert::AreEqual(25.5f, num.getValue(), 0.001f);

            num.setValue(10.0f);
            Assert::AreEqual(10.0f, num.getValue(), 0.001f);
        }

        TEST_METHOD(TestNumberAdd)
        {
            Real::Number n1, n2;
            n1.Init(12.5f);
            n2.Init(7.5f);
            Real::Number res = n1.add(n2);
            Assert::AreEqual(20.0f, res.getValue(), 0.001f);
        }

        TEST_METHOD(TestNumberDivide)
        {
            Real::Number n1, n2;
            n1.Init(20.0f);
            n2.Init(4.0f);
            Real::Number res = n1.divide(n2);
            Assert::AreEqual(5.0f, res.getValue(), 0.001f);
        }

        TEST_METHOD(TestNumberDivideByZeroException)
        {
            Real::Number n1, n2;
            n1.Init(10.0f);
            n2.Init(0.0f);

            Assert::ExpectException<std::invalid_argument>([&]() {
                n1.divide(n2);
                });
        }

       TEST_METHOD(TestRealPower)
        {
            Real::Number baseNum;
            baseNum.Init(3.0f);
            Real r;
            r.Init(baseNum);

            float res = r.power(3.0f); 
            Assert::AreEqual(27.0f, res, 0.001f);
        }

        TEST_METHOD(TestRealLogarithm)
        {
            Real::Number baseNum;
            baseNum.Init(2.7182818f);
            Real r;
            r.Init(baseNum);

            float res = r.logarithm();
            Assert::AreEqual(1.0f, res, 0.01f);
        }

       TEST_METHOD(TestRealLogarithmNegativeException)
        {
            Real::Number baseNum;
            baseNum.Init(-5.0f);
            Real r;
            r.Init(baseNum);

            Assert::ExpectException<std::invalid_argument>([&]() {
                r.logarithm();
                });
        }

        TEST_METHOD(TestToStringRepresentation)
        {
            Real::Number num;
            num.Init(7.8f);
            Real r;
            r.Init(num);

            Assert::AreEqual(std::string("7.80"), r.toString());
        }
    };
}