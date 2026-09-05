// arrays5.c
//
// CONCEPT
// Functions on arrays come in two flavors:
//   - *read-only*: take `const T *`, return a computed value
//     (max, sum, search),
//   - *in-place*: take `T *` and modify the elements (reverse, sort, fill).
// In-place operations are the norm in C because copying costs memory and
// time, and because the caller owns the array anyway. Returning a new
// array is not possible without dynamic allocation.
//
// Swapping two elements needs a temporary: `int t = a[i]; a[i] = a[j];
// a[j] = t;`. Reversing in place swaps a[0] with a[n-1], a[1] with a[n-2],
// and stops in the middle. For an empty array (n == 0) all of these must do
// nothing and not touch memory, so think about the loop bounds.
//
// WHEN YOU USE THIS
// This is what most C code does all day: walk a buffer, compute, transform.
// Getting the `size_t`-indexed loops right, including for length 0 and 1,
// is the skill.
//
// TASK
// Write:
//   index_of_max(values, len)  index of the largest element (first one if
//                              there are ties); len is never 0 here
//   reverse(values, len)       reverse the array in place
//   count_if_even(values, len) how many elements are even
// and `print_array`, which prints the elements separated by single spaces
// on one line, or "(empty)" for len 0.
//
// EXPECTED OUTPUT
//     3 8 -2 8 5
//     max at index 1
//     3 even numbers
//     reversed: 5 8 -2 8 3
//     single: 42
//     empty: (empty)

#include <stddef.h>
#include <stdio.h>

size_t index_of_max(const int *values, size_t len)
{
    // TODO
    (void)values;
    (void)len;
    return 0;
}

void reverse(int *values, size_t len)
{
    // TODO
    (void)values;
    (void)len;
}

size_t count_if_even(const int *values, size_t len)
{
    // TODO
    (void)values;
    (void)len;
    return 0;
}

void print_array(const int *values, size_t len)
{
    // TODO
    (void)values;
    (void)len;
}

int main(void)
{
    int numbers[] = {3, 8, -2, 8, 5};
    size_t len = sizeof(numbers) / sizeof(numbers[0]);
    int single[] = {42};

    print_array(numbers, len);
    printf("max at index %zu\n", index_of_max(numbers, len));
    printf("%zu even numbers\n", count_if_even(numbers, len));
    reverse(numbers, len);
    printf("reversed: ");
    print_array(numbers, len);
    reverse(single, 1);
    printf("single: ");
    print_array(single, 1);
    reverse(numbers, 0);
    printf("empty: ");
    print_array(numbers, 0);
    return 0;
}
