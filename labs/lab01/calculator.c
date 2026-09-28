#include <stdio.h>

float add(float a, float b);
float sub(float a, float b);
float mul(float a, float b);
float div(float a, float b);
float pow(float a, float b);

int main() {
    float (*func[])(float, float) = {add, sub, mul, div, pow};

    int choice;

    do {
        printf("\n1. Add\n");
        printf("2. Subtract\n");
        printf("3. Multiply\n");
        printf("4. Divide\n");
        printf("5. Power\n");
        printf("0. Exit\n");
        scanf("%d", &choice);

        if (!choice) {
            printf("Exiting...\n");
            return 0;
        }

        float a, b;
        printf("Input a: ");
        scanf("%f", &a);

        int buf = 1;
        do {
            printf("Input b: ");
            scanf("%f", &b);
            if (choice != 4 || b != 0) buf = 0;
            else printf("Invalid\n");
        } while (buf);

        printf("Result: %0.4f\n", func[choice - 1](a, b));

    } while (choice);
    return 0;
}

float add(float a, float b) {
    printf("\nAdding...\n");
    return a + b;
}

float sub(float a, float b) {
    printf("\nSubtracting...\n");
    return a - b;
}

float mul(float a, float b) {
    printf("\nMultiplying...\n");
    return a * b;
}

float div(float a, float b) {
    printf("\nDividing...\n");
    return a / b;
}

float pow(float a, float b) {
    printf("\nPowering...\n");

    if (a == 0)
        return b == 0;
    else if (b < 0) {
        a = 1/a;
        b = -b;
    }

    float buf = a, result = 1;
    
    int power;
    for (power = (int) b; power != 0; power /= 2) {
        if (power % 2) result *= buf;
        buf *= buf;
    }

    return result;
}