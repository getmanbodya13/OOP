#include <iostream>
#include <string>
#include "Point.h"

using namespace std;

#pragma pack(push, 1)
struct PackedPoint
{
    double first;
    double second;
};
#pragma pack(pop)

int main()
{
    setlocale(LC_ALL, "");

    Point p1;
    cout << "Default constructor: " << p1 << endl;

    Point p2(3, 4);
    cout << "\nInitialization constructor: " << p2 << endl;

    Point p3(p2);
    cout << "Copy constructor: " << p3 << endl;

    Point p4 = makePoint(-5, 12);
    cout << "\nPoint created by makePoint(): " << p4 << endl;

    p1 = p2;
    cout << "\nAfter assignment p1 = p2: " << p1 << endl;

    cout << "\nX coordinate: " << p2.GetFirst() << endl;
    cout << "Y coordinate: " << p2.GetSecond() << endl;

    p1.SetFirst(6);
    p1.SetSecond(8);
    cout << "After setters: ";
    p1.Display();

    cout << "\nDistance from origin: "
        << p2.distance() << endl;

    cout << "\nPrefix increment (++p2): "
        << ++p2 << endl;

    cout << "Prefix decrement (--p2): "
        << --p2 << endl;

    cout << "\nPostfix increment (p2++): "
        << p2++ << endl;
    cout << "After p2++: " << p2 << endl;

    cout << "Postfix decrement (p2--): "
        << p2-- << endl;
    cout << "After p2--: " << p2 << endl;

    string text = static_cast<string>(p4);
    cout << "\nString conversion: " << text << endl;

    Point p5;
    cout << "\nEnter coordinates for a new point:" << endl;
    p5.Read();
    cout << "Entered point: ";
    p5.Display();
    cout << endl;

    Point points[3] = {
        Point(1, 2),
        Point(3, 4),
        Point(-6, 8)
    };

    cout << "\nArray of points:" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << "points[" << i << "] = "
            << points[i]
            << ", distance = "
            << points[i].distance() << endl;
    }

    cout << "\nClass size without packing: "
        << sizeof(Point) << " bytes" << endl;

    cout << "Equivalent layout with #pragma pack(1): "
        << sizeof(PackedPoint) << " bytes" << endl;

    cout << "\nProgram completed successfully." << endl;

    return 0;
}
