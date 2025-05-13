// Define the type of elements stored in the Binary Tree
typedef int BTElem;
// You can change this to another type (e.g., float, char, or a struct)
// if you want the list to store different types of data.

// Define the structure for a node in the binary tree
typedef struct BTNode
{
  BTElem data;          // The value stored in the node
  struct BTNode *left;  // Pointer to the left child
  struct BTNode *right; // Pointer to the right child
} BTNode;