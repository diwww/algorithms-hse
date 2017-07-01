// Name: Surovtsev Maxim
// Group: BSE151
// Books used: Introduction to Algorithms by Thomas H. Cormen
// and also the materials from presentation

#include "quick_sort.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Sort array by middle pivot
void q_sort::quick_sort_middle(int* arr, int n) //pivot is middle
{
    quick_sort(arr, 0, n, get_middle_pivot);
}

// Sort array by last pivot
void q_sort::quick_sort_last(int* arr, int n) //pivot is last
{
    quick_sort(arr, 0, n, get_last_pivot);
}

// Sort array by random pivot
// between "from" and "to"
void q_sort::quick_sort_rand(int* arr, int n)
{
    quick_sort(arr, 0, n, get_rand_pivot);
}

// Returns middle index
int q_sort::get_middle_pivot(int from, int to)
{
    return (from + to) / 2;
}

// Returns last index
int q_sort::get_last_pivot(int from, int to)
{
    return to - 1;
}

// Returns random index
// between "from" and "to"
int q_sort::get_rand_pivot(int from, int to)
{
    // True random
    std::srand(time(NULL));
    // Random between "from" and "to"
    return rand() % (to - from) + from;
}

// Quick sort function
void q_sort::quick_sort(int* arr, int from, int to, pivot_chooser chooser)
{
    if (from < to)
    {
        // Get pivot index depending on
        // which function was passed
        // as third argument
        int pivot_index1 = chooser(from, to);
        // Partitioning and getting new pivot index
        int pivot_index2  = rearrange_array_with_pivot(arr, from, to, pivot_index1);
        // Recursively sort left part
        quick_sort(arr, from, pivot_index2, chooser);
        // Recursively sort right part
        quick_sort(arr, pivot_index2 + 1, to, chooser);

    }
}

// Partition function
int q_sort::rearrange_array_with_pivot(int* arr, int from, int to, int pivot_index)
{
    // Pivot element
    int pivot = arr[pivot_index];
    // Left bound
    int i = from - 1;
    // Right bound
    int j = to + 1;

    while (true)
    {
        do
            i++; // Increase left bound
        while (arr[i] < pivot);

        do
            j--; // Decrease right bound
        while (arr[j] > pivot);

        if (i >= j)
            return j; // Return j as pivot index

        std::swap(arr[i], arr[j]);
    }
}