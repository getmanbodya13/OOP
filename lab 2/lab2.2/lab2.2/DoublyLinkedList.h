#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

class DoublyLinkedList
{
private:
    struct Node
    {
        int data;
        Node* prev;
        Node* next;

        Node(int value)
            : data(value), prev(nullptr), next(nullptr) {
        }
    };

    Node* head;
    Node* tail;
    Node* current;
    int count;

    void clear();
    void copyFrom(const DoublyLinkedList& other);
    Node* getNode(int index) const;

public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& other);
    ~DoublyLinkedList();

    int GetSize() const;
    bool IsEmpty() const;
    int GetElement(int index) const;
    void SetElement(int index, int value);

    DoublyLinkedList& operator=(const DoublyLinkedList& other);
    
    friend DoublyLinkedList operator+(
        const DoublyLinkedList& list, int value);

    DoublyLinkedList& operator+=(int value);

    DoublyLinkedList& operator-(int value);

    friend bool operator==(const DoublyLinkedList& a,
        const DoublyLinkedList& b);
    friend bool operator!=(const DoublyLinkedList& a,
        const DoublyLinkedList& b);
    friend bool operator>(const DoublyLinkedList& a,
        const DoublyLinkedList& b);
    friend bool operator<(const DoublyLinkedList& a,
        const DoublyLinkedList& b);
    friend bool operator>=(const DoublyLinkedList& a,
        const DoublyLinkedList& b);
    friend bool operator<=(const DoublyLinkedList& a,
        const DoublyLinkedList& b);

    int& operator[](int index);
    const int& operator[](int index) const;

    DoublyLinkedList& operator++();
    DoublyLinkedList& operator--();

    std::string operator()(int first, int last) const;
    
    explicit operator std::string() const;

    friend std::ostream& operator<<(
        std::ostream& out, const DoublyLinkedList& list);
    friend std::istream& operator>>(
        std::istream& in, DoublyLinkedList& list);
};