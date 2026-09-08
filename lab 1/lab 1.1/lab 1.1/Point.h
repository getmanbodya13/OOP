#pragma once

class Point
{
private:
    double first;
    double second;

public:
    double GetFirst() const { return first; }
    double GetSecond() const { return second; }

    bool SetFirst(double value);
    bool SetSecond(double value);

    bool Init(double x, double y);

    void Read();
    void Display() const;

    double Distance() const;
};