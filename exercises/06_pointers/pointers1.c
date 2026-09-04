// pointers1.c
//
// A pointer stores the *address* of a variable. `&x` is the address of x,
// and `*p` is the value that p points to. Assigning through `*p` changes
// the variable at that address.
//
// The pointer below is initialized with the value of x instead of its
// address. Fix it so the program prints:
//
//     x is 20

#include <stdio.h>

int main(void)
{
    int x = 10;
    int *p = x;

    *p = 20;

    printf("x is %d\n", x);
    return 0;
}
