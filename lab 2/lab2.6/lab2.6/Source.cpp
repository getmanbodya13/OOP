#include "Real.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{

    cout << "\n--- Object creation ---" << endl;

    Real r1;
    Real r2(16.0f);
    Real r3(r2);

    cout << "r1: " << r1 << endl;
    cout << "r2: " << r2 << endl;
    cout << "r3: " << r3 << endl;


    cout << "\n--- Nested class Number ---" << endl;

    Real::Number n1;
    Real::Number n2(20.0f);
    Real::Number n3(n2);

    cout << "n1 = " << n1 << endl;
    cout << "n2 = " << n2 << endl;
    cout << "n3 = " << n3 << endl;

    cout << "\n--- Assignment ---" << endl;

    r1 = r2;
    cout << "r1 after assignment: " << r1 << endl;

    n1 = n2;
    cout << "n1 after assignment: " << n1 << endl;

    cout << "\n--- Arithmetic operations ---" << endl;

    Real::Number sum = n1 + n2;
    Real::Number division = n1 / n2;

    cout << "Addition: " << sum << endl;
    cout << "Division: " << division << endl;

    Real::Number sumMethod = n1.add(n2);
    Real::Number divisionMethod = n1.divide(n2);

    cout << "Addition method: " << sumMethod << endl;
    cout << "Division method: " << divisionMethod << endl;


    cout << "\n--- Mathematical operations ---" << endl;

    Real r4(4.0f);

    cout << "Number: " << r4 << endl;
    cout << "Power (4^3): " << r4.power(3) << endl;
    cout << "Natural logarithm: " << r4.logarithm() << endl;


    cout << "\n--- Number increment and decrement ---" << endl;

    Real::Number num(10.0f);

    cout << "Initial: " << num << endl;

    cout << "Prefix ++: " << ++num << endl;
    cout << "Postfix ++: " << num++ << endl;
    cout << "After postfix ++: " << num << endl;

    cout << "Prefix --: " << --num << endl;
    cout << "Postfix --: " << num-- << endl;
    cout << "After postfix --: " << num << endl;


    cout << "\n--- Real increment and decrement ---" << endl;

    Real test(5.0f);

    cout << "Initial: " << test << endl;

    cout << "Prefix ++: " << ++test << endl;
    cout << "Postfix ++: " << test++ << endl;
    cout << "After postfix ++: " << test << endl;

    cout << "Prefix --: " << --test << endl;
    cout << "Postfix --: " << test-- << endl;
    cout << "After postfix --: " << test << endl;


    cout << "\n--- String conversion ---" << endl;

    string str = string(r4);
    cout << "Converted string: " << str << endl;

    string numStr = string(n2);
    cout << "Number as string: " << numStr << endl;


    cout << "\n--- Input ---" << endl;

    Real inputReal;
    cin >> inputReal;

    cout << "Entered value: " << inputReal << endl;

    Real::Number inputNumber;
    cin >> inputNumber;

    cout << "Entered Number: " << inputNumber << endl;

    cout << "\n--- Array of Real objects ---" << endl;

    Real arr[3] = { Real(2), Real(4), Real(8) };

    for (int i = 0; i < 3; i++)
    {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }


    cout << "\n--- Dynamic object creation ---" << endl;

    Real* dynamicReal = new Real(25.0f);

    cout << *dynamicReal << endl;

    delete dynamicReal;


    cout << "\n--- Object counters ---" << endl;

    cout << "Real objects: "
        << Real::getCounter() << endl;

    cout << "Number objects: "
        << Real::Number::getCounter() << endl;


    cout << "\n--- Class sizes ---" << endl;

    cout << "sizeof(Real): "
        << sizeof(Real) << " bytes" << endl;

    cout << "sizeof(Real::Number): "
        << sizeof(Real::Number) << " bytes" << endl;

    struct NormalLayout
    {
        char marker;
        Real object;
    };

#pragma pack(push, 1)
    struct PackedLayout
    {
        char marker;
        Real object;
    };
#pragma pack(pop)

    cout << "Normal layout size: "
        << sizeof(NormalLayout) << " bytes" << endl;

    cout << "Packed layout size: "
        << sizeof(PackedLayout) << " bytes" << endl;

    return 0;
}
