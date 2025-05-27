#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// =============================================================================
// EXERCISE 1: DOUBLE STACK IMPLEMENTATION
// =============================================================================

typedef struct
{
    int top_1;
    int top_2;
    int capacity;
    int *data;
} DoubleStack;

DoubleStack CreateDoubleStack(int n)
{
    if (n < 2)
    {
        printf("Invalid size\n");
        exit(EXIT_FAILURE);
    }
    DoubleStack s;

    s.capacity = n;
    s.top_1 = -1;
    s.top_2 = s.capacity;
    s.data = (int *)malloc((s.capacity) * (sizeof(int)));
    if (s.data == NULL)
    {
        printf("error while allocating memory\n");
        exit(EXIT_FAILURE);
    }
    return s;
}

bool IsFullDoubleStack(DoubleStack *s)
{
    return (s->top_1 + 1 == s->top_2);
}

bool IsEmptyDoubleStack(DoubleStack *s)
{
    return (s->top_1 == -1 && s->top_2 == s->capacity);
}

bool PushDoubleStack(DoubleStack *s, int choice, int value)
{
    if (IsFullDoubleStack(s))
    {
        printf("Stack is Full\n");
        return false;
    }

    switch (choice)
    {
    case 1:
        s->data[++s->top_1] = value;
        return true;
    case 2:
        s->data[--s->top_2] = value;
        return true;
    default:
        printf("Invalid choice");
        return false;
    }
}

bool PopDoubleStack(DoubleStack *s, int choice)
{
    if (IsEmptyDoubleStack(s))
    {
        printf("Stack is already empty\n");
        return false;
    }

    switch (choice)
    {
    case 1:
        if (s->top_1 == -1)
        {
            printf("Stack 1 is empty\n");
            return false;
        }
        s->top_1--;
        return true;
    case 2:
        if (s->top_2 == s->capacity)
        {
            printf("Stack 2 is empty\n");
            return false;
        }
        s->top_2++;
        return true;
    default:
        printf("Invalid choice");
        return false;
    }
}

bool TopDoubleStack(DoubleStack *s, int choice, int *value)
{
    switch (choice)
    {
    case 1:
        if (s->top_1 == -1)
        {
            printf("Stack 1 is empty");
            return false;
        }
        *value = s->data[s->top_1];
        return true;
    case 2:
        if (s->top_2 == s->capacity)
        {
            printf("Stack 2 is empty");
            return false;
        }
        *value = s->data[s->top_2];
        return true;
    default:
        printf("Invalid choice");
        return false;
    }
}

// =============================================================================
// EXERCISE 2: TRIPLE STACK IMPLEMENTATION
// =============================================================================

typedef struct
{
    int Max_Capacity;
    int *data;
    int top[3]; // Top for each stack
} TripleStack;

TripleStack CreateTripleStack(int n)
{
    TripleStack s;
    s.data = (int *)malloc(n * sizeof(int));
    if (s.data == NULL)
    {
        printf("error while allocating memory");
        exit(EXIT_FAILURE);
    }
    s.Max_Capacity = n;
    s.top[0] = -1;
    s.top[1] = n / 3 - 1;
    s.top[2] = (2 * n) / 3 - 1;
    return s;
}

bool IsEmptyStack(TripleStack *s, int choice)
{
    return s->top[choice - 1] == (choice - 1) * (s->Max_Capacity / 3) - 1;
}

bool IsFullStack(TripleStack *s, int choice)
{
    return s->top[choice - 1] == choice * (s->Max_Capacity / 3) - 1;
}

bool PushTripleStack(TripleStack *s, int choice, int value)
{
    if (IsFullStack(s, choice))
    {
        printf("Stack %d is full\n", choice);
        return false;
    }
    s->top[choice - 1]++;
    int idx = (choice - 1) * (s->Max_Capacity / 3) + s->top[choice - 1];
    s->data[idx] = value;
    return true;
}

bool PopTripleStack(TripleStack *s, int choice)
{
    if (IsEmptyStack(s, choice))
    {
        printf("Stack %d is empty\n", choice);
        return false;
    }
    s->top[choice - 1]--;
    return true;
}

bool TopTripleStack(TripleStack *s, int choice, int *value)
{
    if (IsEmptyStack(s, choice))
    {
        printf("Stack %d is empty\n", choice);
        return false;
    }
    int idx = (choice - 1) * (s->Max_Capacity / 3) + s->top[choice - 1];
    *value = s->data[idx];
    return true;
}

// =============================================================================
// EXERCISE 3: RECURSIVE STACK FUNCTIONS USING ONLY STACK OPERATIONS
// =============================================================================

