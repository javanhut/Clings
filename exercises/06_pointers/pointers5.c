// pointers5.c
//
// CONCEPT
// A C function returns one value. When it has more to say, the extra
// results go through *output parameters*: the caller passes the address
// of a variable, and the function writes into it. By convention the
// return value is then used for success/failure, and the outputs are only
// valid when the call succeeded.
//
//     bool divmod(int a, int b, int *quotient, int *remainder);
//
//     int q, r;
//     if (divmod(17, 5, &q, &r)) { ... use q and r ... }
//
// Sometimes a caller does not care about one of the outputs; a friendly
// function accepts NULL for it and skips the write.
//
// WHEN YOU USE THIS
// This is the standard C error-handling shape: `int parse(const char *s,
// int *out)`, `bool lookup(table, key, value *out)`. The alternative,
// returning a struct, works too but is less common in C APIs.
//
// TASK
// Write `divmod`, which returns false (and writes nothing) when b is 0,
// and `min_max`, which finds the smallest and largest of `len` values;
// either output pointer may be NULL, meaning "not interested".
//
// EXPECTED OUTPUT
//     17 / 5 = 3 remainder 2
//     division by zero
//     min 3, max 42
//     max only: 42

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool divmod(int a, int b, int *quotient, int *remainder)
{
    // TODO
    (void)a;
    (void)b;
    (void)quotient;
    (void)remainder;
    return false;
}

void min_max(const int *values, size_t len, int *min, int *max)
{
    // TODO: len is at least 1. min or max may be NULL.
    (void)values;
    (void)len;
    (void)min;
    (void)max;
}

int main(void)
{
    int q = 0;
    int r = 0;
    int values[] = {7, 42, 3, 19};
    int lo = 0;
    int hi = 0;

    if (divmod(17, 5, &q, &r)) {
        printf("17 / 5 = %d remainder %d\n", q, r);
    }
    if (!divmod(1, 0, &q, &r)) {
        printf("division by zero\n");
    }
    min_max(values, 4, &lo, &hi);
    printf("min %d, max %d\n", lo, hi);
    hi = 0;
    min_max(values, 4, NULL, &hi);
    printf("max only: %d\n", hi);
    return 0;
}
