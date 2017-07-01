////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Int Stack class definition
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      23.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Implementations for the methods declared in the classes below must be put
/// in corresponding module named int_stack.cpp.
///
/// Initially created by Sergey on 24.01.2016.
/// See http://www.stack.nl/~dimitri/doxygen/manual/docblocks.html for Doxygen documenting
///
////////////////////////////////////////////////////////////////////////////////




#ifndef STACKMACHINE_INT_STACK_H
#define STACKMACHINE_INT_STACK_H

#include <stddef.h>     // need fo size_t



namespace xi {


/** Declares a stack of integers.
 */
class IntStack {
public:
    // const
    static const int STACK_SIZE = 1024;     ///< Defines a maximum number of stack elements

public:
    // Constructors
    IntStack(size_t sz = STACK_SIZE);           ///< Default constructor
    ~IntStack();

public:
    //----<Main ADT interface>----

    /** Pushes a given element onto the stack.
     *
     *  If no more elements can be placed onto the stack due to its overflow an std::logic_error is thrown.
     */
    void push(int el);

    /** Pops an element from the stack and returns its value.
     *
     *  If no elements stored in the stack, a std::logic_error is thrown.
     */
    int pop();

    /** Looks up an element from the top of the stack and returns its value.
     *
     *  If no elements stored in the stack, a std::logic_error is thrown.
     */
    int top();

    /** Clears the stack and makes it empty.
     *
     *  Often named as makeEmpty or similar
     */
    void clear();

public:
    // Non classic ADT helper methods

    /** Returns true if the stack is empty, false otherwise */
    bool isEmpty() const;

    /** Returns true if the stack is full, false otherwise */
    bool isFull() const;


protected:
    //int     _stack[STACK_SIZE];             ///< Stack elements as an fixed size array
    int*    _stack;                         ///< Stack as a dynamic array
    size_t  _ssize;                         ///< Actual stack size
    size_t  _head;                          ///< Stack head
}; // class IntStack


} // namespace xi

#endif //STACKMACHINE_INT_STACK_H
