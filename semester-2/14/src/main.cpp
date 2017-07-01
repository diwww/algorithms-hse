////////////////////////////////////////////////////////////////////////////////
// Module Name:  main.cpp
// Authors:      Sergey Shershakov
// Version:      0.1.0
// Date:         01.05.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "rbtree.h"
#include "def_dumper.h"

using namespace std;


void simplestTest()
{
    using namespace xi;

    RBTree<int> tree1;
    RBTreeDefDumper<int, std::less<int> >* dumper = new RBTreeDefDumper<int, std::less<int> >(
            "/home/maxim/Desktop/logs/log.txt", "/home/maxim/Desktop/pics/gv/");
    tree1.setDumper(dumper);

    tree1.insert(4);
    tree1.insert(50);
    tree1.insert(10);
    tree1.insert(40);
    tree1.insert(17);
    tree1.insert(35);
    tree1.insert(20);
    tree1.insert(27);
    tree1.insert(37);
    tree1.insert(45);
    tree1.insert(60);
    tree1.insert(21);
    tree1.insert(1);
    tree1.insert(30);


    delete dumper;
}


int main()
{
    cout << "Hello, World!" << endl;

    simplestTest();

    return 0;
}
