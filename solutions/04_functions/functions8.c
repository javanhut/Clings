// functions8.c - solution

#include <stdio.h>

long power(long base, unsigned int exp)
{
    if (exp == 0) {
        return 1;
    }
    return base * power(base, exp - 1);
}

long fib(unsigned int n)
{
    if (n < 2) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

long hanoi(unsigned int disks)
{
    if (disks == 0) {
        return 0;
    }
    return 2 * hanoi(disks - 1) + 1;
}

int main(void)
{
    printf("power(2, 10) = %ld\n", power(2, 10));
    printf("power(7, 0) = %ld\n", power(7, 0));
    printf("fib(10) = %ld\n", fib(10));
    printf("fib(20) = %ld\n", fib(20));
    printf("hanoi(3) = %ld\n", hanoi(3));
    printf("hanoi(10) = %ld\n", hanoi(10));
    return 0;
}
