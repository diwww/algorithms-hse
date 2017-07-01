////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Stack Machine class definition
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      23.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Implementations for the methods declared in the classes below must be put
/// in corresponding module named stack_machine.cpp.
///
/// Initially created by Sergey on 24.01.2016.
///
////////////////////////////////////////////////////////////////////////////////


#ifndef STACKMACHINE_STACK_MACHINE_H
#define STACKMACHINE_STACK_MACHINE_H

#include <map>

#include "int_stack.h"

namespace xi {

/** Declares an interface for operator (operation)
 *
 */
class IOperation
{
public:
    /** Enumerates all possible arity of operations
     *
     *  All possible options defined by enum keyword is visible outside the type declaration.
     *  That's why a fairly common practice is to add some prefix to to reduce the probability of name collisions.
     */
    enum Arity {
        arUno,          ///< Unary
        arDue,          ///< Binary
        arTre           ///< Ternary
    }; // enum Arity
public:
    /** Method for overriding: a desirable operation \param op with possible 3 args at most
     *
     *  Pure virtual methods is used to declare methods without their defining.
     */
    virtual int operation(char op, int a, int b = 0, int c = 0) = 0;

    /** Returns an arity of a given (as an IOperation-derived) object
     *
     *  Method is not intended to change an object's state.
     */
    virtual Arity getArity() const = 0;
protected:
    /** Destructor must not be public due to It is not intended to delete an object through this interface!!
     *
     *  See Herb Sutter: Guideline #4: A base class destructor should be either public and virtual,
     *  or protected and nonvirtual.
     *  http://www.gotw.ca/publications/mill18.htm
     */
    ~IOperation() {};
}; // class IOperation


/** An example of operation object that implements PLUS binary operation
 *
 *  Note, that IOperation interface should be inherited with public modifier
 */
class PlusOp : public IOperation {
//public:
//    virtual ~PlusOp() {}
public:
    // IOperation interface overriding
    // We explicitly use virtual keyword to point out the virtual nature of the methods

    /** If a given operator symb is not '+", an exception is thrown*/
    virtual int operation(char op, int a, int b, int c) override;
    virtual Arity getArity() const override;
}; // class PlusOp

class InvOp : public IOperation {
public:
    virtual int operation(char op, int a, int b, int c) override;
    virtual Arity getArity() const override;
}; // class InvOp

class MinusOp : public IOperation {
public:
    virtual int operation(char op, int a, int b, int c) override;
    virtual Arity getArity() const override;
}; // class MinusOp

class MultOp : public IOperation {
public:
    virtual int operation(char op, int a, int b, int c) override;
    virtual Arity getArity() const override;
}; // class MultOp


class StackMachine
{
public:
    // types
    typedef std::map<char, IOperation*> SymbolToOperMap;
    typedef SymbolToOperMap::const_iterator SymbolToOperMapConstIter;

public:
    /** Register an operation object for a given symbol.
     *
     *  If the symbol is already registered, throws an exception.
     *
     *  !The method implementation should be shred with students!
     */
    void registerOperation(char symb, IOperation* oper);

    /** For a given symb returns an operation object.
     *
     *  If the given symbol is not mapped to any operation, a nullptr is returned.
     */
    IOperation* getOperation(char symb);
public:

    /** Calculates given expression using the shared stack and returns the value on its top.
     *
     *  \param clearStack determines if a stack should be clear before parsing the expression.
     *  If one prefer not to clear stack before parsing, the results of previous calculations
     *  can be used further.
     *
     *  \param expr contains a string-based expression contains interger operands and one-symbol operators
     *  If an unrecognized symbol (or substring) is found, throws an exception.
     *  If given expression is not valid (e.g., in the case of lack of operands or similar),
     *  an exception is thrown.
     */
    int calculate(const std::string& expr, bool clearStack = true);
public:

    // sets/gets
    IntStack& getStack() { return _s; }     ///< Returns stack as is
    const IntStack& getStack() const { return _s; }     ///< Overloaded version of getStack()
protected:
    /** Maps of operations */
    SymbolToOperMap _opers;

    /** Common stack
     *
     *  One can define an operation, that pushes, pops or tops stack and, thus, the stack
     *  can be used being shared among multiple machine invocations
     */
    IntStack _s;
}; // class StackMachine

} // namespace xi

#endif //STACKMACHINE_STACK_MACHINE_H
