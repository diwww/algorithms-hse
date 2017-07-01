#include <iostream>
#include "hashtable.h"
#include "../helper.h"

const int LEN = 10;

int main()
{
    Helper helper;
    HashTable<std::string> table(4);
    table.insert(helper.getRandomString(LEN));
    table.insert(helper.getRandomString(LEN));
    table.insert(helper.getRandomString(LEN));
    table.insert(helper.getRandomString(LEN));
    table.insert(helper.getRandomString(LEN));
    table.insert(helper.getRandomString(LEN));
    table.insert(helper.getRandomString(LEN));


    std::cout << "Size = " << table.size() << std::endl;
    std::cout << "Buckets = " << table.bucketCount() << std::endl;
    table.print();

    table.rehash(4);
    std::cout << "Size = " << table.size() << std::endl;
    std::cout << "Buckets = " << table.bucketCount() << std::endl;
    table.print();

    return 0;
}