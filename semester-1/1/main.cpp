#include <iostream>
#include "LinearSort.h"
#include <ctime>
#include <cstdlib>

using namespace std;

void fillArray(int* arr, int N)
{
	srand(time(0));
	for (int i = 0; i < N; ++i)
	{
		arr[i] = rand() % 5000;
	}
}

void showArray(int* arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	int n = 10;
	int *arr0 = new int[n];
	int *arr1 = new int[n] { -6, -3, 1, 9, -8, 5, 4, -6, 3, -3};
	fillArray(arr0, n);
	showArray(arr0, n);
	showArray(arr1, n);
	cout << "..." << endl;
	radix_sort(arr0, n, 10);
	counting_sort(arr1, n);
	showArray(arr0, n);
	showArray(arr1, n);

	delete[] arr0;
	delete[] arr1;
	return 0;
}
