// ub5.c
//
// CONCEPT
// A grand tour. Each function below has one classic bug that the
// earlier sections covered; here they are together, the way you meet
// them in a real code review. The sanitizer output names each one. In
// order of appearance:
//
//   1. off-by-one write past a stack array (stack-buffer-overflow),
//   2. use of heap memory after free (heap-use-after-free),
//   3. a shift by the full width of the type (UB: shift exponent),
//   4. a string copy into a buffer one byte too small (heap-buffer-
//      overflow, from strlen without + 1),
//   5. a null pointer dereference that a missing check lets through.
//
// The point of the exercise is not the fixes, which are small; it is
// recognizing each pattern on sight, and reading a sanitizer report
// down to the line that matters.
//
// WHEN YOU USE THIS
// Reviewing code, yours and others'. Keep -fsanitize=address,undefined
// on in every debug build of every C project you touch; the cost is a
// 2x slowdown, the benefit is finding these bugs in the first test run
// instead of in production.
//
// TASK
// Fix all five. Run the program between fixes and watch the report
// change.
//
// EXPECTED OUTPUT
//     squares: 0 1 4 9 16
//     doubled: 2 4 6
//     mask: 0xffffffff
//     copy: sanitize
//     length of NULL: 0

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void squares(void)
{
    int sq[5];

    for (int i = 0; i <= 5; i++) {
        sq[i] = i * i;
    }
    printf("squares: %d %d %d %d %d\n", sq[0], sq[1], sq[2], sq[3], sq[4]);
}

static void doubled(void)
{
    int *v = malloc(3 * sizeof *v);

    if (v == NULL) {
        return;
    }
    for (int i = 0; i < 3; i++) {
        v[i] = i + 1;
    }
    free(v);
    printf("doubled: %d %d %d\n", v[0] * 2, v[1] * 2, v[2] * 2);
}

static uint32_t low_mask(unsigned int bits)
{
    return (1u << bits) - 1;
}

static void copy(void)
{
    const char *src = "sanitize";
    char *dst = malloc(strlen(src));

    if (dst == NULL) {
        return;
    }
    strcpy(dst, src);
    printf("copy: %s\n", dst);
    free(dst);
}

static size_t length(const char *s)
{
    return strlen(s);
}

int main(void)
{
    squares();
    doubled();
    printf("mask: %#x\n", low_mask(32));
    copy();
    printf("length of NULL: %zu\n", length(NULL));
    return 0;
}
