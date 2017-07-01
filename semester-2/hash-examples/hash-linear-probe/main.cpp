#include <iostream>
#include <bitset>
#include "hashtable.h"

void test1()
{
    HashTable<int> table(Probe::SQUARE);
    table.insert(0);
    table.insert(53);
    table.insert(13);
    table.insert(106);

    table.print();

    std::cout << "---" << std::endl;

    std::cout << std::boolalpha << table.find(0) << std::endl;
    std::cout << std::boolalpha << table.find(53) << std::endl;
    std::cout << std::boolalpha << table.find(106) << std::endl;
    std::cout << std::boolalpha << table.find(13) << std::endl;
    std::cout << std::boolalpha << table.find(153) << std::endl;
}

void test2()
{
    HashTable<std::string> table(Probe::SQUARE);
    table.insert("Hello");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");
    table.insert("Hello1");

    table.insert("WWWWWWWWWWWWWWWWWWWWWw");
    table.remove("WWWWWWWWWWWWWWWWWWWWWw");
    table.print();
}

void test3()
{
    const int SIZE = 4;
    HashTable<std::bitset<SIZE>> table(Probe::LINEAR);

    table.insert(std::bitset<SIZE>("0000"));
    table.insert(std::bitset<SIZE>("0001"));
    table.insert(std::bitset<SIZE>("0010"));
    table.insert(std::bitset<SIZE>("0011"));
    table.insert(std::bitset<SIZE>("0100"));
    table.insert(std::bitset<SIZE>("0100"));

    table.print();
}

int main()
{
    test3();

    return 0;
}