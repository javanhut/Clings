// if2.c
//
// CONCEPT
// An `if` / `else if` / `else` chain tests conditions in order and runs
// the first branch whose condition is true; the rest are skipped. The
// conditions can combine comparisons with `&&` (and), `||` (or) and `!`
// (not). `%` gives the remainder, so `n % 2 == 0` tests for even.
//
// The order of the branches matters: put the most specific test first.
// Checking `n > 0` before `n > 100` means the second branch never runs.
//
// WHEN YOU USE THIS
// Classification, validation, dispatch on ranges. When a chain has many
// `== constant` tests, a `switch` reads better (next exercises). When a
// chain compares ranges, `if` is the tool.
//
// TASK
// Write `describe`, which prints one line for its argument:
//   - "n is zero"                           for 0
//   - "n is a small positive even number"   for 1..9, even
//   - "n is a small positive odd number"    for 1..9, odd
//   - "n is a large positive number"        for 10 and above
//   - "n is negative"                       for anything below 0
// where n is the actual number.
//
// EXPECTED OUTPUT
//     -4 is negative
//     0 is zero
//     7 is a small positive odd number
//     8 is a small positive even number
//     10 is a large positive number

#include <stdio.h>

void describe(int n)
{
    // TODO
    (void)n;
}

int main(void)
{
    int samples[] = {-4, 0, 7, 8, 10};

    for (int i = 0; i < 5; i++) {
        describe(samples[i]);
    }
    return 0;
}
