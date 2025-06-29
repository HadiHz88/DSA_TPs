#include <stdio.h>
#include "dsa.h"

/*
Exercise 1:
    Given a sorted array of integers that represents elements of arithmetic progression in order.
    Some elements may be missing in the progression.
    Write a function in c that takes an array as input with its size and prints all the missing numbers.
    Suppose here that we have the same progression, but some values are missing.

    Examples:
    - Input: arr[ ] = [2, 4, 8, 10, 12, 14]
    - Output: 6
    - Explanation: In this case, the common difference is 2, and 6 is missing between 4 and 8.

    - Input: arr[ ] = [1, 11, 16, 21, 36, 41]
    - Output: 6, 26,31
    - Explanation: In this case, the common difference is 5, and 6, 26 and 31 are missing.

    Attention that the difference between the first two values may not be the value of the progression since the second value may be a missing one.
    Just take the minimal difference between all two consecutive values.
*/
void findMissingMembers(int arr[], int size)
{
    if (size < 2)
    {
        return; // Not enough elements to find a progression
    }

    // Step 1: Find the minimum difference between consecutive elements
    int minDiff = arr[1] - arr[0]; // Initialize with the first difference
    for (int i = 1; i < size - 1; i++)
    {
        int diff = arr[i + 1] - arr[i]; // Calculate the difference between consecutive elements
        if (diff < minDiff)
        {
            minDiff = diff; // Update minDiff if a smaller difference is found
        }
    }

    // Step 2: Iterate through the array and print missing numbers
    for (int i = 0; i < size - 1; i++)
    {
        int current = arr[i];
        while (current + minDiff < arr[i + 1])
        {
            current += minDiff;
            printf("%d, ", current);
        }
    }
    printf("\n");
}

/*
Exercise 2:
    Given a Binary search tree, the task is to write a recursive function to delete all the leaf nodes from the binary search tree.
    Examples:
    - Input:
        20
       /  \
      8    22
     / \
    4  12
       / \
      10 14

    - Output:
        20
       /
      8
       \
        12
*/
BSTNode *deleteLeafNodes(BSTNode *root)
{
    if (root == NULL)
    {
        return NULL; // Base case: if the node is NULL, return NULL
    }

    // If the current node is a leaf node, delete it
    if (root->left == NULL && root->right == NULL)
    {
        free(root);  // Free the memory allocated for the leaf node
        root = NULL; // Set the pointer to NULL to remove the leaf node
        return NULL;
    }

    // Recursively delete leaf nodes in the left and right subtrees
    root->left = deleteLeafNodes(root->left);
    root->right = deleteLeafNodes(root->right);

    return root; // Return the modified tree
}

/*
Exercise 3:
    ou are working with a Single Threaded Binary Search Tree (STBST). In this specific type of BST,
    all NULL right child pointers are "threaded" to point to the in-order successor of the node.
    An integer flag, rightIsThread, within each node distinguishes between a regular right child pointer (0) and a thread (1).
    Left child pointers behave as in standard BST (pointing to a child or NULL). Here is the structure definition:
    (see the exam paper for a visual representation)
    typedef struct Node
    {
        int data;
        struct Node *left;
        struct Node *right;
        int rightIsThread;
    } Node;
*/
typedef struct STBSTNode
{
    int data;                // The value stored in the node
    struct STBSTNode *left;  // Pointer to the left child
    struct STBSTNode *right; // Pointer to the right child or thread
    int rightIsThread;       // 1 if right pointer is a thread, 0 if it is a regular child pointer
} STBSTNode;

/*
part a:
    Implement a C function inorder_traverse_single_threaded_bst(Node* root) that performs an iterative in-order traversal of a given Single Threaded Binary Search Tree.
    You are not allowed here to do a recursive function nor using any auxiliary data structure like array, stack, queue, etc.
    Think to use the rightIsThread flags and the threads to move through the tree.
*/
void inorder_traverse_single_threaded_bst(STBSTNode *root);

/*
part b:
    Implement a C function insert_into_single_threaded_bst(Node* root, int value) that inserts a new value into a Single Threaded Binary Search Tree
    while maintaining both the BST property and the single-threading property.
    If the tree is initially empty, the function should return the new root.
    Otherwise, it should return the original root. In case the value already exists, just ignore the insertion.
*/
STBSTNode *insert_into_single_threaded_bst(STBSTNode *root, int value);

int main()
{
    printf("Exercise 1:\n");
    int ex1_arr1[] = {2, 4, 8, 10, 12, 14};
    int ex1_size1 = sizeof(ex1_arr1) / sizeof(ex1_arr1[0]);
    findMissingMembers(ex1_arr1, ex1_size1);
    int ex1_arr2[] = {1, 11, 16, 21, 36, 41};
    int ex1_size2 = sizeof(ex1_arr2) / sizeof(ex1_arr2[0]);
    findMissingMembers(ex1_arr2, ex1_size2);

    printf("\n#############\n\n");

    printf("Exercise 2:\n");
    BSTNode *root = buildBSTFromArray(
        (int[]){20, 8, 22, 4, 12, 10, 14}, 7);
    printf("Original BST: ");
    inOrderBST(root);
    root = deleteLeafNodes(root);
    printf("\nBST after deleting leaf nodes: ");
    inOrderBST(root);

    printf("\n\n#############\n\n");

    printf("Exercise 3:\n");
    return 0;
}
