#pragma once
#include <string>

class Matrix
{
private:
    int rows;
    int cols;
    int** data;

    void allocateMemory(int newRows, int newCols);
    void freeMemory();

public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    ~Matrix();

    void Init(int newRows, int newCols);
    void Read();
    void Display() const;
    std::string toString() const;

    void resize(int newRows, int newCols);

    void DisplaySubMatrix(int startRow, int startCol,
        int subRows, int subCols) const;

    int getRows() const;
    int getCols() const;

    void setElement(int row, int col, int value);
    int getElement(int row, int col) const;
};