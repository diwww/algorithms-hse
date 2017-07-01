#ifndef BINARY_TREE_BINARY_TREE_H
#define BINARY_TREE_BINARY_TREE_H

/**
 * Class that represents BinarySearchTree data structure for storing any elements
 * (consider that this collection USE C++ templates.
 *
 * You need to implement current class and all its static functions.
 *
 * Consider that all non-static functions of current class are dedicated to
 * the data structure implementation and how it behaves during usage.
 *
 * As always, you need to implement this class in "binary_tree.cpp" file and you MUST NOT
 * change "binary_tree.h" file.
 *
 * If you need some additional functions to implement - be free to add them to your binary_tree.cpp
 * file (not binary_tree.h file!). In fact, that will be appreciated if it is used properly, but it
 * is not necessary (we did without them).
 *
 */
template<class T>
class BinaryTree {
public:
    /**
     * Class of the Node element that are need to be stored in the tree.
     * You don't need to implement anything here.
     *
     * Disclaimer: you can see here that all members of the class are public which is
     * not always good way to do it. Since we assume that Node class is used in BinaryTree
     * class only and not exposed to user, we can safely design it with public members for
     * simplicity.
    */
    class Node {
    public:
        /**Key for element to follow the binary search tree property.*/
        int key;

        /**Value that is stored in current node */
        T value;

        /**Pointers to left and right elements and branches respectively*/
        Node *left = nullptr, *right = nullptr;

        /**
         * Constructor of the node element
         *
         * @param
         *  int key - key of the element.
         *  T value - value of the element.
         */
        Node(int key, T value) : key(key), value(value)
            { }

        /**
         * Destructor of the node element.
         */
        ~Node()
            {
                left = nullptr;
                right = nullptr;
            }
    };
    /**
     * Constructor of Binary Tree object.
     * You don't need to implement anything here.
     */
    BinaryTree(){
            head=nullptr;
            size=0;
        }
    /**
     * Inserts the element with given key and value.
     *
     * @param
     * int key - key of element of the tree
     * T value - value of element
     *
     * @throws logic_error if given key exists
     *
     * Note:
     * Follow the binary search tree property (l<r).
     */
    void insert(int key, T value);

    /**
     * Removes the element with given key.
     *
     * @param
     * int key - key of element of the tree to be removed
     *
     * @throws logic_error if given key doesn't exist
     */
    void remove(int key);

    /**
     * Getting element of the list with specified key
     *
     * @param
     *  int key - key of element of the tree, which needs to be returned.
     *
     * @return Pointer on the node with given key if exists, nullptr otherwise.
     */
    T find(int key);

    /**
     * Applies function func to all nodes in tree in INFIX_TRAVERSE order:
     * left subtree, vertex, right subtree.
     *
     * @param
     * func - pointer on function
     *
     * You don't need to implement anything here.
     */
    void Traverse(T (*func)(T)){
            TraverseNode(head,func);
        }

    /**
     * Destructor of the tree.
     * Don't forget to free ALL memory used.
     */
    ~BinaryTree();

private:
    Node *head;
    int size;
    /**
     * Applies function func to all nodes in tree in INFIX_TRAVERSE order, starting from start
     *
     * @param
     * Node* start - vertex, where Traverse is started
     * func - pointer on function
     */
    void TraverseNode(Node *start, T (*func)(T));
};
#include "binary_tree.cpp"
#endif //BINARY_TREE_BINARY_TREE_H
