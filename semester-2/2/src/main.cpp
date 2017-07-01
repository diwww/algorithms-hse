////////////////////////////////////////////////////////////////////////////////
// Module Name:  main.cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <assert.h>
#include <stdexcept>
#include <string>

#include "int_stack.h"
#include "stack_machine.h"


using namespace std;

void testStack()
{
    xi::IntStack s;

    s.push(42);
    //int a = s.pop();
    assert(s.top() == 42);            // EXPECT_EQ()
    assert(s.pop() == 42);            // EXPECT_EQ()

    // an exception should be thrown
    bool exc = false;
    try {
        s.pop();
    }
    catch (std::logic_error& /*e*/)
    {
        std::cout << "An expected exception on pop() operation is succesfully catched\n";
        exc = true;
    }
    assert(exc);

    // test for overflow
    for (int i = 0; i < xi::IntStack::STACK_SIZE; ++i)
        s.push(i);

    // next element cannot be added and, thus, en exception should be thrown
    exc = false;
    try {
        s.push(43);
    }
    catch (std::logic_error& /*e*/)
    {
        std::cout << "An expected exception on push() operation is succesfully catched\n";
        exc = true;
    }
    assert(exc);

    //int b = 0;
}

void testStackMachine()
{
    xi::StackMachine sm;
    xi::PlusOp plusop;
    sm.registerOperation('+', &plusop);

    //int res = sm.calculate("15 10 +");
    int res = sm.calculate("7 8 10 + +");
    int r1 = sm.getStack().top();
    assert(res == 25);
    assert(r1 == 25);

}

// Output:
// 321
// 5
// 0
// 1
void myTest()
{
    xi::IntStack st;
    st.push(1);
    st.push(2);
    st.push(3);
    for (int i = 0; i < 3; ++i)
    {
        cout << st.pop();
    }
    cout << endl;
    st.push(4);
    st.push(5);
    st.push(6);
    st.pop();
    cout << st.top() << endl;
    cout << st.isEmpty() << endl;
    st.clear();
    cout << st.isEmpty() << endl;
}

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



int main()
{
    xi::StackMachine sm;
    xi::PlusOp plusop;
    xi::InvOp invop;
    xi::MultOp multop;
    xi::MinusOp minusop;
    sm.registerOperation('+', &plusop);
    sm.registerOperation('~', &invop);
    sm.registerOperation('*', &multop);
    sm.registerOperation('-', &minusop);
    
    string expr;
    cout << "Enter expression: ";
    getline(cin, expr);

    try{
        cout << sm.calculate(expr) << endl;
    }
    catch (logic_error& e)
    {
        cerr << e.what() << endl;
    }

    // myTest();
    // testStack();
    // testStackMachine();
    system("PAUSE");
    return 0;
}