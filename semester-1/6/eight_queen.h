/**
 * The current assessment is to implement different algorithms of Eight Queen task.
 * The idea might seem a bit not clear for the first time, but spend some time on
 * understanding the fundamentals of the algorithm. After you really understand how
 * the algorithm works, it will be really easy to implement all methods that are
 * presented here.
 *
 * The only file that you need to upload for the assessment is eight_queen.cpp - your
 * implementation for current header file.
 *
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * You should consider the following descriptions of the methods and find out
 * how they should interact with each other.
 *
 * Then you need to create eight_queen.cpp file and implement all declared functions from here.
 *
 * If you need some additional functions to implement - be free to add them to your eight_queen.cpp
 * file (not eight_queen.h file!). In fact, that will be appreciated if it is used properly.
 *
 * Your eight_queen.cpp file MUST be compatible with this version of current file. So, again:
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * All methods should be implemented and all of them should be used in your work.
 *
 * You should consider that all methods should work in isolation and all of them MUST NOT affect any
 * system state (i.e. static fields and so on).
 *
 * Don't provide any "int main()" method in your eight_queen.cpp file. You can create it for self
 * testing in another separate file.
 *
 * Don't forget about comments and good coding style, which will be appreciated.
 *
 * NOTE: There are some disclaimers in comments about possible values that are passed to the methods.
 * These comments like "Non-negative integer value" or "Strictly positive integer value" are just
 * some hints for you to be aware of possible values that can be passed to your method.
 * In other words, if there is a comment that the input parameter is strictly positive we will not
 * test that method with negative values of this parameter so you don't need to consider such cases.
 * In practice, such comments are widely used in API design where you do not guarantee correct behavior
 * in case of wrong parameters (which would be a nonsense if you do).
 */

#include <vector>

/*
 * Class to have a functions to solve queen problem.
 */
class QueenProblem {
public:
    /**
     * A deafault constructor. You should not implement it.
     */
    QueenProblem() {};

    // You SHOULD implement ALL the methods declared below

    /**
     * A method to initialize data for knapsack problem solution.
     * Don't forget to reset all fields that should be reset and free all the memory that should be freed!
     * @param size A number of square size given
     *
     * // !! it is a postcondition -- the conditiion that should be fulfilled AFTER the method is executed
     * @post size, board are initialized with given values
     * isInitialized() is true
     * isSolved() is false
     *
     */
    void initialize(const int size);

    /**
     * Whether initialize() method was called yet
     * @return true if initialize() was called, false otherwise
     */
    bool isInitialized();

    /**
     * Whether the queen problem on gived data is solves yet
     * @return true if it is, false otherwise
     */
    bool isSolved();

    /**
     * A method to solve queen problem recursively
     *
     * // !! it is a precondition -- the conditiion that should be fulfilled BEFORE the method is executed
     * @pre size, board are initialized
     * @param queen current queen, which we want to insert
     * @post board, numberOfSolutions are filled with values calculated during algorithm executing.
     * Don't forget to free memory of board and itemset before executing the algorithm if they are not nullptr!
     * isSolved() is true
     *
     * // Don't forget about exceptions!
     * // std::logic_error from <stdexcept>
     * @throws logic_error if called before initialize()
     */
    void backtracking(int queen);


    /**
     * One of the main method
     * Whether the queen could be done on the board in point (queen_row, queen_col)
     * @param queen_col, queen_row checking position of queen
     * @return true if it is, false otherwise
     */

    bool isInserted(int queen_row, int queen_col);


    /**
     * A method to receive eventual number of the solutions after solving the problem
     * @return numberOfSolutions eventual number of solutions
     * @throws logic_error if called before solving the problem
     */
    long getNumberOfSolutions();


    /**
     * Destructor frees all the memory that was allocated by the object and not freed before its destruction.
     */
    ~QueenProblem();

private:

    /* A board that is to be fulfilled during execution of backtracking
     * You can fill board only by an int numbers, so feel free to choose
     * a number of empty square and a number of queen's square.
     * Array's is size x size
     * */
    int** board = nullptr;

    /**
     * The size of the board
     */
    int size = 0;

    /**
     * The number of solutions
     */
    long numberOfSolutions = 0;

    bool initialized = false;

    bool solved = false;

};