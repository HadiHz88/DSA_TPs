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

int getLength(struct Node *head)
{
  int length = 0;
  struct Node *current = head;
  while (current != NULL)
  {
    length++;
    current = current->next;
  }
  return length;
}

struct Node *rotateRight(struct Node *head, int k)
{
  if (head == NULL || k == 0)
  {
    return head;
  }

  int length = getLength(head);
  k = k % length; // Normalize k if it's greater than the length of the list

  if (k == 0)
  {
    return head;
  }

  // Find the new tail and the node before it
  struct Node *tail = head;
  struct Node *prev = NULL;
  for (int i = 0; i < length - k; i++)
  {
    prev = tail;
    tail = tail->next;
  }

  // Break the link between the new tail and the node before it
  prev->next = NULL;

  // Connect the original head to the original tail
  struct Node *newHead = tail;
  while (tail->next != NULL)
  {
    tail = tail->next;
  }
  tail->next = head;

  return newHead;
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
  insert(&head, 1);
  insert(&head, 2);
  insert(&head, 3);
  insert(&head, 4);
  insert(&head, 5);

  printf("Original List: ");
  printList(head);

  int k = 2; // Rotate the list to the right by 2 places
  struct Node *rotatedList = rotateRight(head, k);

  printf("Rotated List: ");
  printList(rotatedList);

  // Free the memory allocated for the linked list
  freeList(rotatedList);

  return 0;
}
