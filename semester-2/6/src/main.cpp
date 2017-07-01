#include <iostream>
#include "BidiLinkedList.h"

using namespace std;

template<typename T>
void printList(const BidiLinkedList<T> &list)
{
    typename BidiLinkedList<T>::Node *temp = list.getHeadNode();
    while (temp)
    {
        cout << temp->getValue() << " ";
        temp = temp->getNext();
    }
    cout << endl;
}

int main()
{
    BidiLinkedList<int> list;
    BidiLinkedList<int>::Node *node0 = list.appendEl(0);
    BidiLinkedList<int>::Node *node1 = list.appendEl(1);
    BidiLinkedList<int>::Node *node2 = list.appendEl(1);
    BidiLinkedList<int>::Node *node3 = list.appendEl(1);
    BidiLinkedList<int>::Node *node4 = list.appendEl(4);

//    list.cutNode(node1);
//    list.insertNodeAfter(node0, node1);
//    printList(list);
//    cout << list.getLastNode()->getValue() << endl;
//    list.clear();

    int size = 0;
    BidiLinkedList<int>::Node **nodes = list.findAll(1, size);
    for (int i = 0; i < size; ++i)
    {
        cout << nodes[i]->getValue() << " ";
    }
    cout << endl;
    cout << list.getSize();
    delete[] nodes;

    return 0;
}