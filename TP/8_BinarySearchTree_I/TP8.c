#include "../../src/dsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Ex1: Function to check if a binary tree is a binary search tree (BST) using recursion
int isBST_recursion_util(BSTNode *root, int min, int max)
{
    if (root == NULL)
        return 1;

    if (root->data < min || root->data > max)
        return 0;

    return isBST_recursion_util(root->left, min, root->data - 1) && isBST_recursion_util(root->right, root->data + 1, max);
}

int isBST_recursion(BSTNode *root)
{
    return (isBST_recursion_util(root, INT_MIN, INT_MAX));
}

// Ex1-b: Function to check if a binary tree is a binary search tree (BST) using iteration
// Make sure that the StackElem type is defined as BSTNode* in the stack implementation
int isBST_iterative(BSTNode *root)
{
    if (root == NULL)
        return 1;

    Stack stack;
    initStack(&stack);

    BSTNode *current = root;
    BSTNode *prev = NULL;
    BSTElem last_value = INT_MIN;
    bool first_node = true;

    // In-order traversal: left, root, right
    while (current != NULL || !isStackEmpty(&stack))
    {
        // Go to the leftmost node
        while (current != NULL)
        {
            push(&stack, current);
            current = current->left;
        }

        // Process the current node
        current = (BSTNode *)pop(&stack);

        // Check the BST property - each node must be greater than the previous node
        if (!first_node && current->data <= last_value)
        {
            freeStack(&stack);
            return 0; // Not a BST
        }

        // Update last value and set first_node flag to false
        last_value = current->data;
        first_node = false;

        // Move to right subtree
        current = current->right;
    }

    freeStack(&stack);
    return 1; // It's a BST
}

// ########################################################################################
// ########################################################################################
// ########################################################################################

// Ex2: Function to find the lowest common ancestor (LCA) of two nodes in a BST
BSTNode *LCA(BSTNode *root, BSTElem n1, BSTElem n2)
{
    if (root == NULL)
        return NULL;

    // If both n1 and n2 are smaller than root, then LCA lies in left
    if (root->data > n1 && root->data > n2)
        return LCA(root->left, n1, n2);

    // If both n1 and n2 are greater than root, then LCA lies in right
    if (root->data < n1 && root->data < n2)
        return LCA(root->right, n1, n2);

    return root;
}

// ########################################################################################
// ########################################################################################
// ########################################################################################

// Another Util Function, Search for a value in BST (excluding the current node)
int search(BSTNode *root, BSTNode *exclude, int key)
{
    while (root != NULL)
    {
        if (root != exclude && root->data == key)
            return 1;
        else if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return 0;
}

// Recursive Util function to find a pair with given sum
bool findPairUtil(BSTNode *root, BSTNode *curr, int sum)
{
    if (curr == NULL)
        return false;

    if (search(root, curr, sum - curr->data))
        return true;

    return findPairUtil(root, curr->left, sum) || findPairUtil(root, curr->right, sum);
}

// Ex3: Function to find 2 pairs in BST with given sum
bool findPair(BSTNode *root, int sum)
{
    return findPairUtil(root, root, sum);
}

// ########################################################################################
// ########################################################################################
// ########################################################################################

int main()
{
    printf("Binary Search Tree Tests\n");
    printf("=======================\n\n");

    // Test case 1: Valid BST
    printf("=== Test Case 1: Valid BST ===\n");
    BSTNode *validBST = NULL;
    validBST = insertBSTNode(validBST, 50);
    validBST = insertBSTNode(validBST, 30);
    validBST = insertBSTNode(validBST, 70);
    validBST = insertBSTNode(validBST, 20);
    validBST = insertBSTNode(validBST, 40);
    validBST = insertBSTNode(validBST, 60);
    validBST = insertBSTNode(validBST, 80);

    printf("Tree structure (inorder): ");
    inOrderBST(validBST);
    printf("\n");

    printf("isBST_recursion: %s\n", isBST_recursion(validBST) ? "Yes" : "No");
    printf("isBST_iterative: %s\n", isBST_iterative(validBST) ? "Yes" : "No");

    // Test LCA on valid BST
    BSTNode *lca1 = LCA(validBST, 20, 40);
    BSTNode *lca2 = LCA(validBST, 20, 80);
    printf("LCA of 20 and 40: %d\n", lca1 ? lca1->data : -1);
    printf("LCA of 20 and 80: %d\n", lca2 ? lca2->data : -1);

    // Test case 2: Invalid BST (manually created with a violation)
    printf("\n=== Test Case 2: Invalid BST ===\n");
    BSTNode *invalidBST = createBSTNode(50);
    invalidBST->left = createBSTNode(30);
    invalidBST->right = createBSTNode(70);
    invalidBST->left->left = createBSTNode(20);
    invalidBST->left->right = createBSTNode(60); // Invalid: 60 > 50, violates BST property
    invalidBST->right->left = createBSTNode(60);
    invalidBST->right->right = createBSTNode(80);

    printf("Invalid Tree structure (inorder): ");
    inOrderBST(invalidBST);
    printf("\n");

    printf("isBST_recursion: %s\n", isBST_recursion(invalidBST) ? "Yes" : "No");
    printf("isBST_iterative: %s\n", isBST_iterative(invalidBST) ? "Yes" : "No");

    // Test case 3: Empty BST
    printf("\n=== Test Case 3: Empty BST ===\n");
    BSTNode *emptyBST = NULL;
    printf("isBST_recursion: %s\n", isBST_recursion(emptyBST) ? "Yes" : "No");
    printf("isBST_iterative: %s\n", isBST_iterative(emptyBST) ? "Yes" : "No");

    // Test case 4: Single node BST
    printf("\n=== Test Case 4: Single Node BST ===\n");
    BSTNode *singleNodeBST = createBSTNode(10);

    printf("Single node tree (inorder): ");
    inOrderBST(singleNodeBST);
    printf("\n");

    printf("isBST_recursion: %s\n", isBST_recursion(singleNodeBST) ? "Yes" : "No");
    printf("isBST_iterative: %s\n", isBST_iterative(singleNodeBST) ? "Yes" : "No");

    // Test case 5: More complex LCA tests
    printf("\n=== Test Case 5: Additional LCA Tests ===\n");
    // Create a larger BST for LCA testing
    BSTNode *lcaTestBST = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80, 15, 25, 35, 45, 55, 65, 75, 85};
    int size = sizeof(values) / sizeof(values[0]);

    lcaTestBST = buildBSTFromArray(values, size);

    printf("LCA test tree (inorder): ");
    inOrderBST(lcaTestBST);
    printf("\n");

    BSTNode *lca3 = LCA(lcaTestBST, 15, 45);
    BSTNode *lca4 = LCA(lcaTestBST, 55, 85);
    BSTNode *lca5 = LCA(lcaTestBST, 15, 85);

    printf("LCA of 15 and 45: %d\n", lca3 ? lca3->data : -1);
    printf("LCA of 55 and 85: %d\n", lca4 ? lca4->data : -1);
    printf("LCA of 15 and 85: %d\n", lca5 ? lca5->data : -1);

    // Test case 6: Find pairs with given sum
    printf("\n=== Test Case 6: Find Pairs with Given Sum ===\n");
    int sum = 100;
    printf("Finding pairs with sum %d in the BST...\n", sum);
    if (findPair(lcaTestBST, sum))
        printf("Found a pair with sum %d\n", sum);
    else
        printf("No pair found with sum %d\n", sum);

    // Free all the trees
    freeBST(validBST);
    freeBST(invalidBST);
    freeBST(singleNodeBST);
    freeBST(lcaTestBST);

    return 0;
}
