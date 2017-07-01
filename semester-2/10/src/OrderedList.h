#pragma once

//=============================================================================
//== Node =====================================================================
//=============================================================================

// Abstract list node with a value
template<class Value, class Next>
class NodeAbstract
{
public:
    Value m_value;
    Next* m_next;

    NodeAbstract() : m_next(0)
    {}

    NodeAbstract(const Value& value) : m_next(0), m_value(value)
    {}
};

// We don't have Node class (only NodeAbstract),
// because we don't need to implement simple (unordered) list.

//=============================================================================
//== End of: Node =============================================================
//=============================================================================


//=============================================================================
//== NodeWithKey ==============================================================
//=============================================================================
// Abstract node with a value and a key
// m_key is an ordering key
template<class Value, class Key, class Next>
class NodeWithKeyAbstract : public NodeAbstract<Value, Next>
{
public:
    Key m_key;
};

// Concrete NodeWithKey class
template<class Value, class Key>
class NodeWithKey : public NodeWithKeyAbstract<Value, Key, NodeWithKey<Value, Key> >
{
public:
    NodeWithKey()
    {}

    NodeWithKey(Key key)
    { this->m_key = key; }
};
//=============================================================================
//== End of: NodeWithKey ======================================================
//=============================================================================

//=============================================================================
//== OrderedList ==============================================================
//=============================================================================

template<class Value, class Key, class Node = NodeWithKey<Value, Key> >
class OrderedList
{
protected:
    // Sentinel element - placed before first and after last elements
    Node* m_pPreHead;

public:
    typedef NodeWithKey<Value, Key> TypeNode;

    OrderedList(void);

    virtual Node* getPreHead(void) const;

    // Inserts new node
    virtual void insert(Value value, Key key);

    // Remove node just after nodeBefore
    virtual void remove(Node* nodeBefore);

    // Finds the last node which m_key is less than "key" argument
    virtual Node* findLastLessThan(Key key) const;

    // Finds a node which m_key is equal to "key" argument
    virtual Node* findFirst(Key key) const;
};

//=============================================================================
//== End of: OrderedList ======================================================
//=============================================================================

#include "OrderedList.hpp"
