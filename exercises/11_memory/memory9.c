// memory9.c
//
// CONCEPT
// Three sizing mistakes account for a large share of heap bugs:
//
//   1. `malloc(strlen(s))` for a string copy: one byte short, the
//      terminator lands past the end (heap-buffer-overflow by one).
//   2. `sizeof(p)` where p is a pointer: that is 8, the size of the
//      pointer, not of what it points to. `sizeof *p` is what you meant;
//      `sizeof(struct foo)` also works but does not follow type changes.
//   3. `malloc(n)` for n ints: forgetting to multiply by the element
//      size. Only a quarter of the elements fit.
//
// The idioms that avoid them:
//     char *copy = malloc(strlen(s) + 1);
//     struct foo *f = malloc(sizeof *f);
//     int *a = malloc(n * sizeof *a);        // or calloc(n, sizeof *a)
//
// AddressSanitizer reports each of these as a heap-buffer-overflow with
// the allocation site and the access site; the number of bytes past the
// end tells you which mistake it was.
//
// WHEN YOU USE THIS
// Every allocation. Read each malloc argument and ask: is it a count of
// bytes, and is it the right count?
//
// TASK
// The program has all three bugs. Fix the sizes; do not change the
// logic.
//
// EXPECTED OUTPUT
//     copy: sanitizers are great
//     point: (3, 4)
//     sum: 45

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point {
    int x;
    int y;
};

int main(void)
{
    const char *text = "sanitizers are great";
    char *copy = malloc(strlen(text));
    if (copy == NULL) {
        return 1;
    }
    strcpy(copy, text);
    printf("copy: %s\n", copy);
    free(copy);

    struct point *pt = malloc(sizeof pt);
    if (pt == NULL) {
        return 1;
    }
    pt->x = 3;
    pt->y = 4;
    printf("point: (%d, %d)\n", pt->x, pt->y);
    free(pt);

    int n = 10;
    int *values = malloc(n);
    if (values == NULL) {
        return 1;
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
        values[i] = i;
        sum += values[i];
    }
    printf("sum: %d\n", sum);
    free(values);
    return 0;
}
