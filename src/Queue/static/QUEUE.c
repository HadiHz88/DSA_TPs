#include <stdio.h>
#include <stdlib.h>
#include "Queue.h" // Include the header file for function declarations

// Initializes the queue with a given capacity
void initQueue(Queue *queue, int capacity)
{
  queue->data = (QueueElem *)malloc(capacity * sizeof(QueueElem)); // Allocate memory for the queue
  if (queue->data == NULL)
  {
    printf("Memory allocation failed.\n");
    exit(EXIT_FAILURE); // Exit if memory allocation fails
  }
  queue->front = 0;           // Initialize the front index
  queue->rear = -1;           // Initialize the rear index
  queue->capacity = capacity; // Set the queue capacity
  queue->size = 0;            // Initialize the size to 0
}

// Checks if the queue is empty
bool isQueueEmpty(Queue *queue)
{
  return queue->size == 0; // Queue is empty if size is 0
}

// Checks if the queue is full
bool isQueueFull(Queue *queue)
{
  return queue->size == queue->capacity; // Queue is full if size equals capacity
}

// Enqueues (adds) an element to the rear of the queue
bool enqueue(Queue *queue, QueueElem elem)
{
  if (isQueueFull(queue))
  {
    printf("Queue overflow. Cannot enqueue %d.\n", elem);
    return false; // Return false if the queue is full
  }
  queue->rear = (queue->rear + 1) % queue->capacity; // Circular increment of rear index
  queue->data[queue->rear] = elem;                   // Add the element to the rear
  queue->size++;                                     // Increment the size
  return true;                                       // Return true to indicate success
}

// Dequeues (removes) an element from the front of the queue
QueueElem dequeue(Queue *queue)
{
  if (isQueueEmpty(queue))
  {
    printf("Queue underflow. Cannot dequeue.\n");
    return -1; // Return -1 to indicate failure (or use a sentinel value)
  }
  QueueElem value = queue->data[queue->front];         // Get the front element
  queue->front = (queue->front + 1) % queue->capacity; // Circular increment of front index
  queue->size--;                                       // Decrement the size
  return value;                                        // Return the dequeued value
}

// Returns the front element of the queue without removing it
QueueElem peekFront(Queue *queue)
{
  if (isQueueEmpty(queue))
  {
    printf("Queue is empty. Cannot peek.\n");
    return -1; // Return -1 to indicate failure (or use a sentinel value)
  }
  return queue->data[queue->front]; // Return the front element
}

// Frees the memory allocated for the queue
void freeQueue(Queue *queue)
{
  free(queue->data);   // Free the memory allocated for the queue
  queue->data = NULL;  // Set the data pointer to NULL
  queue->front = 0;    // Reset the front index
  queue->rear = -1;    // Reset the rear index
  queue->capacity = 0; // Reset the capacity
  queue->size = 0;     // Reset the size
}