#include <stdbool.h> // Include for boolean data type (true/false)
#include "DEF_SLL.h" // Include the definition of ListNode and ListElem

// ? Functions Declaration

// Returns the number of elements in the linked list
extern int listLength(ListNode *head);

// Prints all elements in the linked list in order
extern void displayList(ListNode *head);

// Creates a new node for the linked list
extern ListNode *createListNode(ListElem elem);

// Adds a new element to the head (beginning) of the linked list
extern bool addHead(ListNode **head, ListElem elem);

// Adds a new element to the tail (end) of the linked list
extern bool addTail(ListNode **head, ListElem elem);

// Inserts a new element into the linked list
extern bool insert(ListNode **head, ListElem elem);

// Removes and returns the element at the head (beginning) of the linked list
extern ListElem removeHead(ListNode **head);

// Removes and returns the element at the tail (end) of the linked list
extern ListElem removeTail(ListNode **head);

// Frees the memory allocated for the linked list
extern void freeList(ListNode **head);