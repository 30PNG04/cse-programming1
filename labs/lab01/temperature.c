#include <stdio.h>

int main() {
    float lower, upper, step;

    scanf("%f %f %f", &lower, &upper, &step);

    float fahr, celsius;

    for (fahr = lower; fahr <= upper; fahr += step) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f\t%6.1f\n", fahr, celsius);
    }

    return 0;
}