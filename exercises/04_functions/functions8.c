// functions8.c
//
// CONCEPT
// Designing a recursive function is always the same two questions:
//   1. What is the smallest input, and what is its answer? (base case)
//   2. How do I express the answer for n using the answer for something
//      smaller than n? (recursive case)
//
//   power(b, 0)  = 1                     power(b, e) = b * power(b, e - 1)
//   fib(0) = 0, fib(1) = 1               fib(n) = fib(n-1) + fib(n-2)
//   hanoi(0) = 0                         hanoi(n) = 2 * hanoi(n-1) + 1
//
// Naive fib is exponential: fib(40) makes over a billion calls. That is a
// property of this particular recursion, not of recursion in general; the
// fix (remember results, or loop) belongs to the arrays section.
//
// WHEN YOU USE THIS
// Anything defined in terms of itself: file trees, expression evaluation,
// backtracking search, the merge sort and quicksort you will meet later.
//
// TASK
// Write the three functions recursively (no loops).
//
// EXPECTED OUTPUT
//     power(2, 10) = 1024
//     power(7, 0) = 1
//     fib(10) = 55
//     fib(20) = 6765
//     hanoi(3) = 7
//     hanoi(10) = 1023

#include <stdio.h>

long power(long base, unsigned int exp)
{
    // TODO
    (void)base;
    (void)exp;
    return 0;
}

long fib(unsigned int n)
{
    // TODO
    (void)n;
    return 0;
}

long hanoi(unsigned int disks)
{
    // TODO: the minimum number of moves to solve Towers of Hanoi.
    (void)disks;
    return 0;
}

int main(void)
{
    printf("power(2, 10) = %ld\n", power(2, 10));
    printf("power(7, 0) = %ld\n", power(7, 0));
    printf("fib(10) = %ld\n", fib(10));
    printf("fib(20) = %ld\n", fib(20));
    printf("hanoi(3) = %ld\n", hanoi(3));
    printf("hanoi(10) = %ld\n", hanoi(10));
    return 0;
}
