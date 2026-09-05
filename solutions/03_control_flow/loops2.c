// loops2.c - solution

#include <stdio.h>

int main(void)
{
    int i = 0;

    while (i < 10) {
        i++;
        if (i % 2 != 0) {
            continue;
        }
        printf("%d\n", i);
    }
    return 0;
}
