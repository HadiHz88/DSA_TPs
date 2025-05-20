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

// EX-3: Funciton to find the least common ancestor for 2 binary tree node
BTNode *LCA(BTNode *root, BTElem n1, BTElem n2)
{
  if (!root)
    return root;
  if (root->data == n1 || root->data == n2)
    return root;

  BTNode *left = LCA(root->left, n1, n2);
  BTNode *right = LCA(root->right, n1, n2);

  if (left && right)
    return root;
  return (left) ? left : right;
}

// EX-4: Funciton to return the sum for the max level
int Height(BTNode *root)
{
  if (root == NULL)
    return 0;
  else
  {
    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);

    if (leftHeight > rightHeight)
      return leftHeight + 1;
    else
      return rightHeight + 1;
  }
}
///////////////////////////////////////////////
int MaxLevel(BTNode *root)
{
  if (!root)
    return -1;
  int MaxSum = root->data;
  Stack CurrentLevel, NextLevel;

  initStack(&CurrentLevel);
  initStack(&NextLevel);

  BTNode *node;
  push(&CurrentLevel, root);

  while (!isStackEmpty(&CurrentLevel))
  {
    int LevelSum = 0;
    while (!isStackEmpty(&CurrentLevel))
    {
      node = peek(&CurrentLevel);
      pop(&CurrentLevel);
      LevelSum += node->data;

      if (node->left)
        push(&NextLevel, node->left);
      if (node->right)
        push(&NextLevel, node->right);
    }
    if (LevelSum > MaxSum)
      MaxSum = LevelSum;
    Stack tmp = CurrentLevel;
    CurrentLevel = NextLevel;
    NextLevel = tmp;
  }
  return MaxSum;
}

// EX: Function to check if a linkedlist is a path in a binary tree
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

// Test the functions
int main()
{
  // Test data
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof(arr) / sizeof(arr[0]);

  printf("\n===== Binary Tree II Testing =====\n\n");

  // Build the binary tree
  BTNode *root = buildTreeFromArray(arr, size);
  printf("Created binary tree with structure:\n");
  printf("        1\n");
  printf("      /   \\\n");
  printf("     2     3\n");
  printf("   /  \\   / \\\n");
  printf("  4    5 6   7\n");
  printf(" / \\\n");
  printf("8   9\n\n");

  // Print tree traversals for reference
  printf("Tree traversals:\n");
  printf("In-order: ");
  inOrder(root);
  printf("\nPre-order: ");
  preOrder(root);
  printf("\nPost-order: ");
  postOrder(root);
  printf("\n\n");

  // Test EX-1: Print values outside range
  int rangeStart = 3;
  int rangeEnd = 7;
  printf("Test EX-1: Values outside range [%d, %d]: ", rangeStart, rangeEnd);
  printValuesOutsideRange(root, rangeStart, rangeEnd);
  printf("\n\n");

  // Test EX-2: Check if the tree is a sum tree
  printf("Test EX-2: Is it a sum tree? ");
  if (isSumTree(root))
  {
    printf("Yes\n");
  }
  else
  {
    printf("No (expected since this is not a sum tree)\n");
  }

  // Create a simple sum tree for demonstration
  printf("\nCreating a small sum tree for testing:\n");
  BTNode *sumTreeRoot = createBTNode(10);
  sumTreeRoot->left = createBTNode(4);
  sumTreeRoot->right = createBTNode(6);

  printf("Sum tree structure:\n");
  printf("    10\n");
  printf("   /  \\\n");
  printf("  4    6\n");

  printf("Is this a sum tree? ");
  if (isSumTree(sumTreeRoot))
  {
    printf("Yes (correct)\n");
  }
  else
  {
    printf("No (incorrect)\n");
  }
  printf("\n");

  // Test EX-3: Least common ancestor
  BTElem node1 = 8;
  BTElem node2 = 9;
  BTNode *lca = LCA(root, node1, node2);
  printf("Test EX-3: LCA of %d and %d is: %d\n", node1, node2, lca ? lca->data : -1);

  node1 = 4;
  node2 = 7;
  lca = LCA(root, node1, node2);
  printf("LCA of %d and %d is: %d\n\n", node1, node2, lca ? lca->data : -1);

  // Test EX-4: Maximum level sum
  printf("Test EX-4: Maximum level sum is: %d\n\n", MaxLevel(root));

  // Test EX-5: Check if a linked list is a path in the binary tree
  printf("Test EX-5: Checking if linked lists are paths in the tree\n");

  // Create path 1->2->4->8 (exists in tree)
  ListNode *validPath = NULL;
  insert(&validPath, 8);
  insert(&validPath, 4);
  insert(&validPath, 2);
  insert(&validPath, 1);

  printf("Path: ");
  displayList(validPath);
  printf("Is this a path in the tree? %s\n",
         isSubPath(validPath, root) ? "Yes (correct)" : "No (incorrect)");

  // Create path 1->3->7 (exists in tree)
  ListNode *validPath2 = NULL;
  insert(&validPath2, 7);
  insert(&validPath2, 3);
  insert(&validPath2, 1);

  printf("Path: ");
  displayList(validPath2);
  printf("Is this a path in the tree? %s\n",
         isSubPath(validPath2, root) ? "Yes (correct)" : "No (incorrect)");

  // Create path 1->2->5->9 (doesn't exist in tree)
  ListNode *invalidPath = NULL;
  insert(&invalidPath, 9);
  insert(&invalidPath, 5);
  insert(&invalidPath, 2);
  insert(&invalidPath, 1);

  printf("Path: ");
  displayList(invalidPath);
  printf("Is this a path in the tree? %s\n",
         isSubPath(invalidPath, root) ? "Yes (incorrect)" : "No (correct)");

  // Free memory
  freeBinaryTree(root);
  freeBinaryTree(sumTreeRoot);
  freeList(&validPath);
  freeList(&validPath2);
  freeList(&invalidPath);

  printf("\nAll tests completed successfully!\n");
  return 0;
}