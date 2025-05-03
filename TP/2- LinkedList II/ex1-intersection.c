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

struct Node *getIntersection(struct Node *list1, struct Node *list2)
{
  struct Node dummy; // Dummy node to build the result list
  struct Node *tail = &dummy;
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
  // Create the first sorted linked list: 1->2->4->6
  struct Node *list1 = NULL;
  insert(&list1, 1);
  insert(&list1, 2);
  insert(&list1, 4);
  insert(&list1, 6);

  // Create the second sorted linked list: 2->4->5->6
  struct Node *list2 = NULL;
  insert(&list2, 2);
  insert(&list2, 4);
  insert(&list2, 5);
  insert(&list2, 6);

  printf("List 1: ");
  printList(list1);
  printf("List 2: ");
  printList(list2);

  struct Node *intersection = getIntersection(list1, list2);

  printf("Intersection: ");
  printList(intersection);

  // Free the memory allocated for the linked lists
  freeList(list1);
  freeList(list2);
  freeList(intersection);

  return 0;
}
