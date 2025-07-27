#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BT.h"
#include "../Queue/dynamic/Queue.h"

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

// Find a node with the given data in the binary tree
BTNode *searchBTNode(BTNode *root, BTElem data)
{
  // Base case: root is NULL
  if (root == NULL)
  {
    return NULL;
  }

  // Check if current node contains the data
  if (root->data == data)
  {
    return root;
  }

  // Search in left subtree
  BTNode *leftResult = findBTNode(root->left, data);
  if (leftResult != NULL)
  {
    return leftResult;
  }

  // Search in right subtree
  return findBTNode(root->right, data);
}

BTNode *deleteDeepestNodeHelper(BTNode **root, BTNode *delNode)
{

  BTNode *deletedNode;

  if (*root == delNode)
  {
    deletedNode = *root;
    *root = NULL; // If the root is the node to be deleted, set it to NULL
    free(delNode);
    return deletedNode;
  }

  Queue q;
  initQueue(&q);
  enqueue(&q, *root);

  BTNode *temp;

  while (!isQueueEmpty(&q))
  {
    temp = peekFront(&q);
    dequeue(&q);

    if (temp->right != NULL)
    {

      if (temp->right == delNode)
      {
        deletedNode = temp->right;
        free(temp->right);
        temp->right = NULL; // Set the right child to NULL
        return deletedNode;
      }
      else
      {
        enqueue(&q, temp->right);
      }
    }

    if (temp->left != NULL)
    {
      if (temp->left == delNode)
      {
        deletedNode = temp->left;
        free(temp->left);
        temp->left = NULL; // Set the left child to NULL
        return deletedNode;
      }
      else
      {
        enqueue(&q, temp->left);
      }
    }
  }
}

// Delete a node from the binary tree
BTNode *deleteBTNode(BTNode **root, BTElem data)
{

  if (*root == NULL)
  {
    return NULL; // Node not found
  }

  Queue q;
  initQueue(&q);

  BTNode *tmp;
  BTNode *foundNode = NULL;

  enqueue(&q, *root);

  while (!isQueueEmpty(&q))
  {
    tmp = peekFront(&q);

    dequeue(&q);

    if (tmp->data == data)
    {
      foundNode = tmp; // Node to be deleted found
    }

    if (tmp->left != NULL)
    {
      enqueue(&q, tmp->left);
    }

    if (tmp->right != NULL)
    {
      enqueue(&q, tmp->right);
    }
  }

  int lastNodeData = tmp->data; // Store the last node's data

  foundNode->data = lastNodeData; // Replace found node's data with last node's data
  // Now delete the last node
  return deleteDeepestNodeHelper(root, tmp);
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