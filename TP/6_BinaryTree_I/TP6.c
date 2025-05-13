#include "../../src/dsa.h"
#include <stdio.h>
#include <stdlib.h>

// EX-1: Sum of all values in the binary tree
int sum(BTNode *root)
{
  if (root == NULL)
    return 0;
  return root->data + sum(root->left) + sum(root->right);
}

// EX-2: Number of leaf nodes in the binary tree
int countLeaves(BTNode *root)
{
  if (root == NULL)
    return 0;
  if (root->left == NULL && root->right == NULL)
    return 1;
  return countLeaves(root->left) + countLeaves(root->right);
}

// EX-4: Number of full nodes in the binary tree
int countFullNodes(BTNode *root)
{
  if (root == NULL)
    return 0;

  int count = 0;

  // Check if current node is a full node
  if (root->left && root->right)
    count = 1;

  // Add the count of full nodes in left and right subtrees
  return count + countFullNodes(root->left) + countFullNodes(root->right);
}

// EX-5: Function to fill an array with the values of the binary tree in order
void fillArrayInOrderUtil(BTNode *root, int *arr, int *index)
{
  if (root == NULL)
    return;
  fillArrayInOrderUtil(root->left, arr, index);
  arr[(*index)++] = root->data;
  fillArrayInOrderUtil(root->right, arr, index);
}

void fillArrayInOrder(BTNode *root, int arr[])
{
  int index = 0;
  fillArrayInOrderUtil(root, arr, &index);
}

// EX-6: Function ot calculate the difference between the max and min values in the binary tree
BTElem findMax(BTNode *root)
{
  if (root == NULL)
    return INT_MIN;
  BTElem max = root->data;
  BTElem leftMax = findMax(root->left);
  BTElem rightMax = findMax(root->right);
  if (leftMax > max)
    max = leftMax;
  if (rightMax > max)
    max = rightMax;
  return max;
}

BTElem findMin(BTNode *root)
{
  if (root == NULL)
    return INT_MAX;
  BTElem min = root->data;
  BTElem leftMin = findMin(root->left);
  BTElem rightMin = findMin(root->right);
  if (leftMin < min)
    min = leftMin;
  if (rightMin < min)
    min = rightMin;
  return min;
}

BTElem maxMinDifference(BTNode *root)
{
  BTElem max = findMax(root);
  BTElem min = findMin(root);
  return max - min;
}

// Test the functions
int main()
{
  // Test data
  int arr[] = {15, 7, 23, 3, 9, 17, 31, 1, 5, 8, 11, 16, 19, 27, 35};
  int size = sizeof(arr) / sizeof(arr[0]);

  printf("\n===== Binary Tree Testing =====\n\n");

  // Build the binary tree
  BTNode *root = buildTreeFromArray(arr, size);

  printf("Tree traversals:\n");
  printf("In-order: ");
  inOrder(root);
  printf("\nPre-order: ");
  preOrder(root);
  printf("\nPost-order: ");
  postOrder(root);
  printf("\n\n");

  // Test EX-1: Sum of all values
  printf("Sum of all values: %d\n", sum(root));

  // Test EX-2: Count of leaf nodes
  printf("Number of leaf nodes: %d\n", countLeaves(root));

  // Test EX-4: Count of full nodes
  printf("Number of full nodes: %d\n", countFullNodes(root));

  // Test EX-5: Fill array in order
  int inOrderArr[size];
  fillArrayInOrder(root, inOrderArr);
  printf("Array filled in-order: ");
  for (int i = 0; i < size; i++)
  {
    printf("%d ", inOrderArr[i]);
  }
  printf("\n");

  // Test EX-6: Max-Min difference
  printf("Maximum value: %d\n", findMax(root));
  printf("Minimum value: %d\n", findMin(root));
  printf("Max-Min difference: %d\n\n", maxMinDifference(root));

  // Test inserting and deleting nodes
  printf("Testing insert and delete operations:\n");
  printf("Inserting value 10...\n");
  root = insertBTNode(root, 10);
  printf("In-order after insertion: ");
  inOrder(root);

  printf("\nDeleting value 15...\n");
  root = deleteBTNode(root, 15);
  printf("In-order after deletion: ");
  inOrder(root);

  // Test searching
  int searchValue = 9;
  printf("\n\nSearching for value %d: %s\n",
         searchValue,
         searchBTNode(root, searchValue) ? "Found" : "Not found");

  searchValue = 100;
  printf("Searching for value %d: %s\n",
         searchValue,
         searchBTNode(root, searchValue) ? "Found" : "Not found");

  // Free the memory allocated for the tree
  printf("\nFreeing binary tree...\n");
  freeBinaryTree(root);
  printf("Binary tree freed successfully.\n");

  return 0;
}
