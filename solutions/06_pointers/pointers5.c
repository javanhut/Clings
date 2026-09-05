// pointers5.c - solution

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool divmod(int a, int b, int *quotient, int *remainder)
{
    if (b == 0) {
        return false;
    }
    *quotient = a / b;
    *remainder = a % b;
    return true;
}

void min_max(const int *values, size_t len, int *min, int *max)
{
    int lo = values[0];
    int hi = values[0];

    for (size_t i = 1; i < len; i++) {
        if (values[i] < lo) {
            lo = values[i];
        }
        if (values[i] > hi) {
            hi = values[i];
        }
    }
    if (min != NULL) {
        *min = lo;
    }
    if (max != NULL) {
        *max = hi;
    }
}

int main(void)
{
    int q = 0;
    int r = 0;
    int values[] = {7, 42, 3, 19};
    int lo = 0;
    int hi = 0;

    if (divmod(17, 5, &q, &r)) {
        printf("17 / 5 = %d remainder %d\n", q, r);
    }
    if (!divmod(1, 0, &q, &r)) {
        printf("division by zero\n");
    }
    min_max(values, 4, &lo, &hi);
    printf("min %d, max %d\n", lo, hi);
    hi = 0;
    min_max(values, 4, NULL, &hi);
    printf("max only: %d\n", hi);
    return 0;
}
