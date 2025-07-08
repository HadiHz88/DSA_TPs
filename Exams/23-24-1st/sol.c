#include "dsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Exercise 1:
    A perfect binary tree is a special type of binary tree in which all the leaf nodes are at the same
    depth, and all non-leaf nodes have two children. In simple terms, this means that all leaf nodes are
    at the maximum depth of the tree, and the tree is completely filled with no gaps. In the following
    figure, the left figure is a perfect binary tree while the right is not. In this question, you are asked
    to write a function that checks if a binary tree is a perfect one or no. You are allowed to write the
    method recursively or iteratively and use the ADT stack or queue if you need.

    Hint: write a function to calculate the depth of the tree. Then all leaf nodes should be at the same
    depth. Recall that at level 0 (the root), we have 20 nodes, at level 1 we have 21 nodes, at level i we
    have 2i nodes.
*/
int getDepth(BTNode *node)
{
    int depth = 0;
    while (node != NULL)
    {
        depth++;
        node = node->left;
    }
    return depth;
}

int isPerfectUtil(BTNode *root, int depth, int level)
{
    if (root == NULL)
        return 1;

    // If it's a leaf node, check its depth
    if (root->left == NULL && root->right == NULL)
        return (depth == level + 1);

    // If internal node with only one child
    if (root->left == NULL || root->right == NULL)
        return 0;

    // Recur on both children
    return isPerfectUtil(root->left, depth, level + 1) &&
           isPerfectUtil(root->right, depth, level + 1);
}

int isPerfectBinaryTree(BTNode *root)
{
    int depth = getDepth(root);
    return isPerfectUtil(root, depth, 0);
}

/*
Exercise 2:
    Given a binary search tree root and a linked list with head as the first node. We want to write the
    function that returns 1 if all the elements in the linked list starting from the head correspond to
    some downward path connected in the binary tree otherwise return 0. In this context downward
    path means a path that starts at some node and goes downwards.
*/
bool dfs(BSTNode *tree_node, ListNode *list_node)
{
    if (!list_node)
    {
        return true; // Reached end of linked list - path found
    }

    if (!tree_node)
    {
        return false; // Reached end of tree but not end of linked list
    }

    if (tree_node->data != list_node->data)
    {
        return false; // Values don't match
    }

    // Check if remaining path exists in left or right subtree
    return dfs(tree_node->left, list_node->next) ||
           dfs(tree_node->right, list_node->next);
}

bool isSubPath(BSTNode *root, ListNode *head)
{
    if (!head)
    {
        return true; // Empty linked list is always a valid path
    }

    if (!root)
    {
        return false; // Non-empty linked list but empty tree
    }

    // Check if path starts from current node
    if (dfs(root, head))
    {
        return true;
    }

    // Only search subtrees that could contain the first value
    if (head->data <= root->data)
    {
        if (isSubPath(root->left, head))
        {
            return true;
        }
    }
    if (head->data >= root->data)
    {
        if (isSubPath(root->right, head))
        {
            return true;
        }
    }

    return false;
}

/*
Exercise 3:
    Given a BST, transform it into a greater sum tree where each node contains the sum of all nodes
    greater than that node. Your solution should not exceed the complexity O(n).
    Hint: Think to the reverse order of the in-order traversal to do that.
*/
int greaterSumUtil(BSTNode *node, int *sum)
{
    if (node == NULL)
        return 0;

    // Traverse right subtree first (greater values)
    greaterSumUtil(node->right, sum);

    // Update current node's value
    int oldValue = node->data;
    node->data = *sum;
    *sum += oldValue;

    // Traverse left subtree
    greaterSumUtil(node->left, sum);
}

void transformToGreaterSumTree(BSTNode *root)
{
    int sum = 0;
    greaterSumUtil(root, &sum);
}

// Test functions

// Helper function to create linked list from array
ListNode *createLinkedList(int arr[], int n)
{
    if (n == 0)
        return NULL;

    ListNode *head = createListNode(arr[0]);
    ListNode *current = head;

    for (int i = 1; i < n; i++)
    {
        current->next = createListNode(arr[i]);
        current = current->next;
    }

    return head;
}

