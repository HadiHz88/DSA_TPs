#include <stdio.h>
#include <stdlib.h>
#include "HEAP.h"

int main()
{
    // Example usage of the heap functions
    Heap *heap = createHeap(10, 1);

    insert(heap, 5);
    insert(heap, 3);
    insert(heap, 8);
    insert(heap, 1);

    printf("Heap after insertions: ");
    printHeap(heap);

    int min = extractMin(heap);
    printf("Extracted minimum: %d\n", min);

    printf("Heap after extraction: ");
    printHeap(heap);

    freeHeap(heap);

    return 0;
}
