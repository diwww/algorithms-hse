////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Safearray class methods definition
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      30.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// This file contains templates of the method of the class Safearray.
/// This file is not going to be used w/o its main counterpart, safearray.h.
/// Since the file is used only through safearray.h, which has its own "include 
/// watcher", we add no addition "watcher" here.
///
////////////////////////////////////////////////////////////////////////////////

// #ifndef    // No need to have a watcher here!


#include "safearray.h"


// we have to indicate that methods of the class Safearray are also inside the namespace xi
namespace xi {

template<typename T>
void SafeArray<T>::init(size_t cap)
{
    _capacity = cap;
    if (_capacity)
        _storage = new T[_capacity];
    else
        _storage = nullptr;
}

template<typename T>
void SafeArray<T>::copy(const SafeArray& other)
{
    for (int i = 0; i < _capacity; ++i)
        _storage[i] = other[i];
}

template<typename T>
SafeArray<T>::SafeArray(size_t cap)
{
    init(cap);
}

template<typename T>
SafeArray<T>::SafeArray(const SafeArray& other)
// : SafeArray(other.getCapacity()) // Delegating constructor (c++11)
{
    init(other.getCapacity());
    copy(other);
}

template<typename T>
SafeArray<T>::~SafeArray()
{
    if (_storage != nullptr)
    {
        delete[] _storage;
        _storage = nullptr;
    }
}

template<typename T>
T& SafeArray<T>::operator[](size_t k)
{
    checkBounds(k);
    return _storage[k];
}

template<typename T>
const T& SafeArray<T>::operator[](size_t k) const
{
    checkBounds(k);
    return _storage[k];
}

template<typename T>
size_t SafeArray<T>::getCapacity() const
{
    return _capacity;
}

template<typename T>
void SafeArray<T>::checkBounds(size_t index) const
{
    if (index < 0 || index >= _capacity)
        throw std::out_of_range("Index is out of range.");
}

template<typename T>
SafeArray <T>& SafeArray<T>::operator=(const SafeArray <T>& other)
{
    if (this != &other) // self assignment check
    {
        if (_storage != nullptr) // deallocate old storage
            delete[] _storage;

        init(other.getCapacity());
        copy(other);
    }

    return *this;
}

} // namespace xi
