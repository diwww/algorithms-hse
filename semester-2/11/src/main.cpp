///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains the main routine 
///
/// Students do not need to modify the file.
///
///////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <cstdlib>

#include "grid.h"



/** \brief Output results in the standard output */
void outputRes(grid& g, int row, int col)
{
    std::cout << "The colony including the cell at "
        << "(" << row << "," << col << ")"
        << " has an area of " << g.getCount(row, col) << " units.\n";

    std::cout << g << std::endl;
}



/** \brief Main entry point of the program
 *
 *  Should obtain at least 3 command line parameters, which are interpreted as: 
 *  1. the name of a file with units by grid distribution
 *  2. \a row and
 *  3. \a col in a pair (\a row, \a col) representing the cell of interest
 */
int main (int argc, char* argv[]) 
{
    if (argc < 4) 
    {
        std::cerr << "Usage: " << argv[0] << " grid_file row_no col_no\n\n";
        return EXIT_FAILURE;
    }

    try
    {
        grid g(argv[1]);

        int row = atoi(argv[2]);
        int col = atoi(argv[3]);

        outputRes(g, row, col);
    }
    catch (std::exception& e)
    {
        std::cerr << "An error with the grid: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Unknown exception caught!" << std::endl;
        return EXIT_FAILURE;
    }

  
    return EXIT_SUCCESS;
}

