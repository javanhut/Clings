// pointers1.c - solution

#include <stdio.h>

int main(void)
{
    int x = 10;
    int *p = &x;

    *p = 20;
    printf("x is %d\n", x);
    printf("p points to a value of %d\n", *p);
    return 0;
}