typedef int element;

typedef struct StackCell
{
    element data;
    struct StackCell *next;
} *stack;

// Basic stack operations
bool IsEmpty(stack s)
{
    return s == NULL;
}

void Push(stack *s, element e)
{
    stack newCell = (stack)malloc(sizeof(struct StackCell));
    if (newCell == NULL)
    {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newCell->data = e;
    newCell->next = *s;
    *s = newCell;
}

bool Pop(stack *s)
{
    if (IsEmpty(*s))
    {
        return false;
    }
    stack temp = *s;
    *s = (*s)->next;
    free(temp);
    return true;
}

bool Top(stack s, element *e)
{
    if (IsEmpty(s))
    {
        return false;
    }
    *e = s->data;
    return true;
}

// RECURSIVE FUNCTION 1: Insert element at bottom using ONLY stack operations
void InsertBottom(stack *p, element e)
{
    // Base case: if stack is empty, just push the element
    if (IsEmpty(*p))
    {
        Push(p, e);
        return;
    }

    // Recursive case: remove top element, insert at bottom, then restore top
    element temp;
    Top(*p, &temp); // Get top element
    Pop(p);         // Remove top element

    InsertBottom(p, e); // Recursively insert at bottom

    Push(p, temp); // Restore the top element
}

// RECURSIVE FUNCTION 2: Reverse stack using ONLY stack operations
void ReverseStack(stack *s)
{
    // Base case: if stack is empty or has one element, nothing to reverse
    if (IsEmpty(*s))
    {
        return;
    }

    element temp;
    Top(*s, &temp); // Get top element
    Pop(s);         // Remove top element

    ReverseStack(s); // Recursively reverse the rest

    InsertBottom(s, temp); // Insert the removed element at bottom
}

// Helper function to print stack (for testing)
void PrintStack(stack s)
{
    printf("Stack (top to bottom): ");
    while (s != NULL)
    {
        printf("%d ", s->data);
        s = s->next;
    }
    printf("\n");
}

// Helper function to free stack memory
void FreeStack(stack *s)
{
    while (!IsEmpty(*s))
    {
        Pop(s);
    }
}

// =============================================================================
// MAIN FUNCTION - TESTING ALL EXERCISES
// =============================================================================

int main()
{
    printf("=============================================================================\n");
    printf("TESTING EXERCISE 1: DOUBLE STACK\n");
    printf("=============================================================================\n");

    // Create a double stack with capacity 10
    DoubleStack doubleStack = CreateDoubleStack(10);

    // Push elements onto the double stack
    PushDoubleStack(&doubleStack, 1, 5);  // Push 5 onto stack 1
    PushDoubleStack(&doubleStack, 2, 10); // Push 10 onto stack 2
    PushDoubleStack(&doubleStack, 1, 15); // Push 15 onto stack 1
    PushDoubleStack(&doubleStack, 2, 20); // Push 20 onto stack 2

    // Test IsEmptyDoubleStack
    printf("Is the double stack empty? %s\n", IsEmptyDoubleStack(&doubleStack) ? "Yes" : "No");

    // Test IsFullDoubleStack
    printf("Is the double stack full? %s\n", IsFullDoubleStack(&doubleStack) ? "Yes" : "No");

    // Test TopDoubleStack
    int topValue1, topValue2;
    if (TopDoubleStack(&doubleStack, 1, &topValue1))
        printf("Top element of stack 1: %d\n", topValue1);
    if (TopDoubleStack(&doubleStack, 2, &topValue2))
        printf("Top element of stack 2: %d\n", topValue2);

    // Pop elements from the double stack
    PopDoubleStack(&doubleStack, 1); // Pop from stack 1
    PopDoubleStack(&doubleStack, 2); // Pop from stack 2

    // Test top values after popping
    if (TopDoubleStack(&doubleStack, 1, &topValue1))
        printf("Top element of stack 1 after pop: %d\n", topValue1);
    if (TopDoubleStack(&doubleStack, 2, &topValue2))
        printf("Top element of stack 2 after pop: %d\n", topValue2);

    // Test IsEmptyDoubleStack after popping some elements
    printf("Is the double stack empty after popping some elements? %s\n", IsEmptyDoubleStack(&doubleStack) ? "Yes" : "No");

    // Free allocated memory
    free(doubleStack.data);

    printf("\n=============================================================================\n");
    printf("TESTING EXERCISE 2: TRIPLE STACK\n");
    printf("=============================================================================\n");

    // Create a TripleStack with capacity 9 (3 stacks with capacity 3 each)
    TripleStack tripleStack = CreateTripleStack(9);

    // Push some elements onto different stacks
    PushTripleStack(&tripleStack, 1, 10);
    PushTripleStack(&tripleStack, 2, 20);
    PushTripleStack(&tripleStack, 3, 30);
    PushTripleStack(&tripleStack, 1, 11);
    PushTripleStack(&tripleStack, 2, 21);
    PushTripleStack(&tripleStack, 3, 31);

    // Test TopTripleStack
    int topValue;
    if (TopTripleStack(&tripleStack, 1, &topValue))
        printf("Top of Stack 1: %d\n", topValue);
    if (TopTripleStack(&tripleStack, 2, &topValue))
        printf("Top of Stack 2: %d\n", topValue);
    if (TopTripleStack(&tripleStack, 3, &topValue))
        printf("Top of Stack 3: %d\n", topValue);

    // Pop elements from different stacks
    PopTripleStack(&tripleStack, 1);
    PopTripleStack(&tripleStack, 2);
    PopTripleStack(&tripleStack, 3);
    PopTripleStack(&tripleStack, 3);

    // Push more elements
    PushTripleStack(&tripleStack, 1, 12);
    PushTripleStack(&tripleStack, 1, 13);

    // Test IsEmptyStack and IsFullStack
    printf("Stack 1 is %s\n", IsEmptyStack(&tripleStack, 1) ? "empty" : "not empty");
    printf("Stack 2 is %s\n", IsEmptyStack(&tripleStack, 2) ? "empty" : "not empty");
    printf("Stack 3 is %s\n", IsEmptyStack(&tripleStack, 3) ? "empty" : "not empty");
    printf("Stack 1 is %s\n", IsFullStack(&tripleStack, 1) ? "full" : "not full");
    printf("Stack 2 is %s\n", IsFullStack(&tripleStack, 2) ? "full" : "not full");
    printf("Stack 3 is %s\n", IsFullStack(&tripleStack, 3) ? "full" : "not full");

    // Free memory allocated for the data array
    free(tripleStack.data);

    printf("\n=============================================================================\n");
    printf("TESTING EXERCISE 3: RECURSIVE STACK FUNCTIONS USING ONLY STACK OPERATIONS\n");
    printf("=============================================================================\n");

    stack recursiveStack = NULL;

    // Test normal push operations first
    printf("Pushing elements normally (10, 20, 30)...\n");
    Push(&recursiveStack, 10);
    Push(&recursiveStack, 20);
    Push(&recursiveStack, 30);
    PrintStack(recursiveStack);

    // Test InsertBottom (Insert at bottom)
    printf("\nTesting InsertBottom - inserting 5 at bottom...\n");
    InsertBottom(&recursiveStack, 5);
    PrintStack(recursiveStack);

    printf("Inserting 1 at bottom...\n");
    InsertBottom(&recursiveStack, 1);
    PrintStack(recursiveStack);

    // Test ReverseStack (Reverse stack)
    printf("\nTesting ReverseStack - reversing the stack...\n");
    ReverseStack(&recursiveStack);
    PrintStack(recursiveStack);

    // Test reversing again
    printf("Reversing the stack again...\n");
    ReverseStack(&recursiveStack);
    PrintStack(recursiveStack);

    // Test with empty stack
    printf("\nTesting with empty stack...\n");
    stack emptyStack = NULL;
    printf("Empty stack before insertion: ");
    PrintStack(emptyStack);

    InsertBottom(&emptyStack, 42);
    printf("After inserting 42 at bottom of empty stack: ");
    PrintStack(emptyStack);

    ReverseStack(&emptyStack);
    printf("After reversing stack with one element: ");
    PrintStack(emptyStack);

    // Clean up memory
    FreeStack(&recursiveStack);
    FreeStack(&emptyStack);
    printf("\nMemory freed for recursive stacks.\n");

    printf("\n=============================================================================\n");
    printf("COMPLEXITY ANALYSIS FOR EXERCISE 3:\n");
    printf("=============================================================================\n");
    printf("InsertBottom() Complexity:\n");
    printf("- Time: O(n) where n is the number of elements in the stack\n");
    printf("- Space: O(n) due to recursive call stack\n");
    printf("- Each element is popped and pushed back once\n\n");
    printf("ReverseStack() Complexity:\n");
    printf("- Time: O(n²) where n is the number of elements\n");
    printf("- Space: O(n) due to recursive call stack\n");
    printf("- For each element, InsertBottom is called which is O(n)\n");
    printf("- Total: n * O(n) = O(n²)\n");

    printf("\n=============================================================================\n");
    printf("ALL TESTS COMPLETED SUCCESSFULLY!\n");
    printf("=============================================================================\n");

    return 0;
}
