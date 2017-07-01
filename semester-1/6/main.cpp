#include <iostream>
#include "eight_queen.h"

using namespace std;

int main()
{
    QueenProblem *ob = new QueenProblem();
    ob->initialize(8);
    ob->backtracking(0);
    cout << ob->getNumberOfSolutions() << endl;

    delete ob;
    return 0;
}