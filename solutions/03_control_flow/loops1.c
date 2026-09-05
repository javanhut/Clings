// loops1.c - solution

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
