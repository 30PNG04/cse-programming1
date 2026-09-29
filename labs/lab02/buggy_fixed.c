//Fixed

#include <stdio.h>

#define N 5

int sum_array(int a[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    return sum;
}

double average(int a[], int n) {
    if (n == 0) {
        printf("No average returned.\n");
        return 0;
    }
    return sum_array(a, n) / n;
}

int max_array(int a[], int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) 
        max = a[i] > max ? a[i] : max;
    
    return max;
}

void reverse_string(char s[], int len) {
    for (int i = 0; i < len / 2; i++) {
        char tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
}

int main() {
    int data[N] = {10, 20, 30, 40, 51};
    int temps[N] = {-5, -3, -8, -1, -9}; // winter temperatures

    printf("sum = %d\n", sum_array(data, N));
    printf("average = %.2f\n", average(data, N));
    printf("max = %d\n", max_array(data, N));
    printf("max temp = %d\n", max_array(temps, N));

    char word[] = "hello";
    reverse_string(word, 5);
    printf("reversed: %s\n", word);

    return 0;
}
