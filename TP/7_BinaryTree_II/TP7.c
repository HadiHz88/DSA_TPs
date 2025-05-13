#include "../../src/dsa.h"
#include <stdio.h>
#include <stdlib.h>

// EX-1: Function to print the values outside the range [a, b] in a binary tree
void printValuesOutsideRange(BTNode *root, int a, int b)
{
  if (root == NULL)
    return;

  // Check if the current node's value is outside the range [a, b]
  if (root->data < a || root->data > b)
  {
    printf("%d ", root->data);
  }

  // Recursively check the left and right subtrees
  printValuesOutsideRange(root->left, a, b);
  printValuesOutsideRange(root->right, a, b);
}

// EX-2: Fucntion to check if a binary tree is a sumTree
int isSumTreeUtil(BTNode *root, int *isSum)
{
  if (root == NULL)
  {
    return 0;
  }

  // Check if the left and right subtrees are sum trees
  int leftSum = isSumTreeUtil(root->left, isSum);
  int rightSum = isSumTreeUtil(root->right, isSum);

  // Check if the current node's value is equal to the sum of its children's values
  if (root->data != leftSum + rightSum)
  {
    *isSum = 0;
  }

  // Return the sum of the current node's value and its children's values
  return root->data + leftSum + rightSum;
}

int isSumTree(BTNode *root)
{
  int isSum = 1; // Initialize to true
  isSumTreeUtil(root, &isSum);
  return isSum;
}

// EX-4: Function to check if a linkedlist is a path in a binary tree
bool isPathUtil(ListNode *curList, BTNode *curTree)
{
  // If the complete linked list is traversed
  if (curList == NULL)
    return true;

  // If the tree node doesnot exist
  if (curTree == NULL)
    return false;

  if (curList->data == curTree->data)
  {

    // Recursively calling for the next element
    return isPathUtil(curList->next, curTree->left) || isPathUtil(curList->next, curTree->right);
  }
  else
  {

    // If not found, return false
    return false;
  }
}

// Function to check if the linked list exist as a downward path in Binary tree using the DFS Traversal of the Tree
bool isSubPath(ListNode *head, BTNode *root)
{

  // If the current node of the tree is Null
  if (root == NULL)
    return false;

  // If the complete linked list has been found
  if (head == NULL)
    return true;

  // Stores if there exist the required path
  bool isPossible = false;

  if (root->data == head->data)
  {

    // Recursively calling to check the next node of the linked list
    isPossible = isPathUtil(head->next, root->left) || isPathUtil(head->next, root->right);
  }

  // Recursive calling for the next elements of the binary tree
  return isPossible || isSubPath(head, root->left) || isSubPath(head, root->right);
}
