#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a structure for storing key-value pairs and the linked list node
typedef struct Node
{
    int key;           // Unique identifier (key)
    int value;         // Value associated with the key
    struct Node *next; // Pointer to the next node in the linked list
} Node;

// Define a structure for a linked list
typedef struct
{
    Node *head; // Pointer to the first node in the linked list
    Node *tail; // Pointer to the last node in the linked list
    int size;   // Number of elements in the linked list
} LinkedList;

// Define a structure for the hash table entry
typedef struct
{
    LinkedList *list; // Pointer to the linked list
} HashTableEntry;

// Define a structure for the hash table
typedef struct
{
    int size;               // Size of the hash table (number of buckets)
    int capacity;           // Capacity of the hash table (maximum number of elements)
    HashTableEntry **array; // Array of pointers to linked lists
} HashTable;

// Function to calculate the hash code for a given key
int getCode(int key, int size)
{
    return key % size;
}

// Function to create a new hash table
HashTable *createHashTable(int size)
{
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    if (table == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    table->size = size;
    table->capacity = 0;
    table->array = (HashTableEntry **)malloc(size * sizeof(HashTableEntry *));
    if (table->array == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++)
    {
        table->array[i] = NULL;
    }
    return table;
}

// Function to search for a key-value pair in the hash table
int *get(HashTable *table, int key)
{
    int code = getCode(key, table->size);
    if (table->array[code] == NULL)
    {
        return NULL; // Key not found
    }
    LinkedList *list = table->array[code]->list;
    Node *current = list->head;
    while (current != NULL)
    {
        if (current->key == key)
        {
            return &(current->value); // Return a pointer to the value
        }
        current = current->next;
    }
    return NULL; // Key not found
}

// Function to insert a new key-value pair into the hash table
void put(HashTable *table, int key, int value)
{
    int code = getCode(key, table->size);
    if (table->array[code] == NULL)
    {
        table->array[code] = (HashTableEntry *)malloc(sizeof(HashTableEntry));
        if (table->array[code] == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        table->array[code]->list = (LinkedList *)malloc(sizeof(LinkedList));
        if (table->array[code]->list == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        table->array[code]->list->head = NULL;
        table->array[code]->list->tail = NULL;
        table->array[code]->list->size = 0;
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = table->array[code]->list->head;
    table->array[code]->list->head = newNode;
    if (table->array[code]->list->tail == NULL)
    {
        table->array[code]->list->tail = newNode;
    }
    table->array[code]->list->size++;
    table->capacity++;
}

// Function to remove a key-value pair from the hash table
void removeKey(HashTable *table, int key)
{
    int code = getCode(key, table->size);
    if (table->array[code] == NULL)
    {
        return; // Key not found
    }
    LinkedList *list = table->array[code]->list;
    Node *current = list->head;
    Node *prev = NULL;
    while (current != NULL)
    {
        if (current->key == key)
        {
            if (prev == NULL)
            {
                list->head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            if (current == list->tail)
            {
                list->tail = prev;
            }
            free(current);
            list->size--;
            table->capacity--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Function to calculate the load factor of the hash table
float load_factor(HashTable *table)
{
    return (float)table->capacity / table->size;
}

// Function to calculate the collision rate in the hash table
float collision_rate(HashTable *table)
{
    int total_collisions = 0;
    for (int i = 0; i < table->size; i++)
    {
        if (table->array[i] != NULL)
        {
            total_collisions += (table->array[i]->list->size > 1) ? 1 : 0;
        }
    }
    return ((float)total_collisions / table->size) * 100;
}

// Function to deallocate memory used by the hash table
void freeHashTable(HashTable *table)
{
    for (int i = 0; i < table->size; i++)
    {
        if (table->array[i] != NULL)
        {
            Node *current = table->array[i]->list->head;
            while (current != NULL)
            {
                Node *next = current->next;
                free(current);
                current = next;
            }
            free(table->array[i]->list);
            free(table->array[i]);
        }
    }
    free(table->array);
    free(table);
}

// Questions

// 1. Given two arrays of values T1 and T2, write a function that tests whether all values in array T1 are included in array T2.
bool testInclusion(int T1[], int n1, int T2[], int n2)
{
    // Create a hash table to store values of array T2
    HashTable *table = createHashTable(n2);

    // Insert values of array T2 into the hash table
    for (int i = 0; i < n2; i++)
    {
        put(table, T2[i], T2[i]);
    }

    // Check if all values in array T1 are included in array T2
    for (int i = 0; i < n1; i++)
    {
        if (get(table, T1[i]) == NULL)
        {
            // Value from array T1 not found in array T2
            freeHashTable(table);
            return false;
        }
    }

    // All values in array T1 are included in array T2
    freeHashTable(table);
    return true;
}

// 2. Write a function that, for each value in an input array T1, displays the number of times that value appears in the array.
void countOccurrences(int T1[], int n1)
{
    // Create a hash table to store the counts of each value
    HashTable *table = createHashTable(n1);

    // Count the occurrences of each value in array T1
    for (int i = 0; i < n1; i++)
    {
        int *count = get(table, T1[i]);
        if (count == NULL)
        {
            // Value not found in hash table, insert with count 1
            put(table, T1[i], 1);
        }
        else
        {
            // Increment the count for the value
            (*count)++;
        }
    }

    // Display the counts of each value
    printf("Value\tOccurrences\n");
    for (int i = 0; i < table->size; i++)
    {
        if (table->array[i] != NULL)
        {
            LinkedList *list = table->array[i]->list;
            Node *current = list->head;
            while (current != NULL)
            {
                printf("%d\t%d\n", current->key, current->value);
                current = current->next;
            }
        }
    }

    // Free the memory used by the hash table
    freeHashTable(table);
}

// 3. Given two arrays T1 and T2, create a union array containing the union of elements present in both given arrays. The order of elements in the output array does not matter
int *createUnion(int T1[], int n1, int T2[], int n2, int *unionSize)
{
    // Create a hash table to store the unique elements
    HashTable *table = createHashTable(n1 + n2);

    // Insert elements of array T1 into the hash table
    for (int i = 0; i < n1; i++)
    {
        put(table, T1[i], T1[i]);
    }

    // Insert elements of array T2 into the hash table
    for (int i = 0; i < n2; i++)
    {
        put(table, T2[i], T2[i]);
    }

    // Create the union array
    int *unionArray = (int *)malloc(table->capacity * sizeof(int));
    if (unionArray == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Copy the unique elements from the hash table to the union array
    int index = 0;
    for (int i = 0; i < table->size; i++)
    {
        if (table->array[i] != NULL)
        {
            LinkedList *list = table->array[i]->list;
            Node *current = list->head;
            while (current != NULL)
            {
                unionArray[index++] = current->key;
                current = current->next;
            }
        }
    }

    // Set the size of the union array
    *unionSize = index;

    // Free the memory used by the hash table
    freeHashTable(table);

    return unionArray;
}

// 4. Write a function that, given an array A[] of n values and another number x, determines whether there exist two elements in A whose sum is exactly x. For example, if A[] = {1, 4, 45, 6, 10, 8} and x = 16, the output is (10, 6).
bool findPairWithSum(int A[], int n, int x)
{
    // Create a hash table to store the complements of elements
    HashTable *table = createHashTable(n);

    // Check if there exist two elements in array A whose sum is exactly x
    for (int i = 0; i < n; i++)
    {
        int complement = x - A[i];
        if (get(table, complement) != NULL)
        {
            // Pair with sum x found
            freeHashTable(table);
            return true;
        }
        // Insert current element into the hash table
        put(table, A[i], A[i]);
    }

    // No pair with sum x found
    freeHashTable(table);
    return false;
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    // Example usage of the hash table
    // HashTable *table = createHashTable(10);
    // put(table, 5, 42);
    // int *result = get(table, 5);
    // if (result != NULL)
    // {
    //     printf("Value associated with key 5: %d\n", *result);
    // }
    // else
    // {
    //     printf("Key not found.\n");
    // }
    // removeKey(table, 5);
    // result = get(table, 5);
    // if (result != NULL)
    // {
    //     printf("Value associated with key 5: %d\n", *result);
    // }
    // else
    // {
    //     printf("Key not found.\n");
    // }
    // freeHashTable(table);
    // return 0;

    // Example usage of the functions

    // Question 1: Test Inclusion
    printf("Question 1: Test Inclusion\n");
    int q1_T1[] = {1, 2, 3, 4};
    int q1_T2[] = {13, 3, 2, 1, 4, 7, 8};
    int q1_n1 = sizeof(q1_T1) / sizeof(q1_T1[0]);
    int q1_n2 = sizeof(q1_T2) / sizeof(q1_T2[0]);
    printf("Array T1: ");
    printArray(q1_T1, q1_n1);
    printf("Array T2: ");
    printArray(q1_T2, q1_n2);
    printf("Test Inclusion: %s\n", testInclusion(q1_T1, q1_n1, q1_T2, q1_n2) ? "True" : "False");

    printf("\n###################################################\n");

    // Question 2: Count Occurrences
    printf("\nQuestion 2: Count Occurrences\n");
    int q2_T1[] = {1, 2, 3, 2, 1, 4, 5, 1};
    int q2_n1 = sizeof(q2_T1) / sizeof(q2_T1[0]);
    printf("Array T1: ");
    printArray(q2_T1, q2_n1);
    countOccurrences(q2_T1, q2_n1);

    printf("\n###################################################\n");

    // Question 3: Create Union
    printf("\nQuestion 3: Create Union\n");
    int q3_T1[] = {1, 2, 3, 4};
    int q3_T2[] = {3, 4, 5, 6};
    int q3_n1 = sizeof(q3_T1) / sizeof(q3_T1[0]);
    int q3_n2 = sizeof(q3_T2) / sizeof(q3_T2[0]);
    printf("Array T1: ");
    printArray(q3_T1, q3_n1);
    printf("Array T2: ");
    printArray(q3_T2, q3_n2);
    int unionSize;
    int *unionArray = createUnion(q3_T1, q3_n1, q3_T2, q3_n2, &unionSize);
    printf("Union Array: ");
    printArray(unionArray, unionSize);
    free(unionArray);

    printf("\n###################################################\n");

    // Question 4: Find Pair with Sum
    printf("\nQuestion 4: Find Pair with Sum\n");
    int q4_A[] = {1, 4, 45, 6, 10, 8};
    int q4_n = sizeof(q4_A) / sizeof(q4_A[0]);
    int q4_x = 16;
    printf("Array A: ");
    printArray(q4_A, q4_n);
    printf("Sum x: %d\n", q4_x);
    if (findPairWithSum(q4_A, q4_n, q4_x))
        printf("Pair with sum %d found.\n", q4_x);
    else
        printf("No pair with sum %d found.\n", q4_x);

    return 0;
}
