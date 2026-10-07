#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1.4/Matrix.h"
#include "../lab1.4/Matrix.cpp"
#include "../lab1.4/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(DefaultConstructorTest)
    {
    public:

        TEST_METHOD(DefaultConstructor)
        {
            Matrix matrix;

            Assert::AreEqual(0, matrix.getRows());
            Assert::AreEqual(0, matrix.getCols());
        }
    };


    TEST_CLASS(ParameterizedConstructorTest)
    {
    public:

        TEST_METHOD(ParameterizedConstructor)
        {
            Matrix matrix(3, 4);

            Assert::AreEqual(3, matrix.getRows());
            Assert::AreEqual(4, matrix.getCols());
        }
    };

    TEST_CLASS(InitTest)
    {
    public:

        TEST_METHOD(InitializeMatrix)
        {
            Matrix matrix;

            matrix.Init(5, 6);

            Assert::AreEqual(5, matrix.getRows());
            Assert::AreEqual(6, matrix.getCols());
        }
    };

    TEST_CLASS(ElementTest)
    {
    public:

        TEST_METHOD(SetAndGetElement)
        {
            Matrix matrix(3, 3);

            matrix.setElement(0, 0, 10);
            matrix.setElement(1, 1, 20);
            matrix.setElement(2, 2, 30);

            Assert::AreEqual(10, matrix.getElement(0, 0));
            Assert::AreEqual(20, matrix.getElement(1, 1));
            Assert::AreEqual(30, matrix.getElement(2, 2));
        }
    };

    TEST_CLASS(InitialValuesTest)
    {
    public:

        TEST_METHOD(NewMatrixContainsZeros)
        {
            Matrix matrix(2, 3);

            Assert::AreEqual(0, matrix.getElement(0, 0));
            Assert::AreEqual(0, matrix.getElement(0, 1));
            Assert::AreEqual(0, matrix.getElement(0, 2));

            Assert::AreEqual(0, matrix.getElement(1, 0));
            Assert::AreEqual(0, matrix.getElement(1, 1));
            Assert::AreEqual(0, matrix.getElement(1, 2));
        }
    };


    TEST_CLASS(ResizeTest)
    {
    public:

        TEST_METHOD(ResizeMatrix)
        {
            Matrix matrix(2, 2);

            matrix.setElement(0, 0, 1);
            matrix.setElement(0, 1, 2);
            matrix.setElement(1, 0, 3);
            matrix.setElement(1, 1, 4);

            matrix.resize(3, 4);

            Assert::AreEqual(3, matrix.getRows());
            Assert::AreEqual(4, matrix.getCols());

            Assert::AreEqual(1, matrix.getElement(0, 0));
            Assert::AreEqual(2, matrix.getElement(0, 1));
            Assert::AreEqual(3, matrix.getElement(1, 0));
            Assert::AreEqual(4, matrix.getElement(1, 1));

            Assert::AreEqual(0, matrix.getElement(2, 3));
        }
    };


    TEST_CLASS(ResizeSmallerTest)
    {
    public:

        TEST_METHOD(ResizeToSmallerMatrix)
        {
            Matrix matrix(4, 4);

            matrix.setElement(0, 0, 10);
            matrix.setElement(0, 1, 20);
            matrix.setElement(1, 0, 30);
            matrix.setElement(1, 1, 40);

            matrix.resize(2, 2);

            Assert::AreEqual(2, matrix.getRows());
            Assert::AreEqual(2, matrix.getCols());

            Assert::AreEqual(10, matrix.getElement(0, 0));
            Assert::AreEqual(20, matrix.getElement(0, 1));
            Assert::AreEqual(30, matrix.getElement(1, 0));
            Assert::AreEqual(40, matrix.getElement(1, 1));
        }
    };


    TEST_CLASS(ToStringTest)
    {
    public:

        TEST_METHOD(ConvertMatrixToString)
        {
            Matrix matrix(2, 2);

            matrix.setElement(0, 0, 1);
            matrix.setElement(0, 1, 2);
            matrix.setElement(1, 0, 3);
            matrix.setElement(1, 1, 4);

            std::string result = matrix.toString();

            Assert::IsTrue(
                result.find("1") != std::string::npos
            );

            Assert::IsTrue(
                result.find("2") != std::string::npos
            );

            Assert::IsTrue(
                result.find("3") != std::string::npos
            );

            Assert::IsTrue(
                result.find("4") != std::string::npos
            );
        }
    };


    TEST_CLASS(CopyConstructorTest)
    {
    public:

        TEST_METHOD(CopyMatrix)
        {
            Matrix original(2, 2);

            original.setElement(0, 0, 10);
            original.setElement(0, 1, 20);
            original.setElement(1, 0, 30);
            original.setElement(1, 1, 40);

            Matrix copy(original);

            Assert::AreEqual(2, copy.getRows());
            Assert::AreEqual(2, copy.getCols());

            Assert::AreEqual(10, copy.getElement(0, 0));
            Assert::AreEqual(20, copy.getElement(0, 1));
            Assert::AreEqual(30, copy.getElement(1, 0));
            Assert::AreEqual(40, copy.getElement(1, 1));
        }
    };


    TEST_CLASS(CopyIndependenceTest)
    {
    public:

        TEST_METHOD(CopyIsIndependent)
        {
            Matrix original(2, 2);

            original.setElement(0, 0, 10);

            Matrix copy(original);

            copy.setElement(0, 0, 99);

            Assert::AreEqual(
                10,
                original.getElement(0, 0)
            );

            Assert::AreEqual(
                99,
                copy.getElement(0, 0)
            );
        }
    };

    TEST_CLASS(SubMatrixTest)
    {
    public:

        TEST_METHOD(SubMatrixDoesNotThrow)
        {
            Matrix matrix(4, 4);

            int value = 1;

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    matrix.setElement(i, j, value++);
                }
            }

            try
            {
                matrix.DisplaySubMatrix(1, 1, 2, 2);
            }
            catch (...)
            {
                Assert::Fail(
                    L"DisplaySubMatrix generated an exception."
                );
            }
        }
    };


    TEST_CLASS(ObjectArrayTest)
    {
    public:

        TEST_METHOD(ArrayOfObjects)
        {
            Matrix matrices[2] =
            {
                Matrix(2, 2),
                Matrix(3, 3)
            };

            Assert::AreEqual(
                2,
                matrices[0].getRows()
            );

            Assert::AreEqual(
                2,
                matrices[0].getCols()
            );

            Assert::AreEqual(
                3,
                matrices[1].getRows()
            );

            Assert::AreEqual(
                3,
                matrices[1].getCols()
            );
        }
    };


    TEST_CLASS(DynamicObjectArrayTest)
    {
    public:

        TEST_METHOD(DynamicArrayOfObjects)
        {
            Matrix* matrices = new Matrix[2];

            matrices[0].Init(2, 3);
            matrices[1].Init(4, 5);

            Assert::AreEqual(
                2,
                matrices[0].getRows()
            );

            Assert::AreEqual(
                3,
                matrices[0].getCols()
            );

            Assert::AreEqual(
                4,
                matrices[1].getRows()
            );

            Assert::AreEqual(
                5,
                matrices[1].getCols()
            );

            delete[] matrices;
        }
    };
}