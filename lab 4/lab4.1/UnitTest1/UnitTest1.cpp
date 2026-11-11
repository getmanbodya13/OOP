#include "CppUnitTest.h"
#include "../lab4.1/Equations.h"
#include <typeinfo>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab4_1Tests
{
    const double EPS = 1e-9;

    TEST_CLASS(LinearEquationTests)
    {
    public:
        TEST_METHOD(OneRoot)
        {
            LinearEquation eq(2, -4);
            double x1 = 0, x2 = 0;
            int n = eq.koreni_rivnyannya(x1, x2);
            Assert::AreEqual(1, n);
            Assert::AreEqual(2.0, x1, EPS);
        }

        TEST_METHOD(NegativeRoot)
        {
            LinearEquation eq(4, 10);             
            double x1 = 0, x2 = 0;
            Assert::AreEqual(1, eq.koreni_rivnyannya(x1, x2));
            Assert::AreEqual(-2.5, x1, EPS);
        }

        TEST_METHOD(NoRoots_AZero_BNonZero)
        {
            LinearEquation eq(0, 5);             
            double x1 = 0, x2 = 0;
            Assert::AreEqual(0, eq.koreni_rivnyannya(x1, x2));
        }

        TEST_METHOD(InfiniteSolutions)
        {
            LinearEquation eq(0, 0);              
            double x1 = 0, x2 = 0;
            Assert::AreEqual(-1, eq.koreni_rivnyannya(x1, x2));
        }
    };

    TEST_CLASS(QuadraticEquationTests)
    {
    public:
        TEST_METHOD(TwoRoots)
        {
            QuadraticEquation eq(1, -5, 6);        
            double x1 = 0, x2 = 0;
            Assert::AreEqual(2, eq.koreni_rivnyannya(x1, x2));
            Assert::AreEqual(3.0, x1, EPS);
            Assert::AreEqual(2.0, x2, EPS);
        }

        TEST_METHOD(OneRoot_ZeroDiscriminant)
        {
            QuadraticEquation eq(1, 2, 1);        
            double x1 = 0, x2 = 0;
            Assert::AreEqual(1, eq.koreni_rivnyannya(x1, x2));
            Assert::AreEqual(-1.0, x1, EPS);
            Assert::AreEqual(-1.0, x2, EPS);
        }

        TEST_METHOD(NoRealRoots_NegativeDiscriminant)
        {
            QuadraticEquation eq(1, 0, 4);        
            double x1 = 0, x2 = 0;
            Assert::AreEqual(0, eq.koreni_rivnyannya(x1, x2));
        }

        TEST_METHOD(DegenerateToLinear)
        {
            QuadraticEquation eq(0, 2, -6);       
            double x1 = 0, x2 = 0;
            Assert::AreEqual(1, eq.koreni_rivnyannya(x1, x2));
            Assert::AreEqual(3.0, x1, EPS);
        }

        TEST_METHOD(DegenerateNoRoots)
        {
            QuadraticEquation eq(0, 0, 7);         
            double x1 = 0, x2 = 0;
            Assert::AreEqual(0, eq.koreni_rivnyannya(x1, x2));
        }

        TEST_METHOD(DegenerateInfiniteSolutions)
        {
            QuadraticEquation eq(0, 0, 0);
            double x1 = 0, x2 = 0;
            Assert::AreEqual(-1, eq.koreni_rivnyannya(x1, x2));
        }
    };

    TEST_CLASS(PolymorphismTests)
    {
    public:
        TEST_METHOD(VirtualCallThroughBasePointer)
        {
            Equation* arr[2];
            arr[0] = new LinearEquation(2, -4);
            arr[1] = new QuadraticEquation(1, -5, 6);

            double x1 = 0, x2 = 0;
            Assert::AreEqual(1, arr[0]->koreni_rivnyannya(x1, x2));
            Assert::AreEqual(2.0, x1, EPS);

            Assert::AreEqual(2, arr[1]->koreni_rivnyannya(x1, x2));
            Assert::AreEqual(3.0, x1, EPS);
            Assert::AreEqual(2.0, x2, EPS);

            delete arr[0];
            delete arr[1];
        }

        TEST_METHOD(RttiReturnsRealType)
        {
            Equation* p1 = new LinearEquation(1, 1);
            Equation* p2 = new QuadraticEquation(1, 1, 1);

            Assert::IsTrue(typeid(*p1) == typeid(LinearEquation));
            Assert::IsTrue(typeid(*p2) == typeid(QuadraticEquation));
            Assert::IsFalse(typeid(*p1) == typeid(QuadraticEquation));

            delete p1;
            delete p2;
        }
    };
}