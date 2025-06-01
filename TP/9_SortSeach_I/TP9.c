#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h> // Add this for gettimeofday

#define ARRAY_SIZE 100000 // Adjust the size of the array as needed

// Function to generate random integer between min and max
int random_int(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// Utility function to find minimum of two elements
int min(int x, int y) { return (x <= y) ? x : y; }

// Function to generate random array
void generate_random_array(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = random_int(1, 100000); // Adjust the range of random values as needed
    }
}

// Function to sort the array (e.g., using quicksort algorithm)
void bubble_sort(int A[], int n)
{
    int pass, i, temp, swapped = 1;
    for (pass = n - 1; pass >= 0 && swapped; pass--)
    {
        swapped = 0;
        for (i = 0; i < pass; i++)
        {
            if (A[i] > A[i + 1])
            {
                // swap elements
                temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
                swapped = 1;
            }
        }
    }
}

void sort_array(int array[], int size)
{
    // fill code here to test one o the sorting algorithm other than bubble sort
    return;
}

// Function to search in sorted array
int linear_search(int array[], int size, int key)
{
    for (int i = 0; i < size; i++)
        if (array[i] == key)
        {
            printf("element found at position %d\n", i);
            return 1;
        }
    return 0;
}

// An iterative binary search function.
int binary_search(int array[], int l, int r, int key)
{
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        // Check if x is present at mid
        if (array[m] == key)
            return m;
        // If x greater, ignore left half
        if (array[m] < key)
            l = m + 1;
        // If x is smaller, ignore right half
        else
            r = m - 1;
    }
    // If we reach here, then element was not present
    return -1;
}

// Function to search in sorted array
int ternarySearch(int l, int r, int key, int ar[])
{
    if (r >= l)
    {
        // Find the mid1 and mid2
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;
        // Check if key is present at any mid
        if (ar[mid1] == key)
        {
            return mid1;
        }
        if (ar[mid2] == key)
        {
            return mid2;
        }
        // Since key is not present at mid, check in which region it is present
        // then repeat the Search operation in that region
        if (key < ar[mid1])
        {
            // The key lies in between l and mid1
            return ternarySearch(l, mid1 - 1, key, ar);
        }
        else if (key > ar[mid2])
        {
            // The key lies in between mid2 and r
            return ternarySearch(mid2 + 1, r, key, ar);
        }
        else
        {
            // The key lies in between mid1 and mid2
            return ternarySearch(mid1 + 1, mid2 - 1, key, ar);
        }
    }
    // Key not found
    return -1;
}

// Function to search in sorted array
int exponentialSearch(int arr[], int n, int x)
{
    // If x is present at first location itself
    if (arr[0] == x)
        return 0;

    // Find range for binary search by
    // repeated doubling
    int i = 1;
    while (i < n && arr[i] <= x)
        i = i * 2;

    //  Call binary search for the found range.
    return binary_search(arr, i / 2, min(i, n - 1), x);
}

/* Returns index of x if present, else returns -1 */
int Fibonacci_search(int arr[], int x, int n)
{
    /* Initialize fibonacci numbers */
    int fibMMm2 = 0;              // (m-2)'th Fibonacci No.
    int fibMMm1 = 1;              // (m-1)'th Fibonacci No.
    int fibM = fibMMm2 + fibMMm1; // m'th Fibonacci

    /* fibM is going to store the smallest Fibonacci
    Number greater than or equal to n */
    while (fibM < n)
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    // Marks the eliminated range from front
    int offset = -1;

    /* while there are elements to be inspected. Note that
    we compare arr[fibMm2] with x. When fibM becomes 1,
    fibMm2 becomes 0 */
    while (fibM > 1)
    {
        // Check if fibMm2 is a valid location
        int i = min(offset + fibMMm2, n - 1);

        /* If x is greater than the value at index fibMm2,
        cut the subarray array from offset to i */
        if (arr[i] < x)
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }

        /* If x is greater than the value at index fibMm2,
        cut the subarray after i+1 */
        else if (arr[i] > x)
        {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }

        /* element found. return index */
        else
            return i;
    }

    /* comparing the last element with x */
    if (fibMMm1 && arr[offset + 1] == x)
        return offset + 1;

    /*element not found. return -1 */
    return -1;
}

int main()
{
    srand(time(NULL)); // Seed the random number generator
    struct timeval start_time, end_time;
    // Declare variables
    int unsorted_array[ARRAY_SIZE];
    int sorted_array[ARRAY_SIZE];
    int search_key = random_int(1, 100000); // Random search key
    // int search_key = 100004; // this key does not exist in the array
    // Generate random unsorted array
    generate_random_array(unsorted_array, ARRAY_SIZE);

    // Copy unsorted array to sorted array
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        sorted_array[i] = unsorted_array[i];
    }

    // Sort the sorted array
    gettimeofday(&start_time, NULL);
    bubble_sort(sorted_array, ARRAY_SIZE);
    gettimeofday(&end_time, NULL);
    double sort_time = (end_time.tv_sec - start_time.tv_sec) +
                       (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("Time taken to sort array with bubble sort is %lf seconds\n", sort_time);

    // Perform search in unsorted array and measure time using linear_search
    gettimeofday(&start_time, NULL);
    int v = linear_search(unsorted_array, ARRAY_SIZE, search_key);
    gettimeofday(&end_time, NULL);
    double search_time_unsorted = (end_time.tv_sec - start_time.tv_sec) +
                                  (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("Time taken to search in unsorted array is %lf seconds using linear search\n", search_time_unsorted);

    // Perform search in sorted array and measure time using ternarySearch
    gettimeofday(&start_time, NULL);
    int ternary_result = ternarySearch(0, ARRAY_SIZE - 1, search_key, sorted_array);
    gettimeofday(&end_time, NULL);
    double ternary_search_time_sorted = (end_time.tv_sec - start_time.tv_sec) +
                                        (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("Time taken to search in sorted array is %lf seconds using ternarySearch\n", ternary_search_time_sorted);
    printf("Ternary Search: Element %d %s at index %d\n", search_key,
           ternary_result != -1 ? "found" : "not found", ternary_result);

    // Perform search in sorted array and measure time using exponentialSearch
    gettimeofday(&start_time, NULL);
    int exp_result = exponentialSearch(sorted_array, ARRAY_SIZE, search_key);
    gettimeofday(&end_time, NULL);
    double exponential_search_time_sorted = (end_time.tv_sec - start_time.tv_sec) +
                                            (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("Time taken to search in sorted array is %lf seconds using exponentialSearch\n", exponential_search_time_sorted);
    printf("Exponential Search: Element %d %s at index %d\n", search_key,
           exp_result != -1 ? "found" : "not found", exp_result);

    // Perform search in sorted array and measure time using Fibonacci_search
    gettimeofday(&start_time, NULL);
    int fib_result = Fibonacci_search(sorted_array, search_key, ARRAY_SIZE);
    gettimeofday(&end_time, NULL);
    double fibonacci_search_time_sorted = (end_time.tv_sec - start_time.tv_sec) +
                                          (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("Time taken to search in sorted array is %lf seconds using Fibonacci Search\n", fibonacci_search_time_sorted);
    printf("Fibonacci Search: Element %d %s at index %d\n", search_key,
           fib_result != -1 ? "found" : "not found", fib_result);

    return 0;
}
