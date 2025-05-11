#include <stdio.h>
#include "STACK.h" // Include the header file for stack operations

int main()
{
  Stack stack;      // Declare a stack
  int capacity = 5; // Set the stack capacity

  // Initialize the stack
  printf("Initializing stack with capacity %d...\n", capacity);
  initStack(&stack, capacity);

  // Test pushing elements onto the stack
  printf("Pushing elements onto the stack:\n");
  for (int i = 1; i <= 6; i++) // Attempt to push 6 elements (1 more than capacity)
  {
    if (push(&stack, i))
    {
      printf("Pushed: %d\n", i);
    }
  }

  // Test peeking the top element
  printf("\nPeeking the top element: %d\n", peek(&stack));

  // Test popping elements from the stack
  printf("\nPopping elements from the stack:\n");
  while (!isStackEmpty(&stack))
  {
    printf("Popped: %d\n", pop(&stack));
  }

  // Attempt to pop from an empty stack
  printf("\nAttempting to pop from an empty stack:\n");
  pop(&stack);

  // Free the stack memory
  printf("\nFreeing the stack memory...\n");
  freeStack(&stack);

  printf("Stack test completed successfully.\n");
  return 0;
}