// pointers9.c - solution

#include <stdio.h>

int main(void)
{
    int value = 0;
    int *p = &value;
    *p = 5;
    printf("doubled: %d\n", *p * 2);

    int values[] = {7, 42, 3};
    int *best;
    int largest = values[0];
    {
        for (int i = 1; i < 3; i++) {
            if (values[i] > largest) {
                largest = values[i];
            }
        }
        best = &largest;
    }
    printf("largest: %d\n", *best);
    return 0;
}
