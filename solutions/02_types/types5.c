// types5.c - solution

#include <stdio.h>

int main(void)
{
    int negative = -1;
    int limit = 10;

    if (negative < limit) {
        printf("%d is smaller than %u\n", negative, (unsigned int)limit);
    } else {
        printf("%d is NOT smaller than %u\n", negative, (unsigned int)limit);
    }

    int values[] = {0, 1, 2, 3, 4};
    size_t count = sizeof(values) / sizeof(values[0]);
    for (size_t i = count; i-- > 0;) {
        printf("%d ", values[i]);
        if (i == 0) {
            break;
        }
    }
    printf("\n");
    return 0;
}
