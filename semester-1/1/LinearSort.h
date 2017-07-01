/**
 * The current assessment is to implement Radix Sort with specified numerical base.
 * The idea might seem a bit not clear for the first time, but spend some time on
 * understanding the fundamentals of the algorithm. After you really understand how
 * the algorithm works, it will be really easy to implement all methods that are
 * presented here.
 *
 * In this work you first time should use specified templates that are sent
 * to you by the teacher.
 *
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * You should consider the following descriptions of the methods and find out
 * how they should interact with each other.
 *
 * Then you need to create RadixSort.cpp file and implement all declared functions from here.
 *
 * If you need some additional functions to implement - be free to add them to your *.cpp
 * file (not .h file!). In fact, that will be appreciated if it is used properly.
 *
 * Your *.cpp file MUST be compatible with this version of current file. So, again:
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * All methods should be implemented and all of them should be used in your work (in RadixSort.cpp).
 *
 * You should consider that all methods should work in isolation and all of them MUST NOT affect any
 * system state (i.e. static fields and so on).
 *
 * Don't provide any "int main()" method in your RadixSort.cpp file. You can create it for self
 * testing in another separate file.
 *
 * Don't forget about commentaries and good coding style, which will be appreciated.
 */

/**
 *  This is the method of counting sorting.
 *
 * Parameters:
 *  int* arr - array to sort. It may contain positive numbers as well as negative ones.
 *  int n    - size of the array to sort. Strictly positive integer value.
 */
void counting_sort(int* arr, int n);

/**
 * This is the method of radix sorting.
 *
 * Parameters:
 *  int* arr - array to sort.
 *  int n    - size of the array to sort. Strictly positive integer value.
 *  int base - the radix (or base) which should be used in sorting. Strictly positive and less or equal than INT16_MAX.
 */
void radix_sort(int *arr, int n, int base);


/** Other methods that you need to use, but normally not exposed to user */

/**
 * Method to sort array at some particular specified digit with specified base.
 * For instance, if you specified array 1130, 2220, 3310 with base 10 and digit_index 1, the array must be sorted in
 * the order 3310, 2220, 1130.
 *
 * Parameters:
 *  int* arr        - array to sort.
 *  int n           - size of the array to sort. Strictly positive integer value.
 *  int base        - the radix (or base) which should be used in sorting. Strictly positive and less or equal
 *                    than INT16_MAX.
 *  int digit_index - index of the digit that is used to sort the incoming array. Indexing is going from right to
 *                    left from index 0. For instance, in number 123 the 0th digit is 3. Non-negative integer value.
 */
void sort_at_digit(int *arr, int n, int base, int digit_index);

/**
 * Getting the value of the digit in specified number using specified base (radix).
 *
 * Parameters:
 *  int number      - number where a digit is being searched. Integer value.
 *  int base        - the radix (or base) which should be used in sorting. Strictly positive and less or equal
 *                    than INT16_MAX.
 *  int digit_index - index of the digit that is used to sort the incoming array. Indexing is going from right to left
 *                    from index 0. For instance, in number 123 the 0th digit is 3. Non-negative integer value.
 *
 *  Returns: integer value of the digit. Integer value.
 */
int get_digit(int number, int base, int digit_index);

/**
 * Utility method. Find and return maximal integer of an array
 *
 * Parameters:
 *  int* arr - array.
 *  int n    - size of the array. Strictly positive integer value.
 */
int max_element(int* arr, int n);

/**
 * Utility method. Find and return minimal integer of an array
 *
 * Parameters:
 *  int* arr - array.
 *  int n    - size of the array. Strictly positive integer value.
 */
int min_element(int* arr, int n);

/**
 * Utility method. It is not really connected with radix sort, but is useful and needed to be used
 * Copying the numbers from one array to another using specified number of elements to copy.
 *
 * Parameters:
 *  int* from - array-source of elements that are needed to be copied.
 *  int* to   - array that is used to store the copied elements.
 *  int size  - number of elements to be copied from index 0. Non-negative integer value.
 */
void copy_array(int *from, int *to, int size);



