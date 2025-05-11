// Define the type of elements stored in the stack
typedef int StackElem;
// You can change this to another type (e.g., float, char, or a struct)
// if you want the stack to store different types of data.

// Define the structure for a stack
typedef struct Stack
{
  StackElem *data; // Array to store stack elements
  int top;         // Index of the top element in the stack
  int capacity;    // Maximum capacity of the stack
} Stack;
// The stack is implemented as a static array with a fixed capacity.