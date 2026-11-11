#include "Classes.h"

int main() {

    Factory factory;

    int choice;

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Create SymString object\n";
        cout << "2. Create OctString object\n";
        cout << "3. Delete object\n";
        cout << "4. Show all objects\n";
        cout << "5. Show hexadecimal value (ShowHex)\n";
        cout << "6. Subtract two objects (operator -)\n";
        cout << "0. Exit\n";
        cout << "==========================\n";

        cout << "Choose an operation: ";
        cin >> choice;
        cin.ignore(10000, '\n');

        try {
            switch (choice) {

            case 1: {
                string id, value;

                cout << "Enter object ID: ";
                getline(cin, id);

                cout << "Enter symbolic string: ";
                getline(cin, value);

                factory.createSymString(id, value);
                break;
            }

            case 2: {
                string id, value;

                cout << "Enter object ID: ";
                getline(cin, id);

                cout << "Enter octal number: ";
                getline(cin, value);

                factory.createOctString(id, value);
                break;
            }

            case 3: {
                int index;

                factory.showAll();

                cout << "Enter object number to delete: ";
                cin >> index;

                factory.deleteObject(index - 1);
                break;
            }

            case 4: {
                factory.showAll();
                break;
            }

            case 5: {
                int index;

                factory.showAll();

                cout << "Enter object number: ";
                cin >> index;

                factory.showHex(index - 1);
                break;
            }

            case 6: {
                int index1, index2;

                factory.showAll();

                cout << "Enter first object number: ";
                cin >> index1;

                cout << "Enter second object number: ";
                cin >> index2;

                factory.subtractObjects(index1 - 1, index2 - 1);
                break;
            }

            case 0:
                cout << "Program terminated.\n";
                break;

            default:
                cout << "Invalid menu option!\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}
