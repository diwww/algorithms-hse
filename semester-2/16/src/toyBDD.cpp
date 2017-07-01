#include "toyBDD.h"

#include <cstring>
#include <limits>

bddNode* toyBDD::mNodes = 0;
unsigned toyBDD::mMaxNodeNr;
unsigned toyBDD::mFree;

unsigned* toyBDD::mUniqueHash = 0;
unsigned toyBDD::mUniqueHBitNr;
bddBinEntry* toyBDD::mBinCache = 0;
unsigned toyBDD::mBinCBitNr;

/////////////////////////////////////////////////////////////////
// Ensures that p1 <= p2.
inline void
toyBDD::normalize(unsigned& p1, unsigned& p2)
{
    if (p1 > p2)
    {
        unsigned tmp = p1;
        p1 = p2;
        p2 = tmp;
    }
}

// Hash functions.
inline unsigned toyBDD::hash(unsigned i, unsigned j, unsigned k, unsigned hashBitNr)
{
    unsigned mask = (1u << hashBitNr) - 1;
    j ^= 0x55555555;   // XOR.
    return (i +
            (j << (hashBitNr >> 1)) + (j >> (hashBitNr >> 1)) +
            (k << (hashBitNr >> 2)) + (k >> (hashBitNr >> 2))) & mask;
}

// Additional hash functions for comparison.
/*
inline unsigned toyBDD::hash(unsigned i, unsigned j, unsigned hashBitNr) {
  unsigned mask = (1u << hashBitNr) - 1;
  return (i + ((j ^ 0x55555555)<<(hashBitNr>>1)) +
    (j<<(hashBitNr>>2)) + (j>>(hashBitNr>>2))) & mask;
}

inline unsigned toyBDD::hash(unsigned i, unsigned j, unsigned hashBitNr) {
  return ((i * 17765507 + j) * 9243337) >> (32-hashBitNr);
}

inline unsigned toyBDD::hash(unsigned i, unsigned j, unsigned k, unsigned hashBitNr) {
  return (((i * 14099753 + j) * 9243337 + k) * 3901787) >> (32-hashBitNr);
}
*/

// Returns the mNodes-index of the node with the passed var-, low- and
// high-values. If such node does not exists, it is inserted into
// mNodes and mUniqueHash. If there are no free nodes left, throws exception.
unsigned toyBDD::insert(unsigned pVar, unsigned pLow, unsigned pHigh)
{
    unsigned lHashIndex;
    unsigned lResult;

    // BDD-reduction of nodes with equal high- and low-child.
    if (pHigh == pLow)
    {
        return pLow;
    }

    // Search mUniqueHash.
    lHashIndex = hash(pVar, pLow, pHigh, mUniqueHBitNr);
    lResult = mUniqueHash[lHashIndex];
    while (lResult)
    {
        if (mNodes[lResult].var == pVar
            && mNodes[lResult].low == pLow
            && mNodes[lResult].high == pHigh)
        {
            return lResult;
        }
        lResult = mNodes[lResult].next;
    }

    // Create new node.
    if (mFree == 0)
    {
        throw "Error: BDD package out of memory\n";
    }

    lResult = mFree;
    mFree = mNodes[lResult].low;
    mNodes[lResult].var = pVar;
    mNodes[lResult].low = pLow;
    mNodes[lResult].high = pHigh;
    mNodes[lResult].next = mUniqueHash[lHashIndex];
    mUniqueHash[lHashIndex] = lResult;

    return lResult;
}

// Prints BDD with root pRoot as reduced binary decision tree.
void toyBDD::print_(ostream& pS, unsigned pRoot)
{
    if (pRoot == 1)
    {
        cout << '1';
    }
    else
    {
        if (pRoot == 0)
        {
            cout << '0';
        }
        else
        {
            cout << '(';
            print_(pS, mNodes[pRoot].low);
            cout << ' ' << "x" << mNodes[pRoot].var << ' ';
            print_(pS, mNodes[pRoot].high);
            cout << ')';
        }
    }
}

