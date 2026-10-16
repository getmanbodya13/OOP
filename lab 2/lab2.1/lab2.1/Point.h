#pragma once
#include <iostream>
#include <string>

using namespace std;

class Point
{
private:
    double first;
    double second; 

    static bool IsValid(double value);

public:
    Point();
    Point(double x, double y);
    Point(const Point& other);

    double GetFirst() const;
    double GetSecond() const;

    void SetFirst(double value);
    void SetSecond(double value);

    void Init(double x, double y);
    void Read();
    void Display() const;

    double distance() const;

    Point& operator=(const Point& other);

    operator string() const;

    friend istream& operator>>(istream& in, Point& p);
    friend ostream& operator<<(ostream& out, const Point& p);

    Point& operator++();
    Point& operator--();

    Point operator++(int);
    Point operator--(int);
};

Point makePoint(double x, double y);
