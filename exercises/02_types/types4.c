// types4.c
//
// CONCEPT
// C did not have a boolean type for its first 27 years. Conditions work on
// integers: 0 is false, anything else is true, and comparison operators
// produce the int 1 or 0. C99 added `_Bool` and a header, <stdbool.h>,
// that defines the friendlier names `bool`, `true` and `false`. Only C23
// makes them keywords. This exercise compiles as C17, so the header is
// required.
//
// A `bool` stores only 0 or 1: assigning 42 to it gives 1. That is the one
// practical difference from `int`.
//
// WHEN YOU USE THIS
// Flags and predicates: `bool is_empty(...)`, `bool verbose`. Using bool
// instead of int documents that the value is a yes/no answer and nothing
// else. Older code bases use `int` and macros like TRUE/FALSE; you will
// read both.
//
// TASK
// Include the right header so the program compiles.
//
// EXPECTED OUTPUT
//     Ready!
//     42 stored in a bool is 1

#include <stdio.h>

int main(void)
{
    bool ready = true;
    bool big = 42;

    if (ready) {
        printf("Ready!\n");
    }
    printf("42 stored in a bool is %d\n", big);
    return 0;
}
