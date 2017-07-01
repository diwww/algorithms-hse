/**
 * The current assessment is to implement Quick Sort algorithm.
 * The idea might seem a bit not clear for the first time, but spend some time on
 * understanding the fundamentals of the algorithm. After you really understand how
 * the algorithm works, it will be really easy to implement all methods that are
 * presented here.
 *
 * The only file that you need to upload for the assessment is quick_sort.cpp - your
 * implementation for current header file.
 *
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * You should consider the following descriptions of the methods and find out
 * how they should interact with each other.
 *
 * Then you need to create quick_sort.cpp file and implement all declared functions from here.
 *
 * If you need some additional functions to implement - be free to add them to your quick_sort.cpp
 * file (not quick_sort.h file!). In fact, that will be appreciated if it is used properly.
 *
 * Your quick_sort.cpp file MUST be compatible with this version of current file. So, again:
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * All methods should be implemented and all of them should be used in your work.
 *
 * You should consider that all methods should work in isolation and all of them MUST NOT affect any
 * system state (i.e. static fields and so on).
 *
 * Don't provide any "int main()" method in your quick_sort.cpp file. You can create it for self
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
 * Declaring the method signature that should perform choosing of the pivot index.
 * "typedef" here is just a convenient way to declare a method that will take two integer parameters
 * and return one integer value. This also make it easier to pass such methods as a parameters to
 * other methods (which is necessary in current assignment).
 */
typedef int(*pivot_chooser) (int from, int to);

class q_sort {

public:

    /*
     * This is a method to sort array using quick sort algorithm and strategy
     * of picking middle element in sub-arrays as a pivot element.
     *
     * Parameters:
     *  int* arr - array to sort.
     *  int n    - size of the array to sort. Strictly positive integer value.
     */
    static void quick_sort_middle(int* arr, int n);

    /*
     * This is a method to sort array using quick sort algorithm and strategy
     * of picking last element in sub-arrays as a pivot element.
     *
     * Parameters:
     *  int* arr - array to sort.
     *  int n    - size of the array to sort. Strictly positive integer value.
     */
    static void quick_sort_last(int* arr, int n);

    /*
     * This is a method to sort array using quick sort algorithm and strategy
     * of picking random element in sub-arrays as a pivot element.
     *
     * Parameters:
     *  int* arr - array to sort.
     *  int n    - size of the array to sort. Strictly positive integer value.
     */
    static void quick_sort_rand(int* arr, int n);

private:
    /*
     * One of the implementations of pivot_chooser.
     * Getting index of middle element in specified bounds.
     *
     * For instance: if "from" equals 5 and "to" equals then the method should return 6.
     *
     * Parameters:
     *  int from - first index of the array bounds (inclusive). Non-negative integer value.
     *  int to   - last index of the (exclusive). Strictly positive integer value.
     *
     * Returns:
     *  index of the chosen pivot value (in this case, the "middle" index in specified bounds).
     *  Non-negative integer value.
     */
    static int get_middle_pivot(int from, int to);


    /*
     * One of the implementations of pivot_chooser.
     * Getting index of last element in specified bounds
     *
     * Parameters:
     *  int from - first index of the array bounds (inclusive). Non-negative integer value.
     *  int to   - last index of the (exclusive). Strictly positive integer value.
     *
     * Returns:
     *  index of the chosen pivot value (in this case, the last index in specified bounds).
     *  Non-negative integer value.
     */
    static int get_last_pivot(int from, int to);

    /*
     * One of the implementations of pivot_chooser.
     * Getting index of random element in specified bounds
     *
     * Parameters:
     *  int from - first index of the array bounds (inclusive). Non-negative integer value.
     *  int to   - last index of the (exclusive). Strictly positive integer value.
     *
     * Returns:
     *  index of the chosen pivot value (in this case, a random index in specified bounds). Non-negative integer value.
     */
    static int get_rand_pivot(int from, int to);

    /*
     * The generalized method of the Quick Sort algorithms. It does the sorting and it is recommended
     * to have recursive call to itself with modified parameters.
     *
     * Parameters:
     *  int* arr                    - array to sort.
     *  int from                    - first index of the array from which we need to perform sorting (inclusive).
     *                                Non-negative integer value.
     *  int to                      - last index of the array from which we need to perform sorting (exclusive).
     *                                Strictly positive integer value.
     *  pivot_chooser pivot_chooser - reference to the method that is used to choose appropriate pivot index.
     *                                (see typedef declaration above the class declaration)
     */
    static void quick_sort(int* arr, int from, int to, pivot_chooser pivot_chooser);

    /*
     * Method to rearrange values of the specified array in specified bounds using the index of the pivot value.
     * Consider arr[pivot_index] as a value, that is used as a pivot. You need to swap items of the array in
     * specified bounds so that left part of the sub-array has elements that are LESS OR EQUAL to the pivot,
     * and right part of the sub-array has elements that are LARGER OR EQUAL to the pivot. You need also put your
     * pivot value between these parts (between left and right) and return its index.
     *
     * For example, if the pivot value (not index) equals 7. Than the result sub-array should look like this:
     * [ (elements that are <= 7) , 7, (elements that are >= 7) ].
     * Moreover you need to return the index of this 7.
     *
     * The bounds of the array doesn't change and rearrangement occurs only within specified bounds.
     *
     * Parameters:
     *  int* arr        - array where rearrangement occurs.
     *  int from        - first index of the array from which we need to perform rearrangement (inclusive).
     *                    Non-negative integer value.
     *  int to          - last index of the array from which we need to perform rearrangement (exclusive).
     *                    Strictly positive integer value.
     *  int pivot_index - index of the pivot value that we use to perform rearrangement. pivot_index is always
     *                    within the bounds [from, to).
     *
     * Returns:
     *  new index of the position of the pivot value in rearranged sub-array. Non-negative integer value.
     */
    static int rearrange_array_with_pivot(int* arr, int from, int to, int pivot_index);
};