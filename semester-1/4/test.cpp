#include "heapSort.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void fillArray(int *arr, int N, int i)
{
	srand(i);
	for (int i = 0; i < N; ++i)
	{
		arr[i] = (rand() % 100) - 50;
	}
}

void showArray(int *arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main()
{
	bool f = true;
	for (int i = 0; i < 100; ++i)
	{
		int n = 20;
		int *arr = new int[n];
		fillArray(arr, n, i);
		Heapsort::heapSort(arr, n);
		showArray(arr, n);
		for (int j = 0; j < n - 1; ++j)
			if (arr[j] > arr[j + 1])
			{
				f = false;
				break;
			}
		delete[] arr;
		if (f == false) break;
	}

	if (f == true)
		cout << "Sort works!" << endl;
	else
		cout << "Sort does not work!" << endl;

	return 0;
}