// Name: Surovtsev Maxim
// Group: BSE151


#include <stdexcept>
#include "bellman_ford.h"
#include <algorithm>


////--------------- Utility stuff ---------------////

struct Vertex
{
    int id = -1;
    int weight = INT32_MAX;
    Vertex *parent = nullptr;

    Vertex()
    {}

    Vertex(int i)
    {
        id = i;
    }
};

std::vector<Vertex *> vertices;

// Min cost
int mCost = 0;
// Id of vertex within the path,
// which contains negative cycle
int cycleV = -1;

bool relax(Edge edge)
{
    Vertex *from = vertices[edge.from - 1];
    Vertex *to = vertices[edge.to - 1];

    if (from->weight < INT32_MAX)
        if (to->weight > from->weight + edge.cost)
        {
            // Calculate minCost
            mCost = (from->weight + edge.cost) - to->weight;
            // Exclude overflow
            to->weight = std::max(from->weight + edge.cost, INT32_MIN);
            to->parent = from;
            cycleV = to->id;
            return true;
        }
    return false;
}


////--- Bellman-Ford algorithm implementation ---////

void BellmanFord::initialize(int **array, int n, int m, int startV)
{
    start = startV;
    numEdges = n;
    numVertexes = m;
    mCost = minCost = 0;
    cycleV = -1;

    // Path reallocation
    if (path != nullptr)
    {
        delete[] path;
        path = nullptr;
    }
    path = new std::vector<int>[numVertexes];

    // Graph reallocation
    if (graph.size() != 0)
    {
        graph.clear();
    }
    for (int i = 0; i < numEdges; ++i)
    {
        Edge e;
        e.from = array[i][0];
        e.to = array[i][1];
        e.cost = array[i][2];

        graph.push_back(e);
    }

    // Vertices reallocation
    if (vertices.size() != 0)
    {
        for (Vertex *v:vertices)
            delete v;
        vertices.clear();
    }
    for (int i = 1; i <= numVertexes; ++i)
    {
        vertices.push_back(new Vertex(i));
    }
    vertices[start - 1]->weight = 0;

    initialized = true;
}

bool BellmanFord::isInitialized()
{
    return initialized;
}

void BellmanFord::solve()
{
    if (!initialized)
        throw std::logic_error("Not initialized yet.");

    // If Nth iteration relaxes edge,
    // there is negative cycle
    for (int i = 0; i < numVertexes; ++i)
    {
        for (Edge edge : graph)
            isNegative = relax(edge);
    }

    if (isNegative)
        solveNegative();
    else
        solvePositive();
}

void BellmanFord::solveNegative()
{
    Vertex *vertex = vertices[cycleV - 1];
    // Find vertex within the cycle
    for (int i = 0; i < numVertexes; ++i)
    {
        vertex = vertex->parent;
        cycleV = vertex->id;
    }

    minCost = mCost;
    do
    {
        // Negative cycle will be placed
        // in the 0th cell of path,
        // other cells will be empty
        path[0].push_back(vertex->id);
        vertex = vertex->parent;
    } while (vertex->id != cycleV);
    // Reverse vector to show it properly
    std::reverse(path[0].begin(), path[0].end());
}

void BellmanFord::solvePositive()
{
    for (int i = 0; i < numVertexes; ++i)
    {
        Vertex *vertex = vertices[i];
        // For start or unreachable vertex
        // there will be empty vector
        if (vertex->weight == INT32_MAX || vertex->id == start)
            continue;
        // Build path by going though
        // every vertex parent
        while (vertex->parent != nullptr)
        {
            path[i].push_back(vertex->id);
            vertex = vertex->parent;
        }
        path[i].push_back(vertex->id);
        // Reverse vector to show it properly
        std::reverse(path[i].begin(), path[i].end());
    }
}

int BellmanFord::getCost()
{
    return minCost;
}

std::vector<int> *BellmanFord::getPath()
{
    // Copy path
    std::vector<int> *temp = new std::vector<int>[numVertexes];
    for (int i = 0; i < numVertexes; ++i)
    {
        temp[i] = path[i];
    }

    return temp;
}

BellmanFord::~BellmanFord()
{
    if (path != nullptr)
    {
        delete[] path;
        path = nullptr;
    }

    if (vertices.size() != 0)
    {
        for (Vertex *v:vertices)
            delete v;
        vertices.clear();
    }
}