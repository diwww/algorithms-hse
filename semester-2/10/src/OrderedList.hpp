// Default constructor
template <class Value, class Key, class Node >
OrderedList<Value,Key,Node>::OrderedList(void)
{
	m_pPreHead = new Node;

	m_pPreHead->m_next = m_pPreHead;
}

// Returns the sentinel node
template <class Value, class Key, class Node >
Node * OrderedList<Value,Key,Node>::getPreHead(void) const
{
	return m_pPreHead;
}

// Inserts a new node with m_value==value and m_key==key defined
template <class Value, class Key, class Node >
void OrderedList<Value,Key,Node>::insert(Value value, Key key)
{
	Node * run = m_pPreHead;
	while (run->m_next != m_pPreHead)
	{
		run = run->m_next;
	}

	Node * tmp = new Node;
	tmp->m_next = run->m_next;
	tmp->m_key = key;
	tmp->m_value = value;

	run->m_next = tmp;
}

// Remove the node just after the nodeBefore
template <class Value, class Key, class Node >
void OrderedList<Value,Key,Node>::remove(Node * nodeBefore)
{
	if (nodeBefore == 0
		|| nodeBefore->m_next == 0
		|| nodeBefore->m_next == m_pPreHead)
	{
		return;
	}
	Node * tmp = nodeBefore -> m_next;
	nodeBefore -> m_next = tmp -> m_next;
	delete tmp;
}

// Finds last node in the list with m_key strictly less than key
template <class Value, class Key, class Node >
Node * OrderedList<Value,Key,Node>::findLastLessThan(Key key) const
{
	Node * run = m_pPreHead;
	while (run->m_next != m_pPreHead
		&& run->m_next->m_key < key)
	{
		run = run->m_next;
	}
	return run;
}

// Finds the first node in the list with m_key equal to key
template <class Value, class Key, class Node >
Node * OrderedList<Value,Key,Node>::findFirst(Key key) const
{
	Node * run = m_pPreHead;
	while (run->m_next != m_pPreHead)
	{
		run = run->m_next;
		if (run->m_key == key)
		{
			return run;
		}
	}
	return 0;
}
