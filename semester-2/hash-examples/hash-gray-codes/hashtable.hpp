#ifndef HASH_GRAY_CODES_HASHTABLE_HPP
#define HASH_GRAY_CODES_HASHTABLE_HPP

#include <limits>

template<typename T>
HashTable<T>::HashTable(size_t cap)
{
    _capacity = cap;
    _storage = std::vector<Entry>(_capacity);
}


template<typename T>
void HashTable<T>::_collision(size_t& insertPos)
{
    // Collision position binary representation
    std::bitset<NUM_SIZE> offset(insertPos);
    for (size_t i = 0; i < offset.size(); ++i)
    {
        std::bitset<NUM_SIZE> offsetTemp(offset);
        offsetTemp.flip(i);
        size_t pos = offsetTemp.to_ulong() % _capacity;
        if (!_storage.at(pos).used)
        {
            _storage.at(insertPos).offset = offset ^ offsetTemp;
            insertPos = pos;
            return;
        }
    }
    // TODO: throw an exception (all position are used)
}

template<typename T>
void HashTable<T>::_coallition(size_t& insertPos, size_t& trueHash)
{
    // FIXME: выкидывается один элемент из цепочки, а не вся цепочка
    // Ищем новую позицию для "реального/изначального" хэша элемента
    std::bitset<NUM_SIZE> offset(trueHash);
    for (size_t i = 0; i < offset.size(); ++i)
    {
        std::bitset<NUM_SIZE> offsetTemp(offset);
        // Invert a bit in given position
        offsetTemp.flip(i);
        size_t pos = offsetTemp.to_ulong();
        if (!_storage.at(pos).used)
        {
            _storage.at(pos) = _storage.at(insertPos);

            std::bitset<NUM_SIZE> insertPosBitSet(insertPos);
            std::bitset<NUM_SIZE> truehashBitSet(trueHash);
            std::bitset<NUM_SIZE> predPosBitSet = insertPosBitSet ^truehashBitSet;
            predPosBitSet ^= insertPosBitSet;

            size_t predPos = predPosBitSet.to_ulong() % _capacity;
            _storage.at(predPos).offset = offset ^ offsetTemp;
            return;
        }
    }
    // TODO: throw an exception (all position are used)
}

template<typename T>
void HashTable<T>::insert(T key)
{
    // Вычисленный хэш элемента
    size_t h = hash(key) % _capacity;
    // Позиция для вставки элемента
    size_t insertPos = _findLastInChain(h);

    if (_storage.at(insertPos).used)
    {
        // Хэш элемента на позиции insertPos
        size_t hh = hash(_storage.at(insertPos).key) % _capacity;

        if (h != hh) // Coalition
        {
            _coallition(h, hh);
        }
        else // Collision
        {
            _collision(insertPos);
        }
    }

    Entry e;
    e.key = key;
    e.used = true;
    _storage.at(insertPos) = e;
}

template<typename T>
void HashTable<T>::print()
{
    for (int i = 0; i < _storage.size(); ++i)
    {
        std::cout << i << ")\t";
        if (_storage.at(i).used)
            std::cout << _storage.at(i).key;
        if (_storage.at(i).offset.count() != 0)
            std::cout << "\t" << _storage.at(i).offset;
        std::cout << std::endl;
    }
}

template<typename T>
size_t HashTable<T>::_findKeyPos(T key)
{
    size_t h = hash(key) % _capacity;

    do
    {
        if (_storage.at(h).key == key)
            return h;
        std::bitset<NUM_SIZE> hBin(h);
        h = (hBin ^ _storage.at(h).offset).to_ulong();
    } while (_storage.at(h).offset.count());

    return std::numeric_limits<std::size_t>::max();
}

template<typename T>
bool HashTable<T>::find(T key)
{
    return _findKeyPos(key) != std::numeric_limits<std::size_t>::max();
}

template<typename T>
size_t HashTable<T>::_findLastInChain(size_t i)
{
    do
    {
        std::bitset<NUM_SIZE> hBin(i);
        i = (hBin ^ _storage.at(i).offset).to_ulong();
    } while (_storage.at(i).offset.count());
    return i;
}


#endif //HASH_GRAY_CODES_HASHTABLE_HPP
