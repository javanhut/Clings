// memory4.c
//
// CONCEPT
// After `free(p)`, the memory may be handed to the next malloc at any
// time. The pointer still holds the old address, but it is now
// *dangling*: reading through it is a use-after-free, and freeing it
// again is a double free. Both are undefined behavior, both are among
// the most exploited bug classes in C software, and both are silent
// without a sanitizer: the program often keeps "working" until it does
// not.
//
// Defensive habits:
//   - free at one clear point, usually the end of the function or a
//     dedicated `_destroy` function, after the last use,
//   - set the pointer to NULL right after freeing it when it stays in
//     scope (`free(p); p = NULL;`); free(NULL) is a no-op, so a second
//     free becomes harmless and a use becomes an obvious NULL crash,
//   - when two structures point to the same block, decide which one
//     *owns* it; only the owner frees.
//
// WHEN YOU USE THIS
// Every time you free something. The question "could anything still be
// pointing at this?" is the discipline.
//
// TASK
// The program frees too early and then frees again. Run it and read the
// AddressSanitizer report ("heap-use-after-free", then it would be
// "double-free"). Fix the order of operations and remove the double
// free; keep exactly one free.
//
// EXPECTED OUTPUT
//     total: 15
//     first: 1

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *numbers = malloc(5 * sizeof *numbers);

    if (numbers == NULL) {
        return 1;
    }
    for (int i = 0; i < 5; i++) {
        numbers[i] = i + 1;
    }
    free(numbers);

    int total = 0;
    for (int i = 0; i < 5; i++) {
        total += numbers[i];
    }
    printf("total: %d\n", total);
    printf("first: %d\n", numbers[0]);
    free(numbers);
    return 0;
}
