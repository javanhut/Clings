// memory5.c
//
// CONCEPT
// A *leak* is memory that was allocated and never freed. In a short
// program it does not matter; in a server that handles a million
// requests, a 100-byte leak per request is 100 MB gone per million.
// Leaks hide in error paths: the function allocates, something fails,
// and the `return` skips the free.
//
// The C pattern for "several resources, several ways to fail" is a
// single exit point with cleanup, using goto (see ternary1):
//
//     char *a = malloc(...);  if (!a) goto fail_a;
//     char *b = malloc(...);  if (!b) goto fail_b;
//     ... work ...
//     result = 0;
//     free(b);
//     fail_b: free(a);
//     fail_a: return result;
//
// or, simpler when the pointers start as NULL: initialize every pointer
// to NULL, and unconditionally free all of them at one `cleanup:` label
// (free(NULL) does nothing).
//
// LeakSanitizer (part of AddressSanitizer on Linux) prints "detected
// memory leaks" at exit with the allocation site. On macOS leak checking
// is off by default, so this exercise is checked by output there.
//
// WHEN YOU USE THIS
// Any function with more than one allocation or more than one way to
// fail. Which is most of them.
//
// TASK
// `process` leaks on two of its paths. Restructure it with one cleanup
// label so every path frees both buffers exactly once, and returns the
// same values as before. Do not change main.
//
// EXPECTED OUTPUT
//     process(3) = 0
//     process(-1) = -1
//     process(100) = -2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Returns 0 on success, -1 for a negative size, -2 for a size over 50.
int process(int size)
{
    if (size < 0) {
        return -1;
    }
    char *input = malloc(64);
    if (input == NULL) {
        return -3;
    }
    memset(input, 'x', 63);
    input[63] = '\0';

    if (size > 50) {
        return -2;
    }
    char *output = malloc(64);
    if (output == NULL) {
        return -3;
    }
    memcpy(output, input, (size_t)size);
    output[size] = '\0';

    free(output);
    free(input);
    return 0;
}

int main(void)
{
    printf("process(3) = %d\n", process(3));
    printf("process(-1) = %d\n", process(-1));
    printf("process(100) = %d\n", process(100));
    return 0;
}
