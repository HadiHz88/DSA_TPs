#include <stdio.h>
#include "Queue.h" // Include the header file for queue operations

int main()
{
  Queue queue; // Declare a queue

  // Initialize the queue
  printf("Initializing queue...\n");
  initQueue(&queue);

  // Test enqueuing elements
  printf("Enqueuing elements into the queue:\n");
  for (int i = 1; i <= 5; i++) // Enqueue 5 elements
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

  printf("Dynamic queue test completed successfully.\n");
  return 0;
}