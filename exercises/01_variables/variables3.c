// variables3.c
//
// The type of a variable decides which values it can hold. `price` is
// supposed to hold 9.99, but an `int` can only store whole numbers, and
// printing it with `%f` is a mismatch the compiler warns about.
//
// Choose a better type so the program prints:
//
//     Price: 9.99

#include <stdio.h>

int main(void)
{
    int price = 9.99;
    printf("Price: %.2f\n", price);
    return 0;
}
