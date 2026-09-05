// arrays5.c - solution

#include <stddef.h>
#include <stdio.h>

size_t index_of_max(const int *values, size_t len)
{
    size_t best = 0;

    for (size_t i = 1; i < len; i++) {
        if (values[i] > values[best]) {
            best = i;
        }
    }
    return best;
}

void reverse(int *values, size_t len)
{
    for (size_t i = 0, j = len; i + 1 < j; i++, j--) {
        int t = values[i];
        values[i] = values[j - 1];
        values[j - 1] = t;
    }
}

size_t count_if_even(const int *values, size_t len)
{
    size_t count = 0;

    for (size_t i = 0; i < len; i++) {
        if (values[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}

void print_array(const int *values, size_t len)
{
    if (len == 0) {
        printf("(empty)\n");
        return;
    }
    for (size_t i = 0; i < len; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", values[i]);
    }
    printf("\n");
}

int main(void)
{
    int numbers[] = {3, 8, -2, 8, 5};
    size_t len = sizeof(numbers) / sizeof(numbers[0]);
    int single[] = {42};

    print_array(numbers, len);
    printf("max at index %zu\n", index_of_max(numbers, len));
    printf("%zu even numbers\n", count_if_even(numbers, len));
    reverse(numbers, len);
    printf("reversed: ");
    print_array(numbers, len);
    reverse(single, 1);
    printf("single: ");
    print_array(single, 1);
    reverse(numbers, 0);
    printf("empty: ");
    print_array(numbers, 0);
    return 0;
}
