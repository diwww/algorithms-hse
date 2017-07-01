// Name:    Surovtsev Maxim
// Group:   BSE151

#include "LinearSort.h"
#include <cmath>

void counting_sort(int *arr, int n) {
    int max = max_element(arr, n);
    int min = min_element(arr, n);
    int lenC = max - min + 1;

    int *B = new int[n];
    int *C = new int[lenC];

    for (int i = 0; i < lenC; ++i) {
        C[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        C[arr[i] - min] = C[arr[i] - min] + 1;
    }
    for (int i = 1; i < lenC; ++i) {
        C[i] = C[i] + C[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        C[arr[i] - min] = C[arr[i] - min] - 1;
        B[C[arr[i] - min]] = arr[i];
    }
    copy_array(B, arr, n);

    delete[] B;
    delete[] C;
}

void radix_sort(int *arr, int n, int base) {
    // number of digits in the number
    int count = int(log(max_element(arr, n)) / log(base)) + 1;

    for (int i = 0; i < count; ++i) {
        sort_at_digit(arr, n, base, i);
    }
}

void sort_at_digit(int *arr, int n, int base, int digit_index) {
    int lenC = base;

    int *B = new int[n];
    int *C = new int[lenC];

    for (int i = 0; i < lenC; ++i) {
        C[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        int digit = get_digit(arr[i], base, digit_index);
        C[digit] = C[digit] + 1;
    }
    for (int i = 1; i < lenC; ++i) {
        C[i] = C[i] + C[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        int digit = get_digit(arr[i], base, digit_index);
        C[digit] = C[digit] - 1;
        B[C[digit]] = arr[i];
    }
    copy_array(B, arr, n);

    delete[] B;
    delete[] C;
}

int get_digit(int number, int base, int digit_index) {
    for (int i = 0; i < digit_index; ++i) {
        number = number / base;
    }
    return number % base;
}

int max_element(int *arr, int n) {
    int max = 0;
    for (int i = 0; i < n; ++i)
        if (arr[i] > max) max = arr[i];
    return max;
}

int min_element(int *arr, int n) {
    int min = arr[0];
    for (int i = 1; i < n; ++i)
        if (arr[i] < min) min = arr[i];
    return min;
}

void copy_array(int *from, int *to, int size) {
    for (int i = 0; i < size; ++i) {
        to[i] = from[i];
    }
}