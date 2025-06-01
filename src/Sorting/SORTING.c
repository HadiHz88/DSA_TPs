#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> // Added for time() in generateRandomArray
#include "SORTING.h"

/**
 * Bubble Sort Algorithm
 * Time Complexity: O(n²) worst and average case, O(n) best case when array is already sorted
 * Space Complexity: O(1) - in-place sorting
 *
 * Repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order.
 * Uses an optimization to stop early if no swaps occur in a pass.
 */
bool bubbleSort(int arr[], int size)
{
    if (!arr || size <= 0)
    {
        printf("Error: Invalid array.\n");
        return false;
    }

    bool swapped = true;

    // Each pass will bubble the largest unsorted element to its correct position
    for (int pass = size - 1; pass >= 0 && swapped; pass--)
    {
        swapped = false;
        for (int i = 0; i < pass; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(&arr[i], &arr[i + 1]);
                swapped = true;
            }
        }
    }

    return true;
}

/**
 * Selection Sort Algorithm
 * Time Complexity: O(n²) in all cases
 * Space Complexity: O(1) - in-place sorting
 *
 * Divides the input array into two portions: sorted and unsorted.
 * Repeatedly selects the smallest element from the unsorted portion and adds it to the end of the sorted portion.
 */
bool selectionSort(int arr[], int size)
{
    if (arr == NULL || size <= 0)
    {
        printf("Error: Invalid input\n");
        return false;
    }

    for (int i = 0; i < size - 1; i++)
    {
        int min = i; // Index of the smallest element in the unsorted portion
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j; // Update index of the minimum element
            }
        }
        // Swap the found minimum element with the first element of unsorted portion
        if (min != i)
        {
            swap(&arr[i], &arr[min]);
        }
    }
    return true;
}

/**
 * Insertion Sort Algorithm
 * Time Complexity: O(n²) worst and average case, O(n) best case when array is nearly sorted
 * Space Complexity: O(1) - in-place sorting
 *
 * Builds the final sorted array one item at a time.
 * Takes one element from the input array and places it in the correct position within the sorted portion.
 */
bool insertionSort(int arr[], int size)
{
    if (arr == NULL || size <= 0)
    {
        printf("Error: Invalid input\n");
        return false;
    }

    int j, key;
    for (int i = 1; i < size; i++)
    {
        key = arr[i]; // Current element to be inserted in sorted subarray
        j = i;

        // Move elements of arr[0..i-1] that are greater than key to one position ahead
        while (arr[j - 1] > key && j > 0)
        {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key; // Insert the key at its correct position
    }
    return true;
}

/**
 * Merge Sort Algorithm
 * Time Complexity: O(n log n) in all cases
 * Space Complexity: O(n) - requires additional array for merging
 *
 * Divides the array into halves, recursively sorts them, then merges the sorted halves.
 */
bool mergeSort(int arr[], int size)
{
    if (arr == NULL)
    {
        printf("Error: Invalid input\n");
        return false;
    }
    mergeSortUtil(arr, 0, size - 1); // Call the recursive utility function
    return true;
}

/**
 * Merge Sort Utility Function - handles the recursive division of the array
 */
void mergeSortUtil(int arr[], int lower, int upper)
{
    int middle;
    if (lower < upper)
    {
        middle = (lower + upper) / 2;          // Find the middle point
        mergeSortUtil(arr, lower, middle);     // Sort first half
        mergeSortUtil(arr, middle + 1, upper); // Sort second half
        fusion(arr, lower, upper, middle);     // Merge the sorted halves
    }
}

/**
 * Merge (Fusion) Function for Merge Sort
 * Combines two sorted subarrays into one sorted array
 */
void fusion(int arr[], int lower, int upper, int middle)
{
    int i = lower, j = middle + 1, k = 0;
    int newArray[upper - lower + 1]; // Temporary array to hold merged elements

    // Merge the two subarrays by comparing elements
    while (i <= middle && j <= upper)
    {
        if (arr[i] < arr[j])
        {
            newArray[k++] = arr[i++];
        }
        else
        {
            newArray[k++] = arr[j++];
        }
    }

    // Copy remaining elements from left subarray
    while (i <= middle)
        newArray[k++] = arr[i++];

    // Copy remaining elements from right subarray
    while (j <= upper)
        newArray[k++] = arr[j++];

    // Copy merged elements back to original array
    for (i = lower, j = 0; j < k; i++, j++)
    {
        arr[i] = newArray[j];
    }
}

/**
 * Counting Sort Function (used by Radix Sort)
 * Time Complexity: O(n+k) where k is the range of input
 * Space Complexity: O(n+k)
 *
 * Sorts elements based on specific place value (ones, tens, hundreds, etc.)
 */
void countingSort(int arr[], int size, int place)
{
    int output[size + 1]; // Output array

    // Find the largest element at the current place value
    int max = (arr[0] / place) % 10;
    int i;

    for (i = 1; i < size; i++)
    {
        if (((arr[i] / place) % 10) > max)
        {
            max = arr[i];
        }
    }
    int count[max + 1]; // Count array

    // Initialize count array with zeros
    for (i = 0; i < max; ++i)
        count[i] = 0;

    // Store the count of occurrences of each digit at the current place value
    for (i = 0; i < size; i++)
    {
        count[(arr[i] / place) % 10]++;
    }

    // Change count[i] so that it contains the position of this digit in output[]
    for (i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (i = size - 1; i >= 0; i--)
    {
        output[count[(arr[i] / place) % 10] - 1] = arr[i];
        count[(arr[i] / place) % 10]--;
    }

    // Copy the output array to arr[]
    for (i = 0; i < size; i++)
    {
        arr[i] = output[i];
    }
}

/**
 * Radix Sort Algorithm
 * Time Complexity: O(d * (n+k)) where d is the number of digits and k is the range per digit
 * Space Complexity: O(n+k)
 *
 * Sorts integers by processing individual digits from least significant to most significant.
 */
void radixSort(int arr[], int size)
{
    int max = getMax(arr, size); // Find the maximum number to know number of digits

    // Do counting sort for every digit
    for (int place = 1; max / place > 0; place *= 10)
        countingSort(arr, size, place);
}

/**
 * Helper function to find the maximum value in an array
 */
int getMax(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

/**
 * Utility function to swap two integers
 */
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * Function to generate an array with random values
 * Fills the given array with random integers between 0 and max-1
 */
void generateRandomArray(int arr[], int size, int max)
{
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % max;
    }
}

/**
 * Function to print the contents of an array
 * Outputs each element separated by spaces
 */
void printArray(int arr[], int size)
{
    if (arr == NULL || size <= 0)
    {
        printf("Error: Invalid input\n");
        return;
    }

    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    return;
}
