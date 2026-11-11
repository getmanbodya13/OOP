#include "pch.h"
#include "CppUnitTest.h"
#include "../lab4.3/ArrayNumbers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArrayNumbersTests
{
    TEST_CLASS(OctalTests)
    {
    public:

        TEST_METHOD(TestOctalAddition)
        {
            Octal a("157");
            Octal b("23");

            Octal result = a + b;

            Assert::AreEqual(
                string("202"),
                result.toString()
            );
        }

        TEST_METHOD(TestOctalSubtraction)
        {
            Octal a("157");
            Octal b("23");

            Octal result = a - b;

            Assert::AreEqual(
                string("134"),
                result.toString()
            );
        }

        TEST_METHOD(TestOctalMultiplication)
        {
            Octal a("157");
            Octal b("23");

            Octal result = a * b;

            Assert::AreEqual(
                string("4075"),
                result.toString()
            );
        }

        TEST_METHOD(TestOctalDivision)
        {
            Octal a("157");
            Octal b("23");

            Octal result = a / b;

            Assert::AreEqual(
                string("5"),
                result.toString()
            );
        }

        TEST_METHOD(TestOctalRemainder)
        {
            Octal a("157");
            Octal b("23");

            Octal result = a % b;

            Assert::AreEqual(
                string("20"),
                result.toString()
            );
        }

        TEST_METHOD(TestOctalComparison)
        {
            Octal a("157");
            Octal b("23");

            Assert::IsTrue(a > b);
            Assert::IsFalse(a < b);
            Assert::IsFalse(a == b);
        }

        TEST_METHOD(TestOctalIndexing)
        {
            Octal a("157");

            Assert::AreEqual(
                (unsigned char)7,
                a[0]
            );

            Assert::AreEqual(
                (unsigned char)5,
                a[1]
            );
        }

        TEST_METHOD(TestOctalDivisionByZero)
        {
            Octal a("157");
            Octal b("0");

            Assert::ExpectException<domain_error>(
                [&]() { a / b; }
            );
        }
    };


    TEST_CLASS(HexTests)
    {
    public:
        TEST_METHOD(TestHexAddition)
        {
            Hex a("AF");
            Hex b("12");

            Hex result = a + b;

            Assert::AreEqual(
                string("C1"),
                result.toString()
            );
        }

        TEST_METHOD(TestHexSubtraction)
        {
            Hex a("AF");
            Hex b("12");

            Hex result = a - b;

            Assert::AreEqual(
                string("9D"),
                result.toString()
            );
        }

        TEST_METHOD(TestHexMultiplication)
        {
            Hex a("AF");
            Hex b("12");

            Hex result = a * b;

            Assert::AreEqual(
                string("C4E"),
                result.toString()
            );
        }

        TEST_METHOD(TestHexDivision)
        {
            Hex a("AF");
            Hex b("12");

            Assert::AreEqual(
                string("9"),
                (a / b).toString()
            );

            Assert::AreEqual(
                string("D"),
                (a % b).toString()
            );
        }

        TEST_METHOD(TestHexComparison)
        {
            Hex a("AF");
            Hex b("12");

            Assert::IsTrue(a > b);
            Assert::IsFalse(a == b);
        }
    };


    TEST_CLASS(PolymorphismTests)
    {
    public:

        TEST_METHOD(TestVirtualOctalAddition)
        {
            Octal a("157");
            Octal b("23");

            unique_ptr<Array> result = a.add(b);

            Assert::AreEqual(
                string("Octal"),
                result->typeName()
            );

            Assert::AreEqual(
                string("202"),
                static_cast<Octal*>(
                    result.get()
                    )->toString()
            );
        }

        TEST_METHOD(TestVirtualHexAddition)
        {
            Hex a("AF");
            Hex b("12");

            unique_ptr<Array> result = a.add(b);

            Assert::AreEqual(
                string("Hex"),
                result->typeName()
            );

            Assert::AreEqual(
                string("C1"),
                static_cast<Hex*>(
                    result.get()
                    )->toString()
            );
        }

        TEST_METHOD(TestPolymorphicObjectType)
        {
            unique_ptr<Array> obj1 =
                make_unique<Octal>("157");

            unique_ptr<Array> obj2 =
                make_unique<Hex>("AF");

            Assert::AreEqual(
                string("Octal"),
                obj1->typeName()
            );

            Assert::AreEqual(
                string("Hex"),
                obj2->typeName()
            );
        }
    };
}
