#include "Point.h"
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <limits>

bool Point::IsValid(double value)
{
    return std::isfinite(value) &&
        value >= -100.0 && value <= 100.0;
}

Point::Point()
{
    first = 0;
    second = 0;
}

Point::Point(double x, double y)
{
    Init(x, y);
}

Point::Point(const Point& other)
{
    first = other.first;
    second = other.second;
}

double Point::GetFirst() const
{
    return first;
}

double Point::GetSecond() const
{
    return second;
}

void Point::SetFirst(double value)
{
    if (!IsValid(value))
        throw invalid_argument("Invalid x coordinate!");

    first = value;
}

void Point::SetSecond(double value)
{
    if (!IsValid(value))
        throw invalid_argument("Invalid y coordinate!");

    second = value;
}

void Point::Init(double x, double y)
{
    if (!IsValid(x) || !IsValid(y))
        throw invalid_argument("Coordinates must be in [-100, 100]!");

    first = x;
    second = y;
}

void Point::Read()
{
    cin >> *this;
}

void Point::Display() const
{
    cout << *this;
}

double Point::distance() const
{
    return sqrt(first * first + second * second);
}

Point& Point::operator=(const Point& other)
{
    if (this != &other)
    {
        first = other.first;
        second = other.second;
    }

    return *this;
}

Point::operator string() const
{
    ostringstream out;
    out << "Point(x = " << first
        << ", y = " << second << ")";
    return out.str();
}

istream& operator>>(istream& in, Point& p)
{
    double x, y;

    while (true)
    {
        cout << "Enter x (-100..100): ";

        if (!(in >> x))
            return in;

        cout << "Enter y (-100..100): ";

        if (!(in >> y))
            return in;

        if (Point::IsValid(x) && Point::IsValid(y))
        {
            p.first = x;
            p.second = y;
            break;
        }

        cout << "Error! Coordinates must be in [-100, 100]."
            << endl;
    }

    return in;
}

ostream& operator<<(ostream& out, const Point& p)
{
    out << "Point(x = " << p.first
        << ", y = " << p.second << ")";
    return out;
}

Point& Point::operator++()
{
    SetFirst(first + 1);
    return *this;
}

Point& Point::operator--()
{
    SetFirst(first - 1);
    return *this;
}

Point Point::operator++(int)
{
    Point temp(*this);
    SetSecond(second + 1);
    return temp;
}

Point Point::operator--(int)
{
    Point temp(*this);
    SetSecond(second - 1);
    return temp;
}

Point makePoint(double x, double y)
{
    try
    {
        return Point(x, y);
    }
    catch (const invalid_argument& e)
    {
        cerr << "Error creating Point: " << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}
