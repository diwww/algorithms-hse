////////////////////////////////////////////////////////////////////////////////
// Module Name:     int_stack.h/cpp
// Authors:         Sergey Shershakov
// Version:         0.2.0
// Date:            23.01.2017
// Implemented by:  Surovtsev Maxim, BSE151(1)
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include <stdexcept>
#include "int_stack.h"

// TODO: add necessary headers here
// #include <...

namespace xi {

IntStack::IntStack(size_t sz)
{
    _ssize = sz;
    _stack = new int[_ssize];
    _head = 0;
}

IntStack::~IntStack()
{
    if (_stack != nullptr)
    {
        delete[] _stack;
        _stack = nullptr;
    }
}

void IntStack::push(int el)
{
    if (isFull())
        throw std::logic_error("Stack is full.");
    
    _stack[_head] = el;
    _head++;
}

int IntStack::pop()
{
    int temp = top();
    _head--;
    return temp;
}

int IntStack::top()
{
    if (isEmpty())
        throw std::logic_error("Stack is empty.");

    return _stack[_head - 1];
}

void IntStack::clear()
{
    _head = 0;
}

bool IntStack::isEmpty() const
{
    return _head == 0;
}

bool IntStack::isFull() const
{
    return _head == _ssize;
}

} // namespace xi