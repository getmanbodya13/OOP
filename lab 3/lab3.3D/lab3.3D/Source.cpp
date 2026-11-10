#include "RealPub.h"
#include "RealPriv.h"
#include "PackedSize.h"
using namespace std;

int main()
{
    try
    {
        cout << "=== Object counter ===" << endl;
        cout << "Objects at start: " << Object::Count() << endl;
        {
            Number t1, t2(1.5f);
            RealPub t3(2);
            RealPriv t4(3);
            cout << "Objects inside block: " << Object::Count() << endl;
        }
        cout << "Objects after block: " << Object::Count() << endl;

        cout << "\n=== Class sizes ===" << endl;
        cout << "Without pack(1): Object = " << sizeof(Object)
            << ", Number = " << sizeof(Number)
            << ", RealPub = " << sizeof(RealPub)
            << ", RealPriv = " << sizeof(RealPriv) << endl;
        cout << "With pack(1):    Object = " << SizeObjectPacked()
            << ", Number = " << SizeNumberPacked()
            << ", RealPub = " << SizeRealPubPacked()
            << ", RealPriv = " << SizeRealPrivPacked() << endl;

        cout << "\n=== Base class Number ===" << endl;
        Number n0;                    
        Number n1(7.5f);          
        Number n2(n1);                   
        Number n3;
        n3.Init(2);
        Number arr[3] = { Number(1), Number(2.5f), Number() };
        Number* dyn = new Number[2]{ Number(5), Number(0.5f) };

        cout << "Enter n0:" << endl;
        cin >> n0;
        n0.Display();
        cout << "n1 = " << n1 << ", n2 = " << n2 << ", n3 = " << n3 << endl;
        cout << "n1.add(n3) = " << n1.add(n3) << endl;
        cout << "n1 + n3    = " << (n1 + n3) << endl;
        cout << "n1.div(n3) = " << n1.div(n3) << endl;
        cout << "n1 / n3    = " << (n1 / n3) << endl;
        n2 = n3;
        cout << "n2 = n3 -> " << n2 << endl;
        cout << "++n2 = " << ++n2 << endl;
        cout << "n2++ = " << n2++ << endl;
        cout << "now    " << n2 << endl;
        cout << "--n2 = " << --n2 << endl;
        cout << "n2-- = " << n2-- << endl;
        cout << "now    " << n2 << endl;
        string s = n1;
        cout << "string: " << s << endl;
        n1.setValue(10);
        cout << "getValue = " << n1.getValue() << endl;
        for (int i = 0; i < 3; i++) cout << "arr[" << i << "] -> " << arr[i] << endl;
        cout << "dyn[0] -> " << dyn[0] << ", dyn[1] -> " << dyn[1] << endl;
        delete[] dyn;

        cout << "\n=== Public inheritance: RealPub ===" << endl;
        RealPub a1;
        RealPub a2(2);
        RealPub a3(8);
        RealPub a4(a3);
        RealPub a5(n1);          
        RealPub rarr[2] = { RealPub(4), RealPub(100) };
        RealPub* rdyn = new RealPub[2]{ RealPub(9), RealPub(1) };

        cout << "Enter a1:" << endl;
        cin >> a1;                      
        cout << "a1 = " << a1 << endl;
        cout << "a2 = " << a2 << ", a3 = " << a3 << ", a5 = " << a5 << endl;
        cout << "a3.pow(2)    = " << a3.pow(2) << endl;
        cout << "a3.pow(-1)   = " << a3.pow(-1) << endl;
        cout << "a3.pow(0.5)  = " << a3.pow(0.5f) << endl;
        cout << "a3.log()     = " << a3.log() << endl;
        cout << "a3.log(2)    = " << a3.log(2) << endl;
        cout << "a3 + a2      = " << (a3 + a2) << endl;
        cout << "a3 / a2      = " << (a3 / a2) << endl;
        a4 = a2;
        cout << "a4 = a2 -> " << a4 << endl;
        cout << "++a4 = " << ++a4 << endl;
        cout << "a4++ = " << a4++ << endl;
        cout << "now    " << a4 << endl;
        cout << "--a4 = " << --a4 << endl;
        cout << "a4-- = " << a4-- << endl;
        cout << "now    " << a4 << endl;
        string s2 = a2;
        cout << "string: " << s2 << endl;
        a2.Display();
        Number& ref = a3;             
        cout << "as Number: " << ref << endl;
        for (int i = 0; i < 2; i++) cout << "rarr[" << i << "] -> " << rarr[i] << endl;
        cout << "rdyn[0] -> " << rdyn[0] << ", rdyn[1] -> " << rdyn[1] << endl;
        delete[] rdyn;

        cout << "\n=== Private inheritance: RealPriv ===" << endl;
        RealPriv p1;
        RealPriv p2(2);
        RealPriv p3(8);
        RealPriv p4(p3);
        RealPriv p5(n1);
        RealPriv parr[2] = { RealPriv(4), RealPriv(100) };

        cout << "Enter p1:" << endl;
        cin >> p1;                      
        cout << "p1 = " << p1 << endl;
        cout << "p3.pow(2)    = " << p3.pow(2) << endl;
        cout << "p3.log()     = " << p3.log() << endl;
        cout << "p3.log(2)    = " << p3.log(2) << endl;
        cout << "p3.add(p2)   = " << p3.add(p2) << endl;
        cout << "p3 + p2      = " << (p3 + p2) << endl;
        cout << "p3.div(p2)   = " << p3.div(p2) << endl;
        cout << "p3 / p2      = " << (p3 / p2) << endl;
        p4 = p2;
        cout << "p4 = p2 -> " << p4 << endl;
        cout << "++p4 = " << ++p4 << endl;
        cout << "p4++ = " << p4++ << endl;
        cout << "now    " << p4 << endl;
        cout << "--p4 = " << --p4 << endl;
        cout << "p4-- = " << p4-- << endl;
        cout << "now    " << p4 << endl;
        string s3 = p2;
        cout << "string: " << s3 << endl;
        p2.Display();
        cout << "getValue = " << p5.getValue() << endl;
        cout << "parr[1] -> " << parr[1] << endl;

        cout << "\n=== Error handling ===" << endl;
        try { cout << n1.div(Number(0)) << endl; }
        catch (const exception& e) { cout << "Error: " << e.what() << endl; }
        try { cout << RealPub(-8).log() << endl; }
        catch (const exception& e) { cout << "Error: " << e.what() << endl; }
        try { cout << RealPub(-8).pow(0.5f) << endl; }
        catch (const exception& e) { cout << "Error: " << e.what() << endl; }
        try { cout << RealPriv(8).log(1) << endl; }
        catch (const exception& e) { cout << "Error: " << e.what() << endl; }
        try { cout << RealPriv(10).pow(1000) << endl; }
        catch (const exception& e) { cout << "Error: " << e.what() << endl; }

        cout << "\nObjects alive at the end: " << Object::Count() << endl;
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}