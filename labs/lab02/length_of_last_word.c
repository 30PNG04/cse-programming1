#include <stdlib.h>
#include <stdio.h>

static int pass = 0, total = 0;

int lengthOfLastWord(const char* s);

int main(void) {
    struct Test {
        const char *s;
        const char result;
    };

    struct Test test[] = {
        {"Hello World", 5},
        {"   fly me   to   the moon  ", 4},
        {"luffy is still joyboy", 6},
        {NULL, 0}
    };

    total = sizeof(test) / sizeof(struct Test) - 1;

    struct Test *p = test;
    for (;p->s != NULL;p++) {
        int buf = lengthOfLastWord(p->s);
        int flag = buf == p->result;

        if (flag) {
            printf("  PASS  ");
            pass++;
        } else printf("  FAIL  ");

        printf("\"%s\" RESULT %d", p->s, buf);
        if (!flag) printf(" EXPECTED %d", p->result);
        printf("\n");
    }

    printf("PASS %d/%d\n", pass, total);

    return total != pass;
}

int lengthOfLastWord(const char* s) {
    int i;
    for (i = 0; s[i] != '\0'; i++) {}
    i--;

    for(;s[i] == ' ';i--) {}

    int buf = 0;
    for(;(s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'); i--) {
        buf++;
        if (i == 0) break;
    }
    
    return buf;
}