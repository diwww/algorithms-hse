// Name: Surovtsev Maxim
// Group: BSE151


#include "eight_queen.h"
#include <stdexcept>
#include <iostream>


// The board cell can contain 0 or 1
// 1: there is a queen in the cell
// 0: there is no queen in the cell


// Utility method for
// printing the board
void printBoard(int **board, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void QueenProblem::initialize(const int size)
{
    this->size = size;

    // Initializing the board
    board = new int *[size];
    for (int i = 0; i < size; ++i)
    {
        board[i] = new int[size](); // fill with zeros
    }

    initialized = true;
    solved = false;
}

bool QueenProblem::isInitialized()
{
    return initialized;
}

bool QueenProblem::isSolved()
{
    return solved;
}

void QueenProblem::backtracking(int queen)
{
    if (!initialized)
        throw std::logic_error("The board is not initialized.");

    // If all queens are already placed,
    // the problem is solved
    if (queen == size)
    {
        numberOfSolutions++;
        // Uncomment to show the board
//        printBoard(board, size);
        return;
    }

    // Moving row wise
    for (int i = 0; i < size; ++i)
    {
        if (isInserted(i, queen))
        {
            // Insert the queen
            board[i][queen] = 1;
            // Move to the next column
            backtracking(queen + 1);
            // After recursive call is done
            // set the cell value to 0 again
            board[i][queen] = 0;
        }
    }

    // I suppose, that the problem is solved
    // even when there are no solutions.
    // So for size = 2 the output will be 0
    // instead of thrown exception.
    solved = true;
}

bool QueenProblem::isInserted(int queen_row, int queen_col)
{
    // Check if the current row
    // is safe to place the queen
    for (int i = 0; i < queen_col; i++)
    {
        if (board[queen_row][i] == 1)
            return false;
    }

    // Check if the upper diagonal
    // is safe to place the queen
    for (int i = queen_row, j = queen_col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
            return false;
    }

    // Check if the lower diagonal
    // is safe to place the queen
    for (int i = queen_row, j = queen_col; j >= 0 && i < size; i++, j--)
    {
        if (board[i][j] == 1)
            return false;
    }

    return true;
}

long QueenProblem::getNumberOfSolutions()
{
    if (!solved)
        throw std::logic_error("The problem is not solved.");

    return numberOfSolutions;
}

QueenProblem::~QueenProblem()
{
    // Deleting the board
    if (board != nullptr)
    {
        for (int i = 0; i < size; ++i)
        {
            delete[] board[i];
        }
        delete[] board;
        board = nullptr;
    }
}