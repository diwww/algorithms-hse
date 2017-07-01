#ifndef  _DICTIONARY_H_
#define  _DICTIONARY_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>
#include <fstream>
#include  "hashset.h"
#include  "hashset.cpp"

//using namespace std;

class hash_function
{
public:
    static const unsigned int OFFSET_BASIS = 2166136261u;
    static const unsigned int FNV_PRIME = 16777619u;
public:
    hash_function() { }

    // FNV-1a hash algorithm
    unsigned int operator()(const std::string& s) const
    {
        unsigned int hash = OFFSET_BASIS;
        for (int i = 0; i < s.length(); ++i)
        {
            hash ^= s[i];
            hash *= FNV_PRIME;
        }
        return hash;
    }
};

class equality
{
public:
    equality() { }

    bool operator()(const std::string& a, const std::string& b) const
    {
        return (a == b);
    }
};


class Dictionary : public HashSet<std::string, hash_function, equality>
{
public:
    Dictionary(const std::string& path);
};

#endif
