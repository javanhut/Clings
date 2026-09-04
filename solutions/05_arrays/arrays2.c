// arrays2.c
//
// Arrays do not know their own length, but `sizeof` does: the size of the
// whole array divided by the size of one element gives the element count.
//
// `len` is hardcoded to the wrong number. Compute it with `sizeof` instead,
// so that the program still works if more numbers are added. Expected:
//
//     The array has 6 elements and their sum is 21

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
