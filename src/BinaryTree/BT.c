#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BT.h"
#include "./Queue/dynamic/Queue.h"

// Create a binary tree node
BTNode *createBTNode(BTElem data)
{
  BTNode *newNode = (BTNode *)malloc(sizeof(BTNode));
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

// Insert a node into the binary tree
void insertBTNode(BTNode **root, BTElem data)
{
  if (*root == NULL)
  {
    *root = createBTNode(data);
    return;
  }

  Queue q;
  initQueue(&q);
  enqueue(&q, *root);

  while (!isQueueEmpty(&q))
  {
    BTNode *current = peekFront(&q);
    dequeue(&q);

    if (current->left == NULL)
    {
      current->left = createBTNode(data);
      return;
    }
    else
    {
      enqueue(&q, current->left);
    }

    if (current->right == NULL)
    {
      current->right = createBTNode(data);
      return;
    }
    else
    {
      enqueue(&q, current->right);
    }
  }
}

// Build a binary tree from an array
BTNode *buildTreeFromArrayUtil(BTElem *arr, int size, int index)
{
  BTNode *root = NULL;

  if (index < size)
  {
    // Create a new node with the current array element
    root = createBTNode(arr[index]);

    // Recursively build the left and right subtrees
    root->left = buildTreeFromArrayUtil(arr, size, 2 * index + 1);
    root->right = buildTreeFromArrayUtil(arr, size, 2 * index + 2);
  }

  return root;
}

BTNode *buildTreeFromArray(BTElem *arr, int size)
{
  return buildTreeFromArrayUtil(arr, size, 0);
}

// Search for a node in the binary tree
bool searchBTNode(BTNode *root, BTElem data)
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

  // Recur down the appropriate subtree
  if (data < root->data)
  {
    return searchBTNode(root->left, data);
  }
  else
  {
    return searchBTNode(root->right, data);
  }
}

// Print the binary tree using in-order traversal
void inOrder(BTNode *root)
{
  if (root == NULL)
  {
    return;
  }

  inOrder(root->left);
  printf("%d ", root->data);
  inOrder(root->right);
}

// Print the binary tree using pre-order traversal
void preOrder(BTNode *root)
{
  if (root == NULL)
  {
    return;
  }

  printf("%d ", root->data);
  preOrder(root->left);
  preOrder(root->right);
}

// Print the binary tree using post-order traversal
void postOrder(BTNode *root)
{
  if (root == NULL)
  {
    return;
  }

  postOrder(root->left);
  postOrder(root->right);
  printf("%d ", root->data);
}

// Find the node with minimum value in a given BST
static BTNode *findMinValueNode(BTNode *node)
{
  BTNode *current = node;

  // Find the leftmost leaf
  while (current && current->left != NULL)
  {
    current = current->left;
  }

  return current;
}

// Delete a node from the binary tree
BTNode *deleteBTNode(BTNode *root, BTElem data)
{
  // Base case
  if (root == NULL)
  {
    return root;
  }

  // Recur down the tree
  if (data < root->data)
  {
    root->left = deleteBTNode(root->left, data);
  }
  else if (data > root->data)
  {
    root->right = deleteBTNode(root->right, data);
  }
  // If data is same as root's data, then this is the node to be deleted
  else
  {
    // Node with only one child or no child
    if (root->left == NULL)
    {
      BTNode *temp = root->right;
      free(root);
      return temp;
    }
    else if (root->right == NULL)
    {
      BTNode *temp = root->left;
      free(root);
      return temp;
    }

    // Node with two children
    // Get the inorder successor (smallest in the right subtree)
    BTNode *temp = findMinValueNode(root->right);

    // Copy the inorder successor's data to this node
    root->data = temp->data;

    // Delete the inorder successor
    root->right = deleteBTNode(root->right, temp->data);
  }
  return root;
}

// Free the binary tree
void freeBinaryTree(BTNode *root)
{
  if (root == NULL)
  {
    return;
  }

  // Post-order traversal to delete nodes
  freeBinaryTree(root->left);
  freeBinaryTree(root->right);
  free(root);
}