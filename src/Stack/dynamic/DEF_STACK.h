// Define the type of elements stored in the stack
#include "../../BinarySearchTree/DEF_BST.h"
typedef BSTNode *StackElem;
// You can change this to another type (e.g., float, char, or a struct)
// if you want the stack to store different types of data.

// Define the structure for a node in the stack
typedef struct StackNode
{
  StackElem val;          // The value stored in the node
  struct StackNode *next; // Pointer to the next node in the stack
} StackNode;

// Define the structure for the stack
typedef struct Stack
{
  StackNode *top; // Pointer to the top node in the stack
  int size;       // Current size of the stack
} Stack;
// The stack is implemented as a linked list with dynamic memory allocation.