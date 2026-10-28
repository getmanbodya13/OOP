#include "pch.h"
#include "CppUnitTest.h"
#include "../lab2.4.2/Octal.h"
#include "../lab2.4.2/Octal.cpp"

#include <sstream>
#include <string>
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OctalUnitTests
{
    TEST_CLASS(OctalTests)
    {
    public:

        TEST_METHOD(DefaultConstructor)
        {
            Octal value;

            Assert::AreEqual(100, value.size());
            Assert::AreEqual(1, value.count());
            Assert::IsTrue(static_cast<std::string>(value) == "0");
        }

        TEST_METHOD(InitializationConstructor)
        {
            Octal value(20, "157");

            Assert::AreEqual(20, value.size());
            Assert::AreEqual(3, value.count());
            Assert::IsTrue(static_cast<std::string>(value) == "157");
        }

        TEST_METHOD(CopyConstructor)
        {
            Octal original(20, "735");
            Octal copy(original);

            Assert::IsTrue(static_cast<std::string>(copy) == "735");
            Assert::AreEqual(original.size(), copy.size());
            Assert::AreEqual(original.count(), copy.count());
        }

        TEST_METHOD(AssignmentOperator)
        {
            Octal a(20, "123");
            Octal b(10, "7");

            b = a;

            Assert::IsTrue(static_cast<std::string>(b) == "123");
            Assert::AreEqual(a.size(), b.size());
        }

        TEST_METHOD(AccessMethods)
        {
            Octal value(20, "157");

            Assert::AreEqual(20, value.size());
            Assert::AreEqual(3, value.count());
            Assert::AreEqual(7, static_cast<int>(value.getDigit(0)));
            Assert::AreEqual(5, static_cast<int>(value.getDigit(1)));
            Assert::AreEqual(1, static_cast<int>(value.getDigit(2)));
        }

        TEST_METHOD(SetDigit)
        {
            Octal value(20, "157");

            value.setDigit(0, 3);

            Assert::IsTrue(static_cast<std::string>(value) == "153");
        }

        TEST_METHOD(IndexingOperator)
        {
            Octal value(20, "157");

            Assert::AreEqual(7, static_cast<int>(value[0]));

            value[0] = 2;

            Assert::IsTrue(static_cast<std::string>(value) == "152");
        }

        TEST_METHOD(Addition)
        {
            Octal a(20, "157");
            Octal b(20, "24");

            Octal result = a + b;

            Assert::IsTrue(static_cast<std::string>(result) == "203");
        }

        TEST_METHOD(Subtraction)
        {
            Octal a(20, "157");
            Octal b(20, "24");

            Octal result = a - b;

            Assert::IsTrue(static_cast<std::string>(result) == "133");
        }

        TEST_METHOD(SubtractionUnderflow)
        {
            Octal a(20, "10");
            Octal b(20, "20");

            Assert::ExpectException<std::underflow_error>([&]()
                {
                    Octal result = a - b;
                });
        }

        TEST_METHOD(Multiplication)
        {
            Octal a(20, "157");
            Octal b(20, "24");

            Octal result = a * b;

            Assert::IsTrue(static_cast<std::string>(result) == "4254");
        }

        TEST_METHOD(DivisionByZero)
        {
            Octal a(20, "157");
            Octal zero(20, "0");

            Assert::ExpectException<std::domain_error>([&]()
                {
                    Octal result = a / zero;
                });
        }

        TEST_METHOD(Equality)
        {
            Octal a(20, "157");
            Octal b(20, "157");

            Assert::IsTrue(a == b);
            Assert::IsFalse(a != b);
        }

        TEST_METHOD(Comparison)
        {
            Octal a(20, "157");
            Octal b(20, "24");

            Assert::IsTrue(a > b);
            Assert::IsTrue(b < a);
            Assert::IsTrue(a >= b);
            Assert::IsTrue(b <= a);
        }

        TEST_METHOD(PrefixIncrement)
        {
            Octal value(20, "7");

            ++value;

            Assert::IsTrue(static_cast<std::string>(value) == "10");
        }

        TEST_METHOD(PostfixIncrement)
        {
            Octal value(20, "7");

            Octal old = value++;

            Assert::IsTrue(static_cast<std::string>(old) == "7");
            Assert::IsTrue(static_cast<std::string>(value) == "10");
        }

        TEST_METHOD(PrefixDecrement)
        {
            Octal value(20, "10");

            --value;

            Assert::IsTrue(static_cast<std::string>(value) == "7");
        }

        TEST_METHOD(PostfixDecrement)
        {
            Octal value(20, "10");

            Octal old = value--;

            Assert::IsTrue(static_cast<std::string>(old) == "10");
            Assert::IsTrue(static_cast<std::string>(value) == "7");
        }

        TEST_METHOD(DecrementZero)
        {
            Octal value(20, "0");

            Assert::ExpectException<std::underflow_error>([&]()
                {
                    --value;
                });
        }

        TEST_METHOD(StringConversion)
        {
            Octal value(20, "7061");

            std::string result = static_cast<std::string>(value);

            Assert::IsTrue(result == "7061");
        }

        TEST_METHOD(InvalidDigitInConstructor)
        {
            Assert::ExpectException<std::invalid_argument>([]()
                {
                    Octal value(20, "128");
                });
        }

        TEST_METHOD(InvalidDigitInSetter)
        {
            Octal value(20, "123");

            Assert::ExpectException<std::invalid_argument>([&]()
                {
                    value.setDigit(0, 8);
                });
        }

        TEST_METHOD(InvalidIndex)
        {
            Octal value(20, "123");

            Assert::ExpectException<std::out_of_range>([&]()
                {
                    value.getDigit(5);
                });
        }

        TEST_METHOD(InvalidCapacity)
        {
            Assert::ExpectException<std::invalid_argument>([]()
                {
                    Octal value(101);
                });
        }

        TEST_METHOD(InputOutputOperators)
        {
            Octal value(20);
            std::istringstream input("725");
            input >> value;

            Assert::IsTrue(static_cast<std::string>(value) == "725");

            std::ostringstream output;
            output << value;

            Assert::IsTrue(output.str() == "725");
        }

        TEST_METHOD(InvalidInput)
        {
            Octal value(20);
            std::istringstream input("198");

            input >> value;

            Assert::IsTrue(input.fail());
        }

        TEST_METHOD(LeadingZeros)
        {
            Octal value(20, "00017");

            Assert::IsTrue(static_cast<std::string>(value) == "17");
            Assert::AreEqual(2, value.count());
        }

        TEST_METHOD(ZeroArithmetic)
        {
            Octal a(20, "0");
            Octal b(20, "17");

            Assert::IsTrue(static_cast<std::string>(a + b) == "17");
            Assert::IsTrue(static_cast<std::string>(a * b) == "0");
        }
    };
}
