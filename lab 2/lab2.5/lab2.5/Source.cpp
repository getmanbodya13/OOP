#include <iostream>
#include <string>
#include "Number.h"
#include "Real.h"

using namespace std;

int main()
{
    cout << "===== NUMBER CLASS =====" << endl;

    Number n1;

    Number n2(10.0f);
    Number n3(5.0f);

    Number n4(n2);

    cout << "n1: " << n1 << endl;
    cout << "n2: " << n2 << endl;
    cout << "n3: " << n3 << endl;
    cout << "n4: " << n4 << endl;

    n1 = n2;
    cout << "\nAfter assignment: " << n1 << endl;

    Number sum = n2.add(n3);
    cout << "\nAddition: " << sum << endl;

    Number division = n2.divide(n3);
    cout << "Division: " << division << endl;

    cout << "\nPrefix increment: " << ++n2 << endl;
    cout << "Postfix increment: " << n2++ << endl;
    cout << "After postfix increment: " << n2 << endl;

    cout << "\nPrefix decrement: " << --n2 << endl;
    cout << "Postfix decrement: " << n2-- << endl;
    cout << "After postfix decrement: " << n2 << endl;

    string str = string(n3);
    cout << "\nString conversion: " << str << endl;

    Number n5;
    cout << "\nEnter Number object:" << endl;
    n5.Read();
    cout << "Entered number: ";
    n5.Display();


    cout << "\n===== REAL CLASS =====" << endl;

    Real r1;

    Real r2(16.0f);
    Real r3(4.0f);

    Real r4(r2);

    cout << "r1: " << r1 << endl;
    cout << "r2: " << r2 << endl;
    cout << "r3: " << r3 << endl;
    cout << "r4: " << r4 << endl;

    r1 = r2;
    cout << "\nAfter assignment: " << r1 << endl;

    cout << "\nPower (16^2): " << r2.power(2.0f) << endl;

    cout << "Natural logarithm of 16: "
        << r2.logarithm() << endl;

    cout << "\nPrefix increment: " << ++r2 << endl;
    cout << "Postfix increment: " << r2++ << endl;
    cout << "After postfix increment: " << r2 << endl;

    cout << "\nPrefix decrement: " << --r2 << endl;
    cout << "Postfix decrement: " << r2-- << endl;
    cout << "After postfix decrement: " << r2 << endl;

    string realString = string(r3);
    cout << "\nString conversion: " << realString << endl;

    Real r5;
    cout << "\nEnter Real object:" << endl;
    r5.Read();
    cout << "Entered number: ";
    r5.Display();


    cout << "\n===== ARRAY OF OBJECTS =====" << endl;

    Number numbers[3] = {
        Number(2.0f),
        Number(4.0f),
        Number(6.0f)
    };

    for (int i = 0; i < 3; i++)
    {
        cout << "numbers[" << i << "] = "
            << numbers[i] << endl;
    }

    Real reals[3] = {
        Real(3.0f),
        Real(9.0f),
        Real(27.0f)
    };

    for (int i = 0; i < 3; i++)
    {
        cout << "reals[" << i << "] = "
            << reals[i] << endl;
    }


    cout << "\n===== SIZE OF CLASSES =====" << endl;

    cout << "Without #pragma pack(1):" << endl;
    cout << "sizeof(Number) = " << sizeof(Number) << endl;
    cout << "sizeof(Real) = " << sizeof(Real) << endl;

#pragma pack(push, 1)

    cout << "\nWith #pragma pack(1):" << endl;
    cout << "sizeof(Number) = " << sizeof(Number) << endl;
    cout << "sizeof(Real) = " << sizeof(Real) << endl;

#pragma pack(pop)


    cout << "\n===== END OF PROGRAM =====" << endl;

    return 0;
}