
#ifndef _bddBdd_h
#define _bddBdd_h

#include <vector>
#include <set>
#include <map>
#include <iostream>

#include <cassert>
#include <cstdlib>

using namespace std;


// BDD node
struct bddNode
{
    // To mark the node in garbage collection and node count
    unsigned mark:1;
    // Variable id. The ids of variables are multiples of 1, starting with 0!
    unsigned var:31;
    // Index of low son. Also used for linking unused nodes in the node array.
    unsigned low;
    // Index of high son.
    unsigned high;
    // Next node in mUniqueHash-list (0 for end of list).
    unsigned next;
};

// Cache entry for binary operations
struct bddBinEntry
{
    // Identifier of the operation
    unsigned op;
    // First argument of the operation
    unsigned root1;
    // Second argument of the operation
    unsigned root2;
    // Result of the operation
    unsigned result;
};

// One Binary Decision Diagram
// and static data structures of the whole Shared BDD package
class toyBDD
{
private: // Constants.

    // Identifiers of the operations in the cache (mBinCache).
    enum Operation
    {
        mComplement = 1, mRenameVars, mExists,
        mUnite, mIntersect, mSetContains
    };

private: // Static attributes.

    // Node Array.
    // mNodes[0] is the 0-terminal, mNodes[1] is the 1-terminal.
    // Both are always marked (mark == 1) and have the variable id -1.
    static bddNode* mNodes;
    // Number of elements of mNodes.
    static unsigned mMaxNodeNr;
    // Index of the first unused node in mNodes.
    // Unused nodes are linked using their low-element.
    static unsigned mFree;

    // Hash table of all used nodes.
    // Used by insert to ensure that mNodes contains no two equal nodes.
    // mUniqueHash[i] contains the index of first node of a list of all nodes
    // with hash value i. Lists are linked by the next-element of the nodes.
    static unsigned* mUniqueHash;
    // Number of elements of mUniqueHash == 2^mUniqueHBitNr == 1<<mUniqueHBitNr.
    static unsigned mUniqueHBitNr;
    // Cache for the results of binary operations.
    static bddBinEntry* mBinCache;
    // Number of elements of mBinCache == 2^mBinCBitNr.
    static unsigned mBinCBitNr;

private: // Private static methods.

    // Hash/cache functions with 1 and 3 arguments.
    // Possible return values: 0..(1<<hashBitNr)-1.
    static inline unsigned hash(unsigned p1, unsigned p2, unsigned p3, unsigned pHashBitNr);

    // Ensures that p1 <= p2.
    static inline void normalize(unsigned& p1, unsigned& p2);

    // Returns the mNodes-index of the node with the passed var-, low- and
    // high-values. If such node does not exists, it is inserted into
    // mNodes and mUniqueHash. If there are no free nodes left, throws exception.
    static unsigned insert(unsigned pVar, unsigned pLow, unsigned pHigh);

    // Prints BDD with root pRoot as reduced binary decision tree.
    static void print_(ostream& pS, unsigned pRoot);

    static unsigned applyBinary(unsigned pRoot1, unsigned pRoot2, Operation op);

    // Like the equally named non-static functions,
    // except that the static versions do not catch exceptions.
    static unsigned complement_(unsigned pRoot);

    static unsigned unite_(unsigned pRoot1, unsigned pRoot2);

    static unsigned intersect_(unsigned pRoot1, unsigned pRoot2);

    static unsigned exists_(unsigned pRoot, unsigned pVar);

public: // Public static methods.

    // Initialisation of BDD package. Must be called before any other
    // function of the package is used.
    // Parameters: Values for the m... variables.
    //   number of elements of mNodes == pNodes,
    //   number of elements of mUniqueHash == 2^pUniqueHBitNr,
    //   number of elements of mBinCache == 2^pBinCBitNr.
    static void init(unsigned pMaxNodeNr, unsigned pUniqueHBitNr, unsigned pBinCBitNr);

    // Frees memory used by the static data structures.
    // To be called after use of the BDD package.
    static void done();

private: // Attributes.

    // Index (in mNodes) of the Root node of the BDD.
    unsigned mRoot;

public: // Constructors and destructor.

    // Creates BDD with root pRoot.
    toyBDD(unsigned pRoot = 0)
    {
        mRoot = pRoot;
    }

    // Creates BDD as a copy of pBdd.
    toyBDD(const toyBDD& pBdd)
    {
        mRoot = pBdd.mRoot;
    }

    // Creates BDD that assign the bit value 'pValue' to the variable 'pVarId'.
    toyBDD(unsigned pVarId, bool pValue);

    static unsigned bddBdd_(unsigned pVarId, bool pValue);

    // Creates BDD that assign bit values of 'pValue'
    //   to 'pBitNr' variables beginning at position 'pVarId'.
    toyBDD(unsigned pVarId, unsigned pBitNr, unsigned pValue);

    static unsigned bddBdd_(unsigned pVarId, unsigned pBitNr, unsigned pValue);

    // Creates BDD for pVarId1 == pVarId2.
    toyBDD(unsigned pVarId1, unsigned pVarId2);

    static unsigned bddBdd_(unsigned pVarId1, unsigned pVarId2);

    ~toyBDD()
    {}

    // Assignment operator.
    toyBDD& operator=(const toyBDD& aBdd);

public: // Accessors.

    // Prints BDD as reduced binary decision tree.
    void print(ostream& pS) const
    {
        print_(pS, mRoot);
        cout << endl;
    }

public: // Service methods.

    // Computes complement.
    void complement();

    // Unites with pBdd.
    void unite(const toyBDD& pBdd);

    // Intersects with pBdd.
    void intersect(const toyBDD& pBdd);

    // Existantial quantification of the variable pVar.
    void exists(unsigned pVar);

};

#endif
