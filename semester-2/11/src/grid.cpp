///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains implementation of \a grid class
///
/// Should be augmented by students if needed
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "grid.h"

const bool grid::NOT_INFECTED = false;
const bool grid::INFECTED = true;

grid::grid(const std::string& fileName)
{
    std::ifstream grid_file;

    try
    {
        grid_file.open(fileName.c_str());

        // check if it's all ok
        if (!grid_file.good())
            throw std::runtime_error("File cannot be open");

        // opened correctly
        grid_file >> _rows;
        grid_file >> _cols;

        _area = std::vector<std::pair<bool, bool >>(_rows * _cols, {grid::NOT_INFECTED, false});

        int blob_row;
        int blob_col;

        while (!grid_file.eof() && grid_file.good())
        {
            grid_file >> blob_row;
            grid_file >> blob_col;

            _area[indexOf(blob_row, blob_col)].first = INFECTED;
        }
    }
    catch (...)
    {
        // always tries to properly close the file!
        grid_file.close();
        throw;              // dispatch further
    }

    grid_file.close();
}

std::ostream& operator<<(std::ostream& stream, const grid& ob)
{
    for (int row = 0; row < ob._rows; ++row)
    {
        for (int col = 0; col < ob._cols; col++)
            stream << ob._area[ob.indexOf(row, col)].first <<
                   (ob.isVisited(row, col) ? "+" : "") << "\t";
        stream << std::endl;
    }
    stream << std::endl;
    return stream;
}

int grid::count(int row, int col)
{
    if (!checkIndex(row, col) || !isInfected(row, col)
        || isVisited(row, col))
        return 0;

    // Mark as visited
    _area[indexOf(row, col)].second = true;
    // Init sum with 1
    int s = 1;

    // Check 8 adjacent cells
    s += count(row, col + 1);
    s += count(row, col - 1);

    s += count(row + 1, col);
    s += count(row + 1, col + 1);
    s += count(row + 1, col - 1);

    s += count(row - 1, col);
    s += count(row - 1, col + 1);
    s += count(row - 1, col - 1);

    return s;
}

int grid::getCount(int row, int col)
{
    indexOf(row, col);
    return count(row, col);
}

int grid::indexOf(int row, int col) const
{
    if (!checkIndex(row, col))
        throw std::invalid_argument("Index out of range");

    return row * _cols + col;
}

bool grid::isInfected(int row, int col) const
{
    return _area[indexOf(row, col)].first == INFECTED;
}

bool grid::isVisited(int row, int col) const
{
    return _area[indexOf(row, col)].second;
}

bool grid::checkIndex(int row, int col) const
{
    if (row >= _rows || row < 0 || col >= _cols || col < 0)
        return false;
    return true;
}
