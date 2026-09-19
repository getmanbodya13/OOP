#include "Time.h"

using namespace std;

bool Time::setHour(int value)
{
    if (value >= 0 && value <= 23)
    {
        hour = value;
        return true;
    }
    else
    {
        return false;
    }
}

bool Time::setMinute(int value)
{
    if (value >= 0 && value <= 59)
    {
        minute = value;
        return true;
    }
    else
    {
        return false;
    }
}

bool Time::setSecond(int value)
{
    if (value >= 0 && value <= 59)
    {
        second = value;
        return true;
    }
    else
    {
        return false;
    }
}

bool Time::Init(int hour, int minute, int second)
{
    return setHour(hour) &&
        setMinute(minute) &&
        setSecond(second);
}

void Time::Read()
{
    int hour;
    int minute;
    int second;

    do
    {
        cout << "hour = ";
        cin >> hour;

        cout << "minute = ";
        cin >> minute;

        cout << "second = ";
        cin >> second;

        if (!Init(hour, minute, second))
        {
            cout << "Error! Invalid time. Please try again." << endl;
        }

    } while (!Init(hour, minute, second));
}

void Time::Display() const
{
    cout << hour << " hour "
        << minute << " minute "
        << second << " second " << endl;
}

void Time::Display12() const
{
    int hour12;
    string period;

    if (hour == 0)
    {
        hour12 = 12;
        period = "a.m.";
    }
    else if (hour < 12)
    {
        hour12 = hour;
        period = "a.m.";
    }
    else if (hour == 12)
    {
        hour12 = 12;
        period = "p.m.";
    }
    else
    {
        hour12 = hour - 12;
        period = "p.m.";
    }

    cout << hour12 << " " << period << " "
        << minute << " minute "
        << second << " second " << endl;
}

Time makeTime(int hour, int minute, int second)
{
    Time t;

    if (!t.Init(hour, minute, second))
    {
        cout << "Error! Invalid parameters for Time." << endl;
        exit(1);
    }

    return t;
}