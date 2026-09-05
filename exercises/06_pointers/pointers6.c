// pointers6.c
//
// CONCEPT
// Instead of an index, a loop can move a pointer through an array:
//
//     for (const int *p = begin; p != end; p++) { ... *p ... }
//
// `end` is the address one past the last element (`values + len`). That
// position may be computed and compared, but never dereferenced. This
// [begin, end) style is how the C library, and later C++, describe
// ranges. A function can return a pointer *into* the array to say "here
// is what I found", and NULL to say "nothing"; the caller gets the index
// back with `found - begin`.
//
// WHEN YOU USE THIS
// Parsers and tokenizers keep a "cursor" pointer into the input.
// strchr/strstr/memchr all return pointers into their input. Being fluent
// with pointer-walking loops is what makes C library code readable.
//
// TASK
// Write `sum_range` and `find_first` using pointer arithmetic only: no
// indexing with [] and no size_t counters inside the functions.
//
// EXPECTED OUTPUT
//     sum = 60
//     sum of middle = 45
//     15 found at index 2
//     99 not found

#include <stddef.h>
#include <stdio.h>

int sum_range(const int *begin, const int *end)
{
    // TODO
    (void)begin;
    (void)end;
    return 0;
}

const int *find_first(const int *begin, const int *end, int target)
{
    // TODO: return a pointer to the first element equal to target, or NULL.
    (void)begin;
    (void)end;
    (void)target;
    return NULL;
}

int main(void)
{
    int values[] = {5, 10, 15, 20, 10};
    size_t len = sizeof(values) / sizeof(values[0]);
    const int *end = values + len;

    printf("sum = %d\n", sum_range(values, end));
    printf("sum of middle = %d\n", sum_range(values + 1, end - 1));

    const int *hit = find_first(values, end, 15);
    if (hit != NULL) {
        printf("15 found at index %td\n", hit - values);
    }
    if (find_first(values, end, 99) == NULL) {
        printf("99 not found\n");
    }
    return 0;
}
