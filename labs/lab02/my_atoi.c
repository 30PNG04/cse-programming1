#include <stdio.h>

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

int my_atoi(const char s[]);

static int main() {
    struct Test {
        const char *input;
        int expected;
    };

    struct Test tests[] = {
        {"0", 0},
        {"123", 123},
        {"-123", -123},
        {"+123", 123},
        {"   123", 123},
        {"\t-42", -42},
        {"123abc", 123},
        {"abc123", 0},
        {"++123", 0},
        {"--123", 0},
        {"", 0},
        {"   ", 0},
        {"2147483647", 2147483647},
        {NULL, 0}
    };

    printf("Checking...\n");
    
    for (struct Test *i = tests; i->input != NULL; i++)
        CHECK(my_atoi(i->input) == i->expected);

    printf("\nResult: %d/%d PASS\n", passed, total);
    return passed == total ? 0 : 1;
}

int my_atoi(const char s[]) {
    int buf = 0, sign = 1;

    for (;*s == ' ' || *s == '\n' || *s == '\t'; s++) {}

    if (*s == '+' || *s == '-') {
        sign = *s == '+' ? 1 : -1;
        s++;
    }

    for (;*s >= '0' && *s <= '9'; s++)
        buf = buf * 10 + (*s - '0');

    return sign * buf;
}