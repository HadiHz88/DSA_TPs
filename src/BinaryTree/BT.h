#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DEF_BT.h"

// Create a binary tree node
extern BTNode *createBTNode(BTElem data);

// Insert a node into the binary tree
extern void insertBTNode(BTNode **root, BTElem data);

// Build a binary tree from an array
extern BTNode *buildTreeFromArray(BTElem *arr, int size);

// search for a node in the binary tree
extern bool searchBTNode(BTNode *root, BTElem data);

// print the binary using the in-order traversal
extern void inOrder(BTNode *root);

// print the binary using the pre-order traversal
extern void preOrder(BTNode *root);

// print the binary using the post-order traversal
extern void postOrder(BTNode *root);

// Delete a node from the binary tree
extern BTNode *deleteBTNode(BTNode *root, BTElem data);

// free the binary tree
extern void freeBinaryTree(BTNode *root);
