// pointers6.c - solution

#include <stddef.h>
#include <stdio.h>

int sum_range(const int *begin, const int *end)
{
    int total = 0;

    for (const int *p = begin; p != end; p++) {
        total += *p;
    }
    return total;
}

const int *find_first(const int *begin, const int *end, int target)
{
    for (const int *p = begin; p != end; p++) {
        if (*p == target) {
            return p;
        }
    }
    return NULL;
}

int main(void)
{
    int values[] = {5, 10, 15, 20, 10};
    size_t len = sizeof(values) / sizeof(values[0]);
    const int *end = values + len;

    printf("sum = %d\n", sum_range(values, end));
    printf("sum of middle = %d\n", sum_range(values + 1, end - 1));

    const int *hit = find_first(values, end, 15);
    if (hit != NULL) {
        printf("15 found at index %td\n", hit - values);
    }
    if (find_first(values, end, 99) == NULL) {
        printf("99 not found\n");
    }
    return 0;
}
