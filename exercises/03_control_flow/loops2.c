// loops2.c
//
// CONCEPT
// Two statements change the flow inside a loop body:
//   `continue` skips the rest of the body and goes to the next iteration
//              (in a `for`, the step still runs),
//   `break`    leaves the loop entirely.
// Both apply to the *innermost* loop or switch they are in.
//
// `while (condition)` is the loop to use when the number of iterations is
// not known in advance: reading input until it ends, searching until found.
// `while (1)` with a `break` inside is the idiom for "loop until something
// happens in the middle of the body".
//
// WHEN YOU USE THIS
// `continue` is for "this element does not interest me": it avoids nesting
// the whole body in an `if`. `break` is for "found it" and "done" in search
// loops. Overusing both makes loops hard to follow; one of each per loop is
// a good limit.
//
// TASK
// This program should print the even numbers from 1 to 10, one per line,
// but prints nothing at all. Fix it (the fix is a single keyword).
//
// EXPECTED OUTPUT
//     2
//     4
//     6
//     8
//     10

#include <stdio.h>

int main(void)
{
    int i = 0;

    while (i < 10) {
        i++;
        if (i % 2 != 0) {
            break;
        }
        printf("%d\n", i);
    }
    return 0;
}
