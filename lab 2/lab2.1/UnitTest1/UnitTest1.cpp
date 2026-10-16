#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab2.1/Point.h"
#include "../Lab2.1/Point.cpp"

#include <sstream>
#include <string>
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PointUnitTests
{
    TEST_CLASS(ConstructorTests)
    {
    public:
        TEST_METHOD(DefaultConstructor)
        {
            Point p;

            Assert::AreEqual(0.0, p.GetFirst(), 0.0001);
            Assert::AreEqual(0.0, p.GetSecond(), 0.0001);
        }

        TEST_METHOD(InitializationConstructor)
        {
            Point p(3, 4);

            Assert::AreEqual(3.0, p.GetFirst(), 0.0001);
            Assert::AreEqual(4.0, p.GetSecond(), 0.0001);
        }

        TEST_METHOD(CopyConstructor)
        {
            Point original(5, -7);
            Point copy(original);

            Assert::AreEqual(5.0, copy.GetFirst(), 0.0001);
            Assert::AreEqual(-7.0, copy.GetSecond(), 0.0001);
        }

        TEST_METHOD(MakePointFunction)
        {
            Point p = makePoint(-5, 12);

            Assert::AreEqual(-5.0, p.GetFirst(), 0.0001);
            Assert::AreEqual(12.0, p.GetSecond(), 0.0001);
        }
    };

    TEST_CLASS(AccessTests)
    {
    public:
        TEST_METHOD(GettersAndSetters)
        {
            Point p;

            p.SetFirst(10);
            p.SetSecond(-20);

            Assert::AreEqual(10.0, p.GetFirst(), 0.0001);
            Assert::AreEqual(-20.0, p.GetSecond(), 0.0001);
        }

        TEST_METHOD(InvalidFirstCoordinate)
        {
            Point p;

            Assert::ExpectException<std::invalid_argument>(
                [&p]() { p.SetFirst(101); }
            );
        }

        TEST_METHOD(InvalidSecondCoordinate)
        {
            Point p;

            Assert::ExpectException<std::invalid_argument>(
                [&p]() { p.SetSecond(-101); }
            );
        }

        TEST_METHOD(InvalidInitialization)
        {
            Assert::ExpectException<std::invalid_argument>(
                []() { Point p(101, 0); }
            );
        }

        TEST_METHOD(BoundaryCoordinates)
        {
            Point p(-100, 100);

            Assert::AreEqual(-100.0, p.GetFirst(), 0.0001);
            Assert::AreEqual(100.0, p.GetSecond(), 0.0001);
        }
    };

    TEST_CLASS(OperationTests)
    {
    public:
        TEST_METHOD(AssignmentOperator)
        {
            Point p1(2, 3);
            Point p2;

            p2 = p1;

            Assert::AreEqual(2.0, p2.GetFirst(), 0.0001);
            Assert::AreEqual(3.0, p2.GetSecond(), 0.0001);
        }

        TEST_METHOD(DistanceFromOrigin)
        {
            Point p(3, 4);

            Assert::AreEqual(5.0, p.distance(), 0.0001);
        }

        TEST_METHOD(DistanceForNegativeCoordinates)
        {
            Point p(-5, 12);

            Assert::AreEqual(13.0, p.distance(), 0.0001);
        }

        TEST_METHOD(PrefixIncrement)
        {
            Point p(5, 7);

            Point& result = ++p;

            Assert::AreEqual(6.0, p.GetFirst(), 0.0001);
            Assert::AreEqual(7.0, p.GetSecond(), 0.0001);
            Assert::IsTrue(&result == &p);
        }

        TEST_METHOD(PrefixDecrement)
        {
            Point p(5, 7);

            --p;

            Assert::AreEqual(4.0, p.GetFirst(), 0.0001);
            Assert::AreEqual(7.0, p.GetSecond(), 0.0001);
        }

        TEST_METHOD(PostfixIncrement)
        {
            Point p(5, 7);

            Point old = p++;

            Assert::AreEqual(5.0, old.GetFirst(), 0.0001);
            Assert::AreEqual(7.0, old.GetSecond(), 0.0001);
            Assert::AreEqual(5.0, p.GetFirst(), 0.0001);
            Assert::AreEqual(8.0, p.GetSecond(), 0.0001);
        }

        TEST_METHOD(PostfixDecrement)
        {
            Point p(5, 7);

            Point old = p--;

            Assert::AreEqual(5.0, old.GetFirst(), 0.0001);
            Assert::AreEqual(7.0, old.GetSecond(), 0.0001);
            Assert::AreEqual(5.0, p.GetFirst(), 0.0001);
            Assert::AreEqual(6.0, p.GetSecond(), 0.0001);
        }

        TEST_METHOD(StringConversion)
        {
            Point p(3, 4);

            std::string result = static_cast<std::string>(p);

            Assert::IsTrue(
                result.find("Point(x = 3") != std::string::npos
            );
            Assert::IsTrue(
                result.find("y = 4") != std::string::npos
            );
        }
    };

    TEST_CLASS(StreamTests)
    {
    public:
        TEST_METHOD(InputOperator)
        {
            Point p;
            std::istringstream input("3 4");

            input >> p;

            Assert::AreEqual(3.0, p.GetFirst(), 0.0001);
            Assert::AreEqual(4.0, p.GetSecond(), 0.0001);
        }

        TEST_METHOD(OutputOperator)
        {
            Point p(3, 4);
            std::ostringstream output;

            output << p;

            Assert::IsTrue(
                output.str().find("Point(x = 3") != std::string::npos
            );
            Assert::IsTrue(
                output.str().find("y = 4") != std::string::npos
            );
        }
    };
}
