// Name: Surovtsev Maxim
// Group: BSE151
// Books used: Introduction to Algorithms by Thomas H. Cormen

#include "merge_sort.h"
#include <climits>

void merge_sort(int *arr, int n)
{
    // To sort the whole array we use
    // 0 as left index and n as right
    divide_and_merge(arr, 0, n);
}

void merge(int* arr, int start_first, int start_second, int end)
{
    // Length calculation of
    // two subarrays
    // (they must be already sorted)
    int length1 = start_second - start_first;
    int length2 = end - start_second;
    // Initializing arrays:
    // (length + 1) is due to
    // the last special element,
    // which is signal of the end
    int *a1 = new int[length1 + 1];
    int *a2 = new int[length2 + 1];
    // Filling arrays
    for (int i = 0; i < length1; ++i)
        a1[i] = arr[start_first + i];
    for (int i = 0; i < length2; ++i)
        a2[i] = arr[start_second + i];
    // The last special element
    // (signal of the end)
    a1[length1] = INT_MAX;
    a2[length2] = INT_MAX;
    // Temp indexes for merging
    int i = 0;
    int j = 0;
    // Merging and sorting
    // (card deck principle)
    for (int k = start_first; k < end; ++k)
    {
        if (a1[i] <= a2[j])
        {
            arr[k] = a1[i];
            i++;
        }
        else
        {
            arr[k] = a2[j];
            j++;
        }
    }
}

void divide_and_merge(int *arr, int left, int right)
{
    // Recursively divide an array
    // until its length is 1
    if (left < right - 1)
    {
        // Caculation of the middle index
        int mid = int((left + right) / 2);
        // Recursise division
        divide_and_merge(arr, left, mid);
        divide_and_merge(arr, mid, right);
        // Combine sorted parts of
        // an array
        merge(arr, left, mid, right);
    }
}