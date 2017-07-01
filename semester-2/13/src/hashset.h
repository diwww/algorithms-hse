// template hash set class

#ifndef  _HASHSET_H_ 
#define  _HASHSET_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

//using namespace std;

template<class key_type, class hash_func, class key_equal>
class  HashSet {
public:
    // hashtable entries 
    class Entry {
    public:
        key_type key;
        bool used;

        Entry() : used(false) {}
    };

public:
    // we do not compute prime numbers but use a table instead
    static const int num_primes;
    static const unsigned long prime_list[];

    HashSet(): _entries(0), _prime(0)
    {
        _ht = new std::vector<Entry>(prime_list[0]);
    }
          
    virtual ~HashSet() 
    { 
		delete _ht;
	}

    virtual int size() const { return _entries; }
    virtual bool search(const key_type& k);
    virtual void insert(const key_type& k);
    virtual void remove(const key_type& k);    
protected:

    int _entries;      // number of entries
    int _prime;        // index to size table

    std::vector<Entry>* _ht;
    hash_func _hf;        // hash function on key_type
    key_equal _eq;        // equality predicate on key_type

    int table_size()     const { return prime_list[_prime]; }
    double load_factor() const { return double(size()) / table_size(); }
    int resize();   
};

#endif
