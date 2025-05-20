#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BST.h"

// Create a binary search tree node
BSTNode *createBSTNode(BSTElem data)
{
  BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
  if (newNode == NULL)
  {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

// Insert a node into the binary search tree
BSTNode *insertBSTNode(BSTNode *root, BSTElem data)
{
  // If the tree is empty, create a new node
  if (root == NULL)
  {
    return createBSTNode(data);
  }

  // Otherwise, recur down the tree
  if (data < root->data)
  {
    root->left = insertBSTNode(root->left, data);
  }
  else if (data > root->data)
  {
    root->right = insertBSTNode(root->right, data);
  }
  // If data is already present, do nothing (BST doesn't allow duplicates)

  // Return the unchanged node pointer
  return root;
}

// Build a binary search tree from an array
BSTNode *buildBSTFromArray(BSTElem *arr, int size)
{
  BSTNode *root = NULL;

  // Insert each element into the BST
  for (int i = 0; i < size; i++)
  {
    root = insertBSTNode(root, arr[i]);
  }

  return root;
}

// Search for a node in the binary search tree
bool searchBSTNode(BSTNode *root, BSTElem data)
{
  // Base case: root is NULL or data is found
  if (root == NULL)
  {
    return false;
  }

  if (root->data == data)
  {
    return true;
  }

  // BST property: recur on left subtree if data is smaller, right otherwise
  if (data < root->data)
  {
    return searchBSTNode(root->left, data);
  }
  else
  {
    return searchBSTNode(root->right, data);
  }
}

// Print the binary search tree using in-order traversal
void inOrderBST(BSTNode *root)
{
  if (root == NULL)
  {
    return;
  }

  inOrderBST(root->left);
  printf("%d ", root->data);
  inOrderBST(root->right);
}

// Print the binary search tree using pre-order traversal
void preOrderBST(BSTNode *root)
{
  if (root == NULL)
  {
    return;
  }

  printf("%d ", root->data);
  preOrderBST(root->left);
  preOrderBST(root->right);
}

// Print the binary search tree using post-order traversal
void postOrderBST(BSTNode *root)
{
  if (root == NULL)
  {
    return;
  }

  postOrderBST(root->left);
  postOrderBST(root->right);
  printf("%d ", root->data);
}

// Find the minimum value in the binary search tree
BSTNode *findMinBST(BSTNode *root)
{
  // Error case
  if (root == NULL)
  {
    return NULL;
  }

  // In BST, the leftmost node has the minimum value
  BSTNode *current = root;
  while (current->left != NULL)
  {
    current = current->left;
  }

  return current;
}

// Find the maximum value in the binary search tree
BSTNode *findMaxBST(BSTNode *root)
{
  // Error case
  if (root == NULL)
  {
    return NULL;
  }

  // In BST, the rightmost node has the maximum value
  BSTNode *current = root;
  while (current->right != NULL)
  {
    current = current->right;
  }

  return current;
}

// Delete a node from the binary search tree
BSTNode *deleteBSTNode(BSTNode *root, BSTElem data)
{
  // Base case
  if (root == NULL)
  {
    return root;
  }

  // Recur down the tree
  if (data < root->data)
  {
    root->left = deleteBSTNode(root->left, data);
  }
  else if (data > root->data)
  {
    root->right = deleteBSTNode(root->right, data);
  }
  // If data is same as root's data, then this is the node to be deleted
  else
  {
    // Node with only one child or no child
    if (root->left == NULL)
    {
      BSTNode *temp = root->right;
      free(root);
      return temp;
    }
    else if (root->right == NULL)
    {
      BSTNode *temp = root->left;
      free(root);
      return temp;
    }

    // Node with two children
    // Get the inorder successor (smallest in the right subtree)
    BSTNode *temp = findMinBST(root->right);

    // Copy the inorder successor's data to this node
    root->data = temp->data;

    // Delete the inorder successor
    root->right = deleteBSTNode(root->right, temp->data);
  }
  return root;
}

// Free the binary search tree
void freeBST(BSTNode *root)
{
  if (root == NULL)
  {
    return;
  }

  // Post-order traversal to delete nodes
  freeBST(root->left);
  freeBST(root->right);
  free(root);
}