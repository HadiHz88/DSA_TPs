#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct Node
{
  element val;
  struct Node *next;
} Node;

// Function to reverse a linked list in place
Node *reverseList(Node *head)
{
  // Create pointers to the previous, current, and next nodes
  Node *prev = NULL;
  Node *curr = head;
  Node *next = NULL;

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

int main()
{
  // Create a sample linked list
  Node *head = (Node *)malloc(sizeof(Node));
  head->val = 1;
  Node *node2 = (Node *)malloc(sizeof(Node));
  node2->val = 2;
  Node *node3 = (Node *)malloc(sizeof(Node));
  node3->val = 3;
  Node *node4 = (Node *)malloc(sizeof(Node));
  node4->val = 4;
  head->next = node2;
  node2->next = node3;
  node3->next = node4;
  node4->next = NULL;

  // Reverse the list and print the reversed list
  Node *reversed_list = reverseList(head);
  while (reversed_list != NULL)
  {
    printf("%d -> ", reversed_list->val);
    reversed_list = reversed_list->next;
  }
  printf("NULL\n");

  return 0;
}
