#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab2.8/ModelWindow.h"
#include <string>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ModelWindowTests
{
    TEST_CLASS(ModelWindowTests)
    {
    public:

        TEST_METHOD(TestDefaultConstructor)
        {
            ModelWindow w;

            Assert::AreEqual(
                std::string("New Window"),
                w.getTitle()
            );

            Assert::AreEqual(0, w.getX());
            Assert::AreEqual(0, w.getY());
            Assert::AreEqual(640, w.getWidth());
            Assert::AreEqual(480, w.getHeight());

            Assert::AreEqual(
                std::string("White"),
                w.getColor()
            );

            Assert::IsTrue(w.isVisible());
            Assert::IsTrue(w.hasBorder());
        }

        TEST_METHOD(TestParameterizedConstructor)
        {
            ModelWindow::Cursor c(
                100, 150,
                ModelWindow::Cursor::Horizontal,
                5
            );

            ModelWindow w(
                "Test Window",
                100, 200,
                800, 600,
                "Blue",
                true, true,
                c
            );

            Assert::AreEqual(
                std::string("Test Window"),
                w.getTitle()
            );

            Assert::AreEqual(100, w.getX());
            Assert::AreEqual(200, w.getY());
            Assert::AreEqual(800, w.getWidth());
            Assert::AreEqual(600, w.getHeight());

            Assert::AreEqual(
                std::string("Blue"),
                w.getColor()
            );
        }

        TEST_METHOD(TestCopyConstructor)
        {
            ModelWindow w1(
                "Original",
                100, 100,
                500, 400,
                "Red",
                true, false,
                ModelWindow::Cursor()
            );

            ModelWindow w2(w1);

            Assert::AreEqual(w1.getTitle(), w2.getTitle());
            Assert::AreEqual(w1.getX(), w2.getX());
            Assert::AreEqual(w1.getY(), w2.getY());
            Assert::AreEqual(w1.getWidth(), w2.getWidth());
            Assert::AreEqual(w1.getHeight(), w2.getHeight());
            Assert::AreEqual(w1.getColor(), w2.getColor());
        }

        TEST_METHOD(TestAssignmentOperator)
        {
            ModelWindow w1(
                "First",
                50, 60,
                400, 300,
                "Green",
                true, true,
                ModelWindow::Cursor()
            );

            ModelWindow w2;

            w2 = w1;

            Assert::AreEqual(w1.getTitle(), w2.getTitle());
            Assert::AreEqual(w1.getX(), w2.getX());
            Assert::AreEqual(w1.getY(), w2.getY());
            Assert::AreEqual(w1.getWidth(), w2.getWidth());
            Assert::AreEqual(w1.getHeight(), w2.getHeight());
            Assert::AreEqual(w1.getColor(), w2.getColor());
        }

        TEST_METHOD(TestMoveHorizontal)
        {
            ModelWindow w;

            Assert::IsTrue(w.moveHorizontal(100));
            Assert::AreEqual(100, w.getX());

            Assert::IsTrue(w.moveHorizontal(-50));
            Assert::AreEqual(50, w.getX());
        }

        TEST_METHOD(TestMoveVertical)
        {
            ModelWindow w;

            Assert::IsTrue(w.moveVertical(100));
            Assert::AreEqual(100, w.getY());

            Assert::IsTrue(w.moveVertical(-50));
            Assert::AreEqual(50, w.getY());
        }

        TEST_METHOD(TestMovementScreenBoundaries)
        {
            ModelWindow w;

            Assert::IsFalse(w.moveHorizontal(2000));
            Assert::AreEqual(0, w.getX());

            Assert::IsFalse(w.moveVertical(2000));
            Assert::AreEqual(0, w.getY());
        }

        TEST_METHOD(TestResize)
        {
            ModelWindow w;

            Assert::IsTrue(w.resize(800, 600));

            Assert::AreEqual(800, w.getWidth());
            Assert::AreEqual(600, w.getHeight());
        }

        TEST_METHOD(TestInvalidResize)
        {
            ModelWindow w;

            Assert::IsFalse(w.resize(0, 500));
            Assert::AreEqual(640, w.getWidth());

            Assert::IsFalse(w.resize(3000, 2000));
            Assert::AreEqual(480, w.getHeight());
        }

        TEST_METHOD(TestChangeColor)
        {
            ModelWindow w;

            w.changeColor("Red");

            Assert::AreEqual(
                std::string("Red"),
                w.getColor()
            );
        }

        TEST_METHOD(TestWindowState)
        {
            ModelWindow w;

            w.setVisible(false);
            w.setBorder(false);

            Assert::IsFalse(w.isVisible());
            Assert::IsFalse(w.hasBorder());

            w.setVisible(true);
            w.setBorder(true);

            Assert::IsTrue(w.isVisible());
            Assert::IsTrue(w.hasBorder());
        }

        TEST_METHOD(TestIncrementDecrement)
        {
            ModelWindow w;

            ++w;

            Assert::AreEqual(1, w.getX());
            Assert::AreEqual(1, w.getY());

            w++;

            Assert::AreEqual(2, w.getX());
            Assert::AreEqual(2, w.getY());

            --w;

            Assert::AreEqual(1, w.getX());
            Assert::AreEqual(1, w.getY());

            w--;

            Assert::AreEqual(0, w.getX());
            Assert::AreEqual(0, w.getY());
        }

        TEST_METHOD(TestStringConversion)
        {
            ModelWindow w;

            std::string result =
                static_cast<std::string>(w);

            Assert::IsTrue(
                result.find("New Window") != std::string::npos
            );

            Assert::IsTrue(
                result.find("White") != std::string::npos
            );
        }

        TEST_METHOD(TestOutputOperator)
        {
            ModelWindow w;

            std::stringstream ss;
            ss << w;

            Assert::IsTrue(
                ss.str().find("New Window") != std::string::npos
            );
        }

        TEST_METHOD(TestCursorDefaultConstructor)
        {
            ModelWindow::Cursor c;

            Assert::AreEqual(1, c.getX());
            Assert::AreEqual(1, c.getY());
            Assert::AreEqual(1, c.getSize());

            Assert::IsTrue(c.isVisible());
        }

        TEST_METHOD(TestCursorParameterizedConstructor)
        {
            ModelWindow::Cursor c(
                100, 200,
                ModelWindow::Cursor::Vertical,
                10
            );

            Assert::AreEqual(100, c.getX());
            Assert::AreEqual(200, c.getY());
            Assert::AreEqual(10, c.getSize());

            Assert::IsTrue(
                c.getType() == ModelWindow::Cursor::Vertical
            );
        }

        TEST_METHOD(TestCursorCoordinates)
        {
            ModelWindow::Cursor c;

            c.setCoordinates(300, 400);

            Assert::AreEqual(300, c.getX());
            Assert::AreEqual(400, c.getY());

            c.setCoordinates(-10, 500);

            Assert::AreEqual(300, c.getX());
            Assert::AreEqual(400, c.getY());
        }

        TEST_METHOD(TestCursorType)
        {
            ModelWindow::Cursor c;

            c.setType(ModelWindow::Cursor::Vertical);

            Assert::IsTrue(
                c.getType() == ModelWindow::Cursor::Vertical
            );

            c.setType(ModelWindow::Cursor::Horizontal);

            Assert::IsTrue(
                c.getType() == ModelWindow::Cursor::Horizontal
            );
        }

        TEST_METHOD(TestCursorSize)
        {
            ModelWindow::Cursor c;

            c.setSize(10);

            Assert::AreEqual(10, c.getSize());

            c.setSize(20);

            Assert::AreEqual(10, c.getSize());

            c.setSize(1);

            Assert::AreEqual(1, c.getSize());
        }

        TEST_METHOD(TestCursorVisibility)
        {
            ModelWindow::Cursor c;

            Assert::IsTrue(c.isVisible());

            c.erase();

            Assert::IsFalse(c.isVisible());

            c.restore();

            Assert::IsTrue(c.isVisible());
        }

        TEST_METHOD(TestCursorIncrement)
        {
            ModelWindow::Cursor c(
                10, 20,
                ModelWindow::Cursor::Horizontal,
                5
            );

            ++c;

            Assert::AreEqual(6, c.getSize());

            c++;

            Assert::AreEqual(7, c.getSize());
        }

        TEST_METHOD(TestCursorDecrement)
        {
            ModelWindow::Cursor c(
                10, 20,
                ModelWindow::Cursor::Horizontal,
                5
            );

            --c;

            Assert::AreEqual(4, c.getSize());

            c--;

            Assert::AreEqual(3, c.getSize());
        }

        TEST_METHOD(TestCursorSizeBoundaries)
        {
            ModelWindow::Cursor c;

            c.setSize(15);
            ++c;

            Assert::AreEqual(15, c.getSize());

            c.setSize(1);
            --c;

            Assert::AreEqual(1, c.getSize());
        }

        TEST_METHOD(TestCursorCopyConstructor)
        {
            ModelWindow::Cursor c1(
                100, 200,
                ModelWindow::Cursor::Vertical,
                8
            );

            ModelWindow::Cursor c2(c1);

            Assert::AreEqual(c1.getX(), c2.getX());
            Assert::AreEqual(c1.getY(), c2.getY());
            Assert::AreEqual(c1.getSize(), c2.getSize());

            Assert::IsTrue(c1.getType() == c2.getType());
        }

        TEST_METHOD(TestCursorAssignment)
        {
            ModelWindow::Cursor c1(
                100, 200,
                ModelWindow::Cursor::Vertical,
                8
            );

            ModelWindow::Cursor c2;

            c2 = c1;

            Assert::AreEqual(c1.getX(), c2.getX());
            Assert::AreEqual(c1.getY(), c2.getY());
            Assert::AreEqual(c1.getSize(), c2.getSize());

            Assert::IsTrue(c1.getType() == c2.getType());
        }

        TEST_METHOD(TestCursorStringConversion)
        {
            ModelWindow::Cursor c;

            std::string result =
                static_cast<std::string>(c);

            Assert::IsTrue(
                result.find("Cursor") != std::string::npos
            );

            Assert::IsTrue(
                result.find("Horizontal") != std::string::npos
            );
        }

        TEST_METHOD(TestObjectCounters)
        {
            int windowsBefore = ModelWindow::getCounter();
            int cursorsBefore =
                ModelWindow::Cursor::getCounter();

            {
                ModelWindow w;

                Assert::AreEqual(
                    windowsBefore + 1,
                    ModelWindow::getCounter()
                );

                Assert::AreEqual(
                    cursorsBefore + 1,
                    ModelWindow::Cursor::getCounter()
                );
            }

            Assert::AreEqual(
                windowsBefore,
                ModelWindow::getCounter()
            );

            Assert::AreEqual(
                cursorsBefore,
                ModelWindow::Cursor::getCounter()
            );
        }

        TEST_METHOD(TestCursorInputOperator)
        {
            ModelWindow::Cursor c;

            std::stringstream ss("100 200 1 10");

            ss >> c;

            Assert::IsTrue(static_cast<bool>(ss));

            Assert::AreEqual(100, c.getX());
            Assert::AreEqual(200, c.getY());
            Assert::AreEqual(10, c.getSize());

            Assert::IsTrue(
                c.getType() == ModelWindow::Cursor::Vertical
            );
        }

    };
}
