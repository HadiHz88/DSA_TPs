#include <stdbool.h>

// Bubble Sort - O(n²) time, O(1) space - Repeatedly steps through the list, compares adjacent elements and swaps them if needed
extern bool bubbleSort(int arr[], int size);

// Selection Sort - O(n²) time, O(1) space - Divides array into sorted and unsorted sections, repeatedly selects smallest element from unsorted section
extern bool selectionSort(int arr[], int size);

// Insertion Sort - O(n²) time, O(1) space - Builds sorted array one item at a time by inserting each new item into its correct position
extern bool insertionSort(int arr[], int size);

// Quick Sort - O(n log n) average, O(n²) worst case time, O(log n) space - Divide and conquer algorithm that picks a pivot and partitions array around it
extern bool QuickSort(int arr[], int size);

// Utility function for Quick Sort - recursive implementation
extern void QuickSortUtil(int arr[], int low, int high);

// Partitioning function for Quick Sort - arranges elements around pivot
extern int Partition(int arr[], int low, int high);

// Merge Sort - O(n log n) time, O(n) space - Divide and conquer algorithm that divides array in half, sorts, then merges
bool mergeSort(int arr[], int size);

// Recursive utility function for Merge Sort
void mergeSortUtil(int arr[], int lower, int upper);

// Function to merge two sorted subarrays
void fusion(int arr[], int lower, int upper, int middle);

// Helper function for Radix Sort - finds maximum value in array
int getMax(int arr[], int n);

// Counting Sort used as a subroutine in Radix Sort - O(n+k) time and space where k is the range of input
void countingSort(int arr[], int size, int place);

// Radix Sort - O(d*(n+k)) time, O(n+k) space where d is the number of digits and k is the range per digit
void radixSort(int arr[], int size);

// Utility function to swap two integers
extern void swap(int *a, int *b);

// Function to generate an array with random values
extern void generateRandomArray(int arr[], int size, int max);

// Function to print the contents of an array
extern void printArray(int arr[], int size);
