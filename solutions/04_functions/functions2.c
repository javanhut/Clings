// functions2.c
//
// A function that promises to return an `int` must actually return one.
// `square` computes the right value but never hands it back to the caller.
// Fix it so the program prints:
//
//     5 squared is 25

#include <stdio.h>

int square(int n)
{
    return n * n;
}

int main(void)
{
    printf("5 squared is %d\n", square(5));
    return 0;
}
