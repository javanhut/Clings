// arrays7.c - solution

#include <stddef.h>
#include <stdio.h>

int find(const int *a, size_t len, int target)
{
    size_t lo = 0;
    size_t hi = len;

    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        if (a[mid] == target) {
            return (int)mid;
        }
        if (a[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return -1;
}

void insert_sorted(int *a, size_t *len, int value)
{
    size_t pos = 0;

    while (pos < *len && a[pos] < value) {
        pos++;
    }
    for (size_t i = *len; i > pos; i--) {
        a[i] = a[i - 1];
    }
    a[pos] = value;
    (*len)++;
}

int main(void)
{
    int a[16] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    size_t len = 10;

    printf("find(23) = %d\n", find(a, len, 23));
    printf("find(2) = %d\n", find(a, len, 2));
    printf("find(91) = %d\n", find(a, len, 91));
    printf("find(50) = %d\n", find(a, len, 50));
    insert_sorted(a, &len, 50);
    printf("after insert:");
    for (size_t i = 0; i < len; i++) {
        printf(" %d", a[i]);
    }
    printf("\n");
    return 0;
}
