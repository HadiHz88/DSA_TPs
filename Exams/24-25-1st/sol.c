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
    // Check if we have enough elements to determine a progression
    if (size < 2)
    {
        return; // Not enough elements to find a progression
    }

    // Step 1: Find the minimum difference between consecutive elements
    // The minimum difference represents the common difference of the arithmetic progression
    // We need to find the minimum because some elements might be missing, creating larger gaps
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
    // For each pair of consecutive elements, check if there are missing values between them
    for (int i = 0; i < size - 1; i++)
    {
        int current = arr[i]; // Start from the current element

        // Keep adding the common difference until we reach the next element
        while (current + minDiff < arr[i + 1])
        {
            current += minDiff;      // Move to the next expected element in the progression
            printf("%d, ", current); // Print the missing element
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

// Helper function to create a new STBST node
STBSTNode *createSTBSTNode(int data)
{
    STBSTNode *newNode = (STBSTNode *)malloc(sizeof(STBSTNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->rightIsThread = 1; // Initially, the right pointer is a thread
    return newNode;
}

/*
part a:
    Implement a C function inorder_traverse_single_threaded_bst(Node* root) that performs an iterative in-order traversal of a given Single Threaded Binary Search Tree.
    You are not allowed here to do a recursive function nor using any auxiliary data structure like array, stack, queue, etc.
    Think to use the rightIsThread flags and the threads to move through the tree.
*/

// helper function to get the leftMost Node
STBSTNode *leftmost(STBSTNode *node)
{
    if (node == NULL)
        return NULL;

    while (node->left != NULL)
    {
        node = node->left; // Go to the leftmost child
    }
    return node;
}

void inorder_traverse_single_threaded_bst(STBSTNode *root)
{
    STBSTNode *curr = leftmost(root);

    while (curr != NULL)
    {
        printf("%d ", curr->data);

        if (curr->rightIsThread)
        {
            // Follow the thread
            curr = curr->right;
        }
        else
        {
            // Go to leftmost in right subtree
            curr = leftmost(curr->right);
        }
    }
}

/*
part b:
    Implement a C function insert_into_single_threaded_bst(Node* root, int value) that inserts a new value into a Single Threaded Binary Search Tree
    while maintaining both the BST property and the single-threading property.
    If the tree is initially empty, the function should return the new root.
    Otherwise, it should return the original root. In case the value already exists, just ignore the insertion.
*/
STBSTNode *insert_into_single_threaded_bst(STBSTNode *root, int value)
{
    // If tree is empty, return new node as root
    if (root == NULL)
        return createSTBSTNode(value);

    STBSTNode *parent = NULL;
    STBSTNode *current = root;

    while (current != NULL)
    {
        if (value == current->data)
        {
            // Value already exists, do nothing
            return root;
        }

        parent = current;

        if (value < current->data)
        {
            // Go left if possible
            if (current->left == NULL)
                break;
            current = current->left;
        }
        else
        {
            // Go right only if it's a real child
            if (current->rightIsThread)
                break;
            current = current->right;
        }
    }

    STBSTNode *new_node = createSTBSTNode(value);

    if (value < parent->data)
    {
        // Insert as left child
        parent->left = new_node;
        new_node->right = parent; // Thread to in-order successor
    }
    else
    {
        // Insert as right child (taking over thread)
        new_node->right = parent->right;
        parent->right = new_node;
        parent->rightIsThread = 0; // Now right points to actual child
    }

    return root;
}

/*
You are given a positive weighted directed graph. This graph is represented by the right Graph structure which contains the number of vertices, the number of edges, and its adjacency matrix. For each node in the graph, you need to calculate the absolute difference between the total sum of its indegree weights and the total sum of its outdegree weights.
Your task is to implement a C function named calculateDegreeWeightDifferences that takes a pointer to a Graph structure as input. The function should dynamically allocate an integer array, populate it such that result[i] contains the absolute difference for node i, and then return a pointer to this newly allocated array.
Assumptions:
    The graph nodes are indexed from 0 to N-1, where N is the number of vertices.
    The adjacency matrix adjMatrix[i][j] represents the weight of the directed edge from node i to node j.
    If there is no edge from i to j, adjMatrix[i][j] will be 0.
    All weights are positive integers.
    Your solution should not exceed O(N2)
*/
typedef struct Graph
{
    int numVertices; // Number of vertices in the graph
    int numEdges;    // Number of edges in the graph
    int **adjMatrix; // Adjacency matrix representing the graph
} Graph;

int *calculateDegreeWeightDifferences(Graph *graph)
{
    int n = graph->numVertices;

    // Allocate result array
    int *result = (int *)malloc(n * sizeof(int));
    if (!result)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // For each node, calculate sum of indegree and outdegree weights
    for (int i = 0; i < n; i++)
    {
        int outSum = 0;
        int inSum = 0;

        for (int j = 0; j < n; j++)
        {
            outSum += graph->adjMatrix[i][j]; // outdegree: row
            inSum += graph->adjMatrix[j][i];  // indegree: column
        }

        int diff = outSum - inSum;
        result[i] = diff < 0 ? -diff : diff; // absolute difference
    }

    return result;
}

// Functions to test the graph functionality

// Utility to create a graph with dynamic matrix
Graph *createGraph(int vertices)
{
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->numVertices = vertices;
    g->numEdges = 0;
    g->adjMatrix = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++)
    {
        g->adjMatrix[i] = (int *)calloc(vertices, sizeof(int)); // all 0s initially
    }
    return g;
}

// Add edge from u to v with weight w
void addEdge(Graph *g, int u, int v, int w)
{
    if (g->adjMatrix[u][v] == 0)
        g->numEdges++;
    g->adjMatrix[u][v] = w;
}

// Test all the functions
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
    STBSTNode *stbstRoot = NULL;
    stbstRoot = insert_into_single_threaded_bst(stbstRoot, 10);
    stbstRoot = insert_into_single_threaded_bst(stbstRoot, 5);
    stbstRoot = insert_into_single_threaded_bst(stbstRoot, 15);
    stbstRoot = insert_into_single_threaded_bst(stbstRoot, 12);
    stbstRoot = insert_into_single_threaded_bst(stbstRoot, 7);

    printf("In-order traversal of Single Threaded BST: ");
    inorder_traverse_single_threaded_bst(stbstRoot);

    printf("\n\n#############\n\n");

    printf("Exercise 4:\n");
    Graph *g = createGraph(4);
    addEdge(g, 0, 1, 4);
    addEdge(g, 1, 2, 3);
    addEdge(g, 2, 0, 2);
    addEdge(g, 3, 1, 5);

    int *result = calculateDegreeWeightDifferences(g);
    for (int i = 0; i < g->numVertices; i++)
    {
        printf("Node %d: %d\n", i, result[i]);
    }

    return 0;
}
