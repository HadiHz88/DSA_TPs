#include <stdbool.h>   // Include for boolean data type (true/false)
#include "DEF_QUEUE.h" // Include the definition of Queue and QueueElem

// Function declarations for queue operations

// Initializes the queue with a given capacity
extern void initQueue(Queue *queue, int capacity);

// Checks if the queue is empty
extern bool isQueueEmpty(Queue *queue);

// Checks if the queue is full
extern bool isQueueFull(Queue *queue);

// Enqueues (adds) an element to the rear of the queue
extern bool enqueue(Queue *queue, QueueElem elem);

// Dequeues (removes) an element from the front of the queue
extern QueueElem dequeue(Queue *queue);

// Returns the front element of the queue without removing it
extern QueueElem peekFront(Queue *queue);

// Frees the memory allocated for the queue
extern void freeQueue(Queue *queue);