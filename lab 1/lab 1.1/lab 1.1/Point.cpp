#include "Point.h"
#include <iostream>
#include <cmath>

using namespace std;

bool Point::SetFirst(double value)
{
    if (fabs(value) <= 100)
    {
        first = value;
        return true;
    }
    else
    {
        first = 0;
        return false;
    }
}

bool Point::SetSecond(double value)
{
    if (fabs(value) <= 100)
    {
        second = value;
        return true;
    }
    else
    {
        second = 0;
        return false;
    }
}

bool Point::Init(double x, double y)
{
    return SetFirst(x) && SetSecond(y);
}

void Point::Read()
{
    double x, y;

    do
    {
        cout << "Input point coordinates:" << endl;

        cout << "x = ";
        cin >> x;

        cout << "y = ";
        cin >> y;

    } while (!Init(x, y));
}

void Point::Display() const
{
    cout << endl;
    cout << "x = " << first << endl;
    cout << "y = " << second << endl;
}

double Point::Distance() const
{
    return sqrt(first * first + second * second);
}