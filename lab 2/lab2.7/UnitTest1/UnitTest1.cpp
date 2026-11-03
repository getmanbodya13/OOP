#include "pch.h"
#include "CppUnitTest.h"

#include "../Lab2.7/Cursor.h"
#include "../Lab2.7/ModelWindow.h"

#include <sstream>
#include <stdexcept>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{
    TEST_CLASS(CursorTests)
    {
    public:

        TEST_METHOD(Cursor_DefaultConstructor)
        {
            Cursor c;

            Assert::AreEqual(1, c.GetX());
            Assert::AreEqual(1, c.GetY());
            Assert::AreEqual(1, c.GetSize());
            Assert::IsTrue(c.IsActive());
            Assert::IsTrue(c.GetType() == CursorType::Horizontal);
        }

        TEST_METHOD(Cursor_InitializationConstructor)
        {
            Cursor c(100, 200, CursorType::Vertical, 5);

            Assert::AreEqual(100, c.GetX());
            Assert::AreEqual(200, c.GetY());
            Assert::AreEqual(5, c.GetSize());
            Assert::IsTrue(c.GetType() == CursorType::Vertical);
        }

        TEST_METHOD(Cursor_CopyConstructor)
        {
            Cursor c1(100, 200, CursorType::Vertical, 7);
            Cursor c2(c1);

            Assert::AreEqual(c1.GetX(), c2.GetX());
            Assert::AreEqual(c1.GetY(), c2.GetY());
            Assert::AreEqual(c1.GetSize(), c2.GetSize());
            Assert::IsTrue(c1.GetType() == c2.GetType());
        }

        TEST_METHOD(Cursor_SetCoordinates)
        {
            Cursor c;

            c.SetCoordinates(150, 250);

            Assert::AreEqual(150, c.GetX());
            Assert::AreEqual(250, c.GetY());
        }

        TEST_METHOD(Cursor_InvalidCoordinates)
        {
            Cursor c;

            Assert::ExpectException<invalid_argument>([&]()
                {
                    c.SetCoordinates(-10, 50);
                });

            Assert::ExpectException<invalid_argument>([&]()
                {
                    c.SetCoordinates(2000, 50);
                });
        }

        TEST_METHOD(Cursor_InvalidSize)
        {
            Cursor c;

            Assert::ExpectException<invalid_argument>([&]()
                {
                    c.SetSize(0);
                });

            Assert::ExpectException<invalid_argument>([&]()
                {
                    c.SetSize(20);
                });
        }

        TEST_METHOD(Cursor_EraseRestore)
        {
            Cursor c;

            c.Erase();
            Assert::IsFalse(c.IsActive());

            c.Restore();
            Assert::IsTrue(c.IsActive());
        }

        TEST_METHOD(Cursor_AssignmentOperator)
        {
            Cursor c1(100, 200, CursorType::Vertical, 5);
            Cursor c2;

            c2 = c1;

            Assert::AreEqual(c1.GetX(), c2.GetX());
            Assert::AreEqual(c1.GetY(), c2.GetY());
            Assert::AreEqual(c1.GetSize(), c2.GetSize());
        }

        TEST_METHOD(Cursor_InputOperator)
        {
            Cursor c;

            istringstream input("70 80 0 4");

            input >> c;

            Assert::IsTrue(static_cast<bool>(input));
            Assert::AreEqual(70, c.GetX());
            Assert::AreEqual(80, c.GetY());
            Assert::AreEqual(4, c.GetSize());
            Assert::IsTrue(c.GetType() == CursorType::Horizontal);
        }
    };

    TEST_CLASS(ModelWindowTests)
    {
    public:

        TEST_METHOD(Window_DefaultConstructor)
        {
            ModelWindow w;

            Assert::IsTrue(w.GetTitle() == "New Window");
            Assert::AreEqual(0, w.GetX());
            Assert::AreEqual(0, w.GetY());
            Assert::AreEqual(400, w.GetWidth());
            Assert::AreEqual(300, w.GetHeight());
            Assert::IsTrue(w.GetVisible());
            Assert::IsTrue(w.GetBorder());
        }

        TEST_METHOD(Window_InitializationConstructor)
        {
            Cursor c(100, 100, CursorType::Horizontal, 5);

            ModelWindow w(
                "Main Window",
                100, 150,
                600, 400,
                "Blue",
                true,
                true,
                c
            );

            Assert::IsTrue(w.GetTitle() == "Main Window");
            Assert::AreEqual(100, w.GetX());
            Assert::AreEqual(150, w.GetY());
            Assert::AreEqual(600, w.GetWidth());
            Assert::AreEqual(400, w.GetHeight());
            Assert::IsTrue(w.GetColor() == "Blue");
        }

        TEST_METHOD(Window_CopyConstructor)
        {
            Cursor c(100, 100, CursorType::Vertical, 5);

            ModelWindow w1(
                "Test",
                100, 100,
                500, 300,
                "Red",
                true,
                false,
                c
            );

            ModelWindow w2(w1);

            Assert::IsTrue(w1.GetTitle() == w2.GetTitle());
            Assert::AreEqual(w1.GetX(), w2.GetX());
            Assert::AreEqual(w1.GetY(), w2.GetY());
            Assert::AreEqual(w1.GetWidth(), w2.GetWidth());
            Assert::AreEqual(w1.GetHeight(), w2.GetHeight());
            Assert::IsTrue(w1.GetColor() == w2.GetColor());
        }

        TEST_METHOD(Window_AssignmentOperator)
        {
            Cursor c;

            ModelWindow w1(
                "First",
                100, 100,
                400, 300,
                "Green",
                true,
                true,
                c
            );

            ModelWindow w2;

            w2 = w1;

            Assert::IsTrue(w2.GetTitle() == w1.GetTitle());
            Assert::AreEqual(w1.GetWidth(), w2.GetWidth());
            Assert::AreEqual(w1.GetHeight(), w2.GetHeight());
            Assert::IsTrue(w2.GetColor() == "Green");
        }

        TEST_METHOD(Window_MoveHorizontal)
        {
            ModelWindow w;

            w.MoveHorizontal(100);

            Assert::AreEqual(100, w.GetX());
        }

        TEST_METHOD(Window_MoveVertical)
        {
            ModelWindow w;

            w.MoveVertical(150);

            Assert::AreEqual(150, w.GetY());
        }

        TEST_METHOD(Window_MoveOutOfBounds)
        {
            ModelWindow w;

            Assert::ExpectException<invalid_argument>([&]()
                {
                    w.MoveHorizontal(2000);
                });

            Assert::ExpectException<invalid_argument>([&]()
                {
                    w.MoveVertical(1000);
                });
        }

        TEST_METHOD(Window_Resize)
        {
            ModelWindow w;

            w.Resize(800, 600);

            Assert::AreEqual(800, w.GetWidth());
            Assert::AreEqual(600, w.GetHeight());
        }

        TEST_METHOD(Window_InvalidResize)
        {
            ModelWindow w;

            Assert::ExpectException<invalid_argument>([&]()
                {
                    w.Resize(-100, 300);
                });

            Assert::ExpectException<invalid_argument>([&]()
                {
                    w.Resize(3000, 2000);
                });
        }

        TEST_METHOD(Window_VisibilityAndBorder)
        {
            ModelWindow w;

            w.Hide();
            Assert::IsFalse(w.IsVisible());

            w.Show();
            Assert::IsTrue(w.IsVisible());

            w.RemoveBorder();
            Assert::IsFalse(w.HasBorder());

            w.AddBorder();
            Assert::IsTrue(w.HasBorder());
        }

        TEST_METHOD(Window_CursorComposition)
        {
            Cursor c(100, 200, CursorType::Vertical, 5);

            ModelWindow w(
                "Test",
                100, 100,
                400, 300,
                "Blue",
                true,
                true,
                c
            );

            w.MoveCursor(300, 400);
            w.ChangeCursorType(CursorType::Horizontal);
            w.ChangeCursorSize(10);

            Cursor result = w.GetCursor();

            Assert::AreEqual(300, result.GetX());
            Assert::AreEqual(400, result.GetY());
            Assert::AreEqual(10, result.GetSize());
            Assert::IsTrue(
                result.GetType() == CursorType::Horizontal
            );

            w.EraseCursor();
            Assert::IsFalse(w.GetCursor().IsActive());

            w.RestoreCursor();
            Assert::IsTrue(w.GetCursor().IsActive());
        }

        TEST_METHOD(Window_PrefixOperators)
        {
            Cursor c;

            ModelWindow w(
                "Test",
                100, 100,
                300, 200,
                "White",
                true,
                true,
                c
            );

            ++w;
            Assert::AreEqual(301, w.GetWidth());

            --w;
            Assert::AreEqual(300, w.GetWidth());
        }

        TEST_METHOD(Window_PostfixOperators)
        {
            Cursor c;

            ModelWindow w(
                "Test",
                100, 100,
                300, 200,
                "White",
                true,
                true,
                c
            );

            ModelWindow old = w++;

            Assert::AreEqual(200, old.GetHeight());
            Assert::AreEqual(201, w.GetHeight());

            old = w--;

            Assert::AreEqual(201, old.GetHeight());
            Assert::AreEqual(200, w.GetHeight());
        }

        TEST_METHOD(Window_StringConversionAndOutput)
        {
            ModelWindow w;

            string result = w;

            Assert::IsTrue(
                result.find("New Window") != string::npos
            );

            ostringstream output;
            output << w;

            Assert::IsTrue(
                output.str().find("Width: 400") != string::npos
            );
        }

        TEST_METHOD(Window_InputOperator)
        {
            ModelWindow w;

            istringstream input(
                "Input Window\n"
                "10 20 300 200 Purple 1 0"
            );

            input >> w;

            Assert::IsTrue(static_cast<bool>(input));
            Assert::IsTrue(w.GetTitle() == "Input Window");
            Assert::AreEqual(10, w.GetX());
            Assert::AreEqual(20, w.GetY());
            Assert::AreEqual(300, w.GetWidth());
            Assert::AreEqual(200, w.GetHeight());
            Assert::IsTrue(w.GetColor() == "Purple");
            Assert::IsTrue(w.IsVisible());
            Assert::IsFalse(w.HasBorder());
        }
    };
}