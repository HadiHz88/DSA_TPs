#include <stdio.h>
#include "Queue.h" // Include the header file for queue operations

int main()
{
  Queue queue;      // Declare a queue
  int capacity = 5; // Set the queue capacity

  // Initialize the queue
  printf("Initializing queue with capacity %d...\n", capacity);
  initQueue(&queue, capacity);

  // Test enqueuing elements
  printf("Enqueuing elements into the queue:\n");
  for (int i = 1; i <= 6; i++) // Attempt to enqueue 6 elements (1 more than capacity)
  {
    if (enqueue(&queue, i))
    {
      printf("Enqueued: %d\n", i);
    }
  }

  // Test peeking the front element
  printf("\nPeeking the front element: %d\n", peekFront(&queue));

  // Test dequeuing elements
  printf("\nDequeuing elements from the queue:\n");
  while (!isQueueEmpty(&queue))
  {
    printf("Dequeued: %d\n", dequeue(&queue));
  }

  // Attempt to dequeue from an empty queue
  printf("\nAttempting to dequeue from an empty queue:\n");
  dequeue(&queue);

  // Free the queue memory
  printf("\nFreeing the queue memory...\n");
  freeQueue(&queue);

  printf("Static queue test completed successfully.\n");
  return 0;
}