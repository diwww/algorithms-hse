#ifndef COALESCED_HASH_HASHTABLE_H
#define COALESCED_HASH_HASHTABLE_H

#include <cstddef>
#include <functional>
#include <vector>
#include <iostream>

enum Order {EARLY, LATE};
enum Type {STANDARD, BASEMENT};

template<typename T>
class HashTable
{
public:
    struct Entry
    {
        T key;
        Entry* next;
        Entry(T k) { key = k; }
    };

public:
    HashTable(size_t cap, Order ord, Type t);
    ~HashTable();
    double loadFactor() { return ((double) _size) / ((double) _capacity); }
    bool isFull() { return _size == _fullCapacity; }
    void insert(T key);
    bool find(T key);
    void remove(T key);
    void clear();
    void printChain(size_t index);
    void print();

private:
    Type _type = STANDARD;
    Order _order = LATE;
    Entry** _storage = nullptr;
    size_t _size = 0;           // current number of entries
    size_t _capacity = 0;       // N' (only for hash calculations)
    size_t _fullCapacity = 0;   // N (w/ basement)
    std::hash<T> hash;          // hash functor

protected:
    HashTable(HashTable&);
    HashTable& operator=(HashTable);
};

#include "hashtable.hpp"


#endif //COALESCED_HASH_HASHTABLE_H
