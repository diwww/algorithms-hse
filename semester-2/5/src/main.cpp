#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "NiceStack.h"
#include "NiceQueue.h"

using namespace std;

void testStack(int sample, int result)
{
    static int cntTest = 0;
    cntTest++;
    cout << "Stack: Test #" << cntTest;
    if (sample == result)
        cout << " -- passed";
    else cout << " -- failed";
    cout << endl;
}

void testQueue(int sample, int result)
{
    static int cntTest = 0;
    cntTest++;
    cout << "Queue: Test #" << cntTest;
    if (sample == result)
        cout << " -- passed";
    else cout << " -- failed";
    cout << endl;
}

int main(int argc, char *argv[])
{
//    int n = 10;
//    NiceQueue<int> queue(n);
//    int a;
//    while (cin >> a)
//        queue.enq(a);
//
//    cout << queue.getMinimum() << endl;

    try{
        NiceStack<int> nicestack(20);

        // Test #1
        try{
            nicestack.pop();
            testStack(-1, 1);
        }
        catch (out_of_range &ex)
        {
            testStack(1, 1);
        }
        catch (...)
        {
            testStack(-1, 1);
        }

        // Test #2
        try{
            nicestack.getMinimum();
            testStack(-1, 1);
        }
        catch (out_of_range &ex)
        {
            testStack(1, 1);
        }
        catch (...)
        {
            testStack(-1, 1);
        }

        nicestack.push(7);
        // Test #3
        testStack(7, nicestack.getMinimum());

        nicestack.push(15);
        nicestack.push(13);

        // Test #4
        testStack(7, nicestack.getMinimum());

        nicestack.push(5);

        // Test #5
        testStack(5, nicestack.getMinimum());

        nicestack.push(6);
        // Test #6
        testStack(5, nicestack.getMinimum());

        nicestack.push(3);
        // Test #7
        testStack(3, nicestack.getMinimum());

        nicestack.push(2);
        // Test #8
        testStack(2, nicestack.getMinimum());

        nicestack.push(15);
        // Test #9
        testStack(2, nicestack.getMinimum());

        nicestack.pop();
        // Test #10
        testStack(2, nicestack.getMinimum());

        nicestack.pop();
        // Test #11
        testStack(3, nicestack.getMinimum());
    }
    catch(exception &e){
        cout << e.what();
    }
    catch (...){
        cout << "Something wrong happend." << endl;
    }
    cout << endl;

    try{
        NiceQueue<int> nicequeue(20);

        // Test #1
        try{
            nicequeue.deq();
            testQueue(-1, 1);
        }
        catch (out_of_range &ex)
        {
            testQueue(1, 1);
        }
        catch (...)
        {
            testQueue(-1, 1);
        }

        // Test #2
        try{
            nicequeue.getMinimum();
            testQueue(-1, 1);
        }
        catch (out_of_range &ex)
        {
            testQueue(1, 1);
        }
        catch (...)
        {
            testQueue(-1, 1);
        }

        nicequeue.enq(4);
        // Test #3
        testQueue(4, nicequeue.getMinimum());

        nicequeue.enq(5);
        // Test #4
        testQueue(4, nicequeue.getMinimum());

        nicequeue.enq(13);
        nicequeue.enq(7);

        // Test #5
        testQueue(4, nicequeue.getMinimum());

        nicequeue.enq(6);
        // Test #6
        testQueue(4, nicequeue.getMinimum());

        nicequeue.deq();
        // Test #7
        testQueue(5, nicequeue.getMinimum());

        nicequeue.enq(3);
        // Test #8
        testQueue(3, nicequeue.getMinimum());

        nicequeue.enq(2);
        // Test #9
        testQueue(2, nicequeue.getMinimum());

        nicequeue.enq(15);
        // Test #10
        testQueue(2, nicequeue.getMinimum());

        nicequeue.deq();
        nicequeue.deq();
        nicequeue.deq();
        nicequeue.deq();
        nicequeue.deq();
        nicequeue.deq();
        // Test #11
        testQueue(15, nicequeue.getMinimum());
        cout << endl;
    }
    catch (exception &e){
        cout << e.what();
    }
    catch (...){
        cout << "Something wrong happend." << endl;
    }


    return EXIT_SUCCESS;
}