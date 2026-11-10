#pragma once

class Object
{
    static unsigned int count;
public:
    static unsigned int Count() { return count; }
    Object() { count++; }
    Object(const Object&) { count++; }   
    ~Object() { count--; }
};