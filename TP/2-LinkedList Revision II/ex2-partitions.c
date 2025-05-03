#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int data;
  struct Node *next;
};

struct Node *createNode(int data)
{
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL)
  {
    printf("Memory allocation failed.\n");
    exit(1);
  }
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

void insert(struct Node **head, int data)
{
  struct Node *newNode = createNode(data);
  if (*head == NULL)
  {
    *head = newNode;
  }
  else
  {
    struct Node *current = *head;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = newNode;
  }
}

void partitionLinkedList(struct Node **head, int pivot)
{
  if (*head == NULL || (*head)->next == NULL)
  {
    return;
  }

  struct Node *smallerHead = NULL;        // Head of the list containing smaller elements
  struct Node *smallerTail = NULL;        // Tail of the list containing smaller elements
  struct Node *greaterOrEqualHead = NULL; // Head of the list containing greater or equal elements
  struct Node *greaterOrEqualTail = NULL; // Tail of the list containing greater or equal elements

  struct Node *current = *head;
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

void printList(struct Node *head)
{
  while (head != NULL)
  {
    printf("%d ", head->data);
    head = head->next;
  }
  printf("\n");
}

void freeList(struct Node *head)
{
  struct Node *current = head;
  while (current != NULL)
  {
    struct Node *temp = current;
    current = current->next;
    free(temp);
  }
}

int main()
{
  struct Node *head = NULL;

  // Insert nodes into the linked list
  insert(&head, 6);
  insert(&head, 2);
  insert(&head, 8);
  insert(&head, 4);
  insert(&head, 1);
  insert(&head, 9);

  printf("Original List: ");
  printList(head);

  int pivot = 5;
  partitionLinkedList(&head, pivot);

  printf("Partitioned List: ");
  printList(head);

  // Free the memory allocated for the linked list
  freeList(head);

  return 0;
}
