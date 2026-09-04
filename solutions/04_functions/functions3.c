// functions3.c
//
// Arguments are passed *by value*: `increment` receives a copy of `x`,
// so changing `n` inside the function has no effect on `x` in main.
//
// Without using pointers (they come later!), change `increment` so that it
// returns the incremented value, and use that return value in main.
// Expected output:
//
//     x is 2

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
