///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains definition of \a grid class
///
/// Should be augmented by students if needed
///
///////////////////////////////////////////////////////////////////////////////


#ifndef XI_ASSESSING_INFECTION_GRID_H
#define XI_ASSESSING_INFECTION_GRID_H

#include <string>
#include <vector>


/** \brief Represents a tissue sample as a rectangle grid structure
 *
 *  **IMPORTANT NOTE FOR STUDENTS**:
 *
 *  For this assignment, you might need to add state to the
 *  class and/or augment existing methods, and/or create private helper
 *  methods, but you should not delare new public methods
 */
class grid
{
public:
    static const bool NOT_INFECTED;
    static const bool INFECTED;

public:
    /** \brief Inititalizes with a file name 
     *
     *  If the constructor fails to open a file, a \a std::runtime_error is raised
     *
     *  **Students may need** to alter the constructor
     */
    grid(const std::string& fileName);

    /** \brief Returns a count units for the area deftermined by coordinates (\a row, \a col) */
    int getCount(int row, int col);

public:

    /** \brief Operator << overloading
     *
     *  **Students will need** to alter this function to display the
     *  plus signs (+) next to the cells that belong to
     *  a counted colony.
     */
    friend std::ostream& operator<<(std::ostream& stream, const grid& ob);

private:
    /** \brief Calculates a number of units for the cluster determined by coordinates (\a row, \a col) 
     *  \returns the cluster size 
     *
     *  This routine should use a divide and conquer recursive approach to solve the problem. 
     *  This means you will have two or more recursive calls in function \a grid::count(). 
     *  To correctly complete function \a grid::count(), **student will have** to add additional 
     *  data members and/or functions to class grid.
     */
    int count(int row, int col);

    /** \brief Return the number of units for a given cell (\a row, \a col)
     *
     *  Students do not need to alter the function
     */
    int indexOf(int row, int col) const;

    bool checkIndex(int row, int col) const;        ///< returns true, if a given index is in a range, false otherwise

    /** \brief Returns true, if a gven cell (\a row, \a col) is infected, false otherwise
     *
     *  Students do not need to alter the function
     */
    bool isInfected(int row, int col) const;

    /**
     * Returns true, if a given cell is visited, false otherwise
     */
    bool isVisited(int row, int col) const;

private:
    std::vector<std::pair<bool, bool>> _area;
    int _rows;
    int _cols;

}; // class grid



#endif // XI_ASSESSING_INFECTION_GRID_H
