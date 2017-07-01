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
#include <fstream>
#include <vector>

#include "safearray.h"
#include "subject.h"


using namespace std;


int main()
{
    using namespace xi;

//    vector<Subject> subjects;
//    ifstream input("/home/maxim/Desktop/prj/res/raw/subjects.txt");
//    ofstream output("/home/maxim/Desktop/prj/res/raw/subjects_read.txt");

//    while (!input.eof())
//    {
//        Subject s;
//        input >> s;
//        output << s << endl;
//    }

    Subject s;
    cin >> s;
    cout << s;


//    SafeArray<int> sa = SafeArray<int>(5);
//
//    sa[0] = 3;
//    sa[1] = 4;
//    sa[4] = -3;
//
////    SafeArray<int> temp = SafeArray<int>(sa);
//
//    SafeArray<int> temp = sa;
//
//    for (int i = 0; i < temp.getCapacity(); ++i)
//    {
//        cout << temp[i] << endl;
//    }

//    while (true)
//    {
//        SafeArray<int> a = SafeArray<int>(10);
//        SafeArray<int> b = a;
//    }


    return 0;
}