#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

bool hasCycle(struct Node *head)
{
  if (head == NULL || head->next == NULL)
  {
    return false;
  }

  struct Node *slow = head;
  struct Node *fast = head;

  while (fast != NULL && fast->next != NULL)
  {
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast)
    {
      return true;
    }
  }

  return false;
}

struct Node *detectCycle(struct Node *head)
{
  if (head == NULL || head->next == NULL)
  {
    return NULL;
  }

  struct Node *slow = head;
  struct Node *fast = head;
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
  struct Node *temp;
  while (head != NULL)
  {
    temp = head;
    head = head->next;
    free(temp);
  }
}

int main()
{
  struct Node *head = NULL;
  insert(&head, 1);
  insert(&head, 2);
  insert(&head, 3);
  insert(&head, 4);
  insert(&head, 5);

  // Create a cycle for testing
  head->next->next->next->next->next = head->next; // Cycle: 5 -> 2

  if (hasCycle(head))
  {
    struct Node *cycleStart = detectCycle(head);
    if (cycleStart != NULL)
    {
      printf("Cycle detected starting at node with data: %d\n", cycleStart->data);
    }
    else
    {
      printf("No cycle detected.\n");
    }
  }
  else
  {
    printf("No cycle detected.\n");
  }

  freeList(head); // Free the list memory (not applicable for cyclic lists)

  return 0;
}