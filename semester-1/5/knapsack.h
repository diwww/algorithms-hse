/**
 * The current assessment is to implement three different solutions of Knapsack Problem.
 * The idea might seem a bit not clear for the first time, but spend some time on
 * understanding the fundamentals of the algorithm. After you really understand how
 * the algorithm works, it will be really easy to implement all methods that are
 * presented here.
 *
 * The only file that you need to upload for the assessment is knapsack.cpp - your
 * implementation for current header file.
 *
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * You should consider the following descriptions of the methods and find out
 * how they should interact with each other.
 *
 * Then you need to create knapsack.cpp file and implement all declared functions from here.
 *
 * If you need some additional functions to implement - be free to add them to your knapsack.cpp
 * file (not knapsack.h file!). In fact, that will be appreciated if it is used properly.
 *
 * Your knapsack.cpp file MUST be compatible with this version of current file. So, again:
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * All methods should be implemented and all of them should be used in your work.
 *
 * You should consider that all methods should work in isolation and all of them MUST NOT affect any
 * system state (i.e. static fields and so on).
 *
 * Don't provide any "int main()" method in your knapsack.cpp file. You can create it for self
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

#ifndef P5_KNAPSACK_KNAPSACK_H
#define P5_KNAPSACK_KNAPSACK_H

class Knapsack {
public:
    /**
     * A default constructor. You should not implement it.
     */
    Knapsack() {};

    // You SHOULD implement all the methods declared below

    /**
     * A method to initialize data for knapsack problem solution.
     * Don't forget to reset all fields that should be reset and free all the memory that should be freed!
     * @param capacity Maximal capacity of a knapsack
     * @param weights An array of n_items elements containing weights of items given
     * @param costs An array of n_items elements containing costs of items given
     * @param n A number of items given
     *
     * // !! it is a postcondition -- the conditiion that should be fulfilled AFTER the method is executed
     * @post weights, costs, nItems and maxCapacity are initialized with given values
     * isInitialized() is true
     * isSolved() is false
     *
     * Also, this is IMPORTANT not to modify the array that is passes as a parameter.
     * That doesn't mean that you should store that array in such way that is passed,
     * but to copy it to the internal storage.
     */
    void initialize(const int capacity, const int* weights, const int* costs, const int n);

    /**
     * Whether initialize() method was called yet
     * @return true if initialize() was called, false otherwise
     */
    bool isInitialized();

    /**
     * Whether the backpack problem on gived data is solves yet
     * @return true if it is, false otherwise
     */
    bool isSolved();

    /**
     * A method to solve knapsack recursively
     * Don't forget to free memory of grid and itemset before executing the algorithm if they are not nullptr!
     *
     * // !! it is a precondition -- the conditiion that should be fulfilled BEFORE the method is executed
     * @pre weights, costs, nItems and maxCapacity are initialized
     * @post grid, bpWeight, bpCost, itemSet are filled with values calculated during algorithm executing.
     * isSolved() is true
     *
     * // Don't forget about exceptions!
     * // std::logic_error from <stdexcept>
     * @throws logic_error if called before initialize()
     */
    void solveRecursively();

    /**
     * A method to solve knapsack iteratively
     * Don't forget to free memory of grid and itemset before executing the algorithm if they are not nullptr!
     *
     * @pre weights, costs, nItems and maxCapacity are initialized
     * @post grid, bpWeight, bpCost, itemSet are filled with values calculated during algorithm executing.
     * isSolved() is true
     *
     * @throws logic_error if called before initialize()
     */
    void solveIteratively();


    /**
     * A method to solve knapsack iteratively
     * Don't forget to free memory of itemset before executing the algorithm if it is not nullptr!
     *
     * @pre weights, costs, nItems and maxCapacity are initialized
     * @post grid, bpWeight, bpCost, itemSet are filled with values calculated during algorithm executing.
     * isSolved() is true
     *
     * @throws logic_error if called before initialize()
     */
    void solveGreedy();

    /**
     * A method to receive eventual weight of the knapsack after solving the problem
     * @return eventual weight of the knapsack
     * @throws logic_error if called before solving the problem
     */
    int getWeight();

    /**
     * A method to receive eventual weight of the knapsack after solving the problem
     * @return eventual weight of the knapsack
     * @throws logic_error if called before solving the problem
     */
    int getCost();

    /**
     * A method to receive eventual set of items in the knapsack
     * @return set of items in the knapsack presentes as boolean array
     * where the i-th element of the array is true if the i-th item was chosen
     * @throws logic_error if called before solving the problem
     *
     *  !!NB: if you return the itemset field itself, it will be deleted once the object of Knapsack destroyed.
     *  So you need to return a copy of this array.
     */
    bool* getItemset();

    /**
     * Destructor frees all the memory that was allocated by the object and not freed before its destruction.
     */
    ~Knapsack();

private:

    /**
     * A method used by solveRecursively() and solveIteratively()
     * It builds initial grid: an array of arrays NxM where
     * N = nItems + 1
     * M = maxCapacity + 1
     *
     * The first row and the first column of the grid are filled with zeros
     * All other elements should be -1
     *
     * @post grid is initialized as described above
     */
    void buildGrid();

    /**
     * A method used by solveRecursively() to calculate elements in grid.
     * If grid[item][capacity] is already calculated, it is returned.
     * Otherwise, it is calculated recursively,
     * 
     * @return if (item < 1 || capacity < 1) => 0
     * otherwise => If grid[item][capacity]
     *
     * @post if !(item < 1 || capacity < 1) => (grid[item][capacity] != -1)
     */
    int getFromGrid(int item, int capacity);

    /**
     * A method used by solveRecursively() and solveIteratively() to backtrack the items according to grid.
     *
     * @post itemset is filled according to the set of items chosen
     */
    void backtrack();

    /** A grid that is to be fulfilled during execution of solveRecursively or solveIteratively
     * Presented as a pointer-to-pointer (or an array-of-arrays where
     * number of rows is a (number of items in the initial set) + 1
     * number of columns is a (maximum capacity of the knapsack) + 1
     * */
    int** grid = nullptr;

    /**
     * An array containing weights of initial itemset
     * The size of the array is a number of items in the initial set
     */
    int* weights = nullptr;

    /**
     * An array containing costs of initial itemset
     * The size of the array is a number of items in the initial set
     */
    int* costs = nullptr;

    /**
     * A number of itens in the initial itemset.
     */
    int nItems = -1;

    /**
     * A maximal capacity of the backpack.
     */
    int maxCapacity = -1;

    /**
     * The eventual weight of the knapsack
     * that is calculated by solveRecursively(), solveIteratively() or solveGreedy()
     */
    int bpWeight = -1;

    /**
     * The eventual cost of the knapsack
     * that is calculated by solveRecursively(), solveIteratively() or solveGreedy()
     */
    int bpCost = -1;

    /**
     * A boolean array that contains information aboud which items were put into the knapsack
     * The size of the array is a number of items in the initial set
     * i-th element of the array is true if the i-th item was chosen and false otherwise
     */
    bool* itemset = nullptr;

    bool initialized = false;

    bool solved = false;

};

#endif P5_KNAPSACK_KNAPSACK_H
