#include <iostream>
#include <stdexcept>

#include "Complex.h"

using namespace std;

int main()
{
    cout << "\n1. Object created using the default constructor:" << endl;

    Complex c1;

    cout << "c1 = ";
    c1.Display();

    cout << "\n2. Initializing an object using Init():" << endl;

    c1.Init(5.0, 3.0);

    cout << "After Init(5.0, 3.0): ";
    c1.Display();

    cout << "\n3. Object created using the parameterized constructor:" << endl;

    Complex c2(2.0, -4.0);

    cout << "c2 = ";
    c2.Display();

    cout << "\n4. Reading a complex number from the keyboard:" << endl;

    Complex c3;

    c3.Read();

    cout << "Entered number: ";
    c3.Display();

    cout << "\n5. Subtraction of two complex numbers:" << endl;

    Complex subResult = c1.sub(c2);

    cout << "c1 = ";
    c1.Display();

    cout << "c2 = ";
    c2.Display();

    cout << "c1 - c2 = ";
    subResult.Display();

    cout << "\n6. Division of two complex numbers:" << endl;

    try
    {
        Complex divResult = c1.div(c2);

        cout << "c1 = ";
        c1.Display();

        cout << "c2 = ";
        c2.Display();

        cout << "c1 / c2 = ";
        divResult.Display();
    }
    catch (const invalid_argument& error)
    {
        cout << error.what() << endl;
    }

    cout << "\n7. Complex conjugate:" << endl;

    Complex conjugate = c1.conj();

    cout << "c1 = ";
    c1.Display();

    cout << "conj(c1) = ";
    conjugate.Display();

    cout << "\n8. Static array of Complex objects:" << endl;

    Complex numbers[3] =
    {
        Complex(1.0, 2.0),
        Complex(3.0, -4.0),
        Complex(5.0, 6.0)
    };

    for (int i = 0; i < 3; i++)
    {
        cout << "numbers[" << i << "] = ";
        numbers[i].Display();
    }

    cout << "\n9. Dynamic array of Complex objects:" << endl;

    int size = 3;

    Complex* dynamicArray = new Complex[size];

    dynamicArray[0].Init(10.0, 5.0);
    dynamicArray[1].Init(-2.0, 7.0);
    dynamicArray[2].Init(4.0, -3.0);

    for (int i = 0; i < size; i++)
    {
        cout << "dynamicArray[" << i << "] = ";
        dynamicArray[i].Display();
    }

    delete[] dynamicArray;

    cout << "\n10. Converting a Complex object to a string:" << endl;

    Complex c4(7.5, -2.5);

    string text = c4.toString();

    cout << "Result of toString(): " << text << endl;

    cout << "\n11. Additional operations:" << endl;

    Complex a(8.0, 6.0);
    Complex b(2.0, 3.0);

    cout << "a = ";
    a.Display();

    cout << "b = ";
    b.Display();

    Complex subtraction = a.sub(b);
    Complex division = a.div(b);
    Complex conjugateA = a.conj();

    cout << "a - b = ";
    subtraction.Display();

    cout << "a / b = ";
    division.Display();

    cout << "conj(a) = ";
    conjugateA.Display();

    return 0;
}