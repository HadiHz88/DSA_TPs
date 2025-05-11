// Define the type of elements stored in the queue
typedef int QueueElem;
// You can change this to another type (e.g., float, char, or a struct)
// if you want the queue to store different types of data.

// Define the structure for a node in the queue
typedef struct QueueNode
{
  QueueElem val;          // The value stored in the node
  struct QueueNode *next; // Pointer to the next node in the queue
} QueueNode;

// Define the structure for the queue
typedef struct Queue
{
  QueueNode *front; // Pointer to the front node of the queue
  QueueNode *rear;  // Pointer to the rear node of the queue
  int size;         // Current size of the queue
} Queue;
// The queue is implemented as a linked list with dynamic memory allocation.