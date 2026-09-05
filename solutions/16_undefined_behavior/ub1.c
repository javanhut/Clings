// ub1.c - solution

#include <stdio.h>

int main(void)
{
    int values[] = {10, 30, 20};
    int total = 0;
    int largest = values[0];

    for (int i = 0; i < 3; i++) {
        total += values[i];
        if (values[i] > largest) {
            largest = values[i];
        }
    }
    printf("total: %d\n", total);
    printf("largest: %d\n", largest);
    return 0;
}
