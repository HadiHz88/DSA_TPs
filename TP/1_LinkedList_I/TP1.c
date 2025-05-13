#include "../../src/dsa.h"
#include <stdio.h>
#include <stdlib.h>

// EX-1: Function to merge two sorted linked lists
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
  // Create a dummy ListNode to serve as the head of the merged list
  ListNode *dummy = createListNode(0);

  // Create a pointer to keep track of the last ListNode in the merged list
  ListNode *tail = dummy;

  // Merge the two lists
  while (l1 != NULL && l2 != NULL)
  {
    if (l1->data <= l2->data)
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
    if (curr->data == curr->next->data)
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

// Add after the existing code

int main()
{
  // Test mergeTwoLists
  printf("\n----- Testing mergeTwoLists -----\n");
  ListNode *list1 = NULL;
  ListNode *list2 = NULL;

  // Create two sorted lists
  insert(&list1, 1);
  insert(&list1, 3);
  insert(&list1, 5);
  insert(&list1, 7);

  insert(&list2, 2);
  insert(&list2, 4);
  insert(&list2, 6);
  insert(&list2, 8);

  printf("List 1: ");
  displayList(list1);
  printf("List 2: ");
  displayList(list2);

  ListNode *mergedList = mergeTwoLists(list1, list2);
  printf("Merged list: ");
  displayList(mergedList);

  // Test reverseList
  printf("\n----- Testing reverseList -----\n");
  ListNode *originalList = NULL;
  insert(&originalList, 1);
  insert(&originalList, 2);
  insert(&originalList, 3);
  insert(&originalList, 4);
  insert(&originalList, 5);

  printf("Original list: ");
  displayList(originalList);

  ListNode *reversedList = reverseList(originalList);
  printf("Reversed list: ");
  displayList(reversedList);

  // Test removeDuplicates
  printf("\n----- Testing removeDuplicates -----\n");
  ListNode *duplicatesList = NULL;
  insert(&duplicatesList, 1);
  insert(&duplicatesList, 1);
  insert(&duplicatesList, 2);
  insert(&duplicatesList, 3);
  insert(&duplicatesList, 3);
  insert(&duplicatesList, 3);
  insert(&duplicatesList, 4);
  insert(&duplicatesList, 5);
  insert(&duplicatesList, 5);

  printf("List with duplicates: ");
  displayList(duplicatesList);

  removeDuplicates(duplicatesList);
  printf("List after removing duplicates: ");
  displayList(duplicatesList);

  // Free allocated memory
  // Note: mergedList uses the nodes from list1 and list2, so don't free list1 and list2
  freeList(&mergedList);
  freeList(&reversedList);
  freeList(&duplicatesList);

  return 0;
}