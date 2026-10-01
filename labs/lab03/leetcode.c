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

    int flag = 0;

    do {
        flag = 0;
        for (i = 0; i < numsSize - 1; i++) {
            if (nums[i] > nums[i + 1]) {
                flag = 1;
                nums[i] ^= nums[i + 1];
                nums[i + 1] ^= nums[i];
                nums[i] ^= nums[i + 1];
            }
        }
    } while (flag);

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