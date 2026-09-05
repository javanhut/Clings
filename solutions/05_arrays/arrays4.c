// arrays4.c - solution

#include <stdio.h>

int sum(const int values[], size_t len)
{
    int total = 0;

    for (size_t i = 0; i < len; i++) {
        total += values[i];
    }
    return total;
}

int main(void)
{
    int numbers[] = {10, 20, 30, 40, 50};

    printf("sum is %d\n", sum(numbers, sizeof(numbers) / sizeof(numbers[0])));
    return 0;
}
