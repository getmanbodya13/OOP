#include "ComplexPub.h"
#include "ComplexPriv.h"
#include "PackedSize.h"
using namespace std;

int main()
{
    try
    {
        cout << "=== Class sizes ===" << endl;
        cout << "Without pack(1): Complex = " << sizeof(Complex)
            << ", ComplexPub = " << sizeof(ComplexPub)
            << ", ComplexPriv = " << sizeof(ComplexPriv) << endl;
        cout << "With pack(1):    Complex = " << SizeComplexPacked()
            << ", ComplexPub = " << SizeComplexPubPacked()
            << ", ComplexPriv = " << SizeComplexPrivPacked() << endl;

        cout << "\n=== Base class Complex ===" << endl;
        Complex b0, b1(3), b2(3, 4), b3(b2);
        b0.Init(1, 2);
        b1.Display();
        cout << b2 << " " << b3 << " " << b0.toString() << endl;

        cout << "\n=== Public inheritance ===" << endl;
        ComplexPub a1;            
        ComplexPub a2(1, 2);        
        ComplexPub a3(3, -4);
        ComplexPub a4(a2);         
        ComplexPub arr[3] = { ComplexPub(1), ComplexPub(2, 3), ComplexPub() };
        ComplexPub* dyn = new ComplexPub[2]{ ComplexPub(5, 5), ComplexPub(1, 1) };

        cout << "Enter a1:" << endl;
        cin >> a1;                     
        cout << "a1 = " << a1 << endl;
        cout << "a2 = " << a2 << ", a3 = " << a3 << endl;
        cout << "a2 - a3 = " << (a2 - a3) << endl;
        cout << "a2.sub(a3) = " << a2.sub(a3) << endl;
        cout << "a2 / a3 = " << (a2 / a3) << endl;
        cout << "a2.div(a3) = " << a2.div(a3) << endl;
        cout << "~a3 = " << ~a3 << ", a3.conj() = " << a3.conj() << endl;
        a4 = a3;
        cout << "a4 = a3 -> " << a4 << endl;
        cout << "++a4 = " << ++a4 << ", a4++ = " << a4++ << ", now " << a4 << endl;
        cout << "--a4 = " << --a4 << ", a4-- = " << a4-- << ", now " << a4 << endl;
        string s = a2;
        cout << "string: " << s << endl;
        for (int i = 0; i < 3; i++) cout << "arr[" << i << "] = " << arr[i] << endl;
        cout << "dyn[0] = " << dyn[0] << ", dyn[1] = " << dyn[1] << endl;
        delete[] dyn;

        cout << "\n=== Private inheritance ===" << endl;
        ComplexPriv p1;
        ComplexPriv p2(1, 2);
        ComplexPriv p3(3, -4);
        ComplexPriv p4(p2);
        ComplexPriv parr[2] = { ComplexPriv(7), ComplexPriv(8, 9) };

        cout << "Enter p1:" << endl;
        cin >> p1;
        cout << "p1 = " << p1 << endl;
        cout << "p2 - p3 = " << (p2 - p3) << endl;
        cout << "p2 / p3 = " << (p2 / p3) << endl;
        cout << "~p3 = " << ~p3 << endl;
        p4 = p3;
        cout << "p4 = " << p4 << endl;
        cout << "++p4 = " << ++p4 << ", p4++ = " << p4++ << ", now " << p4 << endl;
        cout << "--p4 = " << --p4 << ", p4-- = " << p4-- << ", now " << p4 << endl;
        string s2 = p2;
        cout << "string: " << s2 << endl;
        p2.Display();
        cout << "parr[1] = " << parr[1] << endl;

        cout << "\n=== Division by zero ===" << endl;
        cout << a2 / ComplexPub(0, 0) << endl;
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}