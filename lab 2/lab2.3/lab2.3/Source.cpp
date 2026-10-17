#include "Complex.h"

#include <iostream>
#include <string>
#include <exception>

using namespace std;

int main()
{
    cout << "===== COMPLEX NUMBERS =====\n\n";

    Complex c1;
    Complex c2(6.0, 4.0);
    Complex c3(c2);

    cout << "Default constructor: " << c1 << '\n';
    cout << "Initialization constructor: " << c2 << '\n';
    cout << "Copy constructor: " << c3 << "\n\n";

    cout << "Enter a complex number:\n";
    if (!(cin >> c1))
    {
        cerr << "Invalid input!\n";
        return 1;
    }

    cout << "Entered number: " << c1 << "\n\n";

    c3 = c1;
    cout << "After assignment c3 = c1: " << c3 << '\n';

    cout << "\nReal part: " << c2.GetX() << '\n';
    cout << "Imaginary part: " << c2.GetY() << '\n';

    c3.SetX(8.0);
    c3.SetY(3.0);
    cout << "After SetX and SetY: " << c3 << '\n';

    c3.Init(2.0, 5.0);
    cout << "After Init: ";
    c3.Display();
    cout << '\n';

    cout << "\nRead() method:\n";
    c3.Read();
    cout << "Result: ";
    c3.Display();
    cout << '\n';

    string text = static_cast<string>(c2);
    cout << "\nString conversion: " << text << '\n';
    cout << "toString(): " << c2.toString() << "\n\n";

    Complex a(8.0, 6.0);
    Complex b(2.0, 3.0);

    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';
    cout << "a.sub(b) = " << a.sub(b) << '\n';
    cout << "a - b = " << a - b << "\n\n";

    cout << "a.div(b) = " << a.div(b) << '\n';
    cout << "a / b = " << a / b << "\n\n";

    cout << "conj(a) = " << a.conj() << "\n\n";

    Complex p(3.0, 4.0);
    cout << "Initial p: " << p << '\n';
    cout << "++p = " << ++p << '\n';
    cout << "p after ++p: " << p << "\n\n";

    cout << "--p = " << --p << '\n';
    cout << "p after --p: " << p << "\n\n";

    cout << "p++ = " << p++ << '\n';
    cout << "p after p++: " << p << "\n\n";

    cout << "p-- = " << p-- << '\n';
    cout << "p after p--: " << p << "\n\n";

    Complex arr[3] = {
        Complex(),
        Complex(1.0, 2.0),
        Complex(a)
    };

    cout << "Array of complex numbers:\n";
    for (int i = 0; i < 3; ++i)
    {
        cout << "arr[" << i << "] = ";
        arr[i].Display();
        cout << '\n';
    }

    Complex* dynamicArray = new Complex[2];
    dynamicArray[0] = a;
    dynamicArray[1] = b;

    cout << "\nDynamic array:\n";
    for (int i = 0; i < 2; ++i)
        cout << "dynamicArray[" << i << "] = "
        << dynamicArray[i] << '\n';

    delete[] dynamicArray;

    cout << "\n===== CLASS SIZE =====\n";
    cout << "Complex (normal alignment): "
        << sizeof(Complex) << " bytes\n";

    cout << "ComplexPacked (#pragma pack(1)): "
        << sizeof(ComplexPacked) << " bytes\n";

    try
    {
        Complex zero(0.0, 0.0);
        cout << "\na / zero = " << a / zero << '\n';
    }
    catch (const exception& e)
    {
        cout << "\nError: " << e.what() << '\n';
    }

    cout << "\nProgram completed successfully.\n";

    return 0;
}
