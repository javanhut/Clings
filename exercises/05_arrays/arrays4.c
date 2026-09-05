// arrays4.c
//
// CONCEPT
// When an array is passed to a function, it is not copied. What the
// function receives is a *pointer to the first element*; the array
// "decays" to a pointer. A parameter written `int values[]` is exactly the
// same as `int *values`. Consequently `sizeof(values)` inside the function
// is the size of a pointer (8 bytes), not of the array, and the trick from
// arrays2 silently gives the wrong count. -Wall warns about `sizeof` on an
// array parameter for exactly this reason.
//
// The C way is to pass the length alongside the array:
//
//     int sum(const int *values, size_t len);
//
// `const` says the function only reads the elements. Every function that
// takes an array takes a length, or relies on a terminator (strings end
// in '\0', argv ends in NULL).
//
// WHEN YOU USE THIS
// Every function that works on an array. Signatures like
// `(const T *items, size_t count)` are the C equivalent of a slice.
//
// TASK
// `sum` computes its length from sizeof and gets it wrong. Change it to
// take the length as a parameter (computed by the caller, where sizeof
// still works) and fix the call in main.
//
// EXPECTED OUTPUT
//     sum is 150

#include <stdio.h>

int sum(const int values[])
{
    size_t len = sizeof(values) / sizeof(values[0]);
    int total = 0;

    for (size_t i = 0; i < len; i++) {
        total += values[i];
    }
    return total;
}

int main(void)
{
    int numbers[] = {10, 20, 30, 40, 50};

    printf("sum is %d\n", sum(numbers));
    return 0;
}
