#include "DEF_HEAP.h"

// Creates a new heap with specified capacity and type (Max or Min heap)
// Time Complexity: O(1), Space Complexity: O(capacity)
extern Heap createHeap(int capacity, int Heap_Type);

// Returns the parent index of the HeapElement at index i
// Time Complexity: O(1), Space Complexity: O(1)
extern int parentHeap(Heap H, int i);

// Returns the left child index of the HeapElement at index i
// Time Complexity: O(1), Space Complexity: O(1)
extern int leftHeapChild(Heap H, int i);

// Returns the right child index of the HeapElement at index i
// Time Complexity: O(1), Space Complexity: O(1)
extern int rightHeapChild(Heap H, int i);

// Returns the top HeapElement of the heap without removing it
// Time Complexity: O(1), Space Complexity: O(1)
extern HeapElement getHeapTop(Heap H);

// Maintains the heap property by moving an HeapElement down to its correct position
// Time Complexity: O(log n), Space Complexity: O(log n) due to recursion
extern void percolateDown(Heap *H, int i);

// Removes and returns the maximum HeapElement from the heap
// Time Complexity: O(log n), Space Complexity: O(1)
extern HeapElement deleteHeapMax(Heap *H);

// Doubles the capacity of the heap when it becomes full
// Time Complexity: O(n), Space Complexity: O(n)
extern void resizeHeap(Heap *H);

// Inserts a new HeapElement into the heap
// Time Complexity: O(log n), Space Complexity: O(1)
extern void insertHeap(Heap *H, HeapElement data);

// Deallocates all memory used by the heap
// Time Complexity: O(1), Space Complexity: O(1)
extern void destroyHeap(Heap *H);

// Constructs a heap from an array of HeapElements
// Time Complexity: O(n), Space Complexity: O(1)
extern void buildHeap(Heap *H, int arr[], int n);