unsigned toyBDD::exists_(unsigned pRoot, unsigned pVar)
{
    unsigned lCacheIndex;
    unsigned lResult;

    if (mNodes[pRoot].var < pVar)
    {
        lCacheIndex = hash(mExists, pRoot, pVar, mBinCBitNr);
        if (mBinCache[lCacheIndex].op == mExists
            && mBinCache[lCacheIndex].root1 == pRoot
            && mBinCache[lCacheIndex].root2 == pVar)
        {
            return mBinCache[lCacheIndex].result;
        }

        lResult = insert(mNodes[pRoot].var,
                         exists_(mNodes[pRoot].low, pVar),
                         exists_(mNodes[pRoot].high, pVar));

        mBinCache[lCacheIndex].result = lResult;
        mBinCache[lCacheIndex].op = mExists;
        mBinCache[lCacheIndex].root1 = pRoot;
        mBinCache[lCacheIndex].root2 = pVar;
    }
    else
    {
        if (mNodes[pRoot].var == pVar)
        {
            lResult = unite_(mNodes[pRoot].low, mNodes[pRoot].high);
        }
        else
        {
            lResult = pRoot;
        }
    }

    return lResult;
}

unsigned toyBDD::complement_(unsigned pRoot)
{
    unsigned lResult;
    unsigned lCacheIndex;

    if (pRoot == 1)
        return 0;
    if (pRoot == 0)
        return 1;

    lCacheIndex = hash(mComplement, pRoot, 0, mBinCBitNr);
    if (mBinCache[lCacheIndex].op == mComplement
        && mBinCache[lCacheIndex].root1 == pRoot
        && mBinCache[lCacheIndex].root2 == 0)
    {
        return mBinCache[lCacheIndex].result;
    }

    lResult = insert(mNodes[pRoot].var, complement_(mNodes[pRoot].low), complement_(mNodes[pRoot].high));

    mBinCache[lCacheIndex].result = lResult;
    mBinCache[lCacheIndex].op = mComplement;
    mBinCache[lCacheIndex].root1 = pRoot;
    mBinCache[lCacheIndex].root2 = 0;

    return lResult;
}

unsigned toyBDD::applyBinary(unsigned pRoot1, unsigned pRoot2, toyBDD::Operation op)
{
    switch (op)
    {
        case mIntersect:
            if (pRoot1 == 0 || pRoot2 == 0)
                return 0;
            if (pRoot1 == 1)
                return pRoot2;
            if (pRoot2 == 1)
                return pRoot1;
            break;
        case mUnite:
            if (pRoot1 == 1 || pRoot2 == 1)
                return 1;
            if (pRoot1 == 0)
                return pRoot2;
            if (pRoot2 == 0)
                return pRoot1;
            break;
        default:
            break;
    }
    if (pRoot1 == pRoot2)
        return pRoot1;

    normalize(pRoot1, pRoot2);
    unsigned lResult;
    unsigned lCacheIndex = hash(op, pRoot1, pRoot2, mBinCBitNr);
    if (mBinCache[lCacheIndex].op == op
        && mBinCache[lCacheIndex].root1 == pRoot1
        && mBinCache[lCacheIndex].root2 == pRoot2)
    {
        return mBinCache[lCacheIndex].result;
    }

    if (mNodes[pRoot1].var < mNodes[pRoot2].var)
    {
        lResult = insert(mNodes[pRoot1].var,
                         applyBinary(mNodes[pRoot1].low, pRoot2, op),
                         applyBinary(mNodes[pRoot1].high, pRoot2, op));
    }
    else if (mNodes[pRoot1].var == mNodes[pRoot2].var)
    {
        lResult = insert(mNodes[pRoot1].var,
                         applyBinary(mNodes[pRoot1].low, mNodes[pRoot2].low, op),
                         applyBinary(mNodes[pRoot1].high, mNodes[pRoot2].high, op));
    }
    else
    {
        lResult = insert(mNodes[pRoot2].var,
                         applyBinary(pRoot1, mNodes[pRoot2].low, op),
                         applyBinary(pRoot1, mNodes[pRoot2].high, op));
    }

    mBinCache[lCacheIndex].result = lResult;
    mBinCache[lCacheIndex].op = op;
    mBinCache[lCacheIndex].root1 = pRoot1;
    mBinCache[lCacheIndex].root2 = pRoot2;

    return lResult;
}

