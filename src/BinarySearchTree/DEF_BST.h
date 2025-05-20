// Define the type of elements stored in the Binary Search Tree
typedef int BSTElem;
// You can change this to another type (e.g., float, char, or a struct)
// if you want the list to store different types of data.

// Define the structure for a node in the binary search tree
typedef struct BSTNode
{
  BSTElem data;          // The value stored in the node
  struct BSTNode *left;  // Pointer to the left child
  struct BSTNode *right; // Pointer to the right child
} BSTNode;