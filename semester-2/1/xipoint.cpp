////////////////////////////////////////////////////////////////////////////////
// Module Name:     xipoint.h/cpp
// Authors:         Sergey Shershakov
// Version:         0.2.0
// Date:            14.01.2017
//
// Implemented by:  Surovtsev Maxim, BSE151(1)
// Date:            18.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "xipoint.h"

#include <algorithm>        // min

namespace xi {


Point::Point(int x, int y)
{
    _x = x;
    _y = y;
}

void Point::shift(int shf)
{
    _x += shf;
    _y += shf;
}

void Point::shift(int xSh, int ySh)
{
    _x += xSh;
    _y += ySh;
}

void Point::shift(const Point &pt)
{
    _x += pt.getX();
    _y += pt.getY();
}

int Point::getX() const
{
    return _x;
}

int Point::getY() const
{
    return _y;
}

void Point::setX(int x)
{
    _x = x;
}

void Point::setY(int y)
{
    _y = y;
}

/**
 * Utility copy function
 * @param from - array to copy from
 * @param to - array where to copy
 * @param size - size of array
 * @pre "to" and "from" should be allocated
 */
void copy(const Point *from, Point *to, PointArray::Uint size)
{
    for (int i = 0; i < size; ++i)
    {
        to[i] = from[i];
    }
}

PointArray::PointArray()
{
    _size = 0;
    _arr = nullptr;
}

PointArray::PointArray(const Point points[], const PointArray::Uint n)
{
    _size = n;
    _arr = new Point[_size];
    copy(points, _arr, _size);
}

PointArray::PointArray(const PointArray &pv)
{
    _size = pv.getSize();
    _arr = new Point[_size];
    const Point *temp = pv.getRawPtr();
    copy(temp, _arr, _size);
}

PointArray::~PointArray()
{
    clear();
}

void PointArray::append(const Point &pt)
{
    resize(_size + 1);
    _arr[_size - 1] = pt;
}

void PointArray::insert(const Point &pt, PointArray::Uint pos)
{
    if (pos >= 0 && pos < _size) // when pos is within array bounds
    {
        resize(_size + 1);
        // Shift cycle
        for (int i = _size - 1; i > pos; --i)
        {
            _arr[i] = _arr[i - 1];
        }
        _arr[pos] = pt;
    }
    else if (pos >= _size) // when pos is bigger than size
    {
        append(pt);
    }
}

void PointArray::remove(const PointArray::Uint pos)
{
    if (pos >= 0 && pos < _size) // when pos is within array bounds
    {
        // Shift cycle
        for (int i = pos; i < _size - 1; ++i)
        {
            _arr[i] = _arr[i + 1];
        }
        resize(_size - 1);
    }
}

void PointArray::clear()
{
    if (_arr != nullptr)
    {
        delete[] _arr;
        _arr = nullptr;
    }
    _size = 0;
}

const PointArray::Uint PointArray::getSize() const
{
    return _size;
}

Point *PointArray::get(PointArray::Uint pos)
{
    if (pos < 0 || pos >= _size)
    {
        return nullptr;
    }

    // Get a pointer to given element and return it
    return _arr + pos;
}

const Point *PointArray::get(PointArray::Uint pos) const
{
    if (pos < 0 || pos >= _size)
    {
        return nullptr;
    }

    // Get a pointer to given element and return it
    return _arr + pos;
}

void PointArray::resize(PointArray::Uint n)
{
    Point *tempArr = new Point[n];
    Uint sizeToCopy = std::min(_size, n);

    for (int i = 0; i < sizeToCopy; ++i)
    {
        tempArr[i] = _arr[i];
    }

    _size = n;
    delete[] _arr;
    _arr = tempArr;
}


} // namespace xi {