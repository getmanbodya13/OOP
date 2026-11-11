#include "Classes.h"
#include <sstream>
#include <iomanip>
#include <typeinfo>

SymString::SymString(const string& objectId,
    const string& objectValue)
    : id(objectId), value(objectValue) {
}

string SymString::getId() const {
    return id;
}

string SymString::getValue() const {
    return value;
}

string SymString::getType() const {
    return "SymString";
}

void SymString::Show() const {
    cout << "Type: " << getType() << endl;
    cout << "ID: " << id << endl;
    cout << "Value: " << value << endl;
}

OctString::OctString(const string& objectId,
    const string& octValue)
    : SymString(objectId, octValue) {

    if (octValue.empty()) {
        throw invalid_argument(
            "Octal string cannot be empty!"
        );
    }

    for (char c : octValue) {
        if (c < '0' || c > '7') {
            throw invalid_argument(
                "Octal number must contain digits from 0 to 7!"
            );
        }
    }

    toDecimal();
}

unsigned long long OctString::toDecimal() const {
    size_t pos = 0;

    unsigned long long number = stoull(value, &pos, 8);

    if (pos != value.length()) {
        throw invalid_argument("Invalid octal number!");
    }

    return number;
}

string OctString::getType() const {
    return "OctString";
}

void OctString::ShowHex() const {
    unsigned long long number = toDecimal();

    cout << "Octal value: " << value << endl;

    cout << "Hexadecimal value: "
        << uppercase << hex << number << dec << endl;
}

SymString operator-(const SymString& s1, const SymString& s2)
{
    string result = s1.value;

    size_t pos = result.find(s2.value);

    if (pos != string::npos)
    {
        result.erase(pos, s2.value.length());
    }

    size_t first = result.find_first_not_of(" \t\n\r");

    if (first == string::npos)
    {
        result.clear();
    }
    else
    {
        size_t last = result.find_last_not_of(" \t\n\r");
        result = result.substr(first, last - first + 1);
    }

    return SymString(s1.id, result);
}
OctString operator-(const OctString& s1,
    const OctString& s2) {

    unsigned long long number1 = s1.toDecimal();
    unsigned long long number2 = s2.toDecimal();

    if (number2 > number1) {
        throw invalid_argument(
            "Result cannot be negative!"
        );
    }

    unsigned long long result = number1 - number2;

    stringstream ss;
    ss << oct << result;

    return OctString("result", ss.str());
}

void Factory::createSymString(const string& id,
    const string& value) {

    objects.push_back(
        make_unique<SymString>(id, value)
    );

    cout << "SymString object created successfully!\n";
}

void Factory::createOctString(const string& id,
    const string& value) {

    objects.push_back(
        make_unique<OctString>(id, value)
    );

    cout << "OctString object created successfully!\n";
}

void Factory::deleteObject(int index) {

    if (index < 0 || index >= (int)objects.size()) {
        cout << "Invalid object index!\n";
        return;
    }

    objects.erase(objects.begin() + index);

    cout << "Object deleted successfully!\n";
}

void Factory::showAll() const {

    if (objects.empty()) {
        cout << "No objects available.\n";
        return;
    }

    for (size_t i = 0; i < objects.size(); i++) {
        cout << "\nObject #" << i + 1 << endl;
        objects[i]->Show();
    }
}

void Factory::showHex(int index) const {

    if (index < 0 || index >= (int)objects.size()) {
        cout << "Invalid object index!\n";
        return;
    }

    OctString* oct =
        dynamic_cast<OctString*>(objects[index].get());

    if (oct == nullptr) {
        cout << "This operation is available only for OctString!\n";
        return;
    }

    oct->ShowHex();
}

void Factory::subtractObjects(int index1, int index2) {

    if (index1 < 0 || index1 >= (int)objects.size() ||
        index2 < 0 || index2 >= (int)objects.size()) {

        cout << "Invalid object index!\n";
        return;
    }

    SymString* s1 = objects[index1].get();
    SymString* s2 = objects[index2].get();

    try {

        if (typeid(*s1) == typeid(SymString) &&
            typeid(*s2) == typeid(SymString)) {

            SymString result = *s1 - *s2;

            cout << "\nSubtraction result:\n";
            result.Show();
        }

        else if (dynamic_cast<OctString*>(s1) &&
            dynamic_cast<OctString*>(s2)) {

            OctString* o1 = dynamic_cast<OctString*>(s1);
            OctString* o2 = dynamic_cast<OctString*>(s2);

            OctString result = *o1 - *o2;

            cout << "\nSubtraction result:\n";
            result.Show();
            result.ShowHex();
        }

        else {
            cout << "Objects must have the same type!\n";
        }

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

int Factory::getCount() const {
    return (int)objects.size();
}
