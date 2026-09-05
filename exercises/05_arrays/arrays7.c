// arrays7.c
//
// CONCEPT
// Binary search finds a value in a *sorted* array in about log2(n) steps:
// look at the middle element; if it is the target, done; if it is smaller,
// the target can only be in the right half; otherwise in the left half.
// Keep two indices, `lo` and `hi`, for the range still possible.
//
// Two classic traps:
//   - computing the middle as `(lo + hi) / 2` can overflow for huge
//     arrays; `lo + (hi - lo) / 2` cannot,
//   - with unsigned indices, `hi = mid - 1` when mid is 0 wraps around.
//     Using a half-open range [lo, hi) where hi is "one past the last
//     candidate" avoids the -1 entirely: shrink with `hi = mid` and
//     `lo = mid + 1`, and stop when `lo == hi`.
//
// Inserting into a sorted array means shifting everything after the
// insertion point one slot to the right, starting from the *end* (or you
// overwrite what you have not moved yet). The array needs spare capacity.
//
// WHEN YOU USE THIS
// Binary search is in every symbol table, every "find the bucket for this
// value" in a range table, and in the standard library as bsearch. The
// shifting insert is how small sorted arrays and insertion sort work.
//
// TASK
// Write `find` (returns the index of `target` or -1) using the half-open
// binary search described above, and `insert_sorted`, which inserts
// `value` into the sorted array `a` that currently holds `*len` elements
// (and has room for one more), keeping it sorted and updating `*len`.
// `len` is passed as a pointer so the function can change the caller's
// count; that is the pointers section, but the mechanics are just
// `*len` to read or write it.
//
// EXPECTED OUTPUT
//     find(23) = 5
//     find(2) = 0
//     find(91) = 9
//     find(50) = -1
//     after insert: 2 5 8 12 16 23 38 50 56 72 91

#include <stddef.h>
#include <stdio.h>

int find(const int *a, size_t len, int target)
{
    // TODO
    (void)a;
    (void)len;
    (void)target;
    return -1;
}

void insert_sorted(int *a, size_t *len, int value)
{
    // TODO
    (void)a;
    (void)len;
    (void)value;
}

int main(void)
{
    int a[16] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    size_t len = 10;

    printf("find(23) = %d\n", find(a, len, 23));
    printf("find(2) = %d\n", find(a, len, 2));
    printf("find(91) = %d\n", find(a, len, 91));
    printf("find(50) = %d\n", find(a, len, 50));
    insert_sorted(a, &len, 50);
    printf("after insert:");
    for (size_t i = 0; i < len; i++) {
        printf(" %d", a[i]);
    }
    printf("\n");
    return 0;
}
