#include "SCCSolver.h"
#include <iostream>


void test_0()
{
    SCCSolver *solver = new SCCSolver;

    int n;
    std::vector<int> *adjlist;
    n = 4;
    adjlist = new std::vector<int>[n];
    adjlist[1].push_back(2);
    adjlist[1].push_back(0);
    adjlist[2].push_back(3);
    adjlist[3].push_back(1);

    solver->initialize(adjlist, n);
    solver->solve();
    std::cout << solver->getResult().size() << "\n";
    for (std::vector<int> v : solver->getResult())
    {
        for (int i : v)
            std::cout << i << " ";
        std::cout << std::endl;
    }
    delete[] adjlist;

    std::cout << std::endl;

    n = 10;
    adjlist = new std::vector<int>[n];
    adjlist[0].push_back(1);
    adjlist[0].push_back(2);
    adjlist[1].push_back(3);
    adjlist[2].push_back(5);
    adjlist[3].push_back(4);
    adjlist[3].push_back(6);
    adjlist[4].push_back(1);
    adjlist[4].push_back(2);
    adjlist[4].push_back(6);
    adjlist[5].push_back(4);
    adjlist[5].push_back(9);
    adjlist[6].push_back(7);
    adjlist[7].push_back(9);
    adjlist[8].push_back(7);
    adjlist[9].push_back(8);

    solver->initialize(adjlist, n);
    solver->solve();
    std::cout << solver->getResult().size() << "\n";
    for (std::vector<int> v : solver->getResult())
    {
        for (int i : v)
            std::cout << i << " ";
        std::cout << std::endl;
    }
    delete[] adjlist;

    delete solver;
}

int main()
{
    // Output:
    // 2
    // 1 3 2
    // 0
    //
    // 4
    // 0
    // 1 4 3 5 2
    // 6
    // 9 7 8
//    while (true)
    test_0();

    return 0;
}