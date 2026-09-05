// pointers3.c - solution

#include <stddef.h>
#include <stdio.h>

int main(void)
{
    int values[] = {5, 10, 15, 20};
    size_t count = sizeof(values) / sizeof(values[0]);
    int *first = values;
    int *second = values + 1;
    int *last = values + count - 1;
    ptrdiff_t distance = last - first;

    printf("first: %d\n", *first);
    printf("second: %d\n", *second);
    printf("last: %d\n", *last);
    printf("last is %td elements after first\n", distance);
    return 0;
}
