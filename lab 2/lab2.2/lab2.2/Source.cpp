#include <iostream>
#include <string>
#include <stdexcept>
#include "DoublyLinkedList.h"

using namespace std;

int main()
{
    try
    {
        DoublyLinkedList list1;

        cout << "Enter the number of elements and "
            << "the elements of the list: ";
        cin >> list1;

        cout << "List 1: " << list1 << endl;

        list1 = list1 + 40;
        cout << "After + 40: " << list1 << endl;

        list1 += 5;
        cout << "After += 5: " << list1 << endl;
        
        DoublyLinkedList list2(list1);
        cout << "Copied list: " << list2 << endl;

        list2 - 40;
        cout << "After removing 40: " << list2 << endl;

        DoublyLinkedList list3;
        list3 = list1;
        cout << "Assigned list: " << list3 << endl;

        cout << boolalpha;
        cout << "list1 == list3: " << (list1 == list3) << endl;
        cout << "list1 != list2: " << (list1 != list2) << endl;
        cout << "list1 > list2: " << (list1 > list2) << endl;
        cout << "list1 < list2: " << (list1 < list2) << endl;
        cout << "list1 >= list2: " << (list1 >= list2) << endl;
        cout << "list1 <= list3: " << (list1 <= list3) << endl;

        if (!list1.IsEmpty())
        {
            cout << "Element at index 0: " << list1[0] << endl;

            list1[0] = 100;
            cout << "After changing element 0: "
                << list1 << endl;

            cout << "GetElement(0): "
                << list1.GetElement(0) << endl;

            list1.SetElement(0, 5);
            cout << "After SetElement: "
                << list1 << endl;
        }

        ++list1;
        --list1;
        cout << "After pointer operations: " << list1 << endl;

        if (list1.GetSize() >= 2)
        {
            cout << "Part of list: "
                << list1(0, 1) << endl;
        }

        string text = static_cast<string>(list1);
        cout << "String representation: " << text << endl;

        cout << "Size: " << list1.GetSize() << endl;
        cout << "Is empty: " << list1.IsEmpty() << endl;

        DoublyLinkedList arr[2];
        arr[0] = list1;
        arr[1] = list2;

        cout << "\nArray of lists:" << endl;

        for (int i = 0; i < 2; ++i)
            cout << "arr[" << i << "] = " << arr[i] << endl;

        cout << "\nClass size: "
            << sizeof(DoublyLinkedList) << " bytes" << endl;

        cout << "Program completed successfully." << endl;
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}