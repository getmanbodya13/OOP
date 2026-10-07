#include <iostream>
#include <stdexcept>
#include "Real.h"

int main()
{
    std::cout << "========== NUMBER CLASS (NESTED) ==========\n";

    Real::Number n1;
    n1.Init(10.0f);

    std::cout << "n1: ";
    n1.Display();

    Real::Number n2;
    n2.Init(5.0f);

    std::cout << "n2: ";
    n2.Display();

    std::cout << "n1 value = " << n1.getValue() << std::endl;

    n1.setValue(20.0f);

    std::cout << "After setValue(20): ";
    n1.Display();

    Real::Number sum = n1.add(n2);

    std::cout << "n1 + n2 = ";
    sum.Display();

    Real::Number division = n1.divide(n2);

    std::cout << "n1 / n2 = ";
    division.Display();

    std::cout << "n1.toString() = " << n1.toString() << std::endl;


    std::cout << "\n========== REAL CLASS ==========\n";

    Real::Number baseNumber;
    baseNumber.Init(16.0f);

    Real r1;
    r1.Init(baseNumber);

    std::cout << "r1: ";
    r1.Display();

    Real::Number extracted = r1.getNumber();

    std::cout << "Number inside Real: ";
    extracted.Display();

    Real::Number newNumber;
    newNumber.Init(25.0f);

    r1.setNumber(newNumber);

    std::cout << "After setNumber(25): ";
    r1.Display();

    std::cout << "25^2 = "
        << r1.power(2.0f)
        << std::endl;

    std::cout << "ln(25) = "
        << r1.logarithm()
        << std::endl;

    std::cout << "r1.toString() = "
        << r1.toString()
        << std::endl;


    std::cout << "\n========== READ() DEMONSTRATION ==========\n";

    Real r2;

    r2.Read();

    std::cout << "\nEntered object:\n";
    r2.Display();

    std::cout << "String representation: "
        << r2.toString()
        << std::endl;

    std::cout << "Square: "
        << r2.power(2.0f)
        << std::endl;

    if (r2.getNumber().getValue() > 0)
    {
        std::cout << "Natural logarithm: "
            << r2.logarithm()
            << std::endl;
    }


    std::cout << "\n========== OBJECT ARRAYS ==========\n";

    Real::Number numbers[3];

    numbers[0].Init(2.0f);
    numbers[1].Init(4.0f);
    numbers[2].Init(8.0f);

    std::cout << "Number array:\n";

    for (int i = 0; i < 3; i++)
    {
        std::cout << "numbers[" << i << "] = "
            << numbers[i].toString()
            << std::endl;
    }


    Real reals[3];

    Real::Number value1;
    value1.Init(4.0f);

    Real::Number value2;
    value2.Init(9.0f);

    Real::Number value3;
    value3.Init(16.0f);

    reals[0].Init(value1);
    reals[1].Init(value2);
    reals[2].Init(value3);

    std::cout << "\nReal array:\n";

    for (int i = 0; i < 3; i++)
    {
        std::cout << "reals[" << i << "] = "
            << reals[i].toString()
            << std::endl;
    }


    std::cout << "\n========== EXCEPTION TESTS ==========\n";

    try
    {
        Real::Number zero;
        zero.Init(0.0f);

        n1.divide(zero);
    }
    catch (const std::exception& exception)
    {
        std::cout << "Division error: "
            << exception.what()
            << std::endl;
    }


    try
    {
        Real::Number negative;
        negative.Init(-5.0f);

        Real negativeReal;
        negativeReal.Init(negative);

        negativeReal.logarithm();
    }
    catch (const std::exception& exception)
    {
        std::cout << "Logarithm error: "
            << exception.what()
            << std::endl;
    }


    try
    {
        Real::Number negative;
        negative.Init(-4.0f);

        Real negativeReal;
        negativeReal.Init(negative);

        negativeReal.power(0.5f);
    }
    catch (const std::exception& exception)
    {
        std::cout << "Power error: "
            << exception.what()
            << std::endl;
    }

    return 0;
}