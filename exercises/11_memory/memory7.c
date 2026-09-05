// memory7.c
//
// CONCEPT
// Building a string of unknown length is a two-pass job in C:
//   1. compute the exact length (walk the inputs, add up strlen),
//   2. allocate length + 1, then copy the pieces in.
// The alternative, growing a buffer while appending, is what memory2's
// vector does; the two-pass version is simpler when the inputs are all
// known up front.
//
// `strdup(s)` (POSIX, and standard since C23) is malloc + strcpy: a
// heap copy the caller owns. Writing your own is a ten-line exercise
// that makes the ownership obvious. A function that returns a
// heap-allocated string should say so in a comment, every time:
// "Returns a newly allocated string; the caller frees it."
//
// WHEN YOU USE THIS
// Joining paths, building command lines, formatting messages, copying
// strings into structs that outlive their source. Half of all C string
// bugs are somebody forgetting the + 1 for the terminator.
//
// TASK
// Write `my_strdup` and `join`, which concatenates `count` strings with
// `sep` between them into a newly allocated string ("" for count 0).
// Both return NULL on allocation failure.
//
// EXPECTED OUTPUT
//     copy: clings (same memory: no)
//     joined: usr/local/bin
//     joined: alpha, beta
//     joined: ''

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Returns a newly allocated copy of s; the caller frees it.
char *my_strdup(const char *s)
{
    // TODO
    (void)s;
    return NULL;
}

// Returns a newly allocated string; the caller frees it.
char *join(const char **parts, size_t count, const char *sep)
{
    // TODO: two passes, length then copy.
    (void)parts;
    (void)count;
    (void)sep;
    return NULL;
}

int main(void)
{
    const char *original = "clings";
    char *copy = my_strdup(original);
    const char *path[] = {"usr", "local", "bin"};
    const char *greek[] = {"alpha", "beta"};

    if (copy == NULL) {
        return 1;
    }
    printf("copy: %s (same memory: %s)\n", copy, copy == original ? "yes" : "no");
    free(copy);

    char *j1 = join(path, 3, "/");
    char *j2 = join(greek, 2, ", ");
    char *j3 = join(path, 0, "/");
    if (j1 == NULL || j2 == NULL || j3 == NULL) {
        return 1;
    }
    printf("joined: %s\n", j1);
    printf("joined: %s\n", j2);
    printf("joined: '%s'\n", j3);
    free(j1);
    free(j2);
    free(j3);
    return 0;
}
