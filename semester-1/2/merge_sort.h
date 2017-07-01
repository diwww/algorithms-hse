/**
 * The current assessment is to implement Merge Sort algorithm.
 * The idea might seem a bit not clear for the first time, but spend some time on
 * understanding the fundamentals of the algorithm. After you really understand how
 * the algorithm works, it will be really easy to implement all methods that are
 * presented here.
 *
 * The only file that you need to upload for the assessment is merge_sort.cpp - your
 * implementation for current header file.
 *
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * You should consider the following descriptions of the methods and find out
 * how they should interact with each other.
 *
 * Then you need to create merge_sort.cpp file and implement all declared functions from here.
 *
 * If you need some additional functions to implement - be free to add them to your merge_sort.cpp
 * file (not merge_sort.h file!). In fact, that will be appreciated if it is used properly.
 *
 * Your merge_sort.cpp file MUST be compatible with this version of current file. So, again:
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * All methods should be implemented and all of them should be used in your work.
 *
 * You should consider that all methods should work in isolation and all of them MUST NOT affect any
 * system state (i.e. static fields and so on).
 *
 * Don't provide any "int main()" method in your merge_sort.cpp file. You can create it for self
 * testing in another separate file.
 *
 * Don't forget about comments and good coding style, which will be appreciated.
 * 
 * NOTE: There are some disclaimers in comments about possible values that are passed to the methods.
 * These comments like "Non-negative integer value" or "Strictly positive integer value" are just
 * some hints for you to be aware of possible values that can be passed to your method.
 * In other words, if there is a comment that the input parameter is strictly positive we will not
 * test that method with negative values of this parameter so you don't need to consider such cases.
 * In practice, such comments are widely used in API design where you do not guarantee correct behavior
 * in case of wrong parameters (which would be a nonsense if you do).
 */


/*
 * This is the main method of sorting. In real world, this should be the only
 * method that is exposed to user.
 *
 * Parameters:
 *  int* arr - array to sort.
 *  int n    - size of the array to sort. Strictly positive integer value.
 */
void merge_sort(int *arr, int n);

/*
 * Method to merge two sorted sections of the array to one sorted section.
 *
 * For instance:
 * if you pass array [ 7, 1, 3, 5, 7, 2, 4, 6, 1 ] with start_first == 1, start_second == 5 and end == 8 then
 * the array must be [ 7, 1, 2, 3, 4, 5, 6, 7, 1 ] after the method execution.
 * int end          - bound of both sorted
 *  Parameters:
 *  int* arr         - array, which has two sorted sections and needs to merge them to one sorted section.
 *  int start_first  - index of the start of the first sorted section of the array (inclusive). Non-negative integer value.
 *  int start_second - index of the start of the second sorted section of the array (inclusive). Non-negative integer value.
 *  int end          - bound of both sorted sections (exclusive). Strictly positive integer value.
 */
void merge(int* arr, int start_first, int start_second, int end);

/*
 * Recursively splits array into two parts and merges it within bounds [ left (inclusively), right (exclusively) )
 *
 * Parameters:
 *  int* arr  - array to sort.
 *  int left  - left bound (inclusive). Non-negative integer value.
 *  int right - right bound (exclusive). Strictly positive integer value.
 */
void divide_and_merge(int *arr, int left, int right);