#include <stdio.h>
#include <stdlib.h>

// Structure to represent an element of the priority queue
typedef struct
{
    int data;
    int priority;
} Element;

// Structure to represent a node in the priority queue
typedef struct Node
{
    Element element;
    struct Node *next;
} Node;

// Structure to represent the priority queue
typedef struct
{
    Node *front;
    Node *rear;
} PriorityQueue;

// Initialize the queue
PriorityQueue *initialize()
{
    PriorityQueue *q = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    q->front = q->rear = NULL;
    return q;
}

// Check if the queue is empty
int isEmpty(PriorityQueue *q)
{
    return (q->front == NULL && q->rear == NULL);
}

// Add an element to the queue
void enqueue(PriorityQueue *q, int data, int priority)
{
    Element newElement;
    newElement.data = data;
    newElement.priority = priority;

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->element = newElement;
    newNode->next = NULL;

    if (isEmpty(q))
    {
        q->front = q->rear = newNode;
    }
    else
    {
        Node *temp = q->front;
        Node *prev = NULL;
        while (temp != NULL && temp->element.priority >= priority)
        {
            prev = temp;
            temp = temp->next;
        }
        if (prev == NULL)
        { // Insertion at the front
            newNode->next = q->front;
            q->front = newNode;
        }
        else
        { // Insertion in the middle or at the end
            prev->next = newNode;
            newNode->next = temp;
            if (temp == NULL) // If inserted at the end
                q->rear = newNode;
        }
    }
}

// Remove and return an element from the queue
Element dequeue(PriorityQueue *q)
{
    Element temp;
    temp.data = -1;
    temp.priority = -1;

    if (isEmpty(q))
    {
        printf("The queue is empty.\n");
    }
    else
    {
        Node *tempNode = q->front;
        temp = tempNode->element;
        q->front = q->front->next;
        free(tempNode);
        if (q->front == NULL) // If the queue is empty after removal
            q->rear = NULL;
    }
    return temp;
}

// Main program to test the implementation
int main()
{
    // Test the implementation
    PriorityQueue *q = initialize();

    // Enqueue some elements
    enqueue(q, 10, 2);
    enqueue(q, 20, 1);
    enqueue(q, 30, 3);

    // Dequeue and print the elements
    Element dequeued_element = dequeue(q);
    printf("Dequeued element: %d (priority: %d)\n", dequeued_element.data, dequeued_element.priority);
    dequeued_element = dequeue(q);
    printf("Dequeued element: %d (priority: %d)\n", dequeued_element.data, dequeued_element.priority);

    free(q);

    return 0;
}