int main()
{
    printf("=== Testing DSA Functions ===\n\n");

    // Test 1: Perfect Binary Tree
    printf("1. Testing Perfect Binary Tree:\n");

    // Create a perfect binary tree
    //       1
    //      / \
    //     2   3
    //    / \ / \
    //   4 5 6 7
    BTNode *perfect = createBTNode(1);
    perfect->left = createBTNode(2);
    perfect->right = createBTNode(3);
    perfect->left->left = createBTNode(4);
    perfect->left->right = createBTNode(5);
    perfect->right->left = createBTNode(6);
    perfect->right->right = createBTNode(7);

    printf("Perfect tree test: %s\n", isPerfectBinaryTree(perfect) ? "PERFECT" : "NOT PERFECT");

    // Create a non-perfect binary tree
    //       1
    //      / \
    //     2   3
    //    /
    //   4
    BTNode *notPerfect = createBTNode(1);
    notPerfect->left = createBTNode(2);
    notPerfect->right = createBTNode(3);
    notPerfect->left->left = createBTNode(4);

    printf("Non-perfect tree test: %s\n", isPerfectBinaryTree(notPerfect) ? "PERFECT" : "NOT PERFECT");

    // Test 2: BST Subpath
    printf("\n2. Testing BST Subpath:\n");

    // Create BST
    //       5
    //      / \
    //     3   7
    //    / \ / \
    //   2 4 6 8
    BSTNode *bst = createBSTNode(5);
    bst->left = createBSTNode(3);
    bst->right = createBSTNode(7);
    bst->left->left = createBSTNode(2);
    bst->left->right = createBSTNode(4);
    bst->right->left = createBSTNode(6);
    bst->right->right = createBSTNode(8);

    printf("BST inorder: ");
    inOrderBST(bst);
    printf("\n");

    // Test valid paths
    int path1[] = {5, 3, 2};
    ListNode *list1 = createLinkedList(path1, 3);
    printf("Path [5->3->2]: ");
    displayList(list1);
    printf("Result: %s\n", isSubPath(bst, list1) ? "VALID PATH" : "INVALID PATH");

    int path2[] = {5, 7, 8};
    ListNode *list2 = createLinkedList(path2, 3);
    printf("Path [5->7->8]: ");
    displayList(list2);
    printf("Result: %s\n", isSubPath(bst, list2) ? "VALID PATH" : "INVALID PATH");

    // Test invalid path
    int path3[] = {5, 3, 8};
    ListNode *list3 = createLinkedList(path3, 3);
    printf("Path [5->3->8]: ");
    displayList(list3);
    printf("Result: %s\n", isSubPath(bst, list3) ? "VALID PATH" : "INVALID PATH");

    // Test single node
    int path4[] = {7};
    ListNode *list4 = createLinkedList(path4, 1);
    printf("Path [7]: ");
    displayList(list4);
    printf("Result: %s\n", isSubPath(bst, list4) ? "VALID PATH" : "INVALID PATH");

    // Test 3: Greater Sum Tree
    printf("\n3. Testing Greater Sum Tree:\n");

    // Create a copy of BST for transformation
    BSTNode *gst = createBSTNode(5);
    gst->left = createBSTNode(3);
    gst->right = createBSTNode(7);
    gst->left->left = createBSTNode(2);
    gst->left->right = createBSTNode(4);
    gst->right->left = createBSTNode(6);
    gst->right->right = createBSTNode(8);

    printf("Original BST inorder: ");
    inOrderBST(gst);
    printf("\n");

    transformToGreaterSumTree(gst);

    printf("Greater Sum Tree inorder: ");
    inOrderBST(gst);
    printf("\n");

    printf("\nExplanation:\n");
    printf("- Node 8: sum of greater nodes = 0\n");
    printf("- Node 7: sum of greater nodes = 8\n");
    printf("- Node 6: sum of greater nodes = 8+7 = 15\n");
    printf("- Node 5: sum of greater nodes = 8+7+6 = 21\n");
    printf("- Node 4: sum of greater nodes = 8+7+6+5 = 26\n");
    printf("- Node 3: sum of greater nodes = 8+7+6+5+4 = 30\n");
    printf("- Node 2: sum of greater nodes = 8+7+6+5+4+3 = 33\n");

    printf("\n=== All tests completed! ===\n");

    return 0;
}
