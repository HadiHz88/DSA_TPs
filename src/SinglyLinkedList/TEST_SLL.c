#include <stdio.h>
#include <stdlib.h>
#include "SLL.h" // Include the header file for singly linked list functions

int main()
{
  // Declare a pointer to the head of the linked list
  ListNode *head = NULL;

  // Test adding elements to the head of the list
  printf("Adding elements to the head of the list:\n");
  addHead(&head, 10); // Add 10 to the head
  addHead(&head, 20); // Add 20 to the head
  addHead(&head, 30); // Add 30 to the head
  printList(head);    // Expected output: 30 -> 20 -> 10

  // Test adding elements to the tail of the list
  printf("\nAdding elements to the tail of the list:\n");
  addTail(&head, 40); // Add 40 to the tail
  addTail(&head, 50); // Add 50 to the tail
  printList(head);    // Expected output: 30 -> 20 -> 10 -> 40 -> 50

  // Test removing the head element
  printf("\nRemoving the head element:\n");
  ListElem removedHead = removeHead(&head); // Remove the head element
  printf("Removed head: %d\n", removedHead);
  printList(head); // Expected output: 20 -> 10 -> 40 -> 50

  // Test removing the tail element
  printf("\nRemoving the tail element:\n");
  ListElem removedTail = removeTail(&head); // Remove the tail element
  printf("Removed tail: %d\n", removedTail);
  printList(head); // Expected output: 20 -> 10 -> 40

  // Test the length of the list
  printf("\nLength of the list: %d\n", listLength(head)); // Expected output: 3

  // Test the size of the list (same as length in this implementation)
  printf("Size of the list: %d\n", listSize(head)); // Expected output: 3

  // Free the memory allocated for the list
  printf("\nFreeing the list:\n");
  while (head != NULL)
  {
    removeHead(&head);
  }
  printf("List freed successfully.\n");

  return 0;
}