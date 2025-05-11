#include <stdio.h>
#include <stdlib.h>
#include "Queue.h" // Include the header file for function declarations

// Initializes the queue
void initQueue(Queue *queue)
{
  queue->front = NULL; // Initialize the front pointer to NULL
  queue->rear = NULL;  // Initialize the rear pointer to NULL
  queue->size = 0;     // Initialize the size to 0
}

// Checks if the queue is empty
bool isQueueEmpty(Queue *queue)
{
  return queue->front == NULL; // Queue is empty if front is NULL
}

// Enqueues (adds) an element to the rear of the queue
bool enqueue(Queue *queue, QueueElem elem)
{
  QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode)); // Allocate memory for a new node
  if (newNode == NULL)
  {
    printf("Memory allocation failed. Cannot enqueue %d.\n", elem);
    return false; // Return false if memory allocation fails
  }
  newNode->val = elem;  // Set the value of the new node
  newNode->next = NULL; // Set the next pointer of the new node to NULL

  if (queue->rear == NULL)
  {
    // If the queue is empty, both front and rear point to the new node
    queue->front = newNode;
    queue->rear = newNode;
  }
  else
  {
    queue->rear->next = newNode; // Link the new node to the rear
    queue->rear = newNode;       // Update the rear pointer
  }
  queue->size++; // Increment the size of the queue
  return true;   // Return true to indicate success
}

// Dequeues (removes) an element from the front of the queue
QueueElem dequeue(Queue *queue)
{
  if (isQueueEmpty(queue))
  {
    printf("Queue underflow. Cannot dequeue.\n");
    return -1; // Return -1 to indicate failure (or use a sentinel value)
  }
  QueueNode *temp = queue->front; // Store the current front node
  QueueElem value = temp->val;    // Get the value of the front node
  queue->front = temp->next;      // Update the front pointer to the next node

  if (queue->front == NULL)
  {
    // If the queue becomes empty, set the rear pointer to NULL
    queue->rear = NULL;
  }
  free(temp);    // Free the memory of the old front node
  queue->size--; // Decrement the size of the queue
  return value;  // Return the dequeued value
}

// Returns the front element of the queue without removing it
QueueElem peekFront(Queue *queue)
{
  if (isQueueEmpty(queue))
  {
    printf("Queue is empty. Cannot peek.\n");
    return -1; // Return -1 to indicate failure (or use a sentinel value)
  }
  return queue->front->val; // Return the value of the front node
}

// Frees the memory allocated for the queue
void freeQueue(Queue *queue)
{
  while (!isQueueEmpty(queue))
  {
    dequeue(queue); // Dequeue all elements to free the memory
  }
  queue->front = NULL; // Set the front pointer to NULL
  queue->rear = NULL;  // Set the rear pointer to NULL
  queue->size = 0;     // Reset the size to 0
}