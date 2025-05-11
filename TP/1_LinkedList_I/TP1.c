#include "../../src/dsa.h"
#include <stdio.h>
#include <stdlib.h>

// EX-1: Function to merge two sorted linked lists
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
  // Create a dummy ListNode to serve as the head of the merged list
  ListNode *dummy = (ListNode *)malloc(sizeof(ListNode));
  dummy->val = 0;
  dummy->next = NULL;

  // Create a pointer to keep track of the last ListNode in the merged list
  ListNode *tail = dummy;

  // Merge the two lists
  while (l1 != NULL && l2 != NULL)
  {
    if (l1->val <= l2->val)
    {
      tail->next = l1;
      l1 = l1->next;
    }
    else
    {
      tail->next = l2;
      l2 = l2->next;
    }
    tail = tail->next;
  }

  // Append any remaining ListNodes from the first or second list to the merged list
  if (l1 != NULL)
  {
    tail->next = l1;
  }
  else
  {
    tail->next = l2;
  }

  // Return the merged list
  return dummy->next;
}

// EX-2: Function to reverse a linked list in place
ListNode *reverseList(ListNode *head)
{
  // Create pointers to the previous, current, and next nodes
  ListNode *prev = NULL;
  ListNode *curr = head;
  ListNode *next = NULL;

  // Reverse the list by iteratively moving the current node to the previous position
  while (curr != NULL)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  // Return the new head of the reversed list
  return prev;
}

// EX-3: Function to remove duplicates from a sorted linked list
void removeDuplicates(ListNode *head)
{
  // Create a pointer to the current node
  ListNode *curr = head;

  // Iterate over the list, removing duplicates as we go
  while (curr != NULL && curr->next != NULL)
  {
    if (curr->val == curr->next->val)
    {
      ListNode *temp = curr->next;
      curr->next = curr->next->next;
      free(temp);
    }
    else
    {
      curr = curr->next;
    }
  }
}

// Test the functions
int main()
{
  // Create a sample linked list
  ListNode *head = createListNode(1);
  head->next = createListNode(2);
  head->next->next = createListNode(2);
  head->next->next->next = createListNode(4);
  head->next->next->next->next = createListNode(4);
  head->next->next->next->next->next = createListNode(6);

  // Print the original list
  printf("Original List:\n");
  printList(head);

  // Remove duplicates from the list
  printf("\nList after removing duplicates:\n");
  removeDuplicates(head);
  printList(head);

  // Reverse the list
  printf("\nReversed List:\n");
  head = reverseList(head);
  printList(head);

  // Create another sample linked list
  ListNode *l1 = createListNode(1);
  l1->next = createListNode(2);
  l1->next->next = createListNode(4);
  ListNode *l2 = createListNode(1);
  l2->next = createListNode(3);
  l2->next->next = createListNode(4);

  // Print the two lists
  printf("\nList 1:\n");
  printList(l1);
  printf("\nList 2:\n");
  printList(l2);

  // Merge the two lists
  ListNode *mergedList = mergeTwoLists(l1, l2);
  printf("\nMerged List:\n");
  printList(mergedList);

  // Free the memory allocated for the lists
  printf("\nFreeing memory... ");
  freeList(&head);
  freeList(&mergedList);
  printf("Done.\n");

  return 0;
}
