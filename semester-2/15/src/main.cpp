////////////////////////////////////////////////////////////////////////////////
// Module Name:  main.cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         30.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <assert.h>
#include <stdexcept>


#include "btree.h"
#include "mycomp.h"

using namespace std;


/** \brief Тестирует открытие дерева в новом файле (1). */
void stOpenFileBTree()
{
    using namespace xi;

    string fn = "/home/maxim/Desktop/test.xibt";


    ByteComparator* comp = new ByteComparator;
    FileBaseBTree bt(2, 10, comp, fn);

    xi::BaseBTree::PageWrapper pw(&bt);

    string a = "hello";
    xi::Byte* byte = (Byte*) a.c_str();
    bt.insert(byte);


//    for (Byte i = 0; i < 10; ++i)
//    {
//        byte[i] = i;
//    }

    cout << boolalpha << (bt.search(byte) == nullptr) << std::endl;
    cout << bt.getRootPage().getKeysNum() << endl;


    delete comp;

}


int main()
{
    stOpenFileBTree();


    cout << "Hello, World!" << endl;
    return 0;
}