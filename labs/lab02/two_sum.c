#include <stddef.h>
#include <stdio.h>

static int passed = 0, total = 0;

#define RESULT_SIZE 2

static int ResultCheck(const int a[], const int b[]);

void twoSum(const int nums[], int n, int target, int result[]);

int main(void)
{
    struct Test {
        const int *nums;
        int n;
        int target;
        const int result[RESULT_SIZE];
    };

    const int num1[] = {1, 2, 3, 4};
    const int num2[] = {2, 7, 11, 15};
    const int num3[] = {3, 2, 4};
    const int num4[] = {-3, 4, 3, 90};
    const int num5[] = {3, 3};
    const int num6[] = {-5, -2, 0, 3, 7};
    const int num7[] = {1, 2, 3, 4, 5};
    const int num8[] = {0, 0};
    const int num9[] = {-10, 1, 2, 3, 10};
    const int num10[] = {5};
    const int num11[] = {-5, -4, -3, -2, -1};

    struct Test test[] = {
        /* Normal cases */
        {num1,  4,  6,  {1, 3}},
        {num2,  4,  9,  {0, 1}},
        {num3,  3,  6,  {1, 2}},

        /* Negative + positive */
        {num4,  4,  0,  {0, 2}},
        {num6,  5,  2,  {0, 4}},
        {num9,  5,  0,  {0, 4}},

        /* Duplicate values */
        {num5,  2,  6,  {0, 1}},
        {num8,  2,  0,  {0, 1}},

        /* Pair near the end */
        {num7,  5,  9,  {3, 4}},

        /* No solution */
        {num7,  5,  100, {-1, -1}},
        {num11, 5,  100, {-1, -1}},

        /* Single element */
        {num10, 1, 10, {-1, -1}},

        {NULL, 0, 0, {-1, -1}}
    };

    total = sizeof(test) / sizeof(struct Test) - 1;

    struct Test *i = test;
    for (; i->nums != NULL; i++) {
        int result[RESULT_SIZE] = {-1, -1};
        twoSum(i->nums, i->n, i->target, result);

        int flag = ResultCheck(result, i->result);
        if (flag) {
            printf("  PASS  ");
            passed++;
        } else printf("  FAIL  ");

        printf("{");
        for (int j = 0; j < i->n - 1; j++)
            printf("%d, ", i->nums[j]);
        printf("%d}", i->nums[i->n - 1]);
        printf(" RESULT [%d, %d]", result[0], result[1]);
        if (!flag) printf(" EXPECTED [%d, %d]", i->result[0], i->result[1]);
        printf("\n");
    }

    printf("PASS %d/%d\n", passed, total);

    return !(passed == total);
}

static int ResultCheck(const int a[], const int b[]) {
    return a[0] == b[0] && a[1] == b[1];
}

void twoSum(const int nums[], int n, int target, int result[]) {
    int i, j, buf;
    int low = nums[0], high = nums[0];

    for (i = 0; i < n; i++) {
        buf = nums[i];
        if (buf > high) high = buf;
        if (buf < low) low = buf;
    }

    for (i = 0; i < n - 1; i++) {
        buf = nums[i];
        if (buf + high < target) continue;
        if (buf + low > target) continue;

        for (j = i + 1; j < n; j++) {
            if (nums[j] + buf == target) {
                result[0] = i;
                result[1] = j;
                return;
            }
        }
    }
}
