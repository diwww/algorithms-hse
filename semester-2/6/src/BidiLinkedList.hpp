///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains pseudo-implementation part of bidirectional list structure 
/// template declared in the file's h-counterpart
///
/// © Sergey Shershakov 2015–2016
///
/// No part of this code can be used without an explicit permission of the author. 
/// The exception is done for educational goals of the course "Algorithms and Data 
/// Structures" provided by the School of Software Engineering of the Faculty 
/// of Computer Science at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///////////////////////////////////////////////////////////////////////////////

#include <stdexcept>

//==============================================================================
// class BidiList<T>::Node
//==============================================================================

template<typename T>
typename BidiLinkedList<T>::Node *
BidiLinkedList<T>::Node::insertAfterInternal(Node *insNode)
{
    if (this->_next)
    {
        insNode->_next = this->_next;
        this->_next->_prev = insNode;
    }

    this->_next = insNode;
    insNode->_prev = this;

    return insNode;
}

//==============================================================================
// class BidiList<T>
//==============================================================================

template<typename T>
BidiLinkedList<T>::~BidiLinkedList()
{
    clear();
}


template<typename T>
void BidiLinkedList<T>::clear()
{
    Node *temp = _head;
    while (temp)
    {
        Node *toDelete = temp;
        temp = temp->_next;
        delete toDelete;
    }
    _head = nullptr;
    invalidateSize();
}


template<typename T>
size_t BidiLinkedList<T>::getSize()
{
    if (_size == NO_SIZE)
        calculateSize();

    return _size;
}


template<typename T>
void BidiLinkedList<T>::calculateSize()
{
    _size = 0;
    Node *temp = _head;
    while (temp)
    {
        _size++;
        temp = temp->_next;
    }
}


template<typename T>
typename BidiLinkedList<T>::Node *
BidiLinkedList<T>::getLastNode() const
{
    Node *temp = _head;
    if (temp) // if head is not nullptr
    {
        while (temp->_next)
            temp = temp->_next;
    }
    return temp;
}


template<typename T>
typename BidiLinkedList<T>::Node *
BidiLinkedList<T>::appendEl(const T &val)
{
    Node *newNode = new Node(val);
    return insertNodeAfter(getLastNode(), newNode);
}


template<typename T>
typename BidiLinkedList<T>::Node *
BidiLinkedList<T>::insertNodeAfter(Node *node, Node *insNode)
{
    insertNodesAfter(node, insNode, insNode);
    return insNode;
}


template<typename T>
void BidiLinkedList<T>::insertNodesAfter(Node *node, Node *beg, Node *end)
{
    if (!beg || !end)
        throw std::invalid_argument("Either `beg` or `end` is nullptr");

    if (!node)
        node = getLastNode();

    if (!node) // if even last node is nullptr
        _head = beg;
    else
    {
        if (node->_next)
        {
            end->_next = node->_next;
            node->_next->_prev = end;
        }

        node->_next = beg;
        beg->_prev = node;
    }

    invalidateSize();
}


template<typename T>
void BidiLinkedList<T>::cutNodes(Node *beg, Node *end)
{
    if (!beg || !end)
        throw std::invalid_argument("Either `beg` or `end` is nullptr");

    if (beg->_prev)
        beg->_prev->_next = end->_next;
    else // if beg is head
        _head = end->_next;

    if (end->_next)
        end->_next->_prev = beg->_prev;

    beg->_prev = nullptr;
    end->_next = nullptr;

    invalidateSize();
}


template<typename T>
typename BidiLinkedList<T>::Node *
BidiLinkedList<T>::cutNode(Node *node)
{
    cutNodes(node, node);
    return node;
}


template<typename T>
typename BidiLinkedList<T>::Node *
BidiLinkedList<T>::findFirst(Node *startFrom, const T &val)
{
    while (startFrom)
    {
        if (startFrom->_val == val)
            return startFrom;
        startFrom = startFrom->_next;
    }

    return nullptr; // not found
}


template<typename T>
typename BidiLinkedList<T>::Node **
BidiLinkedList<T>::findAll(Node *startFrom, const T &val, int &size)
{
    if (!startFrom)
        return nullptr;

    // try not to use any standard containers. create an array only when found a first occurence 
    Node **res = nullptr;
    size = 0;

    while (startFrom)
    {
        if (startFrom->_val == val)
        {
            if (!res)
                res = new Node *[getSize()];
            res[size++] = startFrom;
        }
        startFrom = startFrom->_next;
    }

    // recreates array if created
    if (res)
    {
        Node **temp = res;
        res = new Node *[size];
        for (int i = 0; i < size; ++i)
        {
            res[i] = temp[i];
        }
        delete[] temp;
    }

    return res;
}

#ifdef IWANNAGET10POINTS
template <typename T>
typename BidiLinkedList<T>::Node**  
BidiLinkedList<T>::cutAll(Node* startFrom, const T& val, int& size)
{

    // !...
    // Реализуй метод, если хочешь получит оценку повыше!
    // !...


}
template <typename T>
typename BidiLinkedList<T>::Node*
    BidiLinkedList<T>::insertNodeBefore(Node* node, Node* insNode)
{



    // !...
    // Реализуй метод, если хочешь получит оценку повыше!
    // !...



}


template <typename T>
void BidiLinkedList<T>::insertNodesBefore(Node* node, Node* beg, Node* end)
{
    // !...
    // Реализуй метод, если хочешь получит оценку повыше!
    // !...

}
#endif // IWANNAGET10POINTS