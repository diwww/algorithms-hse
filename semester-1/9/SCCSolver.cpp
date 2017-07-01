// Name: Surovtsev Maxim
// Group: BSE151


#include "SCCSolver.h"
#include <algorithm>
#include <stdexcept>


/**
 * Public SCCSolver methods
 */

// Vertex?
Vertice::Vertice(int id)
{
    this->id = id;
}

void Vertice::refresh()
{
    discovered_step = -1;
    finished_step = -1;
    passed = false;
}

bool Vertice::compare(Vertice *v1, Vertice *v2)
{
    return v1->finished_step > v2->finished_step;
}

void SCCSolver::initialize(std::vector<int> *adjList, int n)
{
    if (adjacencyList != nullptr)
    {
        delete[] adjacencyList;
        adjacencyList = nullptr;
    }

    adjacencyList = new std::vector<int>[n];
    nVertices = n;

    // Copy array to avoid sharing
    for (int i = 0; i < n; ++i)
    {
        adjacencyList[i] = adjList[i];
    }

    buildPool();
    solved = false;
    initialized = true;
}

void SCCSolver::solve()
{
    if (!initialized)
        throw std::logic_error("Not initialized yet.");

    runDFS();
    // Transpose adjList and delete old one
    std::vector<int> *oldAdjList = adjacencyList;
    adjacencyList = reverseAdjacencyList(adjacencyList, nVertices);
    delete[] oldAdjList;
    sortPool();
    refreshPool();
    result = runDFS();
    solved = true;
}

std::vector<int> *SCCSolver::reverseAdjacencyList(std::vector<int> *adjList, int n)
{
    std::vector<int> *temp = new std::vector<int>[n];
    for (int i = 0; i < n; ++i)
    {
        for (int j : adjList[i])
            temp[j].push_back(i);
    }
    return temp;
}

std::vector<std::vector<int>> SCCSolver::getResult()
{
    if (!solved)
        throw std::logic_error("Not solved yet.");
    return result;
}

bool SCCSolver::isSolved()
{
    return solved;
}

bool SCCSolver::isInitialized()
{
    return initialized;
}

// I had to remove braces in destructor declaration
SCCSolver::~SCCSolver()
{
    if (adjacencyList != nullptr)
    {
        delete[] adjacencyList;
        adjacencyList = nullptr;
    }
    if (vertPool.size() > 0)
    {
        for (Vertice *i: vertPool)
            delete i;
        vertPool.clear();
    }
}


/**
 * Private SCCSolver methods
 */

void SCCSolver::buildPool()
{
    if (vertPool.size() == 0)
    {
        for (int i = 0; i < nVertices; ++i)
            vertPool.push_back(new Vertice(i));
    }
    else
    {
        // Reallocate memory for the pool
        for (Vertice *i: vertPool)
            delete i;
        vertPool.clear();
        buildPool();
    }
}

void SCCSolver::sortPool()
{
    std::sort(vertPool.begin(), vertPool.end(), Vertice::compare);
}

std::vector<std::vector<int>> SCCSolver::runDFS()
{
    int step = 0;

    std::vector<std::vector<int>> forest;

    // Scan every vertex
    for (int i = 0; i < nVertices; ++i)
    {
        if (!vertPool[i]->passed)
        {
            std::vector<int> tree;
            DFSVisit(vertPool[i], step, tree);
            forest.push_back(tree);
        }
    }

    return forest;
}

void SCCSolver::DFSVisit(Vertice *v, int &step, std::vector<int> &tree)
{
    v->discovered_step = ++step;
    v->passed = true;
    tree.push_back(v->id);

    // Scan every vertex neighbour
    for (int i : adjacencyList[v->id])
    {
        Vertice *tmp = getVertice(i);
        if (!tmp->passed)
        {
            DFSVisit(tmp, step, tree);
        }
    }

    v->finished_step = ++step;
}

void SCCSolver::refreshPool()
{
    for (int i = 0; i < nVertices; ++i)
    {
        vertPool[i]->refresh();
    }
}

Vertice *SCCSolver::getVertice(int id)
{
    for (Vertice *i : vertPool)
    {
        if (i->id == id)
            return i;
    }
}
