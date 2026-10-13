#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1.8/ModelWindow.h"
#include "../lab1.8/ModelWindow.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(ModelWindowTests)
    {
    public:

        TEST_METHOD(DefaultConstructorTest)
        {
            ModelWindow window;

            Assert::IsTrue(window.GetTitle() == "Untitled");
            Assert::AreEqual(0, window.GetX());
            Assert::AreEqual(0, window.GetY());
            Assert::AreEqual(800, window.GetWidth());
            Assert::AreEqual(600, window.GetHeight());
            Assert::IsTrue(window.GetColor() == "White");
            Assert::IsTrue(window.IsVisible());
            Assert::IsTrue(window.HasBorder());
        }

        TEST_METHOD(ParameterizedConstructorTest)
        {
            ModelWindow window(
                "Main", 100, 150, 640, 480,
                "Blue", true, false
            );

            Assert::IsTrue(window.GetTitle() == "Main");
            Assert::AreEqual(100, window.GetX());
            Assert::AreEqual(150, window.GetY());
            Assert::AreEqual(640, window.GetWidth());
            Assert::AreEqual(480, window.GetHeight());
            Assert::IsTrue(window.GetColor() == "Blue");
            Assert::IsTrue(window.IsVisible());
            Assert::IsFalse(window.HasBorder());
        }

        TEST_METHOD(InitValidValuesTest)
        {
            ModelWindow window;

            bool result = window.Init(
                "Settings", 50, 60, 400, 300,
                "Gray", false, true
            );

            Assert::IsTrue(result);
            Assert::IsTrue(window.GetTitle() == "Settings");
            Assert::AreEqual(50, window.GetX());
            Assert::AreEqual(60, window.GetY());
            Assert::AreEqual(400, window.GetWidth());
            Assert::AreEqual(300, window.GetHeight());
        }

        TEST_METHOD(InitInvalidGeometryTest)
        {
            ModelWindow window;

            bool result = window.Init(
                "Invalid", 1900, 100, 200, 300,
                "Red", true, true
            );

            Assert::IsFalse(result);
            Assert::IsTrue(window.GetTitle() == "Untitled");
            Assert::AreEqual(0, window.GetX());
        }

        TEST_METHOD(MoveHorizontalTest)
        {
            ModelWindow window(
                "Test", 100, 100, 400, 300,
                "Blue", true, true
            );

            Assert::IsTrue(window.MoveHorizontal(50));
            Assert::AreEqual(150, window.GetX());
        }

        TEST_METHOD(MoveHorizontalBoundaryTest)
        {
            ModelWindow window(
                "Test", 100, 100, 400, 300,
                "Blue", true, true
            );

            Assert::IsFalse(window.MoveHorizontal(-101));
            Assert::AreEqual(100, window.GetX());

            Assert::IsFalse(window.MoveHorizontal(1500));
            Assert::AreEqual(100, window.GetX());
        }

        TEST_METHOD(MoveVerticalTest)
        {
            ModelWindow window(
                "Test", 100, 100, 400, 300,
                "Blue", true, true
            );

            Assert::IsTrue(window.MoveVertical(50));
            Assert::AreEqual(150, window.GetY());
        }

        TEST_METHOD(MoveVerticalBoundaryTest)
        {
            ModelWindow window(
                "Test", 100, 100, 400, 300,
                "Blue", true, true
            );

            Assert::IsFalse(window.MoveVertical(-101));
            Assert::AreEqual(100, window.GetY());

            Assert::IsFalse(window.MoveVertical(800));
            Assert::AreEqual(100, window.GetY());
        }

        TEST_METHOD(ResizeValidValuesTest)
        {
            ModelWindow window(
                "Test", 100, 100, 400, 300,
                "Blue", true, true
            );

            Assert::IsTrue(window.Resize(500, 400));
            Assert::AreEqual(500, window.GetWidth());
            Assert::AreEqual(400, window.GetHeight());
        }

        TEST_METHOD(ResizeInvalidValuesTest)
        {
            ModelWindow window(
                "Test", 100, 100, 400, 300,
                "Blue", true, true
            );

            Assert::IsFalse(window.Resize(0, 300));
            Assert::AreEqual(400, window.GetWidth());
            Assert::AreEqual(300, window.GetHeight());

            Assert::IsFalse(window.Resize(2000, 1200));
            Assert::AreEqual(400, window.GetWidth());
            Assert::AreEqual(300, window.GetHeight());
        }

        TEST_METHOD(SetWidthTest)
        {
            ModelWindow window(
                "Test", 100, 100, 400, 300,
                "Blue", true, true
            );

            Assert::IsTrue(window.SetWidth(500));
            Assert::AreEqual(500, window.GetWidth());

            Assert::IsFalse(window.SetWidth(0));
            Assert::AreEqual(500, window.GetWidth());

            Assert::IsFalse(window.SetWidth(1900));
            Assert::AreEqual(500, window.GetWidth());
        }

        TEST_METHOD(SetHeightTest)
        {
            ModelWindow window(
                "Test", 100, 100, 400, 300,
                "Blue", true, true
            );

            Assert::IsTrue(window.SetHeight(400));
            Assert::AreEqual(400, window.GetHeight());

            Assert::IsFalse(window.SetHeight(0));
            Assert::AreEqual(400, window.GetHeight());
        }

        TEST_METHOD(ChangeColorTest)
        {
            ModelWindow window;

            Assert::IsTrue(window.ChangeColor("Green"));
            Assert::IsTrue(window.GetColor() == "Green");

            Assert::IsFalse(window.ChangeColor(""));
            Assert::IsTrue(window.GetColor() == "Green");
        }

        TEST_METHOD(SetTitleTest)
        {
            ModelWindow window;

            Assert::IsTrue(window.SetTitle("Profile"));
            Assert::IsTrue(window.GetTitle() == "Profile");

            Assert::IsFalse(window.SetTitle(""));
            Assert::IsTrue(window.GetTitle() == "Profile");
        }

        TEST_METHOD(WindowStateTest)
        {
            ModelWindow window;

            window.SetState(false, false);

            bool visible = true;
            bool bordered = true;

            window.GetState(visible, bordered);

            Assert::IsFalse(visible);
            Assert::IsFalse(bordered);

            window.SetState(true, true);
            window.GetState(visible, bordered);

            Assert::IsTrue(visible);
            Assert::IsTrue(bordered);
        }

        TEST_METHOD(DisplayMakesWindowVisibleTest)
        {
            ModelWindow window;

            window.SetVisible(false);
            Assert::IsFalse(window.IsVisible());

            window.Display();

            Assert::IsTrue(window.IsVisible());
        }

        TEST_METHOD(CursorDefaultConstructorTest)
        {
            ModelWindow::Cursor cursor;

            Assert::AreEqual(1, cursor.GetX());
            Assert::AreEqual(1, cursor.GetY());
            Assert::AreEqual(1, cursor.GetSize());
            Assert::IsTrue(cursor.IsActive());

            Assert::IsTrue(
                cursor.GetType() ==
                ModelWindow::Cursor::Type::Horizontal
            );
        }

        TEST_METHOD(CursorInitTest)
        {
            ModelWindow::Cursor cursor;

            bool result = cursor.Init(
                500, 400,
                ModelWindow::Cursor::Type::Vertical,
                10
            );

            Assert::IsTrue(result);
            Assert::AreEqual(500, cursor.GetX());
            Assert::AreEqual(400, cursor.GetY());
            Assert::AreEqual(10, cursor.GetSize());

            Assert::IsTrue(
                cursor.GetType() ==
                ModelWindow::Cursor::Type::Vertical
            );
        }

        TEST_METHOD(CursorInvalidCoordinatesTest)
        {
            ModelWindow::Cursor cursor;

            Assert::IsFalse(cursor.SetX(0));
            Assert::AreEqual(1, cursor.GetX());

            Assert::IsFalse(cursor.SetY(1081));
            Assert::AreEqual(1, cursor.GetY());

            Assert::IsFalse(cursor.SetCoordinates(100, 0));
            Assert::AreEqual(1, cursor.GetX());
            Assert::AreEqual(1, cursor.GetY());
        }

        TEST_METHOD(CursorSizeValidationTest)
        {
            ModelWindow::Cursor cursor;

            Assert::IsTrue(cursor.SetSize(15));
            Assert::AreEqual(15, cursor.GetSize());

            Assert::IsFalse(cursor.SetSize(0));
            Assert::AreEqual(15, cursor.GetSize());

            Assert::IsFalse(cursor.SetSize(16));
            Assert::AreEqual(15, cursor.GetSize());
        }

        TEST_METHOD(CursorTypeTest)
        {
            ModelWindow::Cursor cursor;

            Assert::IsTrue(
                cursor.SetType(
                    ModelWindow::Cursor::Type::Vertical
                )
            );

            Assert::IsTrue(
                cursor.GetType() ==
                ModelWindow::Cursor::Type::Vertical
            );
        }

        TEST_METHOD(CursorEraseRestoreTest)
        {
            ModelWindow::Cursor cursor;

            Assert::IsTrue(cursor.IsActive());

            cursor.Erase();
            Assert::IsFalse(cursor.IsActive());

            cursor.Restore();
            Assert::IsTrue(cursor.IsActive());
        }

        TEST_METHOD(SetCursorTest)
        {
            ModelWindow window;
            ModelWindow::Cursor cursor;

            Assert::IsTrue(
                cursor.Init(
                    300, 200,
                    ModelWindow::Cursor::Type::Vertical,
                    7
                )
            );

            window.SetCursor(cursor);

            ModelWindow::Cursor result = window.GetCursor();

            Assert::AreEqual(300, result.GetX());
            Assert::AreEqual(200, result.GetY());
            Assert::AreEqual(7, result.GetSize());

            Assert::IsTrue(
                result.GetType() ==
                ModelWindow::Cursor::Type::Vertical
            );
        }

        TEST_METHOD(ToStringTest)
        {
            ModelWindow window(
                "Dashboard", 10, 20, 300, 200,
                "Red", true, false
            );

            std::string result = window.toString();

            Assert::IsTrue(
                result.find("Dashboard") != std::string::npos
            );
            Assert::IsTrue(
                result.find("Red") != std::string::npos
            );
            Assert::IsTrue(
                result.find("300 x 200") != std::string::npos
            );
        }
    };
}
