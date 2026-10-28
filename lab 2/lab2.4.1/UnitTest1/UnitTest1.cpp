#include "pch.h"
#include "CppUnitTest.h"
#include "../lab2.4.1/Vector.h"
#include "../lab2.4.1/Vector.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VectorUnitTests
{
    TEST_CLASS(VectorTests)
    {
    public:

        TEST_METHOD(DefaultConstructorTest)
        {
            Vector v;

            Assert::AreEqual(0, v.getSize());
        }

        TEST_METHOD(InitializationConstructorTest)
        {
            Vector v(3);

            Assert::AreEqual(3, v.getSize());
            Assert::AreEqual(0, v[0]);
            Assert::AreEqual(0, v[1]);
            Assert::AreEqual(0, v[2]);
        }

        TEST_METHOD(InitializerListConstructorTest)
        {
            Vector v = { 1, 2, 3 };

            Assert::AreEqual(3, v.getSize());
            Assert::AreEqual(1, v[0]);
            Assert::AreEqual(2, v[1]);
            Assert::AreEqual(3, v[2]);
        }

        TEST_METHOD(CopyConstructorTest)
        {
            Vector original = { 4, 5, 6 };
            Vector copy(original);

            Assert::IsTrue(copy == original);

            copy[0] = 100;

            Assert::AreEqual(4, original[0]);
            Assert::AreEqual(100, copy[0]);
        }

        TEST_METHOD(AssignmentOperatorTest)
        {
            Vector a = { 1, 2, 3 };
            Vector b;

            b = a;

            Assert::IsTrue(a == b);
        }

        TEST_METHOD(IndexingOperatorTest)
        {
            Vector v = { 10, 20, 30 };

            Assert::AreEqual(20, v[1]);

            v[1] = 50;

            Assert::AreEqual(50, v[1]);
        }

        TEST_METHOD(AccessMethodsTest)
        {
            Vector v = { 1, 2, 3 };

            Assert::AreEqual(2, v.getElement(1));

            v.setElement(1, 10);

            Assert::AreEqual(10, v.getElement(1));
        }

        TEST_METHOD(AdditionOperatorTest)
        {
            Vector a = { 1, 2, 3 };
            Vector b = { 4, 5, 6 };

            Vector result = a + b;
            Vector expected = { 5, 7, 9 };

            Assert::IsTrue(result == expected);
        }

        TEST_METHOD(AdditionDifferentSizesTest)
        {
            Vector a = { 1, 2 };
            Vector b = { 1, 2, 3 };

            Assert::ExpectException<std::invalid_argument>(
                [&]() {
                    Vector result = a + b;
                }
            );
        }

        TEST_METHOD(EqualityOperatorTest)
        {
            Vector a = { 1, 2, 3 };
            Vector b = { 1, 2, 3 };
            Vector c = { 1, 2, 4 };

            Assert::IsTrue(a == b);
            Assert::IsFalse(a == c);
        }

        TEST_METHOD(InequalityOperatorTest)
        {
            Vector a = { 1, 2, 3 };
            Vector b = { 4, 5, 6 };

            Assert::IsTrue(a != b);
        }

        TEST_METHOD(NormTest)
        {
            Vector v = { 1, 5, 3, 9 };

            Assert::AreEqual(8, v.norm());
        }

        TEST_METHOD(NormNegativeNumbersTest)
        {
            Vector v = { -5, -2, 0 };

            Assert::AreEqual(5, v.norm());
        }

        TEST_METHOD(NormEqualElementsTest)
        {
            Vector v = { 7, 7, 7 };

            Assert::AreEqual(0, v.norm());
        }

        TEST_METHOD(PrefixIncrementTest)
        {
            Vector v = { 1, 2, 3 };

            ++v;

            Vector expected = { 2, 3, 4 };

            Assert::IsTrue(v == expected);
        }

        TEST_METHOD(PostfixIncrementTest)
        {
            Vector v = { 1, 2, 3 };

            Vector old = v++;

            Vector expectedOld = { 1, 2, 3 };
            Vector expectedNew = { 2, 3, 4 };

            Assert::IsTrue(old == expectedOld);
            Assert::IsTrue(v == expectedNew);
        }

        TEST_METHOD(PrefixDecrementTest)
        {
            Vector v = { 2, 3, 4 };

            --v;

            Vector expected = { 1, 2, 3 };

            Assert::IsTrue(v == expected);
        }

        TEST_METHOD(PostfixDecrementTest)
        {
            Vector v = { 2, 3, 4 };

            Vector old = v--;

            Vector expectedOld = { 2, 3, 4 };
            Vector expectedNew = { 1, 2, 3 };

            Assert::IsTrue(old == expectedOld);
            Assert::IsTrue(v == expectedNew);
        }

        TEST_METHOD(StringConversionTest)
        {
            Vector v = { 1, 2, 3 };

            std::string result = static_cast<std::string>(v);

            Assert::AreEqual(
                std::string("[1, 2, 3]"),
                result
            );
        }

        TEST_METHOD(InvalidIndexTest)
        {
            Vector v = { 1, 2, 3 };

            Assert::ExpectException<std::out_of_range>(
                [&]() {
                    v[5] = 10;
                }
            );
        }

        TEST_METHOD(NegativeSizeTest)
        {
            Assert::ExpectException<std::invalid_argument>(
                []() {
                    Vector v(-3);
                }
            );
        }
    };
}
