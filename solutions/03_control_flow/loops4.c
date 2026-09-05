// loops4.c - solution

#include <stdio.h>

int digit_sum(int n)
{
    int sum = 0;

    do {
        sum += n % 10;
        n /= 10;
    } while (n != 0);
    return sum;
}

int collatz_steps(long n)
{
    int steps = 0;

    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        steps++;
    }
    return steps;
}

int main(void)
{
    printf("digit_sum(0) = %d\n", digit_sum(0));
    printf("digit_sum(98765) = %d\n", digit_sum(98765));
    printf("collatz_steps(1) = %d\n", collatz_steps(1));
    printf("collatz_steps(6) = %d\n", collatz_steps(6));
    printf("collatz_steps(27) = %d\n", collatz_steps(27));
    return 0;
}
