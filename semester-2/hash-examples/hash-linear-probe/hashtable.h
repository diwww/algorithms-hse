#ifndef HASH_LINEAR_PROBE_HASHTABLE_H
#define HASH_LINEAR_PROBE_HASHTABLE_H

#include <vector>
#include <cstddef>
#include <iostream>

enum Probe {LINEAR, SQUARE};

template<typename T>
class HashTable
{
public:
    static const size_t TABLE_SIZE[];
    static const size_t NUM_PRIMES;
    static const double MAX_LOAD_FACTOR ;

public:
    struct Entry
    {
        T key;
        bool used;
        Entry() : used(false) { }
    };

public:
    HashTable(Probe);
    void insert(T key);
    bool find(T key);
    void remove(T key);
    void rehash();
    void print();
    double loadFactor() { return (double) _size / _storage.size(); };

protected:
    void _insert(T key);

private:
    std::vector<Entry> _storage;
    size_t _size = 0;
    size_t _capacity = 0;
    std::hash<T> _hash;
    size_t _sizeIndex = 0;
    Probe _probe;
};

#include "hashtable.hpp"

#endif //HASH_LINEAR_PROBE_HASHTABLE_H
