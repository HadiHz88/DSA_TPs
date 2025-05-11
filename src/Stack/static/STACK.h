#include <stdbool.h>   // Include for boolean data type (true/false)
#include "DEF_STACK.h" // Include the definition of Stack and StackElem

// Function declarations for stack operations

// Initializes the stack with a given capacity
extern void initStack(Stack *stack, int capacity);

// Checks if the stack is empty
extern bool isStackEmpty(Stack *stack);

// Checks if the stack is full
extern bool isStackFull(Stack *stack);

// Pushes an element onto the stack
extern bool push(Stack *stack, StackElem elem);

// Pops an element from the stack
extern StackElem pop(Stack *stack);

// Returns the top element of the stack without removing it
extern StackElem peek(Stack *stack);

// Frees the memory allocated for the stack
extern void freeStack(Stack *stack);