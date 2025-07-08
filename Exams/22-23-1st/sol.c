#include "dsa.h"
#include <stdio.h>

/*
Exercise 1.1: Print values in a BST inside the range [a,b]
*/
void printBSTInRange(BSTNode *root, int a, int b)
{
    if (root == NULL)
        return;

    // If current node's value is greater than a, explore left subtree
    if (root->data > a)
    {
        printBSTInRange(root->left, a, b);
    }

    // If current node's value is within the range [a, b], print it
    if (root->data >= a && root->data <= b)
    {
        printf("%d ", root->data);
    }

    // If current node's value is less than b, explore right subtree
    if (root->data < b)
    {
        printBSTInRange(root->right, a, b);
    }
}

/*
Exercise 1.2: Print values in a BST outside the range [a,b]
*/
void printBSTOutsideRange(BSTNode *root, int a, int b)
{
    if (root == NULL)
        return;

    // If current node's value is less than a, print it and explore right subtree
    if (root->data < a)
    {
        printf("%d ", root->data);
        printBSTOutsideRange(root->right, a, b);
    }
    // If current node's value is greater than b, print it and explore left subtree
    else if (root->data > b)
    {
        printf("%d ", root->data);
        printBSTOutsideRange(root->left, a, b);
    }
}

/*
Exercise 2.1: Recursive function aiming to check if a binary tree is sum balanced tree or no.
A sum balanced binary tree is a binary tree where the sum of the left subtree of each node is equal
to the sum of the nodes in its right subtree. You should provide a solution with complexity O(n).
*/

int abs(int x) { return (x < 0) ? -x : x; }

int isSumBalancedUtil(BTNode *root, int *isBalanced)
{
    if (root == NULL)
        return 0;

    // Calculate the sum of left and right subtrees
    int leftSum = isSumBalancedUtil(root->left, isBalanced);
    int rightSum = isSumBalancedUtil(root->right, isBalanced);

    // If the absolute difference between left and right sums is greater than 1, set isBalanced to 0
    if (abs(leftSum - rightSum) > 1)
    {
        *isBalanced = 0;
    }
    // Return the total sum of the subtree rooted at this node
    return leftSum + rightSum + root->data;
}

int isSumBalanced(BTNode *root)
{
    int isBalanced = 1;
    isSumBalancedUtil(root, &isBalanced);
    return isBalanced;
}

/*
Exercise 2.2: Recursive function aiming to check if a binary tree is a sum tree. A binary sum
tree is a binary tree where the value of a node is equal to the sum of the nodes present in its left
subtree and right sub-tree. You should provide a solution with complexity O(n).
*/
int isSumTreeUtil(BTNode *root, int *isSumT)
{
    if (root == NULL)
        return 0;

    // If it's a leaf node, return its value
    if (root->left == NULL && root->right == NULL)
        return root->data;

    // Calculate the sum of left and right subtrees
    int leftSum = isSumTreeUtil(root->left, isSumT);
    int rightSum = isSumTreeUtil(root->right, isSumT);

    // If the current node's value is not equal to the sum of its children, set isSumT to 0
    if (root->data != leftSum + rightSum)
    {
        *isSumT = 0;
    }

    // Return the total sum of the subtree rooted at this node
    return leftSum + rightSum + root->data;
}

int isSumTree(BTNode *root)
{
    int isSumT = 1;
    isSumTreeUtil(root, &isSumT);
    return isSumT;
}

/*
Exercise 3.1: Recursive method that takes two values v and x (x is negative) and returns v power x
(vx). The complexity of the function should be no more than O(log(n)).
*/
double powerNegative(double v, double x)
{
    if (x == 0)
        return 1; // Base case: v^0 = 1

    if (x < 0)
        return 1 / powerNegative(v, -x); // Convert to positive exponent

    double halfPower = powerNegative(v, x / 2);
    if ((int)x % 2 == 0)
        return halfPower * halfPower; // Even exponent
    else
        return halfPower * halfPower * v; // Odd exponent
}

