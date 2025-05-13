#include "../../src/dsa.h"
#include <stdio.h>
#include <stdlib.h>

// EX-1: Function to return the intersection of 2 sorted linked lists
ListNode *getIntersection(ListNode *list1, ListNode *list2)
{
  ListNode dummy; // Dummy ListNode to build the result list
  ListNode *tail = &dummy;
  dummy.next = NULL;

  while (list1 != NULL && list2 != NULL)
  {
    if (list1->data == list2->data)
    {
      insert(&(tail->next), list1->data);
      tail = tail->next;
      list1 = list1->next;
      list2 = list2->next;
    }
    else if (list1->data < list2->data)
    {
      list1 = list1->next;
    }
    else
    {
      list2 = list2->next;
    }
  }

  return dummy.next;
}

// EX-2: Function to partition a linked list around a pivot
void partitionLinkedList(ListNode **head, int pivot)
{
  if (*head == NULL || (*head)->next == NULL)
  {
    return;
  }

  ListNode *smallerHead = NULL;        // Head of the list containing smaller elements
  ListNode *smallerTail = NULL;        // Tail of the list containing smaller elements
  ListNode *greaterOrEqualHead = NULL; // Head of the list containing greater or equal elements
  ListNode *greaterOrEqualTail = NULL; // Tail of the list containing greater or equal elements

  ListNode *current = *head;
  while (current != NULL)
  {
    if (current->data < pivot)
    {
      if (smallerHead == NULL)
      {
        smallerHead = current;
        smallerTail = current;
      }
      else
      {
        smallerTail->next = current;
        smallerTail = smallerTail->next;
      }
    }
    else
    {
      if (greaterOrEqualHead == NULL)
      {
        greaterOrEqualHead = current;
        greaterOrEqualTail = current;
      }
      else
      {
        greaterOrEqualTail->next = current;
        greaterOrEqualTail = greaterOrEqualTail->next;
      }
    }
    current = current->next;
  }

  if (smallerHead != NULL)
  {
    smallerTail->next = greaterOrEqualHead;
    *head = smallerHead;
  }
  else
  {
    *head = greaterOrEqualHead;
  }

  if (greaterOrEqualTail != NULL)
  {
    greaterOrEqualTail->next = NULL;
  }
}

// EX-3: Function to detect a cycle in a linked list and return the starting node of the cycle
ListNode *detectCycle(ListNode *head)
{
  if (head == NULL || head->next == NULL)
  {
    return NULL;
  }

  ListNode *slow = head;
  ListNode *fast = head;
  bool hasCycle = false;

  while (fast != NULL && fast->next != NULL)
  {
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast)
    {
      hasCycle = true;
      break;
    }
  }

  if (!hasCycle)
  {
    return NULL;
  }

  slow = head;
  while (slow != fast)
  {
    slow = slow->next;
    fast = fast->next;
  }

  return slow;
}

// EX-4: Function to rotate a linked list to the right by k places
ListNode *rotateRight(ListNode *head, int k)
{
  if (head == NULL || k == 0)
  {
    return head;
  }

  int length = listLength(head);
  k = k % length; // Normalize k if it's greater than the length of the list

  if (k == 0)
  {
    return head;
  }

  // Find the new tail and the node before it
  ListNode *tail = head;
  ListNode *prev = NULL;
  for (int i = 0; i < length - k; i++)
  {
    prev = tail;
    tail = tail->next;
  }

  // Break the link between the new tail and the node before it
  prev->next = NULL;

  // Connect the original head to the original tail
  ListNode *newHead = tail;
  while (tail->next != NULL)
  {
    tail = tail->next;
  }
  tail->next = head;

  return newHead;
}

ListNode *addNumbers(ListNode *num1, ListNode *num2)
{
  if (num1 == NULL)
  {
    return num2;
  }
  if (num2 == NULL)
  {
    return num1;
  }

  ListNode *result = NULL;
  ListNode *tail = NULL;
  int carry = 0;

  while (num1 != NULL || num2 != NULL || carry != 0)
  {
    int sum = carry;
    if (num1 != NULL)
    {
      sum += num1->data;
      num1 = num1->next;
    }
    if (num2 != NULL)
    {
      sum += num2->data;
      num2 = num2->next;
    }

    carry = sum / 10;
    int digit = sum % 10;

    ListNode *newNode = createListNode(digit);
    if (result == NULL)
    {
      result = newNode;
      tail = newNode;
    }
    else
    {
      tail->next = newNode;
      tail = newNode;
    }
  }

  return result;
}

