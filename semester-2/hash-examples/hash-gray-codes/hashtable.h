#ifndef HASH_GRAY_CODES_HASHTABLE_H
#define HASH_GRAY_CODES_HASHTABLE_H


#include <bitset>
#include <cmath>
#include <vector>

template<typename T>
class HashTable
{
public:
    // FIXME: hardcoded param
    // nbits = ceil(log2(capacity))
    static const int NUM_SIZE = 4;


public:
    struct Entry
    {
        T key;
        bool used;
        std::bitset<NUM_SIZE> offset;
    };

public:
    HashTable(size_t);
    void insert(T key);
    void print();
    bool find(T key);

private:
    std::vector<Entry> _storage;
    std::hash<T> hash;
    size_t _capacity;

protected:
    void _collision(size_t& insertPos);
    void _coallition(size_t& insertPos, size_t& trueHash);
    size_t _findLastInChain(size_t i);
    size_t _findKeyPos(T key);

};

#include "hashtable.hpp"

#endif //HASH_GRAY_CODES_HASHTABLE_H
