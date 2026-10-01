// Lab 3 — Valgrind exercise
// The program prints results that "look correct" but has 4 memory bugs.
//   gcc -Wall -g leaky.c -o leaky
//   valgrind --leak-check=full --track-origins=yes ./leaky
// Fix all the bugs until valgrind reports: 0 errors, no leaks.
//
// Record the bugs you find:
//   Bug 1: line 19, valgrind reports invalid access to memory outside of "name"'s alloc'd mem, fix line 17: ...malloc(strlen(s) + 1);
//   Bug 2: line 27, valgrind reports reading an uninitialised value, fix line 26: ...int i = 0...
//   Bug 3: line 43, valgrind reports invalid access to memory after freeing memory, fix swap line 42 and 43
//   Bug 4: line 32, valgrind reports memory leak, add free(name) 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a copy of the string on the heap
char *copy_string(const char *s) {
    char *copy = malloc(strlen(s));
    strcpy(copy, s);
    return copy;
}

// Create an array of n elements: element i equals i * i
int *make_squares(int n) {
    int *a = malloc(n * sizeof(int));
    for (int i = 1; i < n; i++)
        a[i] = i * i;
    return a;
}

int main() {
    char *name = copy_string("Programming 1");
    printf("name = %s\n", name);

    int *squares = make_squares(5);
    int sum = 0;
    for (int i = 0; i < 5; i++)
        sum += squares[i];
    if (sum > 0)
        printf("sum of squares = %d\n", sum);

    free(squares);
    printf("first square = %d\n", squares[1]);

    return 0;
}
