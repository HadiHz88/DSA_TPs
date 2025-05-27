#include "../../src/dsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Ex1: Implement a Static Stack Using an Array
// Solution in `src` folder

// Ex2: Implement a Dynamic Stack Using a Linked List
// Solution in `src` folder

// Ex3: Function to reverse a word using a stack
void reverseWord(char *word)
{
    Stack s;
    initStack(&s); // Initialize the stack

    // Empiler chaque caract�re du mot
    for (int i = 0; i < strlen(word); i++)
    {
        push(&s, word[i]);
    }

    // D�piler et reconstruire le mot invers�
    int index = 0;
    StackElem e;
    while (!isStackEmpty(&s))
    {
        e = peek(&s); // Peek the top element without popping it
        pop(&s);      // Pop the top element from the stack
        word[index++] = e;
    }
}

// Ex4: Function to check if a word is a palindrome using a stack
bool isPalindrome(char *word)
{
    Stack s;
    initStack(&s); // Initialize the stack

    // Empiler chaque caract�re du mot
    for (int i = 0; i < strlen(word); i++)
    {
        push(&s, word[i]);
    }

    // V�rifier si le mot est un palindrome
    for (int i = 0; i < strlen(word); i++)
    {
        if (peek(&s) != word[i])
        {
            return false; // Si un caract�re ne correspond pas, ce n'est pas un palindrome
        }
        pop(&s); // Pop le caract�re du stack
    }

    return true; // Si tous les caract�res correspondent, c'est un palindrome
}

// Ex5: Function to check if a word is a suffix of another using stacks
bool isSuffix(char *word, char *suffix)
{
    int WordSize = strlen(word);
    int SfxSize = strlen(suffix);

    if (SfxSize > WordSize)
    {
        printf("Error: The suffix cannot be longer than the word.\n");
        return false;
    }

    Stack s;
    initStack(&s); // Initialize the stack
    for (int i = 0; i < SfxSize; i++)
    {
        push(&s, suffix[i]);
    }

    StackElem tmp;
    for (int i = WordSize - 1; i >= 0; i--)
    {
        if (isStackEmpty(&s))
        {
            return true;
        }

        tmp = peek(&s);
        if (word[i] != tmp)
        {
            return false;
        }
        pop(&s);
    }
    return true;
}

// Ex6: Function to validate an arithmetic expression with brackets using a stack
bool isValidExpression(char *expression)
{
    Stack s;
    initStack(&s);

    for (int i = 0; i < strlen(expression); i++)
    {
        char current = expression[i];

        // If opening bracket, push onto stack
        if (current == '(' || current == '{' || current == '[')
        {
            push(&s, current);
        }
        // If closing bracket, check if it matches with the top of the stack
        else if (current == ')' || current == '}' || current == ']')
        {
            // If stack is empty, no matching opening bracket
            if (isStackEmpty(&s))
            {
                return false;
            }

            char top = peek(&s);

            // Check if the closing bracket matches the corresponding opening bracket
            if ((current == ')' && top != '(') ||
                (current == '}' && top != '{') ||
                (current == ']' && top != '['))
            {
                return false;
            }

            // Remove the matched opening bracket
            pop(&s);
        }
        // Ignore other characters in the expression
    }

    // Expression is valid if all brackets were matched (stack is empty)
    return isStackEmpty(&s);
}

// Ex7: Function to evaluate an arithmetic expression
int evaluateExpression(char *expression)
{
    Stack operandStack;
    initStack(&operandStack);

    int i = 0;
    while (expression[i] != '\0')
    {
        // Skip spaces
        if (expression[i] == ' ')
        {
            i++;
            continue;
        }

        // Process numbers
        if (expression[i] >= '0' && expression[i] <= '9')
        {
            int num = 0;
            // Extract full number
            while (expression[i] >= '0' && expression[i] <= '9')
            {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            // Push operand to stack
            push(&operandStack, num);
            continue;
        }

        // Process operators
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
        {
            // Need at least two operands
            if (operandStack.size < 2)
            {
                printf("Error: Invalid expression - not enough operands for operator %c\n", expression[i]);
                return 0;
            }

            // Pop operands in reverse order
            int operand2 = peek(&operandStack);
            pop(&operandStack);
            int operand1 = peek(&operandStack);
            pop(&operandStack);

            int result = 0;
            switch (expression[i])
            {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                if (operand2 == 0)
                {
                    printf("Error: Division by zero\n");
                    return 0;
                }
                result = operand1 / operand2;
                break;
            }

            // Push the result back to the stack
            push(&operandStack, result);
        }

        i++;
    }

    // The final result should be the only element in the stack
    if (operandStack.size != 1)
    {
        printf("Error: Invalid expression - too many operands\n");
        return 0;
    }

    return peek(&operandStack);
}

// Ex8: Function to sort an array using 2 stacks
void sortArrayWithStacks(int *input, int size)
{
    Stack s1;
    initStack(&s1); // Initialize the first stack
    Stack s2;
    initStack(&s2); // Initialize the second stack

    StackElem tmp;
    for (int i = 0; i < size; i++)
    {
        if (!isStackEmpty(&s1))
        {
            tmp = peek(&s1);
            while (!isStackEmpty(&s1) && tmp > input[i])
            {
                push(&s2, tmp);
                pop(&s1);
                if (!isStackEmpty(&s1))
                    tmp = peek(&s1);
            }
        }
        push(&s1, input[i]);
        while (!isStackEmpty(&s2))
        {
            tmp = peek(&s2);
            pop(&s2);
            push(&s1, tmp);
        }
    }

    printf("Sorted stack: {");
    while (!isStackEmpty(&s1))
    {
        tmp = peek(&s1);
        pop(&s1);
        printf(" %d,", tmp);
    }
    printf(" }\n");
}

int main()
{
    // Test reverseWord function
    char word[] = "HelloWorld";
    printf("Original word: %s\n", word);
    reverseWord(word);
    printf("Reversed word: %s\n\n", word);

    // Test isPalindrome function
    char palindrome[] = "radar";
    printf("Is '%s' a palindrome? %s\n\n", palindrome,
           isPalindrome(palindrome) ? "Yes" : "No");

    // Test isSuffix function
    char word1[] = "programming";
    char suffix1[] = "ing";
    char suffix2[] = "math";
    char suffix3[] = "programming";

    printf("Suffix tests:\n");
    printf("Is '%s' a suffix of '%s'? %s\n", suffix1, word1,
           isSuffix(word1, suffix1) ? "Yes" : "No");
    printf("Is '%s' a suffix of '%s'? %s\n", suffix2, word1,
           isSuffix(word1, suffix2) ? "Yes" : "No");
    printf("Is '%s' a suffix of '%s'? %s\n", suffix3, word1,
           isSuffix(word1, suffix3) ? "Yes" : "No");

    // Test isValidExpression function
    printf("\nExpression validation tests:\n");
    char expr1[] = "(a + b) * [c - {d / e}]";
    char expr2[] = "((a + b) * [c - d]";
    char expr3[] = "(a + b) * [c - d}";
    char expr4[] = "a + b * c";

    printf("Expression '%s' is %svalid\n", expr1,
           isValidExpression(expr1) ? "" : "not ");
    printf("Expression '%s' is %svalid\n", expr2,
           isValidExpression(expr2) ? "" : "not ");
    printf("Expression '%s' is %svalid\n", expr3,
           isValidExpression(expr3) ? "" : "not ");
    printf("Expression '%s' is %svalid\n", expr4,
           isValidExpression(expr4) ? "" : "not ");

    // Test evaluateExpression function
    printf("\nArithmetic expression evaluation tests:\n");
    char arithmetic1[] = "5 3 +";      // 5 + 3 = 8
    char arithmetic2[] = "10 5 -";     // 10 - 5 = 5
    char arithmetic3[] = "4 2 *";      // 4 * 2 = 8
    char arithmetic4[] = "20 4 /";     // 20 / 4 = 5
    char arithmetic5[] = "5 3 + 2 *";  // (5 + 3) * 2 = 16
    char arithmetic6[] = "10 2 / 3 +"; // (10 / 2) + 3 = 8

    printf("Evaluating '%s' = %d\n", arithmetic1, evaluateExpression(arithmetic1));
    printf("Evaluating '%s' = %d\n", arithmetic2, evaluateExpression(arithmetic2));
    printf("Evaluating '%s' = %d\n", arithmetic3, evaluateExpression(arithmetic3));
    printf("Evaluating '%s' = %d\n", arithmetic4, evaluateExpression(arithmetic4));
    printf("Evaluating '%s' = %d\n", arithmetic5, evaluateExpression(arithmetic5));
    printf("Evaluating '%s' = %d\n", arithmetic6, evaluateExpression(arithmetic6));

    // Test sortArrayWithStacks function
    printf("\nSorting array using stacks:\n");
    int array1[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int size1 = sizeof(array1) / sizeof(array1[0]);
    printf("Original array: {");
    for (int i = 0; i < size1; i++)
    {
        printf(" %d%s", array1[i], i < size1 - 1 ? "," : "");
    }
    printf(" }\n");
    sortArrayWithStacks(array1, size1);

    int array2[] = {42, 17, 8, 99, 5, 23, 11};
    int size2 = sizeof(array2) / sizeof(array2[0]);
    printf("Original array: {");
    for (int i = 0; i < size2; i++)
    {
        printf(" %d%s", array2[i], i < size2 - 1 ? "," : "");
    }
    printf(" }\n");
    sortArrayWithStacks(array2, size2);

    return 0;
}
