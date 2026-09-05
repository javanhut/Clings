// functions4.c - solution

#include <stdio.h>

unsigned long factorial(unsigned int n)
{
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main(void)
{
    printf("5! = %lu\n", factorial(5));
    return 0;
}
