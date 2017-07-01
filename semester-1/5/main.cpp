#include <iostream>
#include "knapsack.h"

using namespace std;

int main()
{
    Knapsack *knapsack;
    int W, n;
    int *costs, *weights;
    bool *ptr;

    // TESTS

    W = 5;
    n = 4;
    costs = new int[n]{3, 4, 5, 6};
    weights = new int[n]{2, 3, 4, 5};

//    W = 100;
//    n = 6;
//    costs = new int[n]{40, 35, 18, 4, 10, 2};
//    weights = new int[n]{100, 50, 45, 20, 10, 5};


    // Iteratively
    knapsack = new Knapsack();
    knapsack->initialize(W, weights, costs, n);
    knapsack->solveIteratively();
    cout << "Cost = " << knapsack->getCost() << endl;
    cout << "Weight = " << knapsack->getWeight() << endl;
    ptr = knapsack->getItemset();
    for (int i = 0; i < n; ++i)
    {
        cout << ptr[i] << " ";
    }
    cout << endl;
    delete knapsack;

    // Recursively
    knapsack = new Knapsack();
    knapsack->initialize(W, weights, costs, n);
    knapsack->solveRecursively();
    cout << "Cost = " << knapsack->getCost() << endl;
    cout << "Weight = " << knapsack->getWeight() << endl;
    ptr = knapsack->getItemset();
    for (int i = 0; i < n; ++i)
    {
        cout << ptr[i] << " ";
    }
    cout << endl;
    delete knapsack;

    // Greedy
    knapsack = new Knapsack();
    knapsack->initialize(W, weights, costs, n);
    knapsack->solveGreedy();
    cout << "Cost = " << knapsack->getCost() << endl;
    cout << "Weight = " << knapsack->getWeight() << endl;
    ptr = knapsack->getItemset();
    for (int i = 0; i < n; ++i)
    {
        cout << ptr[i] << " ";
    }
    cout << endl;
    delete knapsack;


    delete[]costs;
    delete[] weights;

    return 0;
}

