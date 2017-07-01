////////////////////////////////////////////////////////////////////////////////
// Module Name:  linked_list.h/cpp
// Authors:      Sergey Shershakov, Leonid Dworzanski
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
//
// Отделенная часть заголовка шаблона класса "Связанный список"
//
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>

namespace xi {

template<typename T>
Node <T>* LinkedList<T>::getLast(int* size)
{
    Node<T>* temp = _preHead; // _preHead is never nullptr
    while (temp->next != nullptr)
    {
        if (size != nullptr)
            *size = *size + 1;
        temp = temp->next;
    }
    return temp;
}

template<typename T>
void LinkedList<T>::swap(LinkedList& other)
{
    Node<T>* tempPtr = other._preHead;
    other._preHead = this->_preHead;
    this->_preHead = tempPtr;
}

template<typename T>
LinkedList<T>::LinkedList()
{
    //Creation of the dummy/sentinel element
    _preHead = new Node<T>;
    _preHead->next = nullptr;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : LinkedList()
{
    Node<T>* from = other._preHead;
    Node<T>* to = _preHead;

    while (from->next != nullptr)
    {
        to->next = new Node<T>;
        to->next->value = from->next->value;
        to = to->next;
        from = from->next;
    }
}

template<typename T>
LinkedList<T>::~LinkedList()
{
    deleteNodes(_preHead, getLast());
    delete _preHead;
}

template<typename T>
Node <T>* LinkedList<T>::getPreHead()
{
    return _preHead;
}

template<typename T>
T& LinkedList<T>::operator[](int i)
{
    if (i < 0)
        throw std::out_of_range("Index is out of range.");

    Node<T>* temp = _preHead;
    for (int j = 0; j <= i; ++j)
    {
        if (temp->next != nullptr)
            temp = temp->next;
        else
            throw std::out_of_range("Index is out of range.");
    }

    return temp->value;
}

template<typename T>
LinkedList <T>& LinkedList<T>::operator=(const LinkedList <T>& other)
{
    if (this != &other)
    {
        LinkedList temp(other);
        this->swap(temp);
    }
    return *this;
}

template<typename T>
int LinkedList<T>::size()
{
    int size = 0;

    getLast(&size);
    return size;
}

template<typename T>
void LinkedList<T>::addElementToEnd(const T& value)
{
    Node<T>* temp = new Node<T>;
    temp->value = value;
    getLast()->next = temp;
}

template<typename T>
Node <T>* LinkedList<T>::insertNewElement(const T& val, Node <T>* pAfter)
{
    Node<T>* temp = new Node<T>;
    temp->value = val;

    if (pAfter != nullptr)
    {
        temp->next = pAfter->next;
        pAfter->next = temp;
    }
    else
    {
        temp->next = _preHead->next;
        _preHead->next = temp;
    }

    return temp;
}

template<typename T>
void LinkedList<T>::deleteNodes(Node <T>* pNodeBefore, Node <T>* pNodeLast)
{
    // First node that comes after deleted part
    Node<T>* temp = pNodeLast->next;
    // If pNodeBefore->next reaches temp,
    // then all nodes have been deleted
    while (pNodeBefore->next != temp)
        deleteNextNode(pNodeBefore);
}

template<typename T>
void LinkedList<T>::deleteNextNode(Node <T>* pNodeBefore)
{
    Node<T>* temp = pNodeBefore->next; // node to delete
    if (temp != nullptr)
    {
        pNodeBefore->next = temp->next;
        delete temp;
    }
}

template<typename T>
void LinkedList<T>::moveNodesToEnd(Node <T>* pNodeBefore, Node <T>* pNodeLast)
{
    moveNodesAfter(getLast(), pNodeBefore, pNodeLast);
}

template<typename T>
void LinkedList<T>::moveNodeToEnd(Node <T>* pNodeBefore)
{
    moveNodeAfter(getLast(), pNodeBefore);
}

template<typename T>
void LinkedList<T>::moveNodesAfter(Node <T>* pNode, Node <T>* pNodeBefore, Node <T>* pNodeLast)
{
    Node<T>* temp = pNodeBefore->next; // start of a chain

    // Exclude chain from other list
    pNodeBefore->next = pNodeLast->next;

    // Include chain into current list
    pNodeLast->next = pNode->next;
    pNode->next = temp;
}

template<typename T>
void LinkedList<T>::moveNodeAfter(Node <T>* pNode, Node <T>* pNodeBefore)
{
    Node<T>* temp = pNodeBefore->next; // node to move

    if (temp != nullptr)
    {
        // Exclude node from other list
        pNodeBefore->next = temp->next;

        // Include node into current list
        temp->next = pNode->next;
        pNode->next = temp;
    }
}

} // namespace xi