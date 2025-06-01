// Element type used in the heap (can be changed for different applications)
typedef int HeapElement;

// Heap data structure definition
// A heap is a specialized tree-based data structure that satisfies the heap property
typedef struct
{
    HeapElement *array; // Dynamic array to store heap elements
    int count;          // Number of elements currently in the heap
    int capacity;       // Total capacity of the heap array
    int type;           // Heap type: 1 for Max Heap, 0 for Min Heap
} *Heap;
