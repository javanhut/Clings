// arrays1.c
//
// Array indices start at 0, so an array with 5 elements has indices 0 to 4.
// This loop reads one element past the end of the array, which is undefined
// behavior: it prints garbage, or crashes, or appears to work by accident.
// Fix the loop so the program prints exactly:
//
//     10 20 30 40 50

#include <stdio.h>

int main(void)
{
    int numbers[5] = {10, 20, 30, 40, 50};

    for (int i = 0; i < 5; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", numbers[i]);
    }
    printf("\n");
    return 0;
}
