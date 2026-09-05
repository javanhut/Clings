// ub2.c - solution

#include <limits.h>
#include <stdio.h>

// Returns 0 when n! does not fit in an unsigned long long.
unsigned long long factorial(int n)
{
    unsigned long long result = 1;

    for (int i = 2; i <= n; i++) {
        if (result > ULLONG_MAX / (unsigned long long)i) {
            return 0;
        }
        result *= (unsigned long long)i;
    }
    return result;
}

int main(void)
{
    printf("12! = %llu\n", factorial(12));
    printf("20! = %llu\n", factorial(20));
    for (int n = 13; n <= 25; n++) {
        if (factorial(n) == 0) {
            printf("%d! does not fit\n", n);
            break;
        }
    }
    return 0;
}
