/**
 * The current assessment is to implement a Bellman & Ford algorithm to find all the shortest paths from a single source
 * vertex to all of the other vertices in a weighted digraph. You should provide 2 diffenet solving methods
 * for different graphs: with and without negative cycle(s)
 * The only file that you need to upload for the assessment is bellman_ford.cpp - your
 * implementation for current header file.
 *
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * You should consider the following descriptions of the methods and find out
 * how they should interact with each other.
 *
 * Then you need to create bellman_ford.cpp file and implement all declared functions from here.
 *
 * If you need some additional functions to implement - be free to add them to your bellman_ford.cpp
 * file (not bellman_ford.h file!). In fact, that will be appreciated if it is used properly.
 *
 * Your bellman_ford.cpp file MUST be compatible with this version of current file. So, again:
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * All methods should be implemented and all of them should be used in your work.
 *
 * You should consider that all methods should work in isolation and all of them MUST NOT affect any
 * system state (i.e. static fields and so on).
 *
 * Don't provide any "int main()" method in your SCCSolver.cpp file. You can create it for self
 * testing in another separate file.
 *
 * Don't forget about comments and good coding style, which will be appreciated.
 */

#ifndef BELLMANFORD_BELLMAN_FORD_H
#define BELLMANFORD_BELLMAN_FORD_H

#include <vector>
/**
 * A structure of graph. It looks like: the first node (from), the second node (to) and the weight of this way (cost)
 */
struct Edge {

    /**
     * First node
     */
    int from;

    /**
     * Second node
     */
    int to;

    /**
     * Cost of way between @param from and @param to
     */
    int cost;

};

/**
 * A class representing Bellmman & Ford solution
 */

class BellmanFord {

public:

    /**
     * Default constructor. You should not implement it.
     */
    BellmanFord () {};

    /**
     * Initialization method
     * Note that it can be called multiple times so don't forget about memory deallocation
     * Also, the pointer to the array shuold not be shared between the object of SCCSolver and the exterior program.
     * @param n the number of edges
     * @param m the number of vertixes
     * @param array size of array @param n x 3, first colomn is @param from (struct Edge) node,
     * second colomn is @param to (struct Edge) node, third colomn is @param cost (struct Edge) - weight of way
     * @param startV vertex start
     * @post initialized == true
     */
    void initialize(int** array, int n, int m, int startV);

    /**
    * @return true if the object was initialized; otherwise false
    */
    bool isInitialized();

    /**
     * General method of solving. You should choose between solvePositive and solveNegative
     * @pre initialize == true;
     * @throws logic_error if called before initialization
     */
    void solve();

    /**
     * The solving method with negative cycle(s)
     */
    void solveNegative();

    /**
     * The solving method without negative cycle(s)
     */
    void solvePositive();

    /**
     * @return minimum cost of way from start vertex
     */
    int getCost();

    /**
     * @return array of vectors<int> which paths sorted by the smallest to biggest costs
     */
    std::vector<int>* getPath();

    /**
     * Destructor, don't forget to free all the allocated memory
     */
    ~BellmanFord();

private:

    /**
     * The starting vertex
     */
    int start;

    /**
     * The number of vertexes
     */
    int numVertexes;

    /**
     * The number of edges
     */
    int numEdges;

    /**
     * The representation of the input graph (list of vertex)
     */
    std::vector<Edge> graph;

    /**
     * Flag for negative cycle
     */
    bool isNegative = false;

    /**
     * The ARRAY of vectors<int> - all paths with the lowest cost
     */
    std::vector<int>* path;

    /**
     * The costs minimum after Bellman-Ford implementation
     */
    int minCost;

    /**
     * is the problem initialized
    */
    bool initialized = false;


};

#endif //BELLMANFORD_BELLMAN_FORD_H