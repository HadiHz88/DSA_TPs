#include <stdio.h>
#include <stdlib.h>
#include "HEAP.h"

/**
 * Creates a new heap with the specified capacity and type
 * Time Complexity: O(1)
 * Space Complexity: O(capacity)
 *
 * @param capacity Initial size of the heap array
 * @param heapType Type of heap (Max or Min)
 * @return A newly allocated Heap structure
 */
Heap createHeap(int capacity, int heapType)
{
    // Allocate memory for the heap structure
    Heap H = (Heap)malloc(sizeof(*H));
    if (!H)
    {
        printf("Error while allocating memory\n");
        exit(EXIT_FAILURE);
    }
    H->type = heapType;
    H->count = 0;
    H->capacity = capacity;

    // Allocate memory for the array that will store the heap HeapElements
    H->array = (HeapElement *)malloc(sizeof(HeapElement) * H->capacity);
    if (!H->array)
    {
        printf("Error while allocating memory\n");
        free(H);
        exit(EXIT_FAILURE);
    }
    return H;
}

/**
 * Returns the parent index of an HeapElement at index i
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * @param H Heap structure
 * @param i Index of the HeapElement
 * @return Index of the parent or -1 if no parent exists
 */
int parentHeap(Heap H, int i)
{
    if (i <= 0 || i >= H->count)
    {
        return -1; // No parent exists
    }
    return ((i - 1) / 2); // Parent index formula
}

/**
 * Returns the left child index of an HeapElement at index i
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * @param H Heap structure
 * @param i Index of the HeapElement
 * @return Index of the left child or -1 if no left child exists
 */
int leftHeapChild(Heap H, int i)
{
    int left = 2 * i + 1; // Left child index formula
    if (left >= H->count)
        return -1; // No left child exists
    return left;
}

/**
 * Returns the right child index of an HeapElement at index i
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * @param H Heap structure
 * @param i Index of the HeapElement
 * @return Index of the right child or -1 if no right child exists
 */
int rightHeapChild(Heap H, int i)
{
    int right = 2 * i + 2; // Right child index formula
    if (right >= H->count)
        return -1; // No right child exists
    return right;
}

/**
 * Returns the top HeapElement of the heap without removing it
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * @param H Heap structure
 * @return The top HeapElement or -1 if heap is empty
 */
HeapElement getHeapTop(Heap H)
{
    if (H->count == 0)
        return -1;      // Heap is empty
    return H->array[0]; // Top HeapElement is at index 0
}

/**
 * Maintains the heap property by moving an HeapElement down to its correct position
 * Time Complexity: O(log n) where n is the number of HeapElements
 * Space Complexity: O(log n) due to recursion stack
 *
 * @param H Pointer to heap structure
 * @param i Index of the HeapElement to percolate down
 */
void percolateDown(Heap *H, int i)
{
    int left, right, max, tmp;
    left = leftHeapChild(*H, i);
    right = rightHeapChild(*H, i);
    max = i; // Assume current node is largest

    // Find the largest among node i, left child and right child
    if (left != -1 && (*H)->array[left] > (*H)->array[max])
        max = left;
    if (right != -1 && (*H)->array[right] > (*H)->array[max])
        max = right;

    // If largest is not the current node, swap and recursively percolate down
    if (max != i)
    {
        tmp = (*H)->array[i];
        (*H)->array[i] = (*H)->array[max];
        (*H)->array[max] = tmp;
        percolateDown(H, max); // Recursively percolate down
    }
}

/**
 * Removes and returns the maximum HeapElement from the heap
 * Time Complexity: O(log n) where n is the number of HeapElements
 * Space Complexity: O(log n) due to the percolateDown call
 *
 * @param H Pointer to heap structure
 * @return The maximum HeapElement or -1 if heap is empty
 */
HeapElement deleteHeapMax(Heap *H)
{
    HeapElement data;
    if ((*H)->count == 0)
        return -1; // Heap is empty

    // Store the max HeapElement (root)
    data = (*H)->array[0];

    // Replace root with last HeapElement
    (*H)->array[0] = (*H)->array[(*H)->count - 1];
    (*H)->count--;

    // Restore heap property
    percolateDown(H, 0); // Note: This should be percolateDown, case sensitive!

    return data;
}

/**
 * Doubles the capacity of the heap when it becomes full
 * Time Complexity: O(n) where n is the number of HeapElements
 * Space Complexity: O(n)
 *
 * @param H Pointer to heap structure
 */
void resizeHeap(Heap *H)
{
    HeapElement *old_array = (*H)->array;

    // Allocate new array with twice the capacity
    (*H)->array = (HeapElement *)malloc(sizeof(HeapElement) * (*H)->capacity * 2);
    if (!(*H)->array)
    {
        printf("Error while allocating memory\n");
        exit(EXIT_FAILURE);
    }

    // Copy HeapElements from old array to new array
    for (int i = 0; i < (*H)->capacity; i++)
    {
        (*H)->array[i] = old_array[i];
    }

    // Update capacity and free old array
    (*H)->capacity *= 2;
    free(old_array);
}

/**
 * Inserts a new HeapElement into the heap
 * Time Complexity: O(log n) where n is the number of HeapElements
 * Space Complexity: O(1)
 *
 * @param H Pointer to heap structure
 * @param data HeapElement to insert
 */
void insertHeap(Heap *H, HeapElement data)
{
    int i;

    // Resize if heap is full
    if ((*H)->count == (*H)->capacity)
        resizeHeap(H);

    // Add new HeapElement at the end
    (*H)->count++;
    i = (*H)->count - 1;

    // Percolate up: move the HeapElement up until heap property is satisfied
    while (i > 0 && data > (*H)->array[(i - 1) / 2])
    {
        (*H)->array[i] = (*H)->array[(i - 1) / 2];
        i = (i - 1) / 2; // Move to parent
    }

    // Place the HeapElement at its correct position
    (*H)->array[i] = data;
}

/**
 * Deallocates all memory used by the heap
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * @param H Pointer to heap structure pointer
 */
void destroyHeap(Heap *H)
{
    if (!H || !*H)
        return; // Nothing to free

    free((*H)->array); // Free the array
    free(*H);          // Free the heap structure
    *H = NULL;         // Set the pointer to NULL
}

/**
 * Constructs a heap from an array of HeapElements (heapify)
 * Time Complexity: O(n) where n is the number of HeapElements
 * Space Complexity: O(1)
 *
 * @param H Pointer to heap structure
 * @param arr Array of HeapElements
 * @param n Number of HeapElements in the array
 */
void buildHeap(Heap *H, int arr[], int n)
{
    if (!H)
        return;

    // Resize heap if necessary
    while (n > (*H)->capacity)
        resizeHeap(H);

    // Copy HeapElements from array to heap
    for (int i = 0; i < n; i++)
        (*H)->array[i] = arr[i];

    (*H)->count = n;

    // Heapify: start from the last non-leaf node and percolate down
    for (int i = (n - 1) / 2; i >= 0; i--)
    {
        percolateDown(H, i);
    }
}
