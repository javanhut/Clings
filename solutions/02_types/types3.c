// types3.c
//
// Every integer type has a limited range. An `unsigned char` can only hold
// values from 0 to 255; adding beyond that silently wraps around to 0.
//
// Pick a type for `value` that can hold the result, so the program prints:
//
//     value is 260

#include <stdio.h>

int main(void)
{
    int value = 250;

    value += 10;

    printf("value is %d\n", value);
    return 0;
}
