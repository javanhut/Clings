// variables4.c - solution

#include <stdio.h>

int main(void)
{
    int values[] = {7, 42, 3, 19};
    int largest = 0;

    for (int i = 0; i < 4; i++) {
        if (values[i] > largest) {
            largest = values[i];
        }
    }
    printf("largest is %d\n", largest);
    return 0;
}
