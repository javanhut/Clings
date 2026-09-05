// macros1.c - solution

#include <stdio.h>

#define SQUARE(x) ((x) * (x))

int main(void)
{
    printf("SQUARE(2 + 3) = %d\n", SQUARE(2 + 3));
    printf("100 / SQUARE(5) = %d\n", 100 / SQUARE(5));
    return 0;
}
