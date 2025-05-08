#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "bt.c"

/*=========================================================================*/

int sumTree(struct Node *root)
{
  if (!root)
    return 0;

  return root->data + sumTree(root->left) + sumTree(root->right);
}

/*=========================================================================*/

int countLeaves(struct Node *root)
{
  if (!root)
    return 0;

  if (!root->left && !root->right)
  {
    return 1;
  }

  return countLeaves(root->left) + countLeaves(root->right);
}

/*=========================================================================*/

int countFullNodes(struct Node *root)
{
  if (!root)
    return 0;

  if (root->left && root->right)
  {
    return 1;
  }

  return countLeaves(root->left) + countLeaves(root->right);
}

/*=========================================================================*/

void fillArrayInOrderUtil(struct Node *root, int arr[], int *index)
{
  if (!root)
  {
    return;
  }

  fillArrayInOrderUtil(root->left, arr, index);
  arr[(*index)++] = root->data;
  fillArrayInOrderUtil(root->right, arr, index);
}

void fillArrayInOrder(struct Node *root, int arr[])
{
  int index = 0;
  fillArrayInOrderUtil(root, arr, &index);
}

/*=========================================================================*/

int findMax(struct Node *root)
{
  if (!root)
    return INT_MIN;

  int max = root->data;

  int left = findMax(root->left);

  int right = findMax(root->right);

  if (left > max)
    max = left;

  if (right > max)
    max = right;

  return max;
}

int findMin(struct Node *root)
{
  if (!root)
    return INT_MAX;

  int min = root->data;

  int left = findMin(root->left);

  int right = findMin(root->right);

  if (left < min)
    min = left;

  if (right < min)
    min = right;

  return min;
}

int maxMinDifference(struct Node *root)
{
  return findMax(root) - findMin(root);
}

int main()
{

  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  int size = sizeof(arr) / sizeof(arr[0]);

  struct Node *root = buildTree(arr, 0, size);

  printf("Tree Created, Inorder Traversal of the Tree: ");
  inorderTraversal(root);

  printf("\n\n#############\n\n");

  printf("Sum of Tree Nodes: %d", sumTree(root));

  printf("\n\n#############\n\n");

  printf("Number off Leaf Nodes: %d", countLeaves(root));

  printf("\n\n#############\n\n");

  printf("The Difference Between Max and Min: %d", maxMinDifference(root));

  printf("\n\n#############\n\n");

  printf("The Array Filled By Inorder Traversal Of The Tree: ");

  int arr2[size];

  fillArrayInOrder(root, arr2);

  for (int i = 0; i < size; i++)
  {
    printf("%d ", arr2[i]);
  }

  printf("\n\n#############\n\n");

  return 0;
}