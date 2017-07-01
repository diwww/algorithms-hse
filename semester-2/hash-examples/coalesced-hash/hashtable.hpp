#ifndef COALESCED_HASH_HASHTABLE_HPP_H
#define COALESCED_HASH_HASHTABLE_HPP_H

// BETA = N'/N
static const double BETA = 0.86;

template<typename T>
HashTable<T>::HashTable(size_t cap, Order ord, Type t) :
        _order(ord), _type(t), _capacity(cap), _size(0)
{
    if (_type == STANDARD)
        _fullCapacity = _capacity;
    else if (_type == BASEMENT)
        _fullCapacity = (size_t) (_capacity / BETA);

    // initialize every element with nullptr
    _storage = new Entry* [_fullCapacity]();
}

template<typename T>
HashTable<T>::~HashTable()
{
    clear();
    delete[] _storage;
}

template<typename T>
void HashTable<T>::insert(T key)
{
    if (isFull())
        throw std::logic_error("Hash table is full.");

    size_t h = hash(key) % _capacity;
    Entry* toInsert = new Entry(key);

    if (_storage[h]) // if a collision occurs
    {
        size_t i = _fullCapacity - 1;
        // find the first unused bottom pos
        while (_storage[i])
            --i;
        _storage[i] = toInsert;

        Entry* temp = _storage[h];

        if (_order == EARLY)
        {
            // insert into the second pos of a chain
            toInsert->next = temp->next;
        }
        else if (_order == LATE)
        {
            // find the end of a chain
            while (temp->next)
                temp = temp->next;
        }
        temp->next = toInsert;
    }
    else // if there is no collision
        _storage[h] = toInsert;

    ++_size;
}

template<typename T>
void HashTable<T>::clear()
{
    for (size_t i = 0; i < _fullCapacity; ++i)
    {
        delete _storage[i];
        _storage[i] = nullptr;
    }

    _size = 0;
}

template<typename T>
bool HashTable<T>::find(T key)
{
    size_t h = hash(key) % _capacity;

    // if there is no element in given pos
    if (!_storage[h])
        return false;

    Entry* temp = _storage[h];
    while (temp->key != key && temp->next)
        temp = temp->next;

    return temp->key == key;
}

template<typename T>
void HashTable<T>::remove(T key)
{
    size_t h = hash(key) % _capacity;

    // TODO:
}

template<typename T>
void HashTable<T>::print()
{
    const std::string delim = "----------";


    std::cout << delim << std::endl;
    for (size_t i = 0; i < _fullCapacity; ++i)
    {
        if (i == _capacity)
            std::cout << delim << std::endl;

        if (_storage[i])
            std::cout << _storage[i]->key;
        std::cout << std::endl;
    }
    std::cout << delim << std::endl;
}

template<typename T>
void HashTable<T>::printChain(size_t index)
{
    Entry* temp = _storage[index];

    while (temp)
    {
        std::cout << temp->key << "->";
        temp = temp->next;
    }
    std::cout << "(X)" << std::endl;
}

#endif //COALESCED_HASH_HASHTABLE_HPP_H
