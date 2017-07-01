////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Main module for xi Point project
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      14.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// The module provides only a simple "smoke" test if the point class compiles well.
///
////////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include "xipoint.h"

void show(xi::PointArray *pointArray)
{
    using namespace std;

    const xi::Point *temp = pointArray->getRawPtr();
    const int size = pointArray->getSize();

    cout << "size = " << size << endl;
    for (int j = 0; j < size; ++j)
    {
        cout << temp[j].getX() << " " << temp[j].getY() << endl;
    }
}


int main(int argc, char **argv)
{
    using namespace xi;
    using namespace std;
    while (true)
    {
        int n = 7;
        Point *points;

        points = new Point[n];


        for (int i = 0; i < n; ++i)
        {
            Point p(rand() % 10, rand() % 10);
            points[i] = p;
        }


        PointArray *pointArray = new PointArray(points, n);


        // To improve the performance
        // an array can be resized by blocks

        show(pointArray);
        pointArray->insert(Point(1, 1), 99);
        pointArray->get(1)->shift(1, 1);
        pointArray->remove(0);
        show(pointArray);
        PointArray *p2 = new PointArray(*pointArray);
        show(p2);
//    p2->remove(0);
        p2->clear();
        show(p2);
        delete[] points;
        delete pointArray;
        delete p2;
    }
    return 0;
}