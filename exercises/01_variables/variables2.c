// variables2.c
//
// CONCEPT
// `const` in front of a declaration promises that the variable will not be
// changed after initialization. The compiler enforces the promise: any
// assignment to it is a compile error. The value need not be known at
// compile time; `const int n = argc;` is fine, it just cannot change later.
//
// WHEN YOU USE THIS
// Mark everything `const` that does not need to change. It documents intent
// ("this is an input, not a working variable"), lets the compiler catch
// accidental writes, and later, with pointers, becomes the way a function
// promises "I only read this, I do not modify it".
//
// Here the promise is wrong: `count` is meant to be a counter.
//
// TASK
// Make the program compile and print the expected output.
//
// EXPECTED OUTPUT
//     count is 5

#include <stdio.h>

int main(void)
{
    const int count = 0;

    for (int i = 0; i < 5; i++) {
        count = count + 1;
    }
    printf("count is %d\n", count);
    return 0;
}
