#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;

class SymString {
protected:
    string id;
    string value;

public:
    SymString(const string& objectId, const string& objectValue);

    virtual ~SymString() = default;

    string getId() const;
    string getValue() const;

    virtual string getType() const;

    virtual void Show() const;

    friend SymString operator-(const SymString& s1,
        const SymString& s2);
};

class OctString : public SymString {
private:
    unsigned long long toDecimal() const;

public:
    OctString(const string& objectId, const string& octValue);

    string getType() const override;

    void ShowHex() const;

    friend OctString operator-(const OctString& s1,
        const OctString& s2);
};

SymString operator-(const SymString& s1,
    const SymString& s2);

OctString operator-(const OctString& s1,
    const OctString& s2);

class Factory {
private:
    vector<unique_ptr<SymString>> objects;

public:
    void createSymString(const string& id, const string& value);

    void createOctString(const string& id, const string& value);

    void deleteObject(int index);

    void showAll() const;

    void showHex(int index) const;

    void subtractObjects(int index1, int index2);

    int getCount() const;
};
