////////////////////////////////////////////////////////////////////////////////
// Module Name:     stack_machine.h/cpp
// Authors:         Sergey Shershakov
// Version:         0.2.0
// Date:            23.01.2017
// Implemented by:  Surovtsev Maxim, BSE151(1)
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"
#include <vector>
#include <string>

namespace xi {

//==============================================================================
// Free functions -- helpers
//==============================================================================

/**
 * Splits string into substrings with given delimiter 
 */
std::vector<std::string> split(std::string line, char delimiter)
{
    std::vector <std::string> words;
    // ensures the last word will be
    // pushed back to vector
    line += delimiter;
    std::string temp = "";
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] != delimiter)
            temp += line[i];
        else if (temp != "")
        {
            words.push_back(temp);
            temp = "";
        }
    }
    return words;
}

/**
* Converts string into int
*/
bool strToInt(std::string expr, int& num)
{
    try
    {
        num = std::stoi(expr);
        return true;
    }
    catch (std::invalid_argument&)
    {
        return false;
    }
}

//==============================================================================
// class PlusOp
//==============================================================================

int PlusOp::operation(char op, int a, int b, int c)
{
    if(op != '+')
        throw std::logic_error("Operations other than Plus (+) are not supported.");

    // here we just ignore unused operands
    return a + b;
}

IOperation::Arity PlusOp::getArity() const
{
    return arDue;
}

//==============================================================================
// class InvOp
//==============================================================================

int InvOp::operation(char op, int a, int b, int c)
{
    if (op != '~')
        throw std::logic_error("Operations other than Inverse (~) are not supported.");

    return ~a;
}

IOperation::Arity InvOp::getArity() const
{
    return arUno;
}

//==============================================================================
// class MinusOp
//==============================================================================

int MinusOp::operation(char op, int a, int b, int c)
{
    if (op != '-')
        throw std::logic_error("Operations other than Minus (-) are not supported.");

    return a - b;
}

IOperation::Arity MinusOp::getArity() const
{
    return arDue;
}

//==============================================================================
// class MultOp
//==============================================================================

int MultOp::operation(char op, int a, int b, int c)
{
    if (op != '*')
        throw std::logic_error("Operations other than Multiplication (*) are not supported.");

    return a * b;
}

IOperation::Arity MultOp::getArity() const
{
    return arDue;
}

//==============================================================================
// class StackMachine
//==============================================================================

void StackMachine::registerOperation(char symb, IOperation* oper)
{
    SymbolToOperMapConstIter it = _opers.find(symb);
    // If operation is already registered
     if (it != _opers.end())
        throw std::logic_error("An operation is already registered.");
    
     _opers[symb] = oper;
}

IOperation* StackMachine::getOperation(char symb)
{
    SymbolToOperMapConstIter it = _opers.find(symb);
    if (it != _opers.end())
        return it->second;
    else
        return nullptr;
}

int StackMachine::calculate(const std::string& expr, bool clearStack)
{
    if (clearStack) // clear stack if necessary
        _s.clear();

    std::vector<std::string> words = split(expr, ' ');
    for (std::string tmpStr : words)
    {
        int tmpNum;
        if (strToInt(tmpStr, tmpNum)) // if number successfully parsed
        {
            _s.push(tmpNum);
        }
        else // if operation occured
        {
            char op = *tmpStr.c_str();
            IOperation *oper = getOperation(op);

            // word must contain only one symbol
            // and should be registered operation,
            // otherwise it is not an operation
            if (tmpStr.length() != 1)
                throw std::logic_error("Operation must contain only one symbol.");
            if (oper == nullptr)
                throw std::logic_error("Unsupported operation (nullptr).");

            int res; // calculation result
            // if stack does not contain enought numbers
            // to perform an operation, it will throw 
            // an exception
            switch (oper->getArity())
            {
                case IOperation::arUno:
                {
                    res = oper->operation(op, _s.pop());
                    break; 
                }
                case IOperation::arDue:
                {
                    int second = _s.pop();
                    int first = _s.pop();
                    res = oper->operation(op, first, second);
                    break; 
                }
                case IOperation::arTre:
                {
                    int third = _s.pop();
                    int second = _s.pop();
                    int first = _s.pop();
                    res = oper->operation(op, first, second, third);
                    break;
                }
                default:
                    break;
            }
            // push result to the stack
            _s.push(res);
        }
    }
    return _s.top(); // final result is always on the top of the stack
}
} // namespace xi
