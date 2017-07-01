// Name: Surovtsev Maxim
// Group: BSE151


#include "binary_tree.h"
#include <stdexcept>


// Utility function for
// searching min element
// in the subtree
template<class T>
typename BinaryTree<T>::Node *min(typename BinaryTree<T>::Node *start)
{
    while (start->left != nullptr)
        start = start->left;
    return start;
}

// Utility insert function
template<class T>
void insert_node(typename BinaryTree<T>::Node *&start, int key, T value)
{
    if (start == nullptr)
    {
        start = new typename BinaryTree<T>::Node(key, value);
        return;
    }
    else if (key < start->key)
        insert_node<T>(start->left, key, value);
    else if (key > start->key)
        insert_node<T>(start->right, key, value);
    else
        throw std::logic_error("Key already exists.");
}

// Utility remove function
template<class T>
typename BinaryTree<T>::Node *remove_node(typename BinaryTree<T>::Node *start, int key)
{
    if (start == nullptr)
        throw std::logic_error("Key does not exist.");
    else if (key < start->key)
        start->left = remove_node<T>(start->left, key);
    else if (key > start->key)
        start->right = remove_node<T>(start->right, key);
    else
    {
        // No children
        if (start->left == nullptr && start->right == nullptr)
        {
            delete start;
            start = nullptr;
        } // One child
        else if (start->left == nullptr)
        {
            typename BinaryTree<T>::Node *tmp = start;
            start = start->right;
            delete tmp;
        }
        else if (start->right == nullptr)
        {
            typename BinaryTree<T>::Node *tmp = start;
            start = start->left;
            delete tmp;
        } // Two children
        else
        {
            typename BinaryTree<T>::Node *tmp = min<T>(start->right);
            start->key = tmp->key;
            start->value = tmp->value;
            start->right = remove_node<T>(start->right, tmp->key);
        }
    }
    return start;
}

// Utility search function
template<class T>
typename BinaryTree<T>::Node *find_node(typename BinaryTree<T>::Node *start, int key)
{
    if (start == nullptr)
        throw std::logic_error("Key does not exist.");
    else if (key < start->key)
        start = find_node<T>(start->left, key);
    else if (key > start->key)
        start = find_node<T>(start->right, key);

    return start;
}

template<class T>
void BinaryTree<T>::insert(int key, T value)
{
    insert_node<T>(head, key, value);
    size++;
}

template<class T>
void BinaryTree<T>::remove(int key)
{
    head = remove_node<T>(head, key);
    size--;
}

template<class T>
T BinaryTree<T>::find(int key)
{
    return find_node<T>(head, key)->value;
}

template<class T>
void BinaryTree<T>::TraverseNode(Node *start, T (*func)(T))
{
    if (start != nullptr)
    {
        // Left child
        TraverseNode(start->left, func);
        // Apply some function to root value
        func(start->value);
        // Right child
        TraverseNode(start->right, func);
    }
}

template<class T>
BinaryTree<T>::~BinaryTree()
{
    while (head != nullptr)
    {
        remove(head->key);
    }
}