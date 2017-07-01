#ifndef HASH_CHAINING_HASHTABLE_H
#define HASH_CHAINING_HASHTABLE_H

#include <cstddef>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

template<typename T>
class HashTable
{
public:
    const double MAX_LOAD_FACTOR = 1.0;

public:
    HashTable(size_t n);
    size_t size() { return _size; }
    size_t bucketSize(size_t index) { return _storage.at(index).size(); }
    size_t bucketCount() { return _nBuckets; }
    double loadFactor() { return ((double) _size) / ((double) _nBuckets); }
    void rehash(size_t n);
    void insert(T key);
    bool find(T key);
    void remove(T key);
    void clear();
    void print();

private:
    size_t _size = 0;
    size_t _capacity = 0;
    size_t _nBuckets = 0;
    size_t _nBucketsInit = 0;
    std::vector<std::list<T> > _storage;
    std::hash<T> hash;

protected:
    std::list<T>& getBucketByKey(T key);
    void _insert(T key);
    HashTable(HashTable&);
    HashTable& operator=(HashTable);
};

#include "hashtable.hpp"

#endif //HASH_CHAINING_HASHTABLE_H
