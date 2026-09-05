// pointers3.c
//
// CONCEPT
// An array's name, used in an expression, becomes a pointer to its first
// element: `values` is `&values[0]`. Adding an integer to a pointer moves
// it that many *elements* (not bytes): `p + 1` is the address of the next
// int, 4 bytes further. And `values[i]` is defined as `*(values + i)`;
// indexing *is* pointer arithmetic.
//
// Subtracting two pointers into the same array gives the number of
// elements between them, as a `ptrdiff_t` (printed with %td). Comparing
// pointers with `<` is valid within one array. Arithmetic that leaves the
// array (except for the position one past the end, used as a bound) is
// undefined behavior.
//
// WHEN YOU USE THIS
// Walking buffers with a moving pointer instead of an index, computing
// "how far did we parse", returning a pointer into an array from a search
// function (strchr, strstr do this), passing a sub-array as
// `values + start`.
//
// TASK
// Replace the `???` so that `last` points to the last element, `second`
// to the second element, and `distance` is the number of elements between
// `values` and `last`.
//
// EXPECTED OUTPUT
//     first: 5
//     second: 10
//     last: 20
//     last is 3 elements after first

#include <stddef.h>
#include <stdio.h>

int main(void)
{
    int values[] = {5, 10, 15, 20};
    size_t count = sizeof(values) / sizeof(values[0]);
    int *first = values;
    int *second = ???;
    int *last = ???;
    ptrdiff_t distance = ???;

    printf("first: %d\n", *first);
    printf("second: %d\n", *second);
    printf("last: %d\n", *last);
    printf("last is %td elements after first\n", distance);
    return 0;
}