// Test the functions
int main()
{
  // Test getIntersection
  printf("\n----- Testing getIntersection -----\n");
  ListNode *list1 = NULL;
  ListNode *list2 = NULL;

  // Create two sorted lists with some common elements
  insert(&list1, 1);
  insert(&list1, 2);
  insert(&list1, 3);
  insert(&list1, 5);
  insert(&list1, 7);

  insert(&list2, 2);
  insert(&list2, 3);
  insert(&list2, 4);
  insert(&list2, 7);
  insert(&list2, 9);

  printf("List 1: ");
  displayList(list1);
  printf("List 2: ");
  displayList(list2);

  ListNode *intersection = getIntersection(list1, list2);
  printf("Intersection: ");
  displayList(intersection);
  freeList(&intersection);

  // Test partitionLinkedList
  printf("\n----- Testing partitionLinkedList -----\n");
  ListNode *partitionList = NULL;
  insert(&partitionList, 3);
  insert(&partitionList, 8);
  insert(&partitionList, 5);
  insert(&partitionList, 2);
  insert(&partitionList, 1);
  insert(&partitionList, 9);
  insert(&partitionList, 4);

  int pivot = 5;
  printf("Original list: ");
  displayList(partitionList);
  printf("Partitioning around %d\n", pivot);

  partitionLinkedList(&partitionList, pivot);
  printf("After partition: ");
  displayList(partitionList);

  // Test detectCycle
  printf("\n----- Testing detectCycle -----\n");
  ListNode *cycleList = NULL;
  insert(&cycleList, 1);
  insert(&cycleList, 2);
  insert(&cycleList, 3);
  insert(&cycleList, 4);
  insert(&cycleList, 5);

  printf("List without cycle: ");
  displayList(cycleList);

  ListNode *cycleResult = detectCycle(cycleList);
  if (cycleResult == NULL)
  {
    printf("No cycle detected (correct)\n");
  }
  else
  {
    printf("Error: Cycle detected incorrectly\n");
  }

  // Create a cycle (connecting last node to the third node)
  ListNode *last = cycleList;
  while (last->next != NULL)
  {
    last = last->next;
  }

  ListNode *third = cycleList;
  third = third->next->next; // Get the third node (value 3)
  last->next = third;

  printf("Created a cycle (last node points to node with value %d)\n", third->data);

  cycleResult = detectCycle(cycleList);
  if (cycleResult != NULL)
  {
    printf("Cycle detected at node with value: %d (correct)\n", cycleResult->data);
  }
  else
  {
    printf("Error: Failed to detect cycle\n");
  }

  // Break the cycle before freeing memory
  last->next = NULL;

  // Test rotateRight
  printf("\n----- Testing rotateRight -----\n");
  ListNode *rotateList = NULL;
  insert(&rotateList, 1);
  insert(&rotateList, 2);
  insert(&rotateList, 3);
  insert(&rotateList, 4);
  insert(&rotateList, 5);

  printf("Original list: ");
  displayList(rotateList);

  int k = 2;
  printf("Rotating right by %d positions\n", k);
  ListNode *rotated = rotateRight(rotateList, k);
  printf("After rotation: ");
  displayList(rotated);

  // Test addNumbers
  printf("\n----- Testing addNumbers -----\n");
  ListNode *num1 = NULL;
  ListNode *num2 = NULL;

  // Create number 123 (stored in reverse: 3->2->1)
  insert(&num1, 3);
  insert(&num1, 2);
  insert(&num1, 1);

  // Create number 456 (stored in reverse: 6->5->4)
  insert(&num2, 6);
  insert(&num2, 5);
  insert(&num2, 4);

  printf("Number 1: ");
  displayList(num1);
  printf("Number 2: ");
  displayList(num2);

  ListNode *sum = addNumbers(num1, num2);
  printf("Sum: ");
  displayList(sum);
  printf("(should represent 579 stored in reverse)\n");

  // Free all allocated memory
  freeList(&list1);
  freeList(&list2);
  freeList(&partitionList);
  freeList(&cycleList);
  freeList(&rotated);
  freeList(&num1);
  freeList(&num2);
  freeList(&sum);

  return 0;
}