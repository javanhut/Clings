// loops1.c
//
// CONCEPT
// A `for` loop has three parts: `for (init; condition; step)`. The
// condition is checked *before* every iteration, including the first, so
// `i < 10` runs the body for i = 0..9 and `i <= 10` for 0..10. Getting the
// boundary wrong by one is so common it has a name: the off-by-one error.
//
// The two idioms to internalize:
//   for (int i = 0; i < n; i++)     // n times, i = 0..n-1 (array indices)
//   for (int i = 1; i <= n; i++)    // n times, i = 1..n   (counting)
//
// WHEN YOU USE THIS
// Any time you know how many times to loop. `for` puts the whole control of
// the loop on one line, which is why it is preferred over `while` for
// counting: the reader sees init, bound and step together.
//
// TASK
// The loop should add the numbers 1 to 10 inclusive but the result is off.
// Fix it.
//
// EXPECTED OUTPUT
//     The sum of 1 to 10 is 55

#include <stdio.h>

int main(void)
{
    int sum = 0;

    for (int i = 1; i < 10; i++) {
        sum += i;
    }
    printf("The sum of 1 to 10 is %d\n", sum);
    return 0;
}
