// Name: Surovtsev Maxim
// Group: BSE151
// Books used: Introduction to Algorithms by Thomas H. Cormen

#include "heapSort.h"
#include <algorithm>
#include <stdexcept>

/**
 * Heapsort class implementation
 */
void Heapsort::heapSort(int *arr, int n)
{
    Heap h(arr, n);

    // Extract min element everytime
    // and reorganize the heap
    for (int i = 0; i < n; ++i)
        arr[i] = h.extractMin();
}

/**
 * Heap class implementation
 */
Heap::Heap(const int *source, const int n) : capacity(n)
{
    // Intial size of a heap
    currentSize = 0;

    storage = new int[n];

    for (int i = 0; i < n; ++i)
    {
        // Insert new element and
        // reorganize the heap
        insert(source[i]);
    }
}

Heap::~Heap()
{
    delete[] storage;
}

int Heap::getMin()
{
    return storage[0];
}

int Heap::extractMin()
{
    int min;

    if (currentSize < 1)
    {
        throw std::length_error("Heap is empty.");
    }

    // Min element is always
    // the root of a tree
    min = getMin();

    // Last element is now the first
    storage[0] = storage[currentSize - 1];

    // Finally, decrease
    // the heap size by 1
    currentSize--;

    // Build an updated heap
    heapifyDown(0);

    return min;
}

void Heap::insert(const int value)
{
    if (currentSize == capacity)
    {
        throw std::length_error("Heap is full.");
    }

    // Last element is value now
    storage[currentSize] = value;
    currentSize++;

    // Push it up if the heap
    // state is incorrect
    heapifyUp(currentSize - 1);
}

void Heap::heapifyDown(int index)
{
    int min = index;

    // Left node's child index
    int l = index * 2 + 1;
    // Right node's child index
    int r = index * 2 + 2;

    if (l < currentSize && storage[l] < storage[min])
        min = l;
    if (r < currentSize && storage[r] < storage[min])
        min = r;
    if (min != index)
    {
        std::swap(storage[index], storage[min]);
        heapifyDown(min);
    }
}

void Heap::heapifyUp(int index)
{
    int min = index;

    // Parent node's index
    int p = (index - 1) / 2;

    if (p >= 0 && p < currentSize && storage[p] > storage[min])
        min = p;
    if (min != index)
    {
        std::swap(storage[index], storage[min]);
        heapifyUp(min);
    }
}