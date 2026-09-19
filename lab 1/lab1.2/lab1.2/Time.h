#pragma once
#include <iostream>

using namespace std;

class Time
{
private:
    int hour;
    int minute;    
    int second; 

public:
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }

    bool setHour(int);
    bool setMinute(int);
    bool setSecond(int);

    bool Init(int hour, int minute, int second);

    void Read();
    void Display() const;

    void Display12() const;
};

Time makeTime(int hour, int minute, int second);