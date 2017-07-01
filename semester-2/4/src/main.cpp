////////////////////////////////////////////////////////////////////////////////
// Module Name:  main.cpp
// Authors:      Leonid Dworzanski, Sergey Shershakov
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "dna_repairer.h"

using namespace std;

static const char* INP_FILENAME = "/home/maxim/Desktop/prj-1.0/res/test5.in";

void show(xi::LinkedList<int>& list)
{
    xi::Node<int>* last = list.getPreHead();
    while (last->next != nullptr)
    {
        cout << last->next->value << " ";
        last = last->next;
    }
    cout << endl;
}

int main(int argc, char* argv[])
{
    xi::LinkedList<int> list0;

    list0.addElementToEnd(3);
    list0.addElementToEnd(2);
    list0.addElementToEnd(1);

    xi::LinkedList<int> list1 = list0;
    show(list0);
    show(list1);
    cout << list0.size() << " " << list1.size() << endl << endl;

    DNAElement element("b3:G");
    cout << element.id << endl;
    cout << element.number << endl;
    cout << element.base << endl;

    try
    {
        DNARepairer dnarepairer;

        dnarepairer.readFile(INP_FILENAME);


        cout << "Broken DNAs" << endl;
        dnarepairer.printDNAStorage();

        dnarepairer.repairDNA();

        cout << "\nGood as it is" << endl;
        dnarepairer.printDNAStorage();
    }
    catch (exception& e)
    {
        cout << e.what();
    }
    catch (...)
    {
        cout << "Something wrong happend." << endl;
    }
    cout << endl;

    return EXIT_SUCCESS;
}

