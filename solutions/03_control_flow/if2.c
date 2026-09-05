// if2.c - solution

#include <stdio.h>

void describe(int n)
{
    if (n < 0) {
        printf("%d is negative\n", n);
    } else if (n == 0) {
        printf("%d is zero\n", n);
    } else if (n >= 10) {
        printf("%d is a large positive number\n", n);
    } else if (n % 2 == 0) {
        printf("%d is a small positive even number\n", n);
    } else {
        printf("%d is a small positive odd number\n", n);
    }
}

int main(void)
{
    int samples[] = {-4, 0, 7, 8, 10};

    for (int i = 0; i < 5; i++) {
        describe(samples[i]);
    }
    return 0;
}
