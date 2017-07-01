#include <iostream>
#include "binary_tree.h"

using namespace std;

template<class T>
T print(T x)
{
	cout << x << " ";
}

void test_1()
{
	BinaryTree<int> *tr = new BinaryTree<int>();

	tr->insert(4, 4);
	tr->insert(2, 2);
	tr->insert(5, 5);
	tr->insert(1, 1);
	tr->insert(3, 3);
	tr->insert(6, 6);

	tr->remove(4);
//    tr->remove(1);
	tr->remove(2);
	// Causes exception
//    tr->remove(7);

	tr->Traverse(print);
	cout << endl;

	delete tr;
}

void test_2()
{
	BinaryTree<int> *tr = new BinaryTree<int>();

	tr->insert(2, 2);
	tr->insert(1, 1);
	tr->insert(3, 3);

	tr->remove(3);
	tr->remove(1);

	tr->Traverse(print);
	cout << endl;


	delete tr;
}

int main()
{
	while (true)
	{
		test_1();
		test_2();
	}

	return 0;
}