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

    return 0;
}
