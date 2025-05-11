// Define the type of elements stored in the queue
typedef int QueueElem;
// You can change this to another type (e.g., float, char, or a struct)
// if you want the queue to store different types of data.

// Define the structure for the queue
typedef struct Queue
{
  QueueElem *data; // Array to store queue elements
  int front;       // Index of the front element
  int rear;        // Index of the rear element
  int capacity;    // Maximum capacity of the queue
  int size;        // Current size of the queue
} Queue;
// The queue is implemented as a static array with a fixed capacity.