#ifndef HASH_CHAINING_HASHTABLE_HPP_H
#define HASH_CHAINING_HASHTABLE_HPP_H

template<typename T>
HashTable<T>::HashTable(size_t n)
{
    _nBucketsInit = n;
    rehash(_nBucketsInit);
}

template<typename T>
void HashTable<T>::rehash(size_t n)
{
    _nBuckets = n;
    _size = 0;
    std::vector<std::list<T> > temp(_nBuckets);
    temp.swap(_storage);

    for (std::list<T> bucket : temp)
        for (T i : bucket)
            _insert(i);
}

template<typename T>
void HashTable<T>::_insert(T key)
{
	std::list<T>& bucket = getBucketByKey(key);
    bucket.push_back(key);
    ++_size;
}

template<typename T>
void HashTable<T>::insert(T key)
{
    // FIXME: prime numbers for bucket count
    if (loadFactor() >= MAX_LOAD_FACTOR)
        rehash(_nBuckets * 2);

    _insert(key);
}

template<typename T>
bool HashTable<T>::find(T key)
{
    std::list<T>& bucket = getBucketByKey(key);
    typename std::list<T>::iterator it = std::find(bucket.begin(), bucket.end(), key);

    if (it == bucket.end())
        return false;
    else
        return true;
}

template<typename T>
void HashTable<T>::remove(T key)
{
    std::list<T>& bucket = getBucketByKey(key);
    bucket.remove(key);
}

template<typename T>
void HashTable<T>::print()
{
    for (std::list<T> bucket : _storage)
    {
        for (T i : bucket)
            std::cout << i << "->";
        std::cout << std::endl;
    }
}

template<typename T>
void HashTable<T>::clear()
{
    _nBuckets = _nBucketsInit;
    std::vector<std::list<T> >(_nBuckets).swap(_storage);
    _size = 0;
}

template<typename T>
std::list<T>& HashTable<T>::getBucketByKey(T key)
{
    size_t h = hash(key) % _nBuckets;
    return _storage.at(h);
}

#endif //HASH_CHAINING_HASHTABLE_HPP_H
