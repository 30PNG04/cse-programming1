#include <stdio.h>
#include <stdlib.h>

int* runningSum(int* nums, int numsSize, int* returnSize);
int* evenOddBit(int n, int* returnSize);
int* sortedSquares(int* nums, int numsSize, int* returnSize);

int main(void) {
    int nums[] = {-4,-1,0,3,10};
    int numsSize = 5;
    int returnSize;
    int *result = sortedSquares(nums, numsSize, &returnSize);

    printf("{");
    for (int i = 0; i < returnSize - 1; i++) {
        printf("%d, ", result[i]);
    }
    printf("%d", result[returnSize - 1]);
    printf("}\n");
    return 0;
}

int* runningSum(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;

    for (int i = 1; i < numsSize; i++) {
        nums[i] += nums[i - 1];
    }
    
    return nums;
}

int* evenOddBit(int n, int* returnSize) {
    int *arr = calloc(2, sizeof(int));

    *returnSize = 2;

    int index = 0;
    for (; n > 0; n /= 2, index++) {        
        if (n % 2 == 0) continue;
        if (index % 2) arr[1]++;
        else arr[0]++;
    }

   return arr;
}

int* sortedSquares(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;

    int i;
    for (i = 0; i < numsSize; i++) {
        *(nums + i) *= *(nums + i);
    }

    merge_sort(nums, numsSize);
    return nums;
}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    int i = nums1Size - 1, j = m - 1, k = n - 1;

    for (; j >= 0 && k >= 0; i--) {
        if (nums1[j] > nums2[k]) {
            nums1[i] = nums1[j--];
        } else {
            nums1[i] = nums2[k--];
        }
    }

    for(; k >= 0; i--, k--)
        nums1[i] = nums2[k];
}

void merge_sort(int *arr, int n) {
    if (n <= 1) return;
    
    int *buf, n1, n2;

    if (n == 2) {
        if (arr[0] > arr[1]) {
            arr[0] ^= arr[1];
            arr[1] ^= arr[0];
            arr[0] ^= arr[1];
        }
        return;
    } else {
        n2 = n / 2, n1 = n - n2;
        merge_sort(arr, n1);
        buf = malloc(n2 * sizeof(*arr));

        if (buf == NULL) {
            perror("merge_sort: malloc");
            return;
        }

        memcpy(buf, arr + n1, n2 * sizeof(*arr));
        merge_sort(buf, n2);
    }

    n1--; n2--; n--;
    for (;n1 >= 0 && n2 >= 0; n--) {
        if (arr[n1] > buf[n2]) {
            arr[n] = arr[n1--];
        } else {
            arr[n] = buf[n2--];
        }
    }

    for (;n2 >= 0; n--, n2--) {
        arr[n] = buf[n2];
    }

    free(buf);
}