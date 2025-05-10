// Define the type of elements stored in the linked list
typedef int ListElem;
// You can change this to another type (e.g., float, char, or a struct)
// if you want the list to store different types of data.

// Define the structure for a node in the singly linked list
typedef struct ListNode
{
  ListElem val;          // The value stored in the node
  struct ListNode *next; // Pointer to the next node in the list
} ListNode;
// Each node contains a value and a pointer to the next node,
// forming the basis of the singly linked list.