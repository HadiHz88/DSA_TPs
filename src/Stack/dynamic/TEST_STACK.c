#include <stdio.h>
#include "STACK.h" // Include the header file for stack operations

int main()
{
  Stack stack; // Declare a stack

  // Initialize the stack
  printf("Initializing stack...\n");
  initStack(&stack);

  // Test pushing elements onto the stack
  printf("Pushing elements onto the stack:\n");
  for (int i = 1; i <= 5; i++) // Push 5 elements
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

  printf("Dynamic stack test completed successfully.\n");
  return 0;
}