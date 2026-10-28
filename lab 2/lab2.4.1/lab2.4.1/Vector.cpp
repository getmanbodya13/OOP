#include "Vector.h"

#include <stdexcept>
#include <sstream>

Vector::Vector()
{
    n = 0;
    data = nullptr;
}

Vector::Vector(int size)
{
    if (size < 0)
        throw invalid_argument("Vector size cannot be negative!");

    n = size;
    data = (n > 0) ? new int[n]() : nullptr;
}

Vector::Vector(initializer_list<int> values)
{
    n = static_cast<int>(values.size());
    data = (n > 0) ? new int[n] : nullptr;

    int i = 0;
    for (int value : values)
        data[i++] = value;
}

Vector::Vector(const Vector& other)
{
    n = other.n;
    data = (n > 0) ? new int[n] : nullptr;

    for (int i = 0; i < n; i++)
        data[i] = other.data[i];
}

Vector::~Vector()
{
    delete[] data;
}

int Vector::getSize() const
{
    return n;
}

int Vector::getElement(int index) const
{
    if (index < 0 || index >= n)
        throw out_of_range("Vector index out of range!");

    return data[index];
}

void Vector::setElement(int index, int value)
{
    if (index < 0 || index >= n)
        throw out_of_range("Vector index out of range!");

    data[index] = value;
}

Vector& Vector::operator=(const Vector& other)
{
    if (this == &other)
        return *this;

    int* newData = (other.n > 0) ? new int[other.n] : nullptr;

    for (int i = 0; i < other.n; i++)
        newData[i] = other.data[i];

    delete[] data;

    data = newData;
    n = other.n;

    return *this;
}

int& Vector::operator[](int index)
{
    if (index < 0 || index >= n)
        throw out_of_range("Vector index out of range!");

    return data[index];
}

const int& Vector::operator[](int index) const
{
    if (index < 0 || index >= n)
        throw out_of_range("Vector index out of range!");

    return data[index];
}

Vector& Vector::operator++()
{
    for (int i = 0; i < n; i++)
        data[i]++;

    return *this;
}

Vector Vector::operator++(int)
{
    Vector temp(*this);

    for (int i = 0; i < n; i++)
        data[i]++;

    return temp;
}

Vector& Vector::operator--()
{
    for (int i = 0; i < n; i++)
        data[i]--;

    return *this;
}

Vector Vector::operator--(int)
{
    Vector temp(*this);

    for (int i = 0; i < n; i++)
        data[i]--;

    return temp;
}

int Vector::norm() const
{
    if (n == 0)
        return 0;

    int minValue = data[0];
    int maxValue = data[0];

    for (int i = 1; i < n; i++)
    {
        if (data[i] < minValue)
            minValue = data[i];

        if (data[i] > maxValue)
            maxValue = data[i];
    }

    return maxValue - minValue;
}

Vector::operator string() const
{
    stringstream ss;

    ss << "[";

    for (int i = 0; i < n; i++)
    {
        ss << data[i];

        if (i < n - 1)
            ss << ", ";
    }

    ss << "]";

    return ss.str();
}

Vector operator+(const Vector& left, const Vector& right)
{
    if (left.n != right.n)
        throw invalid_argument(
            "Vectors must have the same size!"
        );

    Vector result(left.n);

    for (int i = 0; i < left.n; i++)
        result.data[i] = left.data[i] + right.data[i];

    return result;
}

bool operator==(const Vector& left, const Vector& right)
{
    if (left.n != right.n)
        return false;

    for (int i = 0; i < left.n; i++)
    {
        if (left.data[i] != right.data[i])
            return false;
    }

    return true;
}

bool operator!=(const Vector& left, const Vector& right)
{
    return !(left == right);
}

ostream& operator<<(ostream& out, const Vector& v)
{
    out << string(v);
    return out;
}

istream& operator>>(istream& in, Vector& v)
{
    for (int i = 0; i < v.n; i++)
    {
        cout << "Enter element [" << i << "]: ";
        in >> v.data[i];

        if (!in)
            return in;
    }

    return in;
}