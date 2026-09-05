// memory1.c
//
// CONCEPT
// Local variables and arrays live on the *stack*: automatically created
// when a function starts, destroyed when it returns, limited in size
// (a few megabytes in total). When you need memory that outlives the
// function, or whose size is only known at run time, or is large, you
// ask the *heap* for it:
//
//     int *p = malloc(count * sizeof *p);   // count ints, uninitialized
//     if (p == NULL) { /* out of memory */ }
//     ...
//     free(p);                              // give it back
//
// malloc takes a number of *bytes* and returns `void *`, a pointer to
// untyped memory that converts to any pointer type. `sizeof *p` (the
// size of what p points to) is the idiom that stays correct if p's type
// changes. Every malloc needs exactly one free, when you are done and
// never before. Memory you forget to free is a *leak*; LeakSanitizer
// reports leaks when the program exits.
//
// WHEN YOU USE THIS
// Reading a file of unknown size, building lists and trees, returning a
// string from a function, any buffer bigger than a few kilobytes. Manual
// memory management is the defining feature of C; the next exercises
// cover each way it goes wrong.
//
// TASK
// Replace `???` with the right number of bytes for `count` ints, and
// free the memory at the end.
//
// EXPECTED OUTPUT
//     Squares: 0 1 4 9 16

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int count = 5;
    int *squares = malloc(???);

    if (squares == NULL) {
        return 1;
    }

    for (int i = 0; i < count; i++) {
        squares[i] = i * i;
    }

    printf("Squares:");
    for (int i = 0; i < count; i++) {
        printf(" %d", squares[i]);
    }
    printf("\n");

    // TODO: give the memory back.
    return 0;
}
