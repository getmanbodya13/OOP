#include "Point.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Point makePoint(double x, double y)
{
    Point p;

    if (!p.Init(x, y))
    {
        cout << "Wrong arguments to Init!" << endl;
        exit(1);
    }

    return p;
}

int main()
{
    Point p;

    p.Read();
    p.Display();

    cout << "Distance from point to origin = "
        << p.Distance() << endl << endl;


    double x, y;

    cout << "Input point coordinates:" << endl;

    cout << "x = ";
    cin >> x;

    cout << "y = ";
    cin >> y;

    p = makePoint(x, y);

    p.Display();

    cout << "Distance from point to origin = "
        << p.Distance() << endl;

    return 0;
}