// functions2.c
//
// CONCEPT
// A function declared with a return type other than `void` must end every
// path with `return value;`. `n * n;` on its own is a legal statement that
// computes a value and throws it away. Falling off the end of a non-void
// function and then *using* the result is undefined behavior; the compiler
// warns ("control reaches end of non-void function") and Clings fails on
// warnings.
//
// The reverse also holds: a `void` function may `return;` (nothing) to exit
// early but cannot return a value.
//
// WHEN YOU USE THIS
// Every function that computes something. Watch for it in functions with
// several `if` branches: it is easy to return in three branches and forget
// the fourth. The compiler catches that when warnings are on.
//
// TASK
// `square` computes the right value but never hands it back. Fix it.
//
// EXPECTED OUTPUT
//     5 squared is 25

#include <stdio.h>

int square(int n)
{
    n * n;
}

int main(void)
{
    printf("5 squared is %d\n", square(5));
    return 0;
}
