// Name: Surovtsev Maxim
// Group: BSE151
// Used materials: Dynamic programming 0-1 Knapsack problem by Dr. Steve Goddard

#include "knapsack.h"
#include <algorithm>


#include <iostream>
#include <iomanip>

using namespace std;

// Utility method for copying arrays
void copy_array(const int *from, int *to, const int size)
{
    for (int i = 0; i < size; ++i)
    {
        to[i] = from[i];
    }
}

// Utility method for sorting corresponding arrays
void sort(int *costs, int *weights, int *indexes, int n)
{
    // OMG! Straightforward bubble sort...
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (double(costs[j]) / weights[j] <
                double(costs[j + 1]) / weights[j + 1])
            {
                // Swap 3 times, ugh
                std::swap(costs[j], costs[j + 1]);
                std::swap(weights[j], weights[j + 1]);
                std::swap(indexes[j], indexes[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// Utility method for deleting
// 2d dynamic array
void deleteGrid(int **grid, int n)
{
    for (int i = 0; i < n + 1; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;
}

Knapsack::~Knapsack()
{
    if (weights != nullptr)
    {
        delete[] weights;
        weights = nullptr;
    }
    if (costs != nullptr)
    {
        delete[] costs;
        costs = nullptr;
    }
    if (itemset != nullptr)
    {
        // Remember, that you should not delete
        // pointer to itemset in main.cpp again
        delete[] itemset;
        itemset = nullptr;
    }
}

void Knapsack::initialize(const int capacity, const int *weights, const int *costs, const int n)
{
    // Initial values
    bpWeight = 0;
    bpCost = 0;
    solved = false;
    maxCapacity = capacity;
    nItems = n;

    // Copying arrays
    this->weights = new int[n];
    this->costs = new int[n];
    this->itemset = new bool[n](); // fill with zeros
    copy_array(weights, this->weights, n);
    copy_array(costs, this->costs, n);

    initialized = true;
}

void Knapsack::buildGrid()
{
    int N = nItems + 1;
    int M = maxCapacity + 1;

    // Initializing the grid
    grid = new int *[N];
    for (int i = 0; i < N; ++i)
    {
        grid[i] = new int[M](); // fill with zeros
    }

    // Setting all elements to -1
    // except first row and column
    for (int i = 1; i < N; ++i)
    {
        for (int j = 1; j < M; ++j)
        {
            grid[i][j] = -1;
        }
    }
}

void Knapsack::solveIteratively()
{
    buildGrid();

    for (int i = 1; i <= nItems; i++)
    {
        for (int j = 1; j <= maxCapacity; j++)
        {
            if (weights[i - 1] <= j)
                grid[i][j] = std::max(costs[i - 1] + grid[i - 1][j - weights[i - 1]], grid[i - 1][j]);

            else
                grid[i][j] = grid[i - 1][j];
        }
    }

    backtrack();
    solved = true;
    deleteGrid(grid, nItems);
}

void Knapsack::solveRecursively()
{
    buildGrid();
    getFromGrid(nItems, maxCapacity);
    backtrack();
    deleteGrid(grid, nItems);
}

int Knapsack::getFromGrid(int item, int capacity)
{
    if (item == 0 || capacity == 0)
        return 0;
    if (grid[item][capacity] == -1)
    {
        if (weights[item - 1] <= capacity)
            grid[item][capacity] = std::max(costs[item - 1] +
                                            getFromGrid(item - 1, capacity - weights[item - 1]),
                                            getFromGrid(item - 1, capacity));
        else
            grid[item][capacity] = getFromGrid(item - 1, capacity);
    }
    return grid[item][capacity];
}

void Knapsack::backtrack()
{
    // Initializing grid bounds
    int i = nItems;
    int j = maxCapacity;

    while (i > 0 && j > 0)
    {
        if (grid[i][j] != grid[i - 1][j])
        {
            itemset[i - 1] = true;
            j = j - weights[i - 1];
            i--;
        }
        else
        {
            i--;
        }
    }

    for (int k = 0; k < nItems + 1; ++k)
    {
        for (int l = 0; l < maxCapacity + 1; ++l)
        {
            cout << setw(3) << grid[k][l];
        }
        cout << endl;
    }

    bpCost = grid[nItems][maxCapacity];
    bpWeight = maxCapacity - j;
}

void Knapsack::solveGreedy()
{
    // Create an array of indexes to remember
    // the original order in itemset
    int *indexes = new int[nItems];
    for (int i = 0; i < nItems; ++i)
    {
        indexes[i] = i;
    }

    sort(costs, weights, indexes, nItems);
    int capacity = maxCapacity;

    for (int i = 0; i < nItems; ++i)
    {
        if (capacity >= weights[i])
        {
            bpCost += costs[i];
            bpWeight += weights[i];
            itemset[indexes[i]] = true;
            capacity -= weights[i];
        }
        else
        {
            continue;
        }
    }

    solved = true;
    delete[] indexes;
}

int Knapsack::getCost()
{
    return bpCost;
}

int Knapsack::getWeight()
{
    return bpWeight;
}

bool *Knapsack::getItemset()
{
    return itemset;
}

bool Knapsack::isSolved()
{
    return solved;
}

bool Knapsack::isInitialized()
{
    return initialized;
}