// arrays2.c - solution

#include <stdio.h>

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, 6};
    size_t len = sizeof(numbers) / sizeof(numbers[0]);
    int sum = 0;

    for (size_t i = 0; i < len; i++) {
        sum += numbers[i];
    }
    printf("The array has %zu elements and their sum is %d\n", len, sum);
    return 0;
}
