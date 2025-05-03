#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct Node
{
  element val;
  struct Node *next;
} Node;

// Function to merge two sorted linked lists
Node *mergeTwoLists(Node *l1, Node *l2)
{
  // Create a dummy node to serve as the head of the merged list
  Node *dummy = (Node *)malloc(sizeof(Node));
  dummy->val = 0;
  dummy->next = NULL;

  // Create a pointer to keep track of the last node in the merged list
  Node *tail = dummy;

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

  // Append any remaining nodes from the first or second list to the merged list
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
int main()
{
  // Create two sorted linked lists
  Node *l1 = (Node *)malloc(sizeof(Node));
  l1->val = 1;
  Node *l1_node2 = (Node *)malloc(sizeof(Node));
  l1_node2->val = 2;
  l1->next = l1_node2;
  l1_node2->next = NULL;
  Node *l2 = (Node *)malloc(sizeof(Node));
  l2->val = 1;
  Node *l2_node2 = (Node *)malloc(sizeof(Node));
  l2_node2->val = 3;
  l2->next = l2_node2;
  l2_node2->next = NULL;
  // Merge the two lists and print the merged list
  Node *merged_list = mergeTwoLists(l1, l2);
  while (merged_list != NULL)
  {
    printf("%d -> ", merged_list->val);
    merged_list = merged_list->next;
  }
  printf("NULL\n");
  return 0;
}
