#include <stdio.h>
#include <stdlib.h>
#include "STACK.h" // Include the header file for function declarations

// Initializes the stack
void initStack(Stack *stack)
{
  stack->top = NULL; // Initialize the top pointer to NULL
  stack->size = 0;   // Initialize the size to 0
}

// Checks if the stack is empty
bool isStackEmpty(Stack *stack)
{
  return stack->top == NULL; // Stack is empty if top is NULL
}

// Pushes an element onto the stack
bool push(Stack *stack, StackElem elem)
{
  StackNode *newNode = (StackNode *)malloc(sizeof(StackNode)); // Allocate memory for a new node
  if (newNode == NULL)
  {
    printf("Memory allocation failed. Cannot push %d.\n", elem);
    return false; // Return false if memory allocation fails
  }
  newNode->val = elem;        // Set the value of the new node
  newNode->next = stack->top; // Point the new node to the current top
  stack->top = newNode;       // Update the top pointer to the new node
  stack->size++;              // Increment the size of the stack
  return true;                // Return true to indicate success
}

// Pops an element from the stack
StackElem pop(Stack *stack)
{
  if (isStackEmpty(stack))
  {
    printf("Stack underflow. Cannot pop.\n");
    return NULL; // Return -1 to indicate failure (or use a sentinel value)
  }
  StackNode *temp = stack->top; // Store the current top node
  StackElem value = temp->val;  // Get the value of the top node
  stack->top = temp->next;      // Update the top pointer to the next node
  free(temp);                   // Free the memory of the old top node
  stack->size--;                // Decrement the size of the stack
  return value;                 // Return the popped value
}

// Returns the top element of the stack without removing it
StackElem peek(Stack *stack)
{
  if (isStackEmpty(stack))
  {
    printf("Stack is empty. Cannot peek.\n");
    return NULL; // Return -1 to indicate failure (or use a sentinel value)
  }
  return stack->top->val; // Return the value of the top node
}

// Frees the memory allocated for the stack
void freeStack(Stack *stack)
{
  while (!isStackEmpty(stack))
  {
    pop(stack); // Pop all elements to free the memory
  }
  stack->top = NULL; // Set the top pointer to NULL
  stack->size = 0;   // Reset the size to 0
}