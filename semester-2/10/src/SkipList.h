#pragma once

#include "OrderedList.h"

//=============================================================================
//== NodeSkipList =============================================================
//=============================================================================

//const int numLevels = 15;

// A node of skip-list data structure
template <class Value, class Key, int numLevels, class Next>
class NodeSkipListAbstract : public NodeWithKeyAbstract<Value, Key, Next >
{
public:
	// The lowest (= dense) level is implemented with m_next.
	// Warning! The most dense level is m_next, not m_nextjump[0]!!!

	// Skip list sparse levels
	Next * m_nextjump[numLevels]; //(numLevels-1) - highest/sparsest level.

	// Current highest level of the node
	// Important!!
	// -1 = there are no sparse numLevels
	//  0 = m_nextjump[0] is enabled and contains sparse jumps
	// (numLevels-1) is the maximal value for m_levelHighest
	//
	// Note: In industrial envirnoment I would use 0 for no numLevels,
	// but it may confuse students.
	int m_levelHighest;
};

template <class Value, class Key, int numLevels>
class NodeSkipList : public NodeSkipListAbstract<Value, Key, numLevels, NodeSkipList<Value, Key, numLevels> >
{
	// Clears all next links - dense and sparse levels
	// and other fields
	void clear();

public:
	// Default constructor
	NodeSkipList();
	// Constructors with parameters
	NodeSkipList(Key key);
	NodeSkipList(Key key, Value value);
};
//=============================================================================
//== End of: NodeSkipList =====================================================
//=============================================================================

//=============================================================================
//== SkipList =================================================================
//=============================================================================
template <class Value, class Key, int numLevels >
class SkipList : public OrderedList < Value, Key, NodeSkipList<Value, Key, numLevels> >
{
	// The probability of the next level to appear
	double m_probability;

public:
	typedef NodeSkipList<Value,Key, numLevels> TypeNode;

	// probability is the probability of each sparse level to appear
	SkipList(double probability = 0.5);

	// Insert a new element into your list
	//
	// Think very hard how will you guarantee that
	// new element will be included in sparse levels correctly!
	//
	// Make different test. Check border cases - empty list, end of the list,
	// et cetera ...
	void insert(Value value, Key key);

	// Remove the node from the list and delete it from the memory.
	//
	// Check if an idiot called your function
	// (i.e. don't delete pprehead occasionaly, and other cases)
	//
	// Continue to think hard about sparse levels.
	// Check different cases.
	void remove(TypeNode * node);

	// Find the last element with m_key strictly less than key
	// You have to do it in log(n) time,
	// i.e. you have to use sparse levels correctly
	// from the highest to the lowest
	virtual TypeNode * findLastLessThan(Key key) const;

	// Find the first element with m_key equal to key
	// You have to do it in log(n) time,
	// i.e. you have to use sparse levels correctly
	// from the highest to the lowest
	virtual TypeNode * findFirst(Key key) const;
};
//=============================================================================
//== End of: SkipList =========================================================
//=============================================================================

#include "SkipList.hpp"
