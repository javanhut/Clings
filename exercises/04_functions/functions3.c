// functions3.c
//
// CONCEPT
// C passes arguments *by value*: the function receives a copy. `increment`
// gets a copy of `x` in its parameter `n`, changes the copy, and the copy
// dies when the function returns. `x` in main never hears about it. This
// is true for every type, including structs (the whole struct is copied)
// and, as we will see, pointers (the *address* is copied, and through the
// copied address you can still reach the original).
//
// The two ways to get a result out of a function are: return it, or give
// the function a pointer to where the result should go. The second one is
// the pointers section; here, use the first.
//
// WHEN YOU USE THIS
// Understanding by-value is what makes C predictable: a function cannot
// change your variables unless you hand it their addresses. When you read
// a call like `f(x)`, you know x is unchanged afterwards. When you read
// `f(&x)`, you know it might not be.
//
// TASK
// Without using pointers, change `increment` so that it returns the
// incremented value, and use that return value in main.
//
// EXPECTED OUTPUT
//     x is 2

#include <stdio.h>

void increment(int n)
{
    n = n + 1;
}

int main(void)
{
    int x = 1;

    increment(x);
    printf("x is %d\n", x);
    return 0;
}
