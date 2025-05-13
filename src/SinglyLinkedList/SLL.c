#include <stdio.h>
#include <stdlib.h>
#include "SLL.h" // Include the header file for function declarations

// Returns the number of elements in the linked list
int listLength(ListNode *head)
{
  int count = 0;
  ListNode *current = head;
  while (current != NULL)
  {
    count++;                 // Increment the count for each node
    current = current->next; // Move to the next node
  }
  return count; // Return the total count
}

// Prints all elements in the linked list in order
void displayList(ListNode *head)
{
  ListNode *current = head;
  while (current != NULL)
  {
    printf("%d", current->data); // Print the value of the current node
    if (current->next != NULL)
    {
      printf(" -> "); // Print an arrow if there is a next node
    }
    current = current->next; // Move to the next node
  }
  printf("\n"); // Print a newline at the end
}

// Creates a new node for the linked list
ListNode *createListNode(ListElem elem)
{
  ListNode *newNode = (ListNode *)malloc(sizeof(ListNode)); // Allocate memory for the new node
  if (newNode == NULL)
  {
    printf("Memory allocation failed.\n");
    return NULL; // Return NULL if memory allocation fails
  }
  newNode->data = elem; // Set the value of the new node
  newNode->next = NULL; // Initialize the next pointer to NULL
  return newNode;       // Return the newly created node
}

// Adds a new element to the head (beginning) of the linked list
bool addHead(ListNode **head, ListElem elem)
{
  ListNode *newNode = createListNode(elem); // Create a new node
  if (newNode == NULL)
  {
    return false; // Return false if node creation fails
  }
  newNode->next = *head; // Point the new node to the current head
  *head = newNode;       // Update the head to the new node
  return true;           // Return true to indicate success
}

// Adds a new element to the tail (end) of the linked list
bool addTail(ListNode **head, ListElem elem)
{
  ListNode *newNode = createListNode(elem); // Create a new node
  if (newNode == NULL)
  {
    return false; // Return false if node creation fails
  }
  if (*head == NULL)
  {
    *head = newNode; // If the list is empty, set the new node as the head
  }
  else
  {
    ListNode *current = *head;
    while (current->next != NULL)
    {
      current = current->next; // Traverse to the last node
    }
    current->next = newNode; // Point the last node to the new node
  }
  return true; // Return true to indicate success
}

// Inserts a new element into the linked list
bool insert(ListNode **head, ListElem elem)
{
  return addTail(head, elem); // For simplicity, we can use addTail to insert
}

// Removes and returns the element at the head (beginning) of the linked list
ListElem removeHead(ListNode **head)
{
  if (*head == NULL)
  {
    printf("List is empty. Cannot remove head.\n");
    return -1; // Return -1 to indicate failure (or use a sentinel value)
  }
  ListNode *temp = *head;      // Store the current head
  ListElem value = temp->data; // Get the value of the head
  *head = (*head)->next;       // Update the head to the next node
  free(temp);                  // Free the memory of the old head
  return value;                // Return the removed value
}

// Removes and returns the element at the tail (end) of the linked list
ListElem removeTail(ListNode **head)
{
  if (*head == NULL)
  {
    printf("List is empty. Cannot remove tail.\n");
    return -1; // Return -1 to indicate failure (or use a sentinel value)
  }
  if ((*head)->next == NULL)
  {
    // If there is only one node in the list
    ListElem value = (*head)->data; // Get the value of the head
    free(*head);                    // Free the memory of the head
    *head = NULL;                   // Set the head to NULL
    return value;                   // Return the removed value
  }
  ListNode *current = *head;
  while (current->next->next != NULL)
  {
    current = current->next; // Traverse to the second-to-last node
  }
  ListElem value = current->next->data; // Get the value of the last node
  free(current->next);                  // Free the memory of the last node
  current->next = NULL;                 // Set the next pointer of the second-to-last node to NULL
  return value;                         // Return the removed value
}

// Frees the memory allocated for the linked list
void freeList(ListNode **head)
{
  ListNode *current = *head;
  // Traverse the list and free each node
  while (current != NULL)
  {
    ListNode *temp = current; // Store the current node
    current = current->next;  // Move to the next node
    free(temp);               // Free the memory of the current node
  }
  *head = NULL; // Set the head to NULL after freeing all nodes
}