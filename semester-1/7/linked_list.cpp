// Name: Surovtsev Maxim
// Group: BSE151


#include "linked_list.h"
#include <stdexcept>


/**
 * UTILITY METHODS
 */
void quick_sort(LinkedList *list, int left, int right)
{
    int i = left, j = right;
    int pivot = list->get((left + right) / 2);

    // Partition
    while (i <= j)
    {
        while (list->get(i) < pivot)
            i++;
        while (list->get(j) > pivot)
            j--;
        if (i <= j)
        {
            // Simple implementation, since
            // field "value" is public
            std::swap(list->get_node(i)->value, list->get_node(j)->value);
            i++;
            j--;
        }
    };

    // Recursion
    if (left < j)
        quick_sort(list, left, j);
    if (i < right)
        quick_sort(list, i, right);
}


/**
 * GETTERS
 */
LinkedList::Node *LinkedList::get_node(int index)
{
    // Finding out whether
    // node is closer to tail or head
    if (index < size / 2)
    {
        // Initialize tmp with head node pointer
        LinkedList::Node *tmp = head;
        for (int i = 0; i < index; ++i)
        {
            tmp = tmp->next;
        }
        return tmp;
    }
    else
    {
        // Initialize tmp with tail node pointer
        LinkedList::Node *tmp = tail;
        for (int i = size - 1; i > index; --i)
        {
            tmp = tmp->prev;
        }
        return tmp;
    }
}

int LinkedList::get(int index)
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index is out of range.");
    return get_node(index)->value;
}

int LinkedList::front()
{
    if (size == 0)
        throw std::logic_error("List is empty.");
    return head->value;
}

int LinkedList::back()
{
    if (size == 0)
        throw std::logic_error("List is empty.");
    return tail->value;
}

int LinkedList::get_size()
{
    return size;
}

bool LinkedList::empty()
{
    return size == 0;
}


/**
 * STATIC METHODS
 */
LinkedList *LinkedList::create_from_array(int *source, int size)
{
    LinkedList *list = new LinkedList();
    for (int i = 0; i < size; ++i)
    {
        list->push_back(source[i]);
    }
    return list;
}


/**
 * DESTRUCTOR
 */
LinkedList::~LinkedList()
{
    clear();
}


/**
 * LIST MODIFICATION METHODS
 */
void LinkedList::push_back(int value)
{
    size++;
    if (size == 1)
    {
        // If size == 1 head and tail point
        // to the same node
        head = new Node(value);
        tail = head;
        return;
    }
    else if (size == 2)
    {
        // Distinguishing head and tail
        tail = new Node(value);
        tail->prev = head;
        head->next = tail;
        return;
    }
    else
    {
        LinkedList::Node *tmp = new Node(value);
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
    }
}

void LinkedList::push_front(int value)
{
    size++;
    if (size == 1)
    {
        // If size == 1 head and tail point
        // to the same node
        head = new Node(value);
        tail = head;
        return;
    }
    else if (size == 2)
    {
        // Distinguishing head and tail
        head = new Node(value);
        tail->prev = head;
        head->next = tail;
        return;
    }
    else
    {
        LinkedList::Node *tmp = new Node(value);
        tmp->next = head;
        head->prev = tmp;
        head = tmp;
    }
}

void LinkedList::pop_back()
{
    if (size == 0)
        throw std::logic_error("List is empty.");
    else if (size == 1)
    {
        delete tail;
        tail = nullptr;
        head = nullptr;
        size--;
        return;
    }
    else
    {
        Node *tmp = tail->prev;
        tmp->next = nullptr;
        delete tail;
        tail = tmp;
        size--;
    }
}

void LinkedList::pop_front()
{
    if (size == 0)
        throw std::logic_error("List is empty.");
    else if (size == 1)
    {
        delete head;
        tail = nullptr;
        head = nullptr;
        size--;
        return;
    }
    else
    {
        Node *tmp = head->next;
        tmp->prev = nullptr;
        delete head;
        head = tmp;
        size--;
    }
}

void LinkedList::insert(int index, int value)
{
    if (index < 0 || index > size)
        throw std::out_of_range("Index is out of range.");

    // If index == 0, simply push front
    // If index == size, simply push back
    if (index == 0)
    {
        push_front(value);
        return;
    }
    else if (index == size)
    {
        push_back(value);
        return;
    }
    else
    {
        insert(get_node(index - 1), value);
    }
}

void LinkedList::erase(int index)
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index is out of range.");

    // For the first and the last node
    // there will be no iteration
    if (index == 0)
    {
        pop_front();
        return;
    }
    if (index == size - 1)
    {
        pop_back();
        return;
    }

    // Iterate to find the node
    Node *tmp = get_node(index);
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    // Freeing allocated memory
    delete tmp;
    size--;
}

void LinkedList::insert(Node *prev, int value)
{
    if (size == 0)
        throw std::logic_error("List is empty.");

    Node *tmp = new Node(value);

    // Next node linking
    tmp->next = prev->next;
    if (prev->next != nullptr)
        prev->next->prev = tmp;
    else
        tail = tmp;

    // Previous node linking
    tmp->prev = prev;
    prev->next = tmp;
    size++;
}

void LinkedList::clear()
{
    while (size > 0)
    {
        pop_back();
    }
}

int LinkedList::find_first(int value)
{
    for (int i = 0; i < size; ++i)
    {
        if (get(i) == value)
            return i;
    }
    return size - 1;
}

void LinkedList::sort()
{
    quick_sort(this, 0, size - 1);
}
