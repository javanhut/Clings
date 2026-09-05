// macros5.c - solution

#include <stdio.h>

#include "counter.h"

int main(void)
{
    counter_bump(10);
    counter_bump(20);
    printf("value: %d\n", counter_value());
    printf("bumps: %d\n", bump_count);

    counter_bump(-counter_value());
    printf("value after reset: %d\n", counter_value());
    printf("bumps: %d\n", bump_count);
    return 0;
}
