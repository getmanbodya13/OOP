#include "ArrayNumbers.h"

int main()
{
    setlocale(LC_ALL, "uk_UA");

    cout << "===== OCTAL NUMBERS =====" << endl;

    Octal a("157");
    Octal b("23");

    cout << "A = " << a.toString() << endl;
    cout << "B = " << b.toString() << endl;

    cout << "A + B = " << (a + b).toString() << endl;
    cout << "A - B = " << (a - b).toString() << endl;
    cout << "A * B = " << (a * b).toString() << endl;
    cout << "A / B = " << (a / b).toString() << endl;
    cout << "A % B = " << (a % b).toString() << endl;

    cout << "A > B: " << (a > b) << endl;
    cout << "A == B: " << (a == b) << endl;

    cout << "\n===== HEX NUMBERS =====" << endl;

    Hex h1("AF");
    Hex h2("12");

    cout << "H1 = " << h1.toString() << endl;
    cout << "H2 = " << h2.toString() << endl;

    cout << "H1 + H2 = " << (h1 + h2).toString() << endl;
    cout << "H1 - H2 = " << (h1 - h2).toString() << endl;
    cout << "H1 * H2 = " << (h1 * h2).toString() << endl;
    cout << "H1 / H2 = " << (h1 / h2).toString() << endl;
    cout << "H1 % H2 = " << (h1 % h2).toString() << endl;

    cout << "H1 > H2: " << (h1 > h2) << endl;

    cout << "\n===== INDEXING OPERATOR =====" << endl;

    cout << "A[0] = " << (int)a[0] << endl;

    cout << "\n===== POLYMORPHISM =====" << endl;

    Array* arr1 = new Octal("157");
    Array* arr2 = new Octal("23");

    Array* arr3 = new Hex("AF");
    Array* arr4 = new Hex("12");

    unique_ptr<Array> result1 = arr1->add(*arr2);
    unique_ptr<Array> result2 = arr3->add(*arr4);

    cout << "Result 1:" << endl;
    cout << "Actual type: " << result1->typeName() << endl;
    result1->print();

    cout << "Result 2:" << endl;
    cout << "Actual type: " << result2->typeName() << endl;
    result2->print();

    Array* objects[] = {
        arr1, arr3, arr2, arr4
    };

    cout << "\n===== POLYMORPHIC OBJECT TYPES =====" << endl;

    for (Array* obj : objects)
    {
        cout << "Object type: " << obj->typeName() << endl;
        obj->print();
    }

    cout << "\n===== VIRTUAL ADDITION =====" << endl;

    unique_ptr<Array> result3 = arr1->add(*arr2);
    unique_ptr<Array> result4 = arr3->add(*arr4);

    result3->print();
    result4->print();

    delete arr1;
    delete arr2;
    delete arr3;
    delete arr4;

    return 0;
}
