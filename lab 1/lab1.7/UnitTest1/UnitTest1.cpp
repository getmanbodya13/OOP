#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab1.7\Cursor.h"
#include "..\lab1.7\ModelWindow.h"
#include "..\lab1.7\Cursor.cpp"
#include "..\lab1.7\ModelWindow.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ModelWindowUnitTests
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
            Assert::IsTrue(
                c.GetType() == CursorType::Horizontal);
        }

        TEST_METHOD(Cursor_SetCoordinates_Valid)
        {
            Cursor c;

            Assert::IsTrue(c.SetCoordinates(20, 30));
            Assert::AreEqual(20, c.GetX());
            Assert::AreEqual(30, c.GetY());
        }

        TEST_METHOD(Cursor_SetCoordinates_Invalid)
        {
            Cursor c;

            Assert::IsFalse(c.SetCoordinates(-1, 10));
            Assert::IsFalse(c.SetCoordinates(10, 0));

            Assert::AreEqual(1, c.GetX());
            Assert::AreEqual(1, c.GetY());
        }

        TEST_METHOD(Cursor_SetSize_Boundaries)
        {
            Cursor c;

            Assert::IsTrue(c.SetSize(1));
            Assert::AreEqual(1, c.GetSize());

            Assert::IsTrue(c.SetSize(15));
            Assert::AreEqual(15, c.GetSize());

            Assert::IsFalse(c.SetSize(0));
            Assert::IsFalse(c.SetSize(16));

            Assert::AreEqual(15, c.GetSize());
        }

        TEST_METHOD(Cursor_SetType)
        {
            Cursor c;

            Assert::IsTrue(
                c.SetType(CursorType::Vertical));

            Assert::IsTrue(
                c.GetType() == CursorType::Vertical);

            Assert::IsTrue(
                c.SetType(CursorType::Horizontal));

            Assert::IsTrue(
                c.GetType() == CursorType::Horizontal);
        }

        TEST_METHOD(Cursor_EraseAndRestore)
        {
            Cursor c;

            c.Erase();
            Assert::IsFalse(c.IsActive());

            c.Restore();
            Assert::IsTrue(c.IsActive());
        }

        TEST_METHOD(Cursor_Init)
        {
            Cursor c;

            Assert::IsTrue(
                c.Init(10, 20,
                    CursorType::Vertical, 7));

            Assert::AreEqual(10, c.GetX());
            Assert::AreEqual(20, c.GetY());
            Assert::AreEqual(7, c.GetSize());

            Assert::IsTrue(
                c.GetType() == CursorType::Vertical);

            Assert::IsTrue(c.IsActive());
        }

        TEST_METHOD(Cursor_Init_Invalid)
        {
            Cursor c;

            Assert::IsFalse(
                c.Init(0, 20,
                    CursorType::Vertical, 7));

            Assert::AreEqual(1, c.GetX());
            Assert::AreEqual(1, c.GetY());
        }
    };

    TEST_CLASS(ModelWindowTests)
    {
    public:

        TEST_METHOD(Window_DefaultConstructor)
        {
            ModelWindow w;

            Assert::IsTrue(w.GetTitle() == "Untitled");

            Assert::AreEqual(0, w.GetX());
            Assert::AreEqual(0, w.GetY());
            Assert::AreEqual(400, w.GetWidth());
            Assert::AreEqual(300, w.GetHeight());
            
            Assert::IsTrue(w.GetColor() == "White");

            Assert::IsFalse(w.IsVisible());
            Assert::IsTrue(w.HasFrame());
        }

        TEST_METHOD(Window_Init_Valid)
        {
            ModelWindow w;

            Assert::IsTrue(
                w.Init("Test", 100, 100,
                    500, 300, "Blue", true, false));

            Assert::IsTrue(w.GetTitle() == "Test");

            Assert::AreEqual(100, w.GetX());
            Assert::AreEqual(100, w.GetY());
            Assert::AreEqual(500, w.GetWidth());
            Assert::AreEqual(300, w.GetHeight());

            Assert::IsTrue(w.GetColor() == "Blue");

            Assert::IsTrue(w.IsVisible());
            Assert::IsFalse(w.HasFrame());
        }

        TEST_METHOD(Window_Init_Invalid)
        {
            ModelWindow w;

            Assert::IsFalse(
                w.Init("Invalid", 1900, 100,
                    500, 300, "Red", true, true));

            Assert::IsFalse(
                w.Init("Invalid", 0, 0,
                    0, 300, "Red", true, true));

            Assert::IsFalse(
                w.Init("", 0, 0,
                    100, 100, "Red", true, true));

            Assert::IsTrue(w.GetTitle() == "Untitled");

            Assert::AreEqual(400, w.GetWidth());
        }

        TEST_METHOD(Window_MoveHorizontal)
        {
            ModelWindow w;

            Assert::IsTrue(
                w.Init("Test", 100, 100,
                    400, 300, "Blue", true, true));

            Assert::IsTrue(w.MoveHorizontal(50));
            Assert::AreEqual(150, w.GetX());

            Assert::IsTrue(w.MoveHorizontal(-25));
            Assert::AreEqual(125, w.GetX());
        }


        TEST_METHOD(Window_MoveVertical)
        {
            ModelWindow w;

            Assert::IsTrue(
                w.Init("Test", 100, 100,
                    400, 300, "Blue", true, true));

            Assert::IsTrue(w.MoveVertical(50));
            Assert::AreEqual(150, w.GetY());

            Assert::IsTrue(w.MoveVertical(-25));
            Assert::AreEqual(125, w.GetY());
        }

        TEST_METHOD(Window_MoveOutsideScreen)
        {
            ModelWindow w;

            Assert::IsTrue(
                w.Init("Test", 100, 100,
                    400, 300, "Blue", true, true));

            Assert::IsFalse(w.MoveHorizontal(2000));
            Assert::AreEqual(100, w.GetX());

            Assert::IsFalse(w.MoveVertical(-200));
            Assert::AreEqual(100, w.GetY());
        }

        TEST_METHOD(Window_Resize_Valid)
        {
            ModelWindow w;

            Assert::IsTrue(
                w.Init("Test", 100, 100,
                    400, 300, "Blue", true, true));

            Assert::IsTrue(w.Resize(600, 500));

            Assert::AreEqual(600, w.GetWidth());
            Assert::AreEqual(500, w.GetHeight());
        }

        TEST_METHOD(Window_Resize_Invalid)
        {
            ModelWindow w;

            Assert::IsTrue(
                w.Init("Test", 100, 100,
                    400, 300, "Blue", true, true));

            Assert::IsFalse(w.Resize(0, 300));
            Assert::IsFalse(w.Resize(5000, 300));
            Assert::IsFalse(w.Resize(400, 2000));

            Assert::AreEqual(400, w.GetWidth());
            Assert::AreEqual(300, w.GetHeight());
        }

        TEST_METHOD(Window_SettersAndStates)
        {
            ModelWindow w;

            Assert::IsTrue(w.SetTitle("Editor"));
            Assert::IsTrue(w.SetColor("Green"));

            w.SetVisible(true);
            w.SetFramed(false);

            Assert::IsTrue(w.GetTitle() == "Editor");

            Assert::IsTrue(w.GetColor() == "Green");

            Assert::IsTrue(w.IsVisible());
            Assert::IsFalse(w.HasFrame());

            Assert::IsFalse(w.SetTitle(""));
            Assert::IsFalse(w.SetColor(""));

            Assert::IsTrue(w.GetTitle() == "Editor");

            Assert::IsTrue(w.GetColor() == "Green");
        }

        TEST_METHOD(Window_DisplayMakesVisible)
        {
            ModelWindow w;

            Assert::IsTrue(
                w.Init("Test", 10, 10,
                    200, 100, "White", false, true));

            Assert::IsFalse(w.IsVisible());

            w.Display();

            Assert::IsTrue(w.IsVisible());
        }

        TEST_METHOD(Window_ContainsCursor)
        {
            ModelWindow w;
            Cursor c;

            Assert::IsTrue(
                c.Init(20, 30,
                    CursorType::Vertical, 8));

            w.SetCursor(c);

            Cursor result = w.GetCursor();

            Assert::AreEqual(20, result.GetX());
            Assert::AreEqual(30, result.GetY());
            Assert::AreEqual(8, result.GetSize());

            Assert::IsTrue(
                result.GetType() == CursorType::Vertical);

            Assert::IsTrue(result.IsActive());
        }
    };
}
