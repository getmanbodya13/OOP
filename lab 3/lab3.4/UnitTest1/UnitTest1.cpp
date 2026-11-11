#include "pch.h"
#include "CppUnitTest.h"
#include "../lab3.4/Classes.h"
#include <iostream>
#include <sstream>
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab34Tests
{
    TEST_CLASS(SymStringTests)
    {
    public:
        TEST_METHOD(TestSymStringCreation)
        {
            SymString s("S1", "Hello World");

            Assert::AreEqual(string("S1"), s.getId());
            Assert::AreEqual(string("Hello World"), s.getValue());
            Assert::AreEqual(string("SymString"), s.getType());
        }

        TEST_METHOD(TestSymStringSubtraction)
        {
            SymString s1("S1", "Hello World");
            SymString s2("S2", "World");

            SymString result = s1 - s2;

            Assert::AreEqual(string("Hello"), result.getValue());
        }

        TEST_METHOD(TestSymStringSubtractionWithoutMatch)
        {
            SymString s1("S1", "Hello");
            SymString s2("S2", "World");

            SymString result = s1 - s2;

            Assert::AreEqual(string("Hello"), result.getValue());
        }

        TEST_METHOD(TestOctStringCreation)
        {
            OctString o("O1", "17");

            Assert::AreEqual(string("O1"), o.getId());
            Assert::AreEqual(string("17"), o.getValue());
            Assert::AreEqual(string("OctString"), o.getType());
        }

        TEST_METHOD(TestInheritance)
        {
            Assert::IsTrue(
                (is_base_of<SymString, OctString>::value)
            );

            OctString o("O1", "25");
            SymString* ptr = &o;

            Assert::AreEqual(
                string("OctString"),
                ptr->getType()
            );
        }

        TEST_METHOD(TestShowHex)
        {
            OctString o("O1", "17");

            ostringstream output;
            streambuf* oldBuffer = cout.rdbuf(output.rdbuf());

            o.ShowHex();

            cout.rdbuf(oldBuffer);

            string result = output.str();

            Assert::IsTrue(
                result.find("Hexadecimal value: F") != string::npos
            );
        }

        TEST_METHOD(TestOctStringSubtraction)
        {
            OctString o1("O1", "17");
            OctString o2("O2", "7");

            OctString result = o1 - o2;

            Assert::AreEqual(string("10"), result.getValue());
        }

        TEST_METHOD(TestOctStringSubtractionHex)
        {
            OctString o1("O1", "20");
            OctString o2("O2", "10");

            OctString result = o1 - o2;

            Assert::AreEqual(string("10"), result.getValue());

            ostringstream output;
            streambuf* oldBuffer = cout.rdbuf(output.rdbuf());

            result.ShowHex();

            cout.rdbuf(oldBuffer);

            Assert::IsTrue(
                output.str().find("Hexadecimal value: 8")
                != string::npos
            );
        }

        TEST_METHOD(TestInvalidOctalNumber)
        {
            bool exceptionThrown = false;

            try
            {
                OctString o("O1", "189");
            }
            catch (const invalid_argument&)
            {
                exceptionThrown = true;
            }

            Assert::IsTrue(exceptionThrown);
        }

        TEST_METHOD(TestFactory)
        {
            Factory factory;

            factory.createSymString("S1", "Hello");
            factory.createOctString("O1", "17");

            Assert::AreEqual(2, factory.getCount());

            factory.deleteObject(0);

            Assert::AreEqual(1, factory.getCount());
        }
    };
}
