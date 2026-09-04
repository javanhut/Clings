// loops1.c
//
// This loop is meant to add up the numbers from 1 to 10 inclusive, but the
// result is off. Fix the loop so the program prints:
//
//     The sum of 1 to 10 is 55

#include <stdio.h>

int main(void)
{
    int sum = 0;

    for (int i = 1; i <= 10; i++) {
        sum += i;
    }

    printf("The sum of 1 to 10 is %d\n", sum);
    return 0;
}
