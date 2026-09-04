// functions4.c
//
// A recursive function calls itself. Every recursion needs a *base case*:
// a condition under which it stops calling itself and just returns a
// value. This factorial function has no base case, so it recurses until
// the program crashes. Add one so the program prints:
//
//     5! = 120

#include <stdio.h>

unsigned long factorial(unsigned int n)
{
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main(void)
{
    printf("5! = %lu\n", factorial(5));
    return 0;
}
