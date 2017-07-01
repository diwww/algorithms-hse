#ifndef LIST_PROJECT_LINKEDLIST_H
#define LIST_PROJECT_LINKEDLIST_H

/**
 * Class that represents LinkedList data structure for storing integer elements
 * (consider that this collection does not use C++ templates, so you can store
 * only integers in this collection).
 *
 * Note that current implementation is a doubly linked list. So each node
 * have pointer to both next and previous element in a list.
 *
 * You need to implement current class and all its static functions.
 *
 * Consider that all non-static functions of current class are dedicated to
 * the data structure implementation and how it behaves during usage.
 *
 * As always, you need to implement this class in "linked_list.cpp" file and you MUST NOT
 * change "linked_list.h" file.
 */

class LinkedList {
public:
    /**
     * Class of the Node element that are need to be stored in the linked list.
     * You don't need to implement anything here.
     *
     * Disclaimer: you can see here that all members of the class are public which is
     * not always good way to do it. Since we assume that Node class is used in LinkedList
     * class only and not exposed to user, we can safely design it with public members for
     * simplicity.
    */
    class Node {
    public:
        /** Pointer to next element */
        Node* next = nullptr;
        
        /** Pointer to previous element */
        Node* prev = nullptr;

        /** Integer value that is stored in current node */
        int value;

        /**
         * Constructor of the node element
         *
         * Parameters:
         *  int value - value of the element.
         */
        Node(int value) : value(value) { }

        /**
         * Destructor of the node element.
         */
        ~Node() {
            next = nullptr;
            prev = nullptr;
        }
    };

    /* First element of the linked list. If it equals to nullptr then there are no elements in the list. */
    Node* head = nullptr;

    /* Last element of the linked list. If it equals to nullptr then there are no elements in the list. */
    Node* tail = nullptr;

    /* Number of elements in current linked list */
    int size = 0;

    /**
     * Getting node element of the list with specified index
     *
     * Parameters:
     *  int index - index of the node in the list. Non-negative integer value.
     *
     * Returns:
     *  list node at current index
     */
    Node* get_node(int index);
    
public:
    /**
     * Here we have a section of static factory methods, see
     * some information about such functions in the explanation
     * above.
     */

    /**
     * Static factory function to create linked list filled with
     * items from specified array.
     *
     * Parameters:
     *  int* source - array to be a source of elements that are need to be stored
     *                in created linked list.
     *  int size    - number of elements that are need to be stored in linked list
     *                from index 0 (inclusively). Strictly positive value.
     *
     * Returns:
     *  new linked list object pointer with is filled of "size" items from "source"
     */
    static LinkedList* create_from_array(int* source, int size);
    

    /**
     * Destructor of the list.
     */
    virtual ~LinkedList();
    
    /**
     * Getting integer element of the list with specified index
     *
     * Parameters:
     *  int index - index of element of the list, which needs to be returned. Non-negative integer value.
     *
     * Returns:
     *  value of the element with index of current list
     *
     * Throws:
     *  out_of_range - if index is not within bounds [0, size - 1].
     *
     * Complexity:
     *  ???
     */
    int get(int index);
    
    /**
     *
     * Returns a value of the first element in the list container.
     *
     * @throws logic_error - when list is empty
     *
     * @returns value of the first element
     *
     */
    int front();
    
    /**
     * Returns a value of the last element in the list container.
     *
     * @throws logic_error - when list is empty
     *
     * @returns value of the last element
     *
     */
    int back();
    
    /**
     * Add element at the end
     * Adds a new element at the end of the list container, after its current last element
     * This effectively increases the container size by one.
     *
     * Parameters:
     *  int value - value of the new element
     *
     * Complexity:
     *  ???
     */
    void push_back(int value);
    
    /**
     * Add element at the front
     * Adds a new element at the front of the list container, before its current first element
     * This effectively increases the container size by one.
     *
     * Parameters:
     *  int value - value of the new element
     *
     * Complexity:
     *  ???
     */
    void push_front(int value);
    
    
    /**
     *
     * Delete last element
     * Removes the last element in the list container, effectively reducing its size by one.
     *
     * Throws:
     *  logic_error - when list is empty
     *
     * Complexity:
     *  ???
     */
    void pop_back();
    
    /**
     * Delete first element
     * Removes the first element in the list container, effectively reducing its size by one. 
     *
     * Throws:
     *  logic_error - when list is empty
     *
     * Complexity:
     *  ???
     */
    void pop_front();
    
    /**
     *
     * The container is extended by inserting new elements before the element at the specified position.
     *
     * @param index - the index of the new element, in range [0, size]
     * @param value - value of the new element
     *
     * @throws out_of_range - if index is not within bounds [0, size].
     *
     * Complexity:
     *  ???
     */
    void insert(int index, int value);
    
    /**
     *
     * Removes from the list container a single element (position)
     *
     * @param index - index to be removed, in range [0, size-1]
     *
     * @throws out_of_range - if index is not within bounds [0, size-1].
     *
     * Comlpexity: ???
     *
     */
    void erase(int index);
    
    /**
     *
     * The container is extended by inserting new elements after the element at the specified position.
     *
     * @param prev  - link to previuos node of the new node. The new node should be located between prev and prev->next
     * @param value - value of the new element
     *
     * Complexity:
     *  ???
     */
    void insert(Node* prev, int value);
    
    /**
     *
     * Removes from the list container a single element (position)
     *
     * @param node - node to be removed
     *
     */
    void erase(Node* node);

    /**
     * Returning size of the list, i.e. number of elements in the list.
     *
     * Returns:
     *  non-negative number of the elements in the list.
     *
     * Complexity:
     *  ???
     */
    int get_size();
    
    /**
     * Test whether container is empty
     * Returns whether the list container is empty (i.e. whether its size is 0).
     * This function does not modify the container in any way. To clear the content of a list container, see ::clear.
     *
     * Returns:
     *  true if the container size is 0, false otherwise.
     *
     * Complexity:
     *  ???
     */
    bool empty();
    
    /**
     * Removes all elements from the list container (which are destroyed), and leaving the container with a size of 0.
     *
     * Complexity:
     *  ???
     */
    void clear();
    
    /**
     * Sorts the elements in the list.
     * Complexity: ???
     */
    void sort();
    
    /**
     *
     * Returns first index at the list which contains such value
     *
     * @param value - value to find
     *
     * @return index of the value. Should returns tail in case if it is no such value in list
     *
     */
    int find_first(int value);
};

#endif //LIST_PROJECT_LINKEDLIST_H