unsigned toyBDD::unite_(unsigned pRoot1, unsigned pRoot2)
{
    return applyBinary(pRoot1, pRoot2, mUnite);
}

unsigned toyBDD::intersect_(unsigned pRoot1, unsigned pRoot2)
{
    return applyBinary(pRoot1, pRoot2, mIntersect);
}

// Initialization of BDD package.
// Must be called before any other function of the package is used.
// Parameters: Values for the m... variables.
//   number of elements of mNodes == pNodes,
//   number of elements of mUniqueHash == 2^pUniqueHBitNr,
//   number of elements of mBinCache == 2^pBinCBitNr.
void toyBDD::init(unsigned pMaxNodeNr,
                  unsigned pUniqueHBitNr,
                  unsigned pBinCBitNr
)
{

    // Allocate memory.
    mMaxNodeNr = pMaxNodeNr + 2;
    mNodes = new bddNode[mMaxNodeNr];

    mUniqueHBitNr = pUniqueHBitNr;
    mUniqueHash = new unsigned[1u << mUniqueHBitNr];

    mBinCBitNr = pBinCBitNr;
    mBinCache = new bddBinEntry[1u << mBinCBitNr];

    if (!mNodes || !mUniqueHash || !mBinCache)
    {
        cerr << "Error: "
             << "Not enough memory for initialization of BDD package." << endl;
        exit(EXIT_FAILURE);
    }

    // Initialise arrays.
    memset(mNodes, 0, mMaxNodeNr * sizeof(bddNode));
    memset(mUniqueHash, 0, (1u << mUniqueHBitNr) * sizeof(unsigned));
    memset(mBinCache, 0, (1u << mBinCBitNr) * sizeof(bddBinEntry));

    // Initialise terminal nodes.
    mNodes[0].var = numeric_limits<unsigned>::max();
    mNodes[0].mark = 1;
    mNodes[1].var = numeric_limits<unsigned>::max();
    mNodes[1].mark = 1;

    // Initialise mFree list of unused nodes.
    mFree = 2;
    for (unsigned lCnt = 2; lCnt < mMaxNodeNr - 1; lCnt++)
    {
        mNodes[lCnt].low = lCnt + 1;
    }
}

// Frees memory used by the static data structures.
void toyBDD::done()
{
    delete mNodes;
    delete mUniqueHash;
    delete mBinCache;
}

// Creates BDD that assign the value pValue to the variable pVarId.
toyBDD::toyBDD(unsigned pVarId, bool pValue)
{
    try
    {
        mRoot = toyBDD::bddBdd_(pVarId, pValue);
    }
    catch (...)
    {
        try
        {
            mRoot = toyBDD::bddBdd_(pVarId, pValue);
        }
        catch (...)
        {
            cerr << "Error: BDD package out of memory." << endl;
            exit(EXIT_FAILURE);
        }
    }
}

// Creates BDD that assign the value pValue to the variable pVarId.
unsigned toyBDD::bddBdd_(unsigned pVarId, bool pValue)
{
    if (pValue)
    {
        return insert(pVarId, 0, 1);
    }
    else
    {
        return insert(pVarId, 1, 0);
    }
}

// Creates BDD that assigns bit values of 'pValue' 
//   to 'pBitNr' variables beginning at position 'pVarId'.
toyBDD::toyBDD(unsigned pVarId, unsigned pBitNr, unsigned pValue)
{
    try
    {
        mRoot = toyBDD::bddBdd_(pVarId, pBitNr, pValue);
    }
    catch (...)
    {
        try
        {
            mRoot = toyBDD::bddBdd_(pVarId, pBitNr, pValue);
        }
        catch (...)
        {
            cerr << "Error: BDD package out of memory." << endl;
            exit(EXIT_FAILURE);
        }
    }
}

