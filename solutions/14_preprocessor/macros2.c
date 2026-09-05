// macros2.c - solution

#include <stdio.h>

#define SWAP(x, y)      \
    do {                \
        tmp = x;        \
        x = y;          \
        y = tmp;        \
    } while (0)
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main(void)
{
    int tmp;
    int a = 2;
    int b = 5;
    int c = 1;
    int d = 9;
    int i = 3;

    if (a < b)
        SWAP(a, b);
    if (c > d)
        SWAP(c, d);
    printf("after swap: a = %d, b = %d\n", a, b);
    printf("unchanged: c = %d, d = %d\n", c, d);

    i++;
    int m = MAX(i, 10);
    printf("max = %d, i = %d\n", m, i);
    return 0;
}
