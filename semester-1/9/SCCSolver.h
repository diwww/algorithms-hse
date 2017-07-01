/**
 * The current assessment is to implement an algorithm to find all the strongly connected components in an oriented graph.
 * Chapter 22.5 of Cormen's Introduction to algorithms can be useful in the completing of this task.
 *
 * The only file that you need to upload for the assessment is SCCSolver.cpp - your
 * implementation for current header file.
 *
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * You should consider the following descriptions of the methods and find out
 * how they should interact with each other.
 *
 * Then you need to create SCCSolver.cpp file and implement all declared functions from here.
 *
 * If you need some additional functions to implement - be free to add them to your SCCSolver.cpp
 * file (not SCCSolver.h file!). In fact, that will be appreciated if it is used properly.
 *
 * Your SCCSolver.cpp file MUST be compatible with this version of current file. So, again:
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
 *
 * NOTE: There are some disclaimers in comments about possible values that are passed to the methods.
 * These comments like "Non-negative integer value" or "Strictly positive integer value" are just
 * some hints for you to be aware of possible values that can be passed to your method.
 * In other words, if there is a comment that the input parameter is strictly positive we will not
 * test that method with negative values of this parameter so you don't need to consider such cases.
 * In practice, such comments are widely used in API design where you do not guarantee correct behavior
 * in case of wrong parameters (which would be a nonsense if you do).
 */

#ifndef SCCSOLVER_SCCSOLVER_H
#define SCCSOLVER_SCCSOLVER_H


#include <vector>

/**
 * A class representing a vertice of a graph used for Deep First Search (DFS)
 */
class Vertice
{
public:
    /**
     * Constructor
     * @param id an identifyer of the vertice
     */
    Vertice(int id);

    /**
     * Set the original values to all the fields axcept id.
     * @post discovered_step == -1; finished_step == -1; passed == false;
     */
    void refresh();

    /**
     * A static comparator that you will need for the implementation of SCCSolver.
     * Try to understand how it should work yourself
     * For more inpormation about c++ comparators see documentation for std::sort function
     * @param v1 first vertice
     * @param v2 second vertice
     */
    static bool compare(Vertice *v1, Vertice *v2);

    // indentifier of the vertice
    int id;

    // step on which it was discovered during DFS
    int discovered_step = -1;

    // step on which DFS left it's subtree
    int finished_step = -1;

    // Has DFS already seen this vertice.
    bool passed = false;
};

class SCCSolver
{

public:
    /**
     * Default constructor. You should not implement it.
     */
    SCCSolver()
    {}

    /**
     * Initialization method
     * Note that it can be called multiple times so don't forget about memory deallocation
     * Also, the pointer to the array shuold not be shared between the object of SCCSolver and the exterior program.
     * @param adjList an ARRAY of vectors: adjacency list of a graph
     * @param n number of vertives in graph
     * @post initialized == true; solved == false;
     */
    void initialize(std::vector<int> *adjList, int n);


    /**
     * Main solving method.
     * @pre initialize == true;
     * @throws logic_error if called before initialization
     */
    void solve();

    /**
     * Reverse all edges in the graph.
     * @param adjList initial adjacency list
     * @param n |V|
     * @return adjacency list of the reversed graph
     */
    static std::vector<int> *reverseAdjacencyList(std::vector<int> *adjList, int n);


    /**
     * receive a vector of vectors where each vectos is a set representing a strongly connected component
     * @return set of SCC's
     * @throws logic_error if called before solving
     */
    std::vector<std::vector<int>> getResult();

    /**
     * @return true if the problem for a given graph is solved; otherwise false
     */
    bool isSolved();

    /**
    * @return true if the object was initialized; otherwise false
    */
    bool isInitialized();

    /**
     * Destructor, don't forget to free all the allocated memory
     */
    ~SCCSolver();


private:
    /**
     * Fill the vertPool with all the vertices from a graph
     * This method has nothing to do with the edges of the graph.
     * @pre adjacencyList is initialized
     * @post vertPool is initialized
     */
    void buildPool();

    /**
     * run DFS on the given graph using the adjacencyList and vertPool
     * @return a vector of vectors, where each of them represents a "tree" built during the DFS
     * @pre adjacencyList and vertPool are initialized
     * @post result is initialized
     */
    std::vector<std::vector<int>> runDFS();

    /**
     * recursive method to run DFS starting from the given vertice
     * @param v vertice
     * @param step step counter
     * @param tree a set of vertites of the tree tree of the given DFS
     * (eventually one of the elements of runDFS return value)
     * @pre adjacencyList and vertPool are initialized
     */
    void DFSVisit(Vertice *v, int &step, std::vector<int> &tree);

    /**
     * sorts a vectorPool by v.finished_step
     * @pre vertPool is initialized
     * @post vectorPool is sorted
     */
    void sortPool();

    /**
     * refresh each vertice in the vertPool
     * @pre vertPool is initialized
     * @post vectorPool is refreshed
     */
    void refreshPool();

    /**
     * receive a pointer to a Vertice from vertPool with a given id
     * @param id
     * @return Vertice v: v.id == id
     * @pre vertPool is initialized
     */
    Vertice *getVertice(int id);

    /**
     * is the problem solved
     */
    bool solved = false;

    /**
     * is the problem initialized
     */
    bool initialized = false;

    /**
     * Number of vertices in the graph
     */
    int nVertices;

    /**
     * Vector of all vertices in the graph
     */
    std::vector<Vertice *> vertPool;

    /**
     * vector of vectors representing SCCs of the graph
     */
    std::vector<std::vector<int>> result;

    /**
     * an ajacency list of the graph
     */
    std::vector<int> *adjacencyList = nullptr;


};


#endif //SCCSOLVER_SCCSOLVER_H
