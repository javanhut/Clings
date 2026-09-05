// variables4.c
//
// CONCEPT
// A variable lives in the *block* (the `{ ... }`) where it is declared, and
// dies at the closing brace. This is its *scope*. A loop body, an if body
// and a function body are all blocks. A variable declared in a `for`
// header belongs to the loop and is gone after it.
//
// Declaring a variable with the same name in an inner block *shadows* the
// outer one: inside the block, the name refers to the new variable, and the
// outer one is untouched. That is legal, and a frequent source of "why did
// my change not stick?" bugs. -Wshadow warns about it.
//
// WHEN YOU USE THIS
// Tight scopes are a feature: a variable that only exists for ten lines
// cannot be misused two hundred lines later. Declare the loop counter in
// the `for`, the temporary inside the `if`. But when a value must survive
// the block, it has to be declared *outside* it.
//
// TASK
// `largest` is meant to hold the biggest value seen by the loop, but it is
// declared in the wrong place, and the inner `int largest` shadows the one
// the loop should update. Fix the scoping so the program prints the
// expected output. Do not change the values array.
//
// EXPECTED OUTPUT
//     largest is 42

#include <stdio.h>

int main(void)
{
    int values[] = {7, 42, 3, 19};

    for (int i = 0; i < 4; i++) {
        int largest = 0;
        if (values[i] > largest) {
            largest = values[i];
        }
    }
    printf("largest is %d\n", largest);
    return 0;
}
