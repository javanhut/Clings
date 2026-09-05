// pointers9.c
//
// CONCEPT
// A pointer is only as good as what it points to. Two ways it goes bad:
//
//   - *Wild*: declared but never set. `int *p; *p = 5;` writes to a random
//     address. Initialize pointers when you declare them, to a real
//     address or to NULL.
//   - *Dangling*: it pointed to something that no longer exists. A local
//     variable dies at the closing brace of its block; a pointer to it
//     that outlives the block points into memory that will be reused by
//     the next thing on the stack.
//
// The compiler catches some wild pointers (-Wuninitialized). Dangling
// pointers it usually cannot see; AddressSanitizer can
// ("stack-use-after-scope"), and Clings has it on. In production, these
// bugs show up as values that mysteriously change, or crashes far from
// the cause.
//
// The rule: a pointer must not outlive the object it points to. When you
// take an address, ask "how long does this live, and how long will I
// keep the pointer?"
//
// WHEN YOU USE THIS
// Every time you store a pointer somewhere: in a struct, a global, a
// return value. Lifetime is *the* thing to think about in C, and the
// memory section makes it explicit with malloc and free.
//
// TASK
// Fix both bugs. Do not remove the inner block; instead, declare
// `largest` where it lives long enough, and give `p` a proper target.
//
// EXPECTED OUTPUT
//     doubled: 10
//     largest: 42

#include <stdio.h>

int main(void)
{
    int *p;
    *p = 5;
    printf("doubled: %d\n", *p * 2);

    int values[] = {7, 42, 3};
    int *best;
    {
        int largest = values[0];
        for (int i = 1; i < 3; i++) {
            if (values[i] > largest) {
                largest = values[i];
            }
        }
        best = &largest;
    }
    printf("largest: %d\n", *best);
    return 0;
}
