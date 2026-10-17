#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab2.2/DoublyLinkedList.h"
#include "../Lab2.2/DoublyLinkedList.cpp"

#include <sstream>
#include <string>
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoublyLinkedListTests
{
    TEST_CLASS(DoublyLinkedListUnitTests)
    {
    public:

        TEST_METHOD(DefaultConstructor_CreatesEmptyList)
        {
            DoublyLinkedList list;

            Assert::AreEqual(0, list.GetSize());
            Assert::IsTrue(list.IsEmpty());
        }

        TEST_METHOD(Plus_AddsElementToEnd)
        {
            DoublyLinkedList list;
            list = list + 10;
            list = list + 20;
            list = list + 30;

            Assert::AreEqual(3, list.GetSize());
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(20, list[1]);
            Assert::AreEqual(30, list[2]);
        }

        TEST_METHOD(Plus_PreservesOriginalList)
        {
            DoublyLinkedList original;
            original = original + 10;
            original = original + 20;

            DoublyLinkedList result = original + 30;

            Assert::AreEqual(2, original.GetSize());
            Assert::AreEqual(3, result.GetSize());
            Assert::AreEqual(20, original[1]);
            Assert::AreEqual(30, result[2]);
        }

        TEST_METHOD(PlusEquals_AddsElementToBeginning)
        {
            DoublyLinkedList list;
            list = list + 20;
            list = list + 30;
            list += 10;

            Assert::AreEqual(3, list.GetSize());
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(20, list[1]);
            Assert::AreEqual(30, list[2]);
        }

        TEST_METHOD(Minus_RemovesFirstMatchingElement)
        {
            DoublyLinkedList list;
            list = list + 10;
            list = list + 20;
            list = list + 30;

            list - 20;

            Assert::AreEqual(2, list.GetSize());
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(30, list[1]);
        }

        TEST_METHOD(Minus_AbsentElementPreservesList)
        {
            DoublyLinkedList list;
            list = list + 10;
            list = list + 20;

            list - 99;

            Assert::AreEqual(2, list.GetSize());
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(20, list[1]);
        }

        TEST_METHOD(CopyConstructor_CopiesAllElements)
        {
            DoublyLinkedList original;
            original = original + 10;
            original = original + 20;
            original = original + 30;

            DoublyLinkedList copy(original);

            Assert::AreEqual(3, copy.GetSize());
            Assert::AreEqual(10, copy[0]);
            Assert::AreEqual(20, copy[1]);
            Assert::AreEqual(30, copy[2]);

            copy[0] = 99;

            Assert::AreEqual(10, original[0]);
            Assert::AreEqual(99, copy[0]);
        }

        TEST_METHOD(Assignment_CopiesAllElements)
        {
            DoublyLinkedList original;
            original = original + 5;
            original = original + 15;

            DoublyLinkedList copy;
            copy = original;

            Assert::AreEqual(2, copy.GetSize());
            Assert::AreEqual(5, copy[0]);
            Assert::AreEqual(15, copy[1]);

            copy[1] = 100;
            Assert::AreEqual(15, original[1]);
        }

        TEST_METHOD(Assignment_SelfAssignmentPreservesList)
        {
            DoublyLinkedList list;
            list = list + 10;
            list = list + 20;

            list = list;

            Assert::AreEqual(2, list.GetSize());
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(20, list[1]);
        }

        TEST_METHOD(EqualOperator_ReturnsTrueForEqualLists)
        {
            DoublyLinkedList a;
            a = a + 1;
            a = a + 2;

            DoublyLinkedList b;
            b = b + 1;
            b = b + 2;

            Assert::IsTrue(a == b);
            Assert::IsFalse(a != b);
        }

        TEST_METHOD(NotEqualOperator_ReturnsTrueForDifferentLists)
        {
            DoublyLinkedList a;
            a = a + 1;

            DoublyLinkedList b;
            b = b + 2;

            Assert::IsTrue(a != b);
            Assert::IsFalse(a == b);
        }

        TEST_METHOD(ComparisonOperators_WorkCorrectly)
        {
            DoublyLinkedList a;
            a = a + 1;
            a = a + 2;

            DoublyLinkedList b;
            b = b + 1;
            b = b + 3;

            Assert::IsTrue(a < b);
            Assert::IsTrue(b > a);
            Assert::IsTrue(a <= b);
            Assert::IsTrue(b >= a);
            Assert::IsFalse(a > b);
            Assert::IsFalse(b < a);
        }

        TEST_METHOD(IndexOperator_ReadsAndChangesElement)
        {
            DoublyLinkedList list;
            list = list + 10;
            list = list + 20;

            Assert::AreEqual(20, list[1]);

            list[1] = 50;

            Assert::AreEqual(50, list[1]);
            Assert::AreEqual(50, list.GetElement(1));
        }

        TEST_METHOD(SetElement_ChangesElement)
        {
            DoublyLinkedList list;
            list = list + 10;
            list = list + 20;

            list.SetElement(0, 99);

            Assert::AreEqual(99, list.GetElement(0));
            Assert::AreEqual(2, list.GetSize());
        }

        TEST_METHOD(IndexOperator_ThrowsForInvalidIndex)
        {
            DoublyLinkedList list;
            list = list + 10;

            bool exceptionThrown = false;

            try
            {
                (void)list[5];
            }
            catch (const std::out_of_range&)
            {
                exceptionThrown = true;
            }

            Assert::IsTrue(exceptionThrown);
        }

        TEST_METHOD(FunctionOperator_ReturnsRequestedRange)
        {
            DoublyLinkedList list;
            list = list + 10;
            list = list + 20;
            list = list + 30;
            list = list + 40;

            std::string part = list(1, 2);

            Assert::AreEqual(std::string("20 30"), part);
        }

        TEST_METHOD(FunctionOperator_ThrowsForInvalidRange)
        {
            DoublyLinkedList list;
            list = list + 10;
            list = list + 20;

            bool exceptionThrown = false;

            try
            {
                list(0, 5);
            }
            catch (const std::out_of_range&)
            {
                exceptionThrown = true;
            }

            Assert::IsTrue(exceptionThrown);
        }

        TEST_METHOD(StringConversion_ReturnsAllElements)
        {
            DoublyLinkedList list;
            list = list + 10;
            list = list + 20;
            list = list + 30;

            std::string result =
                static_cast<std::string>(list);

            Assert::AreEqual(std::string("10 20 30"), result);
        }

        TEST_METHOD(OutputOperator_FormatsList)
        {
            DoublyLinkedList list;
            list = list + 10;
            list = list + 20;

            std::ostringstream output;
            output << list;

            Assert::AreEqual(std::string("[10, 20]"),
                output.str());
        }

        TEST_METHOD(InputOperator_ReadsList)
        {
            DoublyLinkedList list;
            std::istringstream input("3 10 20 30");

            input >> list;

            Assert::IsTrue(static_cast<bool>(input));
            Assert::AreEqual(3, list.GetSize());
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(20, list[1]);
            Assert::AreEqual(30, list[2]);
        }

        TEST_METHOD(InputOperator_ReadsEmptyList)
        {
            DoublyLinkedList list;
            list = list + 10;

            std::istringstream input("0");
            input >> list;

            Assert::IsTrue(static_cast<bool>(input));
            Assert::AreEqual(0, list.GetSize());
            Assert::IsTrue(list.IsEmpty());
        }

        TEST_METHOD(EmptyLists_AreEqual)
        {
            DoublyLinkedList a;
            DoublyLinkedList b;

            Assert::IsTrue(a == b);
            Assert::IsFalse(a != b);
            Assert::IsFalse(a < b);
            Assert::IsFalse(a > b);
            Assert::IsTrue(a <= b);
            Assert::IsTrue(a >= b);
        }

        TEST_METHOD(IncrementDecrement_DoNotCrash)
        {
            DoublyLinkedList list;
            list = list + 10;
            list = list + 20;
            list = list + 30;

            ++list;
            ++list;
            --list;
            --list;

            Assert::AreEqual(3, list.GetSize());
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(30, list[2]);
        }

        TEST_METHOD(Minus_RemovesHeadCorrectly)
        {
            DoublyLinkedList list;
            list = list + 10;
            list = list + 20;

            list - 10;

            Assert::AreEqual(1, list.GetSize());
            Assert::AreEqual(20, list[0]);
        }

        TEST_METHOD(Minus_RemovesTailCorrectly)
        {
            DoublyLinkedList list;
            list = list + 10;
            list = list + 20;

            list - 20;

            Assert::AreEqual(1, list.GetSize());
            Assert::AreEqual(10, list[0]);
        }

        TEST_METHOD(Minus_RemovesOnlyElement)
        {
            DoublyLinkedList list;
            list = list + 10;

            list - 10;

            Assert::AreEqual(0, list.GetSize());
            Assert::IsTrue(list.IsEmpty());
        }
    };
}
