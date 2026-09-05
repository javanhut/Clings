// functions3.c - solution

#include <stdio.h>

int increment(int n)
{
    return n + 1;
}

int main(void)
{
    int x = 1;

    x = increment(x);
    printf("x is %d\n", x);
    return 0;
}
