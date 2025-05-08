#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node
struct Node
{
  int data;
  struct Node *left;
  struct Node *right;
};

// Function to create a new node
struct Node *createNode(int data)
{
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

// Function to build a binary tree
struct Node *buildTree(int arr[], int index, int size)
{
  struct Node *root = NULL;

  // Base case for recursion
  if (index < size)
  {
    // Create a new node with the current element
    root = createNode(arr[index]);

    // Recursively construct the left and right subtrees
    root->left = buildTree(arr, 2 * index + 1, size);
    root->right = buildTree(arr, 2 * index + 2, size);
  }

  return root;
}

// Function to print the inorder traversal of the binary tree
void inorderTraversal(struct Node *root)
{
  if (root != NULL)
  {
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
  }
}
