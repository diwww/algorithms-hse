#include "bellman_ford.h"
#include <iostream>

using namespace std;

int test()
{
    BellmanFord *solver = new BellmanFord();
    int n, m;

    n = 14;
    m = 13;
    int **arr = new int *[n];

    arr[0] = new int[3]{8, 13, 1};
    arr[1] = new int[3]{1, 2, 4};
    arr[2] = new int[3]{5, 2, 3};
    arr[3] = new int[3]{1, 4, 4};
    arr[4] = new int[3]{4, 5, -2};
    arr[5] = new int[3]{3, 1, 3};
    arr[6] = new int[3]{3, 4, 2};
    arr[7] = new int[3]{4, 6, 4};
    arr[8] = new int[3]{6, 3, 1,};
    arr[9] = new int[3]{5, 6, -3};
    arr[10] = new int[3]{6, 7, -2};
    arr[11] = new int[3]{7, 8, 2};
    arr[12] = new int[3]{8, 6, -2};
    arr[13] = new int[3]{7, 5, 2};

    solver->initialize(arr, n, m, 1);
    solver->solve();

    cout << solver->getCost();
    cout << endl;
    vector<int> *path = solver->getPath();
//    for (int j = 0; j < m; ++j)
//    {
    for (auto i:path[0])
    {
        cout << i << " ";
    }
    cout << endl;
//    }
    for (int k = 0; k < n; ++k)
    {
        delete arr[k];
    }
    delete[] arr;
    delete[] path;

    n = 3;
    m = 3;
    arr = new int *[n];
    for (int j = 0; j < n; ++j)
    {
        arr[j] = new int[3];
    }

    arr[0][0] = 1;
    arr[0][1] = 2;
    arr[0][2] = 2;

    arr[1][0] = 2;
    arr[1][1] = 3;
    arr[1][2] = 1;

    arr[2][0] = 3;
    arr[2][1] = 1;
    arr[2][2] = -4;


    solver->initialize(arr, n, m, 1);
    solver->solve();
    cout << solver->getCost() << endl;
    path = solver->getPath();
    for (int j = 0; j < m; ++j)
    {
        for (auto i:path[j])
        {
            cout << i << " ";
        }
        cout << endl;
    }

    for (int k = 0; k < n; ++k)
    {
        delete arr[k];
    }
    delete[] arr;
    delete[] path;

    delete solver;
    return 0;
}


int main()
{
//    while (true)
    test();
    return 0;
}


// output: negative cycle (8 6 7)
// n = 14
// m = 13
//arr[0] = new int[3]{8, 13, 1};
//arr[1] = new int[3]{1, 2, 4};
//arr[2] = new int[3]{5, 2, 3};
//arr[3] = new int[3]{1, 4, 4};
//arr[4] = new int[3]{4, 5, -2};
//arr[5] = new int[3]{3, 1, 3};
//arr[6] = new int[3]{3, 4, 2};
//arr[7] = new int[3]{4, 6, 4};
//arr[8] = new int[3]{6, 3, 1,};
//arr[9] = new int[3]{5, 6, -3};
//arr[10] = new int[3]{6, 7, -2};
//arr[11] = new int[3]{7, 8, 2};
//arr[12] = new int[3]{8, 6, -2};
//arr[13] = new int[3]{7, 5, 2};

// output: negative cycle (2 3 1)
// n = 3
// m = 3
//arr[0][0] = 1;
//arr[0][1] = 2;
//arr[0][2] = 2;
//
//arr[1][0] = 2;
//arr[1][1] = 3;
//arr[1][2] = 1;
//
//arr[2][0] = 3;
//arr[2][1] = 1;
//arr[2][2] = -4;


// output: 0 1 2 5
// n = 4
// m = 4
//    arr[0][0] = 1;
//    arr[0][1] = 2;
//    arr[0][2] = 1;
//
//    arr[1][0] = 2;
//    arr[1][1] = 3;
//    arr[1][2] = 2;
//
//    arr[2][0] = 3;
//    arr[2][1] = 4;
//    arr[2][2] = 3;
//
//    arr[3][0] = 1;
//    arr[3][1] = 3;
//    arr[3][2] = 2;

// output: 0 2 7 4 -2
// n = 10
// m = 5
//arr[0][0] = 1;
//arr[0][1] = 2;
//arr[0][2] = 6;
//
//arr[1][0] = 1;
//arr[1][1] = 3;
//arr[1][2] = 7;
//
//arr[2][0] = 2;
//arr[2][1] = 4;
//arr[2][2] = 5;
//
//arr[3][0] = 4;
//arr[3][1] = 2;
//arr[3][2] = -2;
//
//arr[4][0] = 2;
//arr[4][1] = 3;
//arr[4][2] = 8;
//
//arr[5][0] = 3;
//arr[5][1] = 5;
//arr[5][2] = 9;
//
//arr[6][0] = 5;
//arr[6][1] = 4;
//arr[6][2] = 7;
//
//arr[7][0] = 5;
//arr[7][1] = 1;
//arr[7][2] = 2;
//
//arr[8][0] = 2;
//arr[8][1] = 5;
//arr[8][2] = -4;
//
//arr[9][0] = 3;
//arr[9][1] = 4;
//arr[9][2] = -3;