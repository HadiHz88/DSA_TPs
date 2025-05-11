#include <stdio.h>
#include <stdlib.h>
#include "STACK.h" // Include the header file for function declarations

// Initializes the stack with a given capacity
void initStack(Stack *stack, int capacity)
{
  stack->data = (StackElem *)malloc(capacity * sizeof(StackElem)); // Allocate memory for the stack
  if (stack->data == NULL)
  {
    printf("Memory allocation failed.\n");
    exit(EXIT_FAILURE); // Exit if memory allocation fails
  }
  stack->top = -1;            // Initialize the stack as empty
  stack->capacity = capacity; // Set the stack capacity
}

// Checks if the stack is empty
bool isStackEmpty(Stack *stack)
{
  return stack->top == -1; // Stack is empty if top is -1
}

// Checks if the stack is full
bool isStackFull(Stack *stack)
{
  return stack->top == stack->capacity - 1; // Stack is full if top equals capacity - 1
}

// Pushes an element onto the stack
bool push(Stack *stack, StackElem elem)
{
  if (isStackFull(stack))
  {
    printf("Stack overflow. Cannot push %d.\n", elem);
    return false; // Return false if the stack is full
  }
  stack->data[++stack->top] = elem; // Increment top and add the element
  return true;                      // Return true to indicate success
}

// Pops an element from the stack
StackElem pop(Stack *stack)
{
  if (isStackEmpty(stack))
  {
    printf("Stack underflow. Cannot pop.\n");
    return -1; // Return -1 to indicate failure (or use a sentinel value)
  }
  return stack->data[stack->top--]; // Return the top element and decrement top
}

// Returns the top element of the stack without removing it
StackElem peek(Stack *stack)
{
  if (isStackEmpty(stack))
  {
    printf("Stack is empty. Cannot peek.\n");
    return -1; // Return -1 to indicate failure (or use a sentinel value)
  }
  return stack->data[stack->top]; // Return the top element
}

// Frees the memory allocated for the stack
void freeStack(Stack *stack)
{
  free(stack->data);   // Free the memory allocated for the stack
  stack->data = NULL;  // Set the data pointer to NULL
  stack->top = -1;     // Reset the top index
  stack->capacity = 0; // Reset the capacity
}