// variables1.c
//
// In C, every variable must be declared with a type before it is used.
// The variable `x` below is used but never declared. Fix that.

#include <stdio.h>

int main(void)
{
    int x = 42;
    printf("x is %d\n", x);
    return 0;
}
