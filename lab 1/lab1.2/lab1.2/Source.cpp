#include <iostream>
#include "Time.h"

using namespace std;

int main()
{
    Time t;

    t.Read();

    cout << endl;
    cout << "24-hour format:" << endl;
    t.Display();

    cout << endl;
    cout << "12-hour format:" << endl;
    t.Display12();

    cout << endl;
    cout << "Hour: " << t.getHour() << endl;
    cout << "Minute: " << t.getMinute() << endl;
    cout << "Second: " << t.getSecond() << endl;

    cout << endl;
    cout << "Object created using makeTime():" << endl;

    Time t2 = makeTime(16, 18, 3);
    t2.Display();
    t2.Display12();

    return 0;
}