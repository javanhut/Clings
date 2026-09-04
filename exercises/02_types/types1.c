// types1.c
//
// Dividing one integer by another gives an integer: 7 / 2 is 3, not 3.5.
// The remainder is simply thrown away.
//
// Change the calculation (not the variables a and b!) so that the program
// prints:
//
//     7 / 2 = 3.5

#include <stdio.h>

int main(void)
{
    int a = 7;
    int b = 2;

    double result = a / b;

    printf("%d / %d = %.1f\n", a, b, result);
    return 0;
}
