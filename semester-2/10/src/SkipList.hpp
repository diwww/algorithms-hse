#include <cstdlib>
#include <array>
#include <stdexcept>

//=============================================================================
//== NodeSkipList =============================================================
//=============================================================================

template<class Value, class Key, int numLevels>
void NodeSkipList<Value, Key, numLevels>::clear(void)
{
    for (int i = 0; i < numLevels; ++i)
    {
        this->m_nextjump[i] = 0;
    }
    this->m_levelHighest = -1;
}

template<class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(void)
{
    clear();
}

template<class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(Key key)
{
    clear();

    this->m_key = key;
}

template<class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(Key key, Value value)
{
    clear();

    this->m_key = key;
    this->m_value = value;
}
//=============================================================================
//== End of: NodeSkipList =====================================================
//=============================================================================

//=============================================================================
//== SkipList =================================================================
//=============================================================================

/**
 * Custom find function, which acts like
 * findLastLessThan, but it also remembers
 * last nodes on sparse levels, so it can be used both
 * in findLastLessThan and insert(remove)
 */
template<class Value, class Key, int numLevels>
std::array<typename SkipList<Value, Key, numLevels>::TypeNode*, numLevels + 1>
find(SkipList<Value, Key, numLevels> list, Key key)
{
    typename SkipList<Value, Key, numLevels>::TypeNode* pos = list.getPreHead();
    // Temp array to remember the last node on each sparse level
    // (one extra level is used to contain the found node itself)
    std::array<typename SkipList<Value, Key, numLevels>::TypeNode*, numLevels + 1> jumps;

    // Sparse levels search
    // (from the most sparse to the least sparse)
    for (int i = list.getPreHead()->m_levelHighest; i >= 0; --i)
    {
        while (pos->m_nextjump[i] != list.getPreHead() &&
               pos->m_nextjump[i]->m_key < key)
            pos = pos->m_nextjump[i];
        // Add pos to temp jump array
        jumps[i] = pos;
    }

    // Dense level search
    while (pos->m_next != list.getPreHead()
           && pos->m_next->m_key < key)
        pos = pos->m_next;

    // Add found node to temp array
    jumps[numLevels] = pos;
    return jumps;
}

template<class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>::SkipList(double probability)
{
    m_probability = probability;
    for (int i = 0; i < numLevels; ++i)
        this->m_pPreHead->m_nextjump[i] = this->m_pPreHead;
    this->m_pPreHead->m_levelHighest = numLevels - 1;
    // Random initialization
    srand(time(0));
}

template<class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::insert(Value value, Key key)
{
    std::array<typename SkipList<Value, Key, numLevels>::TypeNode*, numLevels + 1> jumps = find(*this, key);
    TypeNode* toInsert = new TypeNode(key, value); // Node to insert

    // Dense level insertion
    toInsert->m_next = jumps[numLevels]->m_next;
    jumps[numLevels]->m_next = toInsert;

    // Sparse levels insertion
    for (int i = 0; i <= this->m_pPreHead->m_levelHighest; ++i)
    {
        if (((double) (rand()) / RAND_MAX) <= this->m_probability)
        {
            toInsert->m_nextjump[i] = jumps[i]->m_nextjump[i];
            jumps[i]->m_nextjump[i] = toInsert;
        }
        else break;
    }
}

template<class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::remove(TypeNode* node)
{
    if (node == this->m_pPreHead)
        throw std::invalid_argument("Attempt to remove the prehead.");

    typename SkipList<Value, Key, numLevels>::TypeNode* pos = this->m_pPreHead;
    // Temp array to remember the last node on each sparse level
    // (one extra level is used to contain the found node itself)
    std::array<typename SkipList<Value, Key, numLevels>::TypeNode*, numLevels + 1> jumps;

    // Sparse levels search
    // (from the most sparse to the least sparse)
    for (int i = this->m_pPreHead->m_levelHighest; i >= 0; --i)
    {
        while (pos->m_nextjump[i] != this->m_pPreHead &&
               pos->m_nextjump[i]->m_key <= node->m_key &&
               pos->m_nextjump[i] != node)
            pos = pos->m_nextjump[i];
        // Add pos to temp jump array
        jumps[i] = pos;
    }

    // Dense level search
    while (pos->m_next != this->m_pPreHead &&
           pos->m_next->m_key <= node->m_key &&
           pos->m_next != node)
        pos = pos->m_next;

    if (pos->m_next != node)
        throw std::invalid_argument("Node not found.");

    // Dense level remove
    pos->m_next = pos->m_next->m_next;

    // Sparse levels remove
    for (int i = 0; i <= this->m_pPreHead->m_levelHighest; ++i)
        if (jumps[i]->m_nextjump[i] == node)
            jumps[i]->m_nextjump[i] = jumps[i]->m_nextjump[i]->m_nextjump[i];

    delete node;
}

template<class Value, class Key, int numLevels>
typename SkipList<Value, Key, numLevels>::TypeNode* SkipList<Value, Key, numLevels>::findLastLessThan(Key key) const
{
    return find(*this, key)[numLevels];
}

template<class Value, class Key, int numLevels>
typename SkipList<Value, Key, numLevels>::TypeNode* SkipList<Value, Key, numLevels>::findFirst(Key key) const
{
    TypeNode* run = findLastLessThan(key);
    if (run->m_next != this->m_pPreHead && run->m_next->m_key == key)
        return run->m_next;

    return nullptr;
}

//=============================================================================
//== End of: SkipList =========================================================
//=============================================================================
