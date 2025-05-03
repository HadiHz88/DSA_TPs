#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct Node
{
  element val;
  struct Node *next;
} Node;

void removeDuplicates(Node *head)
{
  // Create a pointer to the current node
  Node *curr = head;

  // Iterate over the list, removing duplicates as we go
  while (curr != NULL && curr->next != NULL)
  {
    if (curr->val == curr->next->val)
    {
      Node *temp = curr->next;
      curr->next = curr->next->next;
      free(temp);
    }
    else
    {
      curr = curr->next;
    }
  }
}

int main()
{
  // Create a sample linked list
  Node *head = (Node *)malloc(sizeof(Node));
  head->val = 1;
  Node *node2 = (Node *)malloc(sizeof(Node));
  node2->val = 2;
  Node *node3 = (Node *)malloc(sizeof(Node));
  node3->val = 2;
  Node *node4 = (Node *)malloc(sizeof(Node));
  node4->val = 3;
  Node *node5 = (Node *)malloc(sizeof(Node));
  node5->val = 3;
  Node *node6 = (Node *)malloc(sizeof(Node));
  node6->val = 3;
  head->next = node2;
  node2->next = node3;
  node3->next = node4;
  node4->next = node5;
  node5->next = node6;
  node6->next = NULL;

  // Remove duplicates and print the resulting list
  removeDuplicates(head);
  Node *curr = head;
  while (curr != NULL)
  {
    printf("%d -> ", curr->val);
    curr = curr->next;
  }
  printf("NULL\n");

  return 0;
}
