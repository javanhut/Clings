// functions4.c
//
// CONCEPT
// A recursive function calls itself on a smaller version of the problem.
// Every call gets its own fresh set of parameters and local variables on
// the *call stack*, so the calls do not interfere. Every recursion needs a
// *base case*: an input for which the answer is known directly, so the
// chain of calls stops. Without one, the stack grows until the program
// crashes (a "stack overflow", which is where the website got its name).
//
// factorial(n) = n * factorial(n - 1), and factorial(0) = 1.
//
// WHEN YOU USE THIS
// Recursion is natural for tree-shaped data (directories, parse trees,
// JSON), divide-and-conquer algorithms (quicksort, binary search) and
// mathematically defined sequences. For plain counting, a loop is faster
// and cannot overflow the stack; C compilers do not promise to optimize
// tail calls away.
//
// TASK
// Add the base case.
//
// EXPECTED OUTPUT
//     5! = 120

#include <stdio.h>

unsigned long factorial(unsigned int n)
{
    return n * factorial(n - 1);
}

int main(void)
{
    printf("5! = %lu\n", factorial(5));
    return 0;
}
