// loops3.c - solution

#include <stdio.h>

int main(void)
{
    for (int row = 1; row <= 4; row++) {
        for (int col = 1; col <= 4; col++) {
            printf("%3d", row * col);
        }
        printf("\n");
    }
    return 0;
}
