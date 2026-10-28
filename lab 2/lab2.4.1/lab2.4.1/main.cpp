#include <iostream>
#include <string>
#include <stdexcept>
#include "Vector.h"

using namespace std;

struct VectorLayout
{
    int* data;
    int n;
};

#pragma pack(push, 1)
struct PackedVectorLayout
{
    int* data;
    int n;
};
#pragma pack(pop)

int main()
{
    try
    {
        cout << "===== VECTOR CLASS DEMONSTRATION ====="
            << endl << endl;

        Vector v1;

        cout << "1. Default constructor" << endl;
        cout << "v1 = " << v1 << endl;
        cout << "Size: " << v1.getSize() << endl;

        Vector v2(4);

        cout << "\n2. Initialization constructor" << endl;
        cin >> v2;

        cout << "v2 = " << v2 << endl;

        Vector v3 = { 1, 5, 3, 8 };

        cout << "\n3. Initializer-list constructor" << endl;
        cout << "v3 = " << v3 << endl;

        Vector v4(v3);

        cout << "\n4. Copy constructor" << endl;
        cout << "v4 = " << v4 << endl;

        Vector v5;
        v5 = v3;

        cout << "\n5. Assignment operator" << endl;
        cout << "v5 = " << v5 << endl;

        cout << "\n6. Indexing operator" << endl;
        cout << "v3[0] = " << v3[0] << endl;

        v3[0] = 10;

        cout << "After changing v3[0]: " << v3 << endl;

        cout << "\n7. Access methods" << endl;
        cout << "Element at index 1: "
            << v3.getElement(1) << endl;

        v3.setElement(1, 20);

        cout << "After setElement: " << v3 << endl;

        cout << "\n8. Vector addition" << endl;

        Vector a = { 1, 2, 3 };
        Vector b = { 4, 5, 6 };

        Vector c = a + b;

        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "a + b = " << c << endl;

        cout << "\n9. Comparison operators" << endl;

        Vector d = { 1, 2, 3 };

        cout << "a == d: " << (a == d) << endl;
        cout << "a != b: " << (a != b) << endl;

        cout << "\n10. Vector norm" << endl;
        cout << "Vector: " << b << endl;
        cout << "Norm: " << b.norm() << endl;
        
        cout << "\n11. Prefix increment" << endl;
        cout << "++a = " << ++a << endl;

        cout << "\n12. Postfix increment" << endl;

        Vector oldA = a++;
        cout << "Old a = " << oldA << endl;
        cout << "New a = " << a << endl;

        cout << "\n13. Prefix decrement" << endl;
        cout << "--a = " << --a << endl;

        cout << "\n14. Postfix decrement" << endl;

        Vector oldB = b--;
        cout << "Old b = " << oldB << endl;
        cout << "New b = " << b << endl;

        cout << "\n15. Conversion to string" << endl;

        string text = static_cast<string>(v3);
        cout << "String representation: " << text << endl;

        cout << "\n16. Array of objects" << endl;

        Vector arr[3] = {
            Vector{ 1, 2 },
            Vector{ 3, 4 },
            Vector{ 5, 6 }
        };

        for (int i = 0; i < 3; i++)
            cout << "arr[" << i << "] = "
            << arr[i] << endl;

        cout << "\n17. Dynamic object creation" << endl;

        Vector* ptr = new Vector{ 7, 8, 9 };

        cout << "*ptr = " << *ptr << endl;

        delete ptr;

        cout << "\n18. Class size" << endl;

        cout << "Vector size: "
            << sizeof(Vector) << " bytes" << endl;

        cout << "Without #pragma pack(1): "
            << sizeof(VectorLayout) << " bytes" << endl;

        cout << "With #pragma pack(1): "
            << sizeof(PackedVectorLayout) << " bytes" << endl;
    }
    catch (const exception& e)
    {
        cerr << "\nError: " << e.what() << endl;
    }

    return 0;
}