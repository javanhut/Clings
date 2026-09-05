// types5.c
//
// CONCEPT
// When a signed and an unsigned integer of the same size meet in an
// expression, C converts the *signed* one to unsigned. -1 becomes
// 4294967295. So `-1 < 10u` is false, and a loop like
//
//     for (int i = 0; i < strlen(s) - 1; i++)
//
// runs "forever" on an empty string, because `strlen(s) - 1` is not -1 but
// the largest size_t there is. `size_t` (the type of sizeof and strlen) is
// unsigned, so this trap is everywhere. -Wextra enables -Wsign-compare,
// which flags these comparisons, which is why this file does not compile
// under Clings.
//
// WHEN YOU USE THIS
// Every loop over an array indexed by size_t, every comparison with
// `.size()`-like values. The safe habits: index arrays with size_t; count
// down with `for (size_t i = n; i-- > 0;)` instead of `i >= 0`; and never
// subtract from an unsigned value without checking it is big enough.
//
// TASK
// The program has two bugs of this kind. Fix both by changing types or by
// rewriting the comparisons, so it compiles warning-free and prints the
// expected output. Do not remove the checks, and keep the loop counting
// down.
//
// EXPECTED OUTPUT
//     -1 is smaller than 10
//     4 3 2 1 0

#include <stdio.h>

int main(void)
{
    int negative = -1;
    unsigned int limit = 10;

    if (negative < limit) {
        printf("%d is smaller than %u\n", negative, limit);
    } else {
        printf("%d is NOT smaller than %u\n", negative, limit);
    }

    int values[] = {0, 1, 2, 3, 4};
    size_t count = sizeof(values) / sizeof(values[0]);
    for (size_t i = count - 1; i >= 0; i--) {
        printf("%d ", values[i]);
        if (i == 0) {
            break;
        }
    }
    printf("\n");
    return 0;
}
