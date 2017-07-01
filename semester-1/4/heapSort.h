/**
 * The current assessment is to implement Heap Sort algorithm and the Heap datastructure itself.
 * The idea might seem a bit not clear for the first time, but spend some time on
 * understanding the fundamentals of the algorithm. After you really understand how
 * the algorithm works, it will be really easy to implement all methods that are
 * presented here.
 *
 * The only file that you need to upload for the assessment is heap_sort.cpp - your
 * implementation for current header file.
 *
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * You should consider the following descriptions of the methods and find out
 * how they should interact with each other.
 *
 * Then you need to create heap_sort.cpp file and implement all declared functions from here.
 *
 * If you need some additional functions to implement - be free to add them to your heap_sort.cpp
 * file (not heap_sort.h file!). In fact, that will be appreciated if it is used properly.
 *
 * Your heap_sort.cpp file MUST be compatible with this version of current file. So, again:
 * YOU MUST NOT MODIFY CURRENT FILE!!!
 *
 * All methods should be implemented and all of them should be used in your work.
 *
 * You should consider that all methods should work in isolation and all of them MUST NOT affect any
 * system state (i.e. static fields and so on).
 *
 * Don't provide any "int main()" method in your heap_sort.cpp file. You can create it for self
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
 * Class to have a function of sorting.
 */
class Heapsort {
public:
    /*
     * The Heap sort algorithm. The algorithm should sort the array that is passed
     * as a parameter of the function in non-decreasing order.
     *
     * In this function you need to create an instance of the "Heap" class and use it for sorting.
     * Then, if you allocated memory in Heap, you need properly deallocate that memory.
     *
     * KEY HINT: in this case, sort is not meant to be in place.
     * So we assume here that you are going to use some extra memory
     * for Heap data structure itself while heapSort method is processing.
     *
     * Parameters:
     *  int *arr - array to sort.
     *  int n    - size of the array.
     */
    static void heapSort(int *arr, int n);
};

/**
 * Class that represents simplified heap data structure.
 *
 * Current heap type is dedicated to extract THE SMALLEST value
 * from the heap.
 *
 * So every parent element has value less or equal than child elements.
 * This state is referred as "heap" state later in current file.
 *
 * So, you need to figure it out, how you can simply use such heap
 * type in assistance of sorting.
 *
 */
class Heap {
// commented for testing
//private:
public:
    /**
     * Inner values in the heap are stored in this array. This array should
     * have proper "heap" state between any calls of the public functions.
     *
     * In other words, if somebody calls any public functions of this class
     * (except destructor) then the array should have values in such order,
     * that is used in heap data structure in array implementation.
     */
    int *storage;

    /** Number of elements that are currently in current instance of heap */
    int currentSize;

    /**
     * Number of elements that can be stored in current instance of heap.
     * The value should be once initialized in constructor and never change
     * its value.
     */
    const int capacity;

public:
    /**
     * Constructor method of the heap.
     *
     * Parameters:
     *  int *source - array that is need to be stored in heap. The passed array
     *                can be in any order (sorted or not).
     *  int n       - number of elements in passed array. ALSO this value should
     *                be used as a capacity of the current heap instance.
     *
     * Also, this is IMPORTANT not to modify the array that is passes as a parameter.
     * That doesn't mean that you should store that array in such way that is passed,
     * but to copy it to the internal storage.
     */
    Heap(const int *source, const int n);

    /**
     * Destructor of the heap. Don't forget to clean all allocated memory here.
     */
    ~Heap();

    /**
     * Getting the minimum value from the heap. This method doesn't change state of
     * the heap.
     *
     * Complexity: O(1)
     */
    int getMin();

    /**
     * Getting the minimum value from the heap and also extracting it from the heap.
     * After this function, the heap should be modified and be in proper "heap" state.
     *
     * If heap currently has 0 elements stored, then the std::length_error exception
     * should be thrown with informative message.
     *
     * Complexity: O(log(current_size))
     *
     * Returns:
     *  minimum value that is in the heap.
     */
    int extractMin();

    /**
     * Inserting the value in the heap.
     * After this function, the heap should be modified and be in proper "heap" state.
     *
     * If heap currently has "capacity" elements stored, then the std::length_error exception
     * should be thrown with informative message.
     *
     * Complexity: O(log(current_size + 1))
     */
    void insert(const int value);

    // commented for testing
//private:
    /**
     * Method to perform heapify operation to the specified element in terms of checking
     * the "heap" state for it children's values. In other words we need to "bubble-down"
     * the specified element swapping it with one of the child nodes if necessary. After the
     * function execution, the heap storage should be in proper "heap" state (children nodes
     * are equal or greater than parent node).
     *
     * Hint: this method should be used in "extract_min" function.
     *
     * Complexity: O(log(current_size))
     */
    void heapifyDown(int index);

    /**
     * Method to perform heapify operation to the specified element in terms of checking
     * the "heap" state for it parent's values. In other words we need to "bubble-up"
     * the specified element swapping it with parent node if necessary. After the
     * function execution, the heap storage should be in proper "heap" state (children nodes
     * are equal or greater than parent node).
     *
     * Hint: this method should be used in "insert" function.
     *
     * Complexity: O(log(current_size))
     */
    void heapifyUp(int index);
};
