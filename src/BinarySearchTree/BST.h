#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DEF_BST.h"

// Create a binary search tree node
extern BSTNode *createBSTNode(BSTElem data);

// Insert a node into the binary search tree
extern BSTNode *insertBSTNode(BSTNode *root, BSTElem data);

// Build a binary search tree from an array
extern BSTNode *buildBSTFromArray(BSTElem *arr, int size);

// Search for a node in the binary search tree
extern bool searchBSTNode(BSTNode *root, BSTElem data);

// Print the binary search tree using the in-order traversal
extern void inOrderBST(BSTNode *root);

// Print the binary search tree using the pre-order traversal
extern void preOrderBST(BSTNode *root);

// Print the binary search tree using the post-order traversal
extern void postOrderBST(BSTNode *root);

// Find the minimum value in the binary search tree
extern BSTNode *findMinBST(BSTNode *root);

// Find the maximum value in the binary search tree
extern BSTNode *findMaxBST(BSTNode *root);

// Delete a node from the binary search tree
extern BSTNode *deleteBSTNode(BSTNode *root, BSTElem data);

// Free the binary search tree
extern void freeBST(BSTNode *root);