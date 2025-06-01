#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000 // Adjust the size of the array as needed

// Function to generate random integer between min and max
int random_int(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to generate random array
void generate_random_array(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = random_int(1, 100000); // Adjust the range of random values as needed
    }
}

// Function to sort the array (e.g., using quicksort algorithm)
void bubble_sort(int A[],int n){
    int pass, i, temp, swapped = 1;
    for(pass=n-1; pass>=0 && swapped; pass--){
        swapped = 0;
        for(i=0; i<pass; i++){
            if(A[i]>A[i+1]){ 
                //swap elements
                temp = A[i];
                A[i] = A[i+1];
                A[i+1] = temp;
                swapped = 1;
            }
        }
    }
}

void sort_array(int array[], int size) {
    //fill code here to test one o the sorting algorithm other than bubble sort
    return;
}

// Function to search in sorted array
int linear_search(int array[], int size, int key) {
    for(int i = 0; i< size; i++)
        if(array[i] == key){
            printf("element found at position %d\n",i);
            return 1;
        }
    return 0;
}

// An iterative binary search function.
int binary_search(int array[], int size, int key){
    int l = 0, r = size -1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        // Check if x is present at mid
        if (array[m] == key)
            return m;
        // If x greater, ignore left half
        if (array[m] < key)
            l = m + 1;
        // If x is smaller, ignore right half
        else
            r = m - 1;
    }
    // If we reach here, then element was not present
    return -1;
}


// Function to search in sorted array
int ternary_search(int array[], int size, int key) {
    // Implement ternary search algorithm here
    return 0;
}
// Function to search in sorted array
int exponential_search(int array[], int size, int key) {
    // Implement exponential search algorithm here
    return 0;
}
// Function to search in sorted array
int fibonacci_search(int array[], int size, int key) {
    // Implement fibonacci search algorithm here
    return 0;
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    clock_t start_time, end_time;
    // Declare variables
    int unsorted_array[ARRAY_SIZE];
    int sorted_array[ARRAY_SIZE];
    //int search_key = random_int(1, 100000); // Random search key
    int search_key = 100004; //this key does not exist in the array
    // Generate random unsorted array
    generate_random_array(unsorted_array, ARRAY_SIZE);

    // Copy unsorted array to sorted array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sorted_array[i] = unsorted_array[i];
    }

    // Sort the sorted array
    start_time = clock();
    bubble_sort(sorted_array, ARRAY_SIZE);
    end_time = clock();
    double sort_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken to sort array with bubble sort is %lf seconds\n", sort_time);

    // Perform search in unsorted array and measure time
    start_time = clock();
    int v = linear_search(unsorted_array, ARRAY_SIZE, search_key);
    end_time = clock();
    double search_time_unsorted = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken to search in unsorted array is %lf seconds\n", search_time_unsorted);

    // Perform search in sorted array and measure time
    start_time = clock();
    // call here search in a sorted array
    end_time = clock();
    double search_time_sorted = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken to search in sorted array is %lf seconds\n", search_time_sorted);

    return 0;
}