#include <iostream>
#include "Matrix.h"

using namespace std;

void showMenu()
{
    cout << "\n====================================\n";
    cout << "           MATRIX MENU\n";
    cout << "====================================\n";
    cout << "1. Initialize matrix (Init)\n";
    cout << "2. Enter matrix (Read)\n";
    cout << "3. Display matrix (Display)\n";
    cout << "4. Convert matrix to string (toString)\n";
    cout << "5. Resize matrix\n";
    cout << "6. Display submatrix\n";
    cout << "7. Get matrix dimensions\n";
    cout << "8. Set element\n";
    cout << "9. Get element\n";
    cout << "10. Demonstrate object creation\n";
    cout << "0. Exit\n";
    cout << "====================================\n";
    cout << "Choose an option: ";
}

void demonstrateObjects()
{
    cout << "\n===== OBJECT CREATION DEMONSTRATION =====\n";

    Matrix matrix1;

    cout << "\n1. Object created using default constructor:\n";
    matrix1.Init(2, 3);

    matrix1.setElement(0, 0, 1);
    matrix1.setElement(0, 1, 2);
    matrix1.setElement(0, 2, 3);
    matrix1.setElement(1, 0, 4);
    matrix1.setElement(1, 1, 5);
    matrix1.setElement(1, 2, 6);

    matrix1.Display();

    Matrix matrix2(3, 3);

    cout << "\n2. Object created using parameterized constructor:\n";

    int value = 1;

    for (int i = 0; i < matrix2.getRows(); i++)
    {
        for (int j = 0; j < matrix2.getCols(); j++)
        {
            matrix2.setElement(i, j, value++);
        }
    }

    matrix2.Display();

    Matrix matrix3(matrix2);

    cout << "\n3. Object created using copy constructor:\n";
    matrix3.Display();

    Matrix matrices[2] =
    {
        Matrix(2, 2),
        Matrix(3, 2)
    };

    cout << "\n4. Static array of objects:\n";

    matrices[0].setElement(0, 0, 10);
    matrices[0].setElement(0, 1, 20);
    matrices[0].setElement(1, 0, 30);
    matrices[0].setElement(1, 1, 40);

    matrices[1].setElement(0, 0, 1);
    matrices[1].setElement(0, 1, 2);
    matrices[1].setElement(1, 0, 3);
    matrices[1].setElement(1, 1, 4);
    matrices[1].setElement(2, 0, 5);
    matrices[1].setElement(2, 1, 6);

    matrices[0].Display();
    matrices[1].Display();

    Matrix* dynamicMatrices = new Matrix[2];

    dynamicMatrices[0].Init(2, 3);
    dynamicMatrices[1].Init(3, 3);

    cout << "\n5. Dynamic array of objects:\n";

    dynamicMatrices[0].setElement(0, 0, 7);
    dynamicMatrices[0].setElement(0, 1, 8);
    dynamicMatrices[0].setElement(0, 2, 9);
    dynamicMatrices[0].setElement(1, 0, 10);
    dynamicMatrices[0].setElement(1, 1, 11);
    dynamicMatrices[0].setElement(1, 2, 12);

    dynamicMatrices[0].Display();

    delete[] dynamicMatrices;

    cout << "\n=========================================\n";
}

int main()
{
    Matrix matrix;

    int choice;

    do
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int rows, cols;

            cout << "Enter number of rows: ";
            cin >> rows;

            cout << "Enter number of columns: ";
            cin >> cols;

            matrix.Init(rows, cols);

            cout << "Matrix initialized successfully.\n";
            break;
        }

        case 2:
            matrix.Read();
            break;

        case 3:
            matrix.Display();
            break;

        case 4:
            cout << "\nString representation:\n";
            cout << matrix.toString();
            break;

        case 5:
        {
            int rows, cols;

            cout << "Enter new number of rows: ";
            cin >> rows;

            cout << "Enter new number of columns: ";
            cin >> cols;

            matrix.resize(rows, cols);

            cout << "Matrix resized successfully.\n";
            break;
        }

        case 6:
        {
            int startRow, startCol;
            int subRows, subCols;

            cout << "Enter starting row: ";
            cin >> startRow;

            cout << "Enter starting column: ";
            cin >> startCol;

            cout << "Enter number of rows: ";
            cin >> subRows;

            cout << "Enter number of columns: ";
            cin >> subCols;

            matrix.DisplaySubMatrix(
                startRow,
                startCol,
                subRows,
                subCols
            );

            break;
        }

        case 7:
            cout << "\nNumber of rows: "
                << matrix.getRows() << endl;

            cout << "Number of columns: "
                << matrix.getCols() << endl;
            break;

        case 8:
        {
            int row, col, value;

            cout << "Enter row index: ";
            cin >> row;

            cout << "Enter column index: ";
            cin >> col;

            cout << "Enter value: ";
            cin >> value;

            matrix.setElement(row, col, value);

            break;
        }

        case 9:
        {
            int row, col;

            cout << "Enter row index: ";
            cin >> row;

            cout << "Enter column index: ";
            cin >> col;

            cout << "Element = "
                << matrix.getElement(row, col)
                << endl;

            break;
        }

        case 10:
            demonstrateObjects();
            break;

        case 0:
            cout << "\nProgram finished.\n";
            break;

        default:
            cout << "\nInvalid menu option.\n";
        }

    } while (choice != 0);

    return 0;
}