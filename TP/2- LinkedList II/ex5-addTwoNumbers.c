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

struct Node *addNumbers(struct Node *num1, struct Node *num2)
{
  if (num1 == NULL)
  {
    return num2;
  }
  if (num2 == NULL)
  {
    return num1;
  }

  struct Node *result = NULL;
  struct Node *tail = NULL;
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

    struct Node *newNode = createNode(digit);
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
  struct Node *num1 = NULL;
  struct Node *num2 = NULL;

  // Insert digits into the first number (753)
  insert(&num1, 7);
  insert(&num1, 5);
  insert(&num1, 3);

  // Insert digits into the second number (248)
  insert(&num2, 2);
  insert(&num2, 4);
  insert(&num2, 8);

  printf("Number 1: ");
  printList(num1);
  printf("Number 2: ");
  printList(num2);

  struct Node *sum = addNumbers(num1, num2);

  printf("Sum: ");
  printList(sum);

  // Free the memory allocated for the linked lists
  freeList(num1);
  freeList(num2);
  freeList(sum);

  return 0;
}