// Creates BDD that assign bit values of 'pValue' 
//   to 'pBitNr' variables beginning at position 'pVarId'.
unsigned toyBDD::bddBdd_(unsigned pVarId, unsigned pBitNr, unsigned pValue)
{
    unsigned result = 1;

    // For all bits of the binary encoding of 'pValue'.
    for (unsigned lIt = 0;
         lIt < pBitNr;
         ++lIt)
    {
        unsigned lPosition = pVarId + (pBitNr - lIt - 1);
        if ((pValue & (1 << lIt)) > 0)
        {
            result = insert(lPosition, 0, result);
        }
        else
        {
            result = insert(lPosition, result, 0);
        }
    }
    return result;
}

// Creates BDD for pVarId1 == pVarId2.
toyBDD::toyBDD(unsigned pVarId1, unsigned pVarId2)
{
    try
    {
        mRoot = toyBDD::bddBdd_(pVarId1, pVarId2);
    }
    catch (...)
    {
        try
        {
            mRoot = toyBDD::bddBdd_(pVarId1, pVarId2);
        }
        catch (...)
        {
            cerr << "Error: BDD package out of memory." << endl;
            exit(EXIT_FAILURE);
        }
    }
}

// Creates BDD for pVarId1 == pVarId2.
unsigned toyBDD::bddBdd_(unsigned pVarId1, unsigned pVarId2)
{
    unsigned topVarId = pVarId1;
    unsigned bottomVarId = pVarId2;
    if (pVarId1 > pVarId2)
    {
        topVarId = pVarId2;
        bottomVarId = pVarId1;
    }
    return insert(topVarId,
                  insert(bottomVarId, 1, 0),
                  insert(bottomVarId, 0, 1)
    );
}

toyBDD& toyBDD::operator=(const toyBDD& pBdd)
{
    mRoot = pBdd.mRoot;
    return *this;
}

// Computes complement.
void toyBDD::complement()
{
    unsigned lResult;
    try
    {
        lResult = toyBDD::complement_(mRoot);
    }
    catch (...)
    {
        try
        {
            lResult = toyBDD::complement_(mRoot);
        }
        catch (...)
        {
            cerr << "Error: BDD package out of memory." << endl;
            exit(EXIT_FAILURE);
        }
    }
    mRoot = lResult;
}

// Unites with pBdd.
void toyBDD::unite(const toyBDD& pBdd)
{
    unsigned lResult;
    try
    {
        lResult = toyBDD::unite_(mRoot, pBdd.mRoot);
    }
    catch (...)
    {
        try
        {
            lResult = toyBDD::unite_(mRoot, pBdd.mRoot);
        }
        catch (...)
        {
            cerr << "Error: BDD package out of memory." << endl;
            exit(EXIT_FAILURE);
        }
    }
    mRoot = lResult;
}

// Intersects with pBdd.
void toyBDD::intersect(const toyBDD& pBdd)
{
    unsigned lResult;
    try
    {
        lResult = toyBDD::intersect_(mRoot, pBdd.mRoot);
    }
    catch (...)
    {
        try
        {
            lResult = toyBDD::intersect_(mRoot, pBdd.mRoot);
        }
        catch (...)
        {
            cerr << "Error: BDD package out of memory." << endl;
            exit(EXIT_FAILURE);
        }
    }
    mRoot = lResult;
}

// Existantial quantification of the variable pVar.
void toyBDD::exists(unsigned pVar)
{
    unsigned lResult;
    try
    {
        lResult = toyBDD::exists_(mRoot, pVar);
    }
    catch (...)
    {
        try
        {
            lResult = toyBDD::exists_(mRoot, pVar);
        }
        catch (...)
        {
            cerr << "Error: BDD package out of memory." << endl;
            exit(EXIT_FAILURE);
        }
    }
    mRoot = lResult;
}

