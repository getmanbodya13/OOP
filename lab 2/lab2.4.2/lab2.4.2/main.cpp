#include <iostream>
#include <string>
#include "Octal.h"

using namespace std;

#pragma pack(push, 1)
struct PackedOctal {
    unsigned char digits[100];
    int size;
    int count;
};
#pragma pack(pop)

struct NormalOctal {
    unsigned char digits[100];
    int size;
    int count;
};

int main() {
    setlocale(LC_ALL, "");

    try {
        Octal zero;
        Octal a(20, "157");
        Octal b(20, "24");
        Octal copy(a);

        cout << "Initial objects:\n";
        cout << "zero = " << zero << '\n';
        cout << "a = " << a << '\n';
        cout << "b = " << b << '\n';
        cout << "copy = " << copy << "\n\n";

        cout << "Maximum size of a: " << a.size() << '\n';
        cout << "Number of digits in a: " << a.count() << '\n';
        cout << "Digit at index 0: "
            << static_cast<int>(a.getDigit(0)) << "\n\n";

        cout << "a[0] = " << static_cast<int>(a[0]) << '\n';
        a[0] = 3;
        cout << "After a[0] = 3: " << a << "\n\n";

        zero = b;
        cout << "After assignment, zero = " << zero << "\n\n";

        cout << "a + b = " << a + b << '\n';
        cout << "a - b = " << a - b << '\n';
        cout << "a * b = " << a * b << '\n';
        cout << "a / b = " << a / b << '\n';
        cout << "a % b = " << a % b << "\n\n";

        cout << boolalpha;
        cout << "a == b: " << (a == b) << '\n';
        cout << "a != b: " << (a != b) << '\n';
        cout << "a > b: " << (a > b) << '\n';
        cout << "a < b: " << (a < b) << '\n';
        cout << "a >= b: " << (a >= b) << '\n';
        cout << "a <= b: " << (a <= b) << "\n\n";

        Octal c(20, "7");

        cout << "c = " << c << '\n';
        cout << "++c = " << ++c << '\n';
        cout << "c++ = " << c++ << '\n';
        cout << "After c++, c = " << c << '\n';
        cout << "--c = " << --c << '\n';
        cout << "c-- = " << c-- << '\n';
        cout << "After c--, c = " << c << "\n\n";

        string text = static_cast<string>(a);
        cout << "a converted to string: " << text << "\n\n";

        Octal numbers[3] = {
            Octal(10, "12"),
            Octal(10, "34"),
            Octal(10, "56")
        };

        cout << "Array of Octal objects:\n";
        for (const Octal& number : numbers)
            cout << number << '\n';

        Octal input(20);
        cout << "\nEnter an octal number (digits 0-7): ";

        if (cin >> input)
            cout << "You entered: " << input << '\n';
        else
            cout << "Invalid octal number or capacity exceeded.\n";

        cout << "\nSize of PackedOctal: "
            << sizeof(PackedOctal) << " bytes\n";

        cout << "Size of NormalOctal: "
            << sizeof(NormalOctal) << " bytes\n";

        cout << "Size of Octal class: "
            << sizeof(Octal) << " bytes\n";
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}
