// Lab 3 — Pointers and Dynamic Memory
// Compile and run:  gcc -Wall -Wextra -g lab03.c -o lab03 && ./lab03
// Check memory:     valgrind --leak-check=full ./lab03
// Task: implement the functions marked TODO until all tests PASS
//       and valgrind reports 0 errors and no leaks.
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // used only in main for testing

// ---------------------------------------------------------------------------
// Simple test harness (no need to modify)
static int passed = 0, total = 0;
#define CHECK(expr)                                 \
    do {                                            \
        total++;                                    \
        if (expr) {                                 \
            passed++;                               \
            printf("  PASS  %s\n", #expr);          \
        } else {                                    \
            printf("  FAIL  %s\n", #expr);          \
        }                                           \
    } while (0)

static int same_array(const int *a, const int *b, int n) {
    if (a == NULL || b == NULL)
        return 0;
    for (int i = 0; i < n; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}
// ---------------------------------------------------------------------------

// 3.1 Swap the values of two variables
void swap(int *a, int *b) {
    // TODO
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

// 3.2 Find the min and max of the array (n >= 1), returned through pointers
void min_max(const int *a, int n, int *min, int *max) {
    // TODO
    int buf_min = *a, buf_max = *a;

    for(int i = 1; i < n; i++) {
        if (*(a+i) < buf_min) buf_min = *(a+i);
        if (*(a+i) > buf_max) buf_max = *(a+i);
    }

    *min = buf_min, *max = buf_max;
}

// 3.3 Sum of the array. Do NOT use a[i]; use only *p and p++ (or *(a + i))
int sum_pointer(const int *a, int n) {
    // TODO
    int buf = 0;
    for (int i = 0; i < n; i++) 
        buf += *(a + i);

    return buf;
}

// 3.4 Return a copy of the array, allocated on the heap (the caller will free it)
int *copy_array(const int *a, int n) {
    // TODO: malloc(n * sizeof(int)), check for NULL, copy each element
    int *buf = malloc(n * sizeof(int));
    if (buf == NULL) {
        perror("copy_array: malloc");
        return NULL;
    }
    memcpy(buf, a, n * sizeof(*buf));
    return buf;
}

// 3.5 Return a new array containing only the even numbers of a (in the same order).
//     Store the number of elements of the result in *returnSize.
int *filter_even(const int *a, int n, int *returnSize) {
    // TODO
    int *buf = malloc(n * sizeof(int));
    if (!buf) {
        perror("filter_even: malloc");
        return NULL;
    }

    int i = 0, j = 0;
    for (; i < n; i++) {
        int tmp = *(a + i);
        if (!(tmp % 2)) {
            *(buf + j) = tmp;
            j++;
        }
    }

    *returnSize = j;
    return realloc(buf, j * sizeof(int));
}

// 3.6 Implement strdup yourself: return a heap copy of the string s
char *my_strdup(const char *s) {
    unsigned int mem_len = strlen(s) + 1;
    char *buf = malloc(mem_len);
    if (!buf) {
        perror("my_strdup: malloc");
        return NULL;
    }

    memcpy(buf, s, mem_len * sizeof(*buf));
    return buf;
}

// 3.7 Append value to the end of the dynamic array arr.
//     *size: current number of elements; *capacity: number of elements allocated.
//     If full (*size == *capacity): double the capacity using realloc
//     (if *capacity == 0, allocate 1 element).
//     Return a pointer to the array (it may have changed after realloc).
int *push_back(int *arr, int *size, int *capacity, int value) {
    // TODO
    if (*capacity == 0)
        *capacity = 1;
    else if (*size == *capacity)
        *capacity *= 2;

    int *tmp = realloc(arr, *capacity * sizeof(*arr));
    
    if (!tmp) {
        perror("push_back: realloc");
        return NULL;
    }

    arr = tmp;

    *(arr + (*size)++) = value;
    return arr;
}

// 3.8 Allocate a rows x cols matrix as int ** (Lecture 7), initialized to all 0
int **alloc_matrix(int rows, int cols) {
    // TODO: 1 malloc for the array of row pointers + rows calls to calloc, one per row
    int **buf = malloc(rows * sizeof(*buf));
    if (!buf) {
        perror("alloc_matrix: malloc");
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        *(buf + i) = calloc(cols, sizeof(**buf));

        if (!*(buf + i)) {
            perror("alloc_matrix: calloc");
            for (int j = 0; j < i; j++)
                free(*(buf + j));

            free(buf);
            return NULL;
        }
        
    }

    return buf;
}

// 3.8 Free the matrix: each row first, then the array of pointers
void free_matrix(int **m, int rows) {
    for (int i = 0; i < rows; i++)
        free(*(m + i));
    
    free(m);
}

// 3.9 Allocate an int on the heap, set it to value, and "return" it through parameter p
//     (fixes the bug in out-of-scope-allocation_1.c)
void allocate_int(int **p, int value) {
    // TODO
    *p = malloc(sizeof(int));
    if (*p == NULL) {
        perror("allocate_int: malloc");
        return;
    }

    **p = value;
}

int main() {
    printf("3.1 swap\n");
    int x = 1, y = 2;
    swap(&x, &y);
    CHECK(x == 2 && y == 1);

    printf("3.2 min_max\n");
    int a2[] = {4, -7, 9, 0, 3};
    int mn = 0, mx = 0;
    min_max(a2, 5, &mn, &mx);
    CHECK(mn == -7 && mx == 9);

    printf("3.3 sum_pointer\n");
    CHECK(sum_pointer(a2, 5) == 9);
    CHECK(sum_pointer(a2, 0) == 0);

    printf("3.4 copy_array\n");
    int *c = copy_array(a2, 5);
    CHECK(c != NULL && c != a2 && same_array(c, a2, 5));
    free(c);

    printf("3.5 filter_even\n");
    int a5[] = {1, 2, 3, 4, 6, 7}, e5[] = {2, 4, 6};
    int n5 = -1;
    int *ev = filter_even(a5, 6, &n5);
    CHECK(n5 == 3 && same_array(ev, e5, 3));
    free(ev);

    printf("3.6 my_strdup\n");
    const char *orig = "Programming 1";
    char *dup = my_strdup(orig);
    CHECK(dup != NULL && dup != orig && strcmp(dup, orig) == 0);
    free(dup);

    printf("3.7 push_back\n");
    int *arr = NULL, size = 0, capacity = 0;
    for (int i = 1; i <= 10; i++)
        arr = push_back(arr, &size, &capacity, i * 10);
    int e7[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    CHECK(size == 10);
    CHECK(capacity == 16);
    CHECK(same_array(arr, e7, 10));
    free(arr);

    printf("3.8 alloc_matrix\n");
    int **m = alloc_matrix(3, 4);
    int ok = m != NULL;
    for (int i = 0; ok && i < 3; i++)
        for (int j = 0; j < 4; j++)
            ok = ok && m[i][j] == 0;
    CHECK(ok);
    if (m != NULL) {
        m[2][3] = 42;
        CHECK(m[2][3] == 42);
        free_matrix(m, 3);
    }

    printf("3.9 allocate_int\n");
    int *p = NULL;
    allocate_int(&p, 42);
    CHECK(p != NULL && *p == 42);
    free(p);

    printf("\nResult: %d/%d PASS\n", passed, total);
    return passed == total ? 0 : 1;
}
