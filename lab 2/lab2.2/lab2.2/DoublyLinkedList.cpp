#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList()
    : head(nullptr), tail(nullptr), current(nullptr), count(0)
{
}

DoublyLinkedList::DoublyLinkedList(
    const DoublyLinkedList& other)
    : head(nullptr), tail(nullptr), current(nullptr), count(0)
{
    copyFrom(other);
}

DoublyLinkedList::~DoublyLinkedList()
{
    clear();
}

void DoublyLinkedList::clear()
{
    Node* node = head;

    while (node != nullptr)
    {
        Node* nextNode = node->next;
        delete node;
        node = nextNode;
    }

    head = nullptr;
    tail = nullptr;
    current = nullptr;
    count = 0;
}

void DoublyLinkedList::copyFrom(const DoublyLinkedList& other)
{
    for (Node* node = other.head;
        node != nullptr;
        node = node->next)
    {
        Node* newNode = new Node(node->data);

        if (tail == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }

        ++count;
    }
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(
    int index) const
{
    if (index < 0 || index >= count)
        throw std::out_of_range("Invalid list index");

    if (index < count / 2)
    {
        Node* node = head;

        for (int i = 0; i < index; ++i)
            node = node->next;

        return node;
    }
    else
    {
        Node* node = tail;

        for (int i = count - 1; i > index; --i)
            node = node->prev;

        return node;
    }
}

int DoublyLinkedList::GetSize() const
{
    return count;
}

bool DoublyLinkedList::IsEmpty() const
{
    return count == 0;
}

int DoublyLinkedList::GetElement(int index) const
{
    return getNode(index)->data;
}

void DoublyLinkedList::SetElement(int index, int value)
{
    getNode(index)->data = value;
}

DoublyLinkedList& DoublyLinkedList::operator=(
    const DoublyLinkedList& other)
{
    if (this != &other)
    {
        DoublyLinkedList temp(other);

        clear();

        head = temp.head;
        tail = temp.tail;
        count = temp.count;
        current = nullptr;

        temp.head = nullptr;
        temp.tail = nullptr;
        temp.count = 0;
    }

    return *this;
}

DoublyLinkedList operator+(
    const DoublyLinkedList& list, int value)
{
    DoublyLinkedList result(list);

    DoublyLinkedList::Node* node =
        new DoublyLinkedList::Node(value);

    if (result.tail == nullptr)
    {
        result.head = result.tail = node;
    }
    else
    {
        node->prev = result.tail;
        result.tail->next = node;
        result.tail = node;
    }

    ++result.count;
    return result;
}

DoublyLinkedList& DoublyLinkedList::operator+=(int value)
{
    Node* node = new Node(value);

    if (head == nullptr)
    {
        head = tail = node;
    }
    else
    {
        node->next = head;
        head->prev = node;
        head = node;
    }

    ++count;
    return *this;
}

DoublyLinkedList& DoublyLinkedList::operator-(int value)
{
    Node* node = head;

    while (node != nullptr && node->data != value)
        node = node->next;

    if (node == nullptr)
        return *this;

    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
        head = node->next;

    if (node->next != nullptr)
        node->next->prev = node->prev;
    else
        tail = node->prev;

    if (current == node)
        current = node->next != nullptr ? node->next : node->prev;

    delete node;
    --count;

    return *this;
}

bool operator==(const DoublyLinkedList& a,
    const DoublyLinkedList& b)
{
    if (a.count != b.count)
        return false;

    auto* p = a.head;
    auto* q = b.head;

    while (p != nullptr)
    {
        if (p->data != q->data)
            return false;

        p = p->next;
        q = q->next;
    }

    return true;
}

bool operator!=(const DoublyLinkedList& a,
    const DoublyLinkedList& b)
{
    return !(a == b);
}

bool operator<(const DoublyLinkedList& a,
    const DoublyLinkedList& b)
{
    auto* p = a.head;
    auto* q = b.head;

    while (p != nullptr && q != nullptr)
    {
        if (p->data != q->data)
            return p->data < q->data;

        p = p->next;
        q = q->next;
    }

    return p == nullptr && q != nullptr;
}

bool operator>(const DoublyLinkedList& a,
    const DoublyLinkedList& b)
{
    return b < a;
}

bool operator<=(const DoublyLinkedList& a,
    const DoublyLinkedList& b)
{
    return !(a > b);
}

bool operator>=(const DoublyLinkedList& a,
    const DoublyLinkedList& b)
{
    return !(a < b);
}

int& DoublyLinkedList::operator[](int index)
{
    return getNode(index)->data;
}

const int& DoublyLinkedList::operator[](int index) const
{
    return getNode(index)->data;
}

DoublyLinkedList& DoublyLinkedList::operator++()
{
    if (current == nullptr)
        current = head;
    else if (current->next != nullptr)
        current = current->next;

    return *this;
}

DoublyLinkedList& DoublyLinkedList::operator--()
{
    if (current == nullptr)
        current = tail;
    else if (current->prev != nullptr)
        current = current->prev;

    return *this;
}

std::string DoublyLinkedList::operator()(
    int first, int last) const
{
    if (first < 0 || last < first || last >= count)
        throw std::out_of_range("Invalid range");

    std::ostringstream out;

    Node* node = getNode(first);

    for (int i = first; i <= last; ++i)
    {
        if (i > first)
            out << " ";

        out << node->data;
        node = node->next;
    }

    return out.str();
}

DoublyLinkedList::operator std::string() const
{
    std::ostringstream out;
    Node* node = head;

    while (node != nullptr)
    {
        if (node != head)
            out << " ";

        out << node->data;
        node = node->next;
    }

    return out.str();
}

std::ostream& operator<<(
    std::ostream& out, const DoublyLinkedList& list)
{
    auto* node = list.head;

    out << "[";

    while (node != nullptr)
    {
        out << node->data;

        if (node->next != nullptr)
            out << ", ";

        node = node->next;
    }

    out << "]";
    return out;
}

std::istream& operator>>(
    std::istream& in, DoublyLinkedList& list)
{
    int n;

    if (!(in >> n))
        return in;

    if (n < 0)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    DoublyLinkedList temp;

    for (int i = 0; i < n; ++i)
    {
        int value;

        if (!(in >> value))
            return in;

        temp = temp + value;
    }

    list = temp;
    return in;
}