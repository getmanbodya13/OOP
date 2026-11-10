#include <iostream>
#include "Number.h"
#include "Real.h"

using namespace std;

Number processNumber(Number number)
{
    cout << "Function received: " << number << endl;

    return Number(number.getValue() + 1.0f);
}

int main()
{
    cout << "\n--- Creating objects ---" << endl;

    Number n1;
    Number n2(10.5f);
    Number n3(n2);

    Real r1;
    Real r2(16.0f);
    Real r3(r2);

    cout << "n1 = " << n1 << endl;
    cout << "n2 = " << n2 << endl;
    cout << "n3 = " << n3 << endl;

    cout << "r1 = " << r1 << endl;
    cout << "r2 = " << r2 << endl;
    cout << "r3 = " << r3 << endl;

    cout << "\n--- Getters and setters ---" << endl;

    n1.setValue(20.0f);

    cout << "New n1 value: " << n1.getValue() << endl;

    r1.setValue(25.0f);

    cout << "New r1 value: " << r1.getValue() << endl;

    cout << "\n--- Addition ---" << endl;

    Number sum = n1.add(n2);

    cout << n1 << " + " << n2 << " = " << sum << endl;

    cout << "\n--- Division ---" << endl;

    Number quotient = n1.divide(n2);

    cout << n1 << " / " << n2 << " = " << quotient << endl;

    cout << "\n--- Raising to a power ---" << endl;

    Real powerResult = r2.power(2.0f);

    cout << r2 << " ^ 2 = " << powerResult << endl;

    Real anotherPower = r2.power(0.5f);

    cout << "Square root of 16 = " << anotherPower << endl;

    cout << "\n--- Logarithms ---" << endl;

    Real naturalLog = r2.logarithm();

    cout << "ln(16) = " << naturalLog << endl;

    Real logarithmBase = r2.logarithm(2.0f);

    cout << "log2(16) = " << logarithmBase << endl;

    cout << "\n--- String conversion ---" << endl;

    string str = (string)r2;

    cout << "String representation: " << str << endl;

    cout << "\n--- Input ---" << endl;

    Number enteredNumber;
    cin >> enteredNumber;

    cout << "Entered number: " << enteredNumber << endl;

    cout << "\n--- Arrays of objects ---" << endl;

    Number numbers[3] = {
        Number(5.0f),
        Number(10.0f),
        Number(15.0f)
    };

    cout << "Number array:" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << numbers[i] << endl;
    }

    Real reals[3] = {
        Real(2.0f),
        Real(4.0f),
        Real(8.0f)
    };

    cout << "Real array:" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << reals[i] << endl;
    }

    cout << "\n--- Dynamic object creation ---" << endl;

    Number* dynamicNumber = new Number(30.0f);
    Real* dynamicReal = new Real(64.0f);

    cout << *dynamicNumber << endl;
    cout << *dynamicReal << endl;

    delete dynamicNumber;
    delete dynamicReal;

    cout << "\n--- Substitution principle ---" << endl;

    Number& baseReference = r2;

    cout << "Base reference to derived object: "
        << baseReference << endl;

    Number processed = processNumber(r2);

    cout << "Function result: " << processed << endl;

    cout << "\n--- Dynamic array ---" << endl;

    Real* realArray = new Real[3];

    realArray[0].setValue(9.0f);
    realArray[1].setValue(16.0f);
    realArray[2].setValue(25.0f);

    for (int i = 0; i < 3; i++)
    {
        cout << realArray[i] << endl;
    }

    delete[] realArray;

    return 0;
}