/*
Exercise 3.2: Recursive method that takes two values v and x (x is positive) and returns v power x (vx).
The complexity of the function should be no more than O(log(n)).
*/
double powerPositive(double v, int x)
{
    if (x == 0)
        return 1; // Base case: v^0 = 1

    double halfPower = powerPositive(v, x / 2);
    if (x % 2 == 0)
        return halfPower * halfPower; // Even exponent
    else
        return halfPower * halfPower * v; // Odd exponent
}
int main()
{
    printf("=== Testing DSA Functions ===\n\n");

    // Test 1: BST Range Functions
    printf("1. Testing BST Range Functions:\n");
    printf("-------------------------------\n");

    // Create a BST: 50, 30, 70, 20, 40, 60, 80
    BSTNode *bstRoot = NULL;
    int bstValues[] = {50, 30, 70, 20, 40, 60, 80};
    int bstSize = sizeof(bstValues) / sizeof(bstValues[0]);

    for (int i = 0; i < bstSize; i++)
    {
        bstRoot = insertBSTNode(bstRoot, bstValues[i]);
    }

    printf("BST contains: 20, 30, 40, 50, 60, 70, 80\n");

    printf("Values in range [25, 65]: ");
    printBSTInRange(bstRoot, 25, 65);
    printf("\n");

    printf("Values outside range [25, 65]: ");
    printBSTOutsideRange(bstRoot, 25, 65);
    printf("\n\n");

    // Test 2: Sum Balanced Tree
    printf("2. Testing Sum Balanced Tree:\n");
    printf("-----------------------------\n");

    // Create a sum balanced tree
    //      10
    //     /  \
    //    5    5
    //   / \  / \
    //  1  4 2  3
    BTNode *sumBalancedRoot = createBTNode(10);
    sumBalancedRoot->left = createBTNode(5);
    sumBalancedRoot->right = createBTNode(5);
    sumBalancedRoot->left->left = createBTNode(1);
    sumBalancedRoot->left->right = createBTNode(4);
    sumBalancedRoot->right->left = createBTNode(2);
    sumBalancedRoot->right->right = createBTNode(3);

    printf("Tree structure:\n");
    printf("      10\n");
    printf("     /  \\\n");
    printf("    5    5\n");
    printf("   / \\  / \\\n");
    printf("  1  4 2  3\n");
    printf("Is sum balanced: %s\n", isSumBalanced(sumBalancedRoot) ? "Yes" : "No");

    // Create a non-sum balanced tree
    BTNode *nonSumBalancedRoot = createBTNode(10);
    nonSumBalancedRoot->left = createBTNode(8);
    nonSumBalancedRoot->right = createBTNode(2);
    nonSumBalancedRoot->left->left = createBTNode(3);
    nonSumBalancedRoot->left->right = createBTNode(5);

    printf("\nNon-balanced tree structure:\n");
    printf("      10\n");
    printf("     /  \\\n");
    printf("    8    2\n");
    printf("   / \\\n");
    printf("  3   5\n");
    printf("Is sum balanced: %s\n\n", isSumBalanced(nonSumBalancedRoot) ? "Yes" : "No");

    // Test 3: Sum Tree
    printf("3. Testing Sum Tree:\n");
    printf("-------------------\n");

    // Create a sum tree
    //      10
    //     /  \
    //    3    7
    //   / \  / \
    //  1  2 3  4
    BTNode *sumTreeRoot = createBTNode(10);
    sumTreeRoot->left = createBTNode(3);
    sumTreeRoot->right = createBTNode(7);
    sumTreeRoot->left->left = createBTNode(1);
    sumTreeRoot->left->right = createBTNode(2);
    sumTreeRoot->right->left = createBTNode(3);
    sumTreeRoot->right->right = createBTNode(4);

    printf("Tree structure:\n");
    printf("      10\n");
    printf("     /  \\\n");
    printf("    3    7\n");
    printf("   / \\  / \\\n");
    printf("  1  2 3  4\n");
    printf("Is sum tree: %s\n", isSumTree(sumTreeRoot) ? "Yes" : "No");

    // Create a non-sum tree
    BTNode *nonSumTreeRoot = createBTNode(15);
    nonSumTreeRoot->left = createBTNode(5);
    nonSumTreeRoot->right = createBTNode(7);
    nonSumTreeRoot->left->left = createBTNode(1);
    nonSumTreeRoot->left->right = createBTNode(2);

    printf("\nNon-sum tree structure:\n");
    printf("      15\n");
    printf("     /  \\\n");
    printf("    5    7\n");
    printf("   / \\\n");
    printf("  1   2\n");
    printf("Is sum tree: %s\n\n", isSumTree(nonSumTreeRoot) ? "Yes" : "No");

    // Test 4: Power Functions
    printf("4. Testing Power Functions:\n");
    printf("---------------------------\n");

    // Test positive power
    printf("Power function tests:\n");
    printf("2^3 = %.2f\n", powerPositive(2.0, 3));
    printf("5^4 = %.2f\n", powerPositive(5.0, 4));
    printf("3^0 = %.2f\n", powerPositive(3.0, 0));
    printf("2^10 = %.2f\n", powerPositive(2.0, 10));

    // Test negative power
    printf("\nNegative power function tests:\n");
    printf("2^(-3) = %.6f\n", powerNegative(2.0, -3));
    printf("5^(-2) = %.6f\n", powerNegative(5.0, -2));
    printf("4^(-1) = %.6f\n", powerNegative(4.0, -1));
    printf("10^(-2) = %.6f\n", powerNegative(10.0, -2));

    printf("\n=== All tests completed ===\n");

    return 0;
}
