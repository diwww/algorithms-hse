#include <iostream>
#include <sstream>
#include "hashtable.h"

void test1()
{
    HashTable<int> hashTable(20, Order::EARLY, Type::BASEMENT);
    hashTable.insert(25);
    hashTable.insert(2);
    hashTable.insert(8);
    hashTable.insert(9);
    hashTable.insert(17);
    hashTable.insert(18);
    hashTable.insert(16);
    hashTable.insert(1);
    hashTable.insert(21);
    hashTable.insert(41);
    hashTable.print();
    std::cout << std::endl;
    hashTable.printChain(1);
    hashTable.printChain(0);
    std::cout << std::endl;
    std::cout << std::boolalpha << hashTable.find(1) << std::endl;
    std::cout << std::boolalpha << hashTable.find(9) << std::endl;
    std::cout << std::boolalpha << hashTable.find(23) << std::endl;
}

void test2()
{
    std::string temp = "Hello there. Nice to meet you. I have to tell you the honest truth as I see it.";
    std::stringstream ss(temp);
    HashTable<std::string> hashTable(20, Order::EARLY, Type::STANDARD);

    while (ss)
    {
        std::string word;
        ss >> word;
        hashTable.insert(word);
    }
    hashTable.print();
}

int main()
{
    test2();

    return 0;
}