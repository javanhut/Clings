// loops4.c
//
// CONCEPT
// `do { ... } while (condition);` checks the condition *after* the body, so
// the body always runs at least once. That is exactly right when the
// first iteration must happen before there is anything to test: reading a
// menu choice, processing a number digit by digit (even 0 has one digit).
//
// Compare:
//   while (n != 0) { ... }     // may run zero times
//   do { ... } while (n != 0); // runs at least once
//
// The Collatz rule: if n is even, n becomes n/2; if odd, 3n+1. Repeat until
// n is 1. Nobody has proven it always reaches 1, but it does for every
// number ever tried.
//
// WHEN YOU USE THIS
// Input validation loops ("ask again until valid"), retry loops, and any
// algorithm phrased as "do the step, then check". You will use `while` and
// `for` far more often; recognize the cases where do-while removes a
// duplicated first step.
//
// TASK
// Write two functions:
//   digit_sum(n)     adds up the decimal digits of n (n >= 0). Use a
//                    do-while so that 0 correctly reports 0 after one pass.
//   collatz_steps(n) counts how many steps it takes n to reach 1.
//
// EXPECTED OUTPUT
//     digit_sum(0) = 0
//     digit_sum(98765) = 35
//     collatz_steps(1) = 0
//     collatz_steps(6) = 8
//     collatz_steps(27) = 111

#include <stdio.h>

int digit_sum(int n)
{
    // TODO: use do { ... } while (...)
    (void)n;
    return -1;
}

int collatz_steps(long n)
{
    // TODO
    (void)n;
    return -1;
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
