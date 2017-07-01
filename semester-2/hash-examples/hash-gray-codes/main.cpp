#include <iostream>
#include "hashtable.h"

int main()
{
    HashTable<int> table(11);

//    table.insert(27);
//    table.insert(18);
//    table.insert(29);
//    table.insert(28);
//    table.insert(39);
//    table.insert(13);
//    table.insert(16);
//    table.insert(6);

    table.insert(28);
    table.insert(39);
    table.insert(50);

    table.print();

    std::cout << std::boolalpha << table.find(7) << std::endl;
    return 0;
}