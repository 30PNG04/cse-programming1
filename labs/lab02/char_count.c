#include <stdio.h>
#include <unistd.h>
#include <string.h>

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

#define NUM_OF_CHAR 26

void char_count(int table[]);

static int saved_stdin;

static void fake_stdin(const char *input)
{
    int fd[2];

    pipe(fd);

    saved_stdin = dup(STDIN_FILENO);

    write(fd[1], input, strlen(input));
    close(fd[1]);

    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
}

static void restore_stdin(void)
{
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdin);
}


/* ---------- tests ---------- */

static void test_basic(void)
{
    printf("\ntest_basic\n");

    int table[NUM_OF_CHAR] = {0};

    fake_stdin("Hello World!\n");

    char_count(table);

    CHECK(table['h' - 'a'] == 1);
    CHECK(table['e' - 'a'] == 1);
    CHECK(table['l' - 'a'] == 3);
    CHECK(table['o' - 'a'] == 2);
    CHECK(table['w' - 'a'] == 1);
    CHECK(table['r' - 'a'] == 1);
    CHECK(table['d' - 'a'] == 1);

    restore_stdin();
}


static void test_uppercase(void)
{
    printf("\ntest_uppercase\n");

    int table[NUM_OF_CHAR] = {0};

    fake_stdin("ABCabc\n");

    char_count(table);

    CHECK(table['a' - 'a'] == 2);
    CHECK(table['b' - 'a'] == 2);
    CHECK(table['c' - 'a'] == 2);

    restore_stdin();
}


static void test_numbers(void)
{
    printf("\ntest_numbers\n");

    int table[NUM_OF_CHAR] = {0};

    fake_stdin("1234567890\n");

    char_count(table);

    for (int i = 0; i < NUM_OF_CHAR; i++)
        CHECK(table[i] == 0);

    restore_stdin();
}


static void test_empty(void)
{
    printf("\ntest_empty\n");

    int table[NUM_OF_CHAR] = {0};

    fake_stdin("\n");

    char_count(table);

    for (int i = 0; i < NUM_OF_CHAR; i++)
        CHECK(table[i] == 0);

    restore_stdin();
}


static void test_special_characters(void)
{
    printf("\ntest_special_characters\n");

    int table[NUM_OF_CHAR] = {0};

    fake_stdin("!@#$%^&*()_+-=\n");

    char_count(table);

    for (int i = 0; i < NUM_OF_CHAR; i++)
        CHECK(table[i] == 0);

    restore_stdin();
}


/* ---------- test runner ---------- */

int main(void)
{
    test_basic();
    test_uppercase();
    test_numbers();
    test_empty();
    test_special_characters();

    printf("\n%d/%d checks passed\n", passed, total);

    return passed != total;
}

void char_count(int table[])
{
    char string[128];

    fgets(string, sizeof string, stdin);

    char *p = string;
    for (;*p != '\0'; p++)
        *p += ('A' <= *p && *p <= 'Z') ? 32 : 0;

    p = string;
    for (; *p != '\n'; p++)
        if ('a' <= *p && *p <= 'z') table[*p - 'a'] += 1;
}