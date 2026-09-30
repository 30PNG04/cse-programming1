#include <string.h>
#include <stdio.h>

static int pass = 0, total = 0;

void reverseString(char* s, int sSize);

int main(void) {
    struct Test {
        const char *s;
        const char *result;
    };

    struct Test test[] = {
        {"Penguin", "niugneP"},
        {NULL, NULL}
    };

    total = sizeof(test) / sizeof(struct Test) - 1;

    struct Test *p = test;
    for (;p->s != NULL;p++) {
        int len = strlen(p->s);
        char buf[len + 1];

        strcpy(buf, p->s);
        reverseString(buf, len);

        int flag = strcmp(buf, p->result);
        if (!flag) {
            printf("  PASS  ");
            pass++;
        } else printf("  FAIL  ");

        printf("\"%s\" RESULT \"%s\"", p->s, buf);
        if (flag) printf(" EXPECTED \"%s\"", p->result);
        printf("\n");
    }

    printf("PASS %d/%d\n", pass, total);

    return total != pass;
}

void reverseString(char* s, int sSize) {
    for (int i = 0, j = sSize - 1; i < j; i++, j--) {
        s[i] ^= s[j];
        s[j] ^= s[i];
        s[i] ^= s[j];
    }
}