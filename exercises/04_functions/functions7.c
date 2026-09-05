// functions7.c
//
// CONCEPT
// The return type is part of the contract, and conversions happen at the
// `return`: returning `(a + b) / 2` from a function that returns double
// does the division in int first (the operands are ints) and *then*
// converts the truncated result. The return type does not reach into the
// expression.
//
// Also: a function whose declared return type is `int` but which is used
// as a procedure (its result is never looked at) should be declared
// `void`. Otherwise every path must return a value or the compiler warns.
//
// Unused parameters produce a warning too. When a parameter is
// intentionally unused (it exists to match an interface), silence the
// warning with `(void)param;`, which the exercises here use in the stubs.
//
// WHEN YOU USE THIS
// Reading signatures critically is a daily task: "this returns double, but
// does it compute in double?" is a question worth asking of every numeric
// function you review.
//
// TASK
// There are three problems in this file; the compiler finds two of them
// for you and the output shows the third. Fix all three without changing
// main.
//
// EXPECTED OUTPUT
//     === Report ===
//     average of 3 and 4 is 3.5
//     min of 3 and 4 is 3

#include <stdio.h>

int print_banner(const char *title)
{
    printf("=== %s ===\n", title);
}

double average(int a, int b)
{
    return (a + b) / 2;
}

int min(int a, int b, int unused_flag)
{
    return a < b ? a : b;
}

int main(void)
{
    print_banner("Report");
    printf("average of 3 and 4 is %.1f\n", average(3, 4));
    printf("min of 3 and 4 is %d\n", min(3, 4, 0));
    return 0;
}
