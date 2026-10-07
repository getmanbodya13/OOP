#include "Matrix.h"
#include <iostream>
#include <sstream>

using namespace std;

void Matrix::allocateMemory(int newRows, int newCols)
{
    rows = newRows;
    cols = newCols;

    data = new int* [rows];

    for (int i = 0; i < rows; i++)
    {
        data[i] = new int[cols];

        for (int j = 0; j < cols; j++)
        {
            data[i][j] = 0;
        }
    }
}

void Matrix::freeMemory()
{
    if (data != nullptr)
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] data[i];
        }

        delete[] data;
        data = nullptr;
    }

    rows = 0;
    cols = 0;
}

Matrix::Matrix()
{
    rows = 0;
    cols = 0;
    data = nullptr;
}

Matrix::Matrix(int rows, int cols)
{
    if (rows > 0 && cols > 0)
    {
        allocateMemory(rows, cols);
    }
    else
    {
        this->rows = 0;
        this->cols = 0;
        data = nullptr;
    }
}

Matrix::Matrix(const Matrix& other)
{
    if (other.rows > 0 && other.cols > 0)
    {
        allocateMemory(other.rows, other.cols);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                data[i][j] = other.data[i][j];
            }
        }
    }
    else
    {
        rows = 0;
        cols = 0;
        data = nullptr;
    }
}

Matrix::~Matrix()
{
    freeMemory();
}

void Matrix::Init(int newRows, int newCols)
{
    if (newRows <= 0 || newCols <= 0)
    {
        cout << "Error: dimensions must be positive.\n";
        return;
    }

    freeMemory();
    allocateMemory(newRows, newCols);
}

void Matrix::Read()
{
    if (data == nullptr)
    {
        cout << "Matrix is not initialized.\n";
        return;
    }

    cout << "Enter matrix elements:\n";

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << "Element [" << i << "][" << j << "]: ";
            cin >> data[i][j];
        }
    }
}

void Matrix::Display() const
{
    if (data == nullptr)
    {
        cout << "Matrix is empty.\n";
        return;
    }

    cout << "\nMatrix (" << rows << " x " << cols << "):\n";

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << data[i][j] << "\t";
        }

        cout << endl;
    }
}

string Matrix::toString() const
{
    if (data == nullptr)
    {
        return "Empty matrix";
    }

    stringstream ss;

    ss << "Matrix (" << rows << " x " << cols << "):\n";

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            ss << data[i][j];

            if (j < cols - 1)
                ss << "\t";
        }

        ss << "\n";
    }

    return ss.str();
}

void Matrix::resize(int newRows, int newCols)
{
    if (newRows <= 0 || newCols <= 0)
    {
        cout << "Error: dimensions must be positive.\n";
        return;
    }

    int** newData = new int* [newRows];

    for (int i = 0; i < newRows; i++)
    {
        newData[i] = new int[newCols];

        for (int j = 0; j < newCols; j++)
        {
            newData[i][j] = 0;
        }
    }

    int minRows = (rows < newRows) ? rows : newRows;
    int minCols = (cols < newCols) ? cols : newCols;

    for (int i = 0; i < minRows; i++)
    {
        for (int j = 0; j < minCols; j++)
        {
            newData[i][j] = data[i][j];
        }
    }

    freeMemory();

    data = newData;
    rows = newRows;
    cols = newCols;
}

void Matrix::DisplaySubMatrix(int startRow, int startCol,
    int subRows, int subCols) const
{
    if (data == nullptr)
    {
        cout << "Matrix is empty.\n";
        return;
    }

    if (startRow < 0 || startCol < 0 ||
        subRows <= 0 || subCols <= 0 ||
        startRow + subRows > rows ||
        startCol + subCols > cols)
    {
        cout << "Error: invalid submatrix boundaries.\n";
        return;
    }

    cout << "\nSubmatrix:\n";

    for (int i = startRow; i < startRow + subRows; i++)
    {
        for (int j = startCol; j < startCol + subCols; j++)
        {
            cout << data[i][j] << "\t";
        }

        cout << endl;
    }
}

int Matrix::getRows() const
{
    return rows;
}

int Matrix::getCols() const
{
    return cols;
}

void Matrix::setElement(int row, int col, int value)
{
    if (row >= 0 && row < rows &&
        col >= 0 && col < cols)
    {
        data[row][col] = value;
    }
    else
    {
        cout << "Error: invalid index.\n";
    }
}

int Matrix::getElement(int row, int col) const
{
    if (row >= 0 && row < rows &&
        col >= 0 && col < cols)
    {
        return data[row][col];
    }

    cout << "Error: invalid index.\n";
    return 0;
}