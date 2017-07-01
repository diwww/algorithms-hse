#ifndef HASH_LINEAR_PROBE_HASHTABLE_HPP
#define HASH_LINEAR_PROBE_HASHTABLE_HPP


template<typename T>
const size_t HashTable<T>::NUM_PRIMES = 25;

template<typename T>
const size_t HashTable<T>::TABLE_SIZE[] =
        {
                53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613,
                393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653,
                100663319, 201326611, 402653189, 805306457
        };

template<typename T>
const double HashTable<T>::MAX_LOAD_FACTOR = 0.7;


template<typename T>
HashTable<T>::HashTable(Probe p) : _probe(p)
{
    _capacity = TABLE_SIZE[_sizeIndex];
    std::vector<Entry>(_capacity).swap(_storage);
}


template<typename T>
void HashTable<T>::_insert(T key)
{
    size_t h = _hash(key) % _capacity;

    if (_probe == LINEAR)
    {
        while (_storage.at(h).used)
            h = (h + 1) % _capacity;
    }
    else if (_probe == SQUARE)
    {
        int i = 0; // offset init
        size_t pos;
        while (true)
        {
            // positive offset
            pos = (h + i * i) % _capacity;
            if (!_storage.at(pos).used)
            {
                h = pos;
                break;
            }
            // negative offset
            if (h >= i * i)
                pos = (h - i * i) % _capacity;
            else
                // to avoid negative size_t assignment
                pos = h + _capacity - (i * i % _capacity);
            if (!_storage.at(pos).used)
            {
                h = pos;
                break;
            }
            ++i;
        }
    }

    _storage.at(h).key = key;
    _storage.at(h).used = true;

    ++_size;
}

template<typename T>
void HashTable<T>::insert(T key)
{
    if (loadFactor() > MAX_LOAD_FACTOR)
        rehash();

    _insert(key);
}

template<typename T>
bool HashTable<T>::find(T key)
{
    size_t h = _hash(key) % _capacity;

    if (_probe == LINEAR)
    {
        while (_storage.at(h).used)
        {
            if (_storage.at(h).key == key)
                return true;
            h = (h + 1) % _capacity;
        }
        return false;
    }
    else if (_probe == SQUARE)
    {
        int i = 0; // offset init
        size_t pos;
        while (true)
        {
            // positive offset
            pos = (h + i * i) % _capacity;
            if (!_storage.at(pos).used)
                return false;
            if (_storage.at(pos).key == key)
                return true;
            // negative offset
            if (h >= i * i)
                pos = (h - i * i) % _capacity;
            else
                // to avoid negative size_t assignment
                pos = h + _capacity - (i * i % _capacity);
            if (!_storage.at(pos).used)
                return false;
            if (_storage.at(pos).key == key)
                return true;

            ++i;
        }
    }
}

template<typename T>
void HashTable<T>::remove(T key)
{
    size_t h = _hash(key) % _capacity;

    if (_probe == LINEAR)
        while (_storage.at(h).used)
        {
            if (_storage.at(h).key == key)
            {
                _storage.at(h).used = false;
                --_size;
                return;
            }

            h = (h + 1) % TABLE_SIZE[_sizeIndex];
        }
    else if (_probe == SQUARE)
    {
        int i = 0; // offset init
        size_t pos;
        while (true)
        {
            // positive offset
            pos = (h + i * i) % _capacity;
            if (!_storage.at(pos).used)
                return;
            if (_storage.at(pos).key == key)
            {
                _storage.at(pos).used = false;
                --_size;
                return;
            }
            // negative offset
            if (h >= i * i)
                pos = (h - i * i) % _capacity;
            else
                // to avoid negative size_t assignment
                pos = h + _capacity - (i * i % _capacity);
            if (!_storage.at(pos).used)
                return;
            if (_storage.at(pos).key == key)
            {
                _storage.at(pos).used = false;
                --_size;
                return;
            }

            ++i;
        }
    }
}

template<typename T>
void HashTable<T>::print()
{
    for (Entry i : _storage)
    {
        if (i.used)
            std::cout << i.key;
        std::cout << std::endl;
    }
}

template<typename T>
void HashTable<T>::rehash()
{
    if (_sizeIndex == NUM_PRIMES - 1)
        throw std::logic_error("Hash table is full, no extra space to resize");

    _size = 0;
    _capacity = TABLE_SIZE[++_sizeIndex];
    std::vector<Entry> temp(_capacity);
    temp.swap(_storage);

    for (Entry i : temp)
    {
        if (i.used)
            _insert(i.key);
    }
}


#endif //HASH_LINEAR_PROBE_HASHTABLE_HPP
