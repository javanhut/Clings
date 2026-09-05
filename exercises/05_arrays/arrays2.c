// arrays2.c
//
// CONCEPT
// An array does not carry its length; you have to know it. Inside the
// scope where the array is declared, `sizeof` can compute it:
//
//     sizeof(numbers)                 // total bytes, e.g. 24
//     sizeof(numbers[0])              // bytes of one element, e.g. 4
//     sizeof(numbers) / sizeof(numbers[0])   // element count, 6
//
// Many code bases wrap that in a macro, `ARRAY_LEN(a)`. The result has
// type size_t (unsigned), printed with %zu.
//
// WHEN YOU USE THIS
// Any array whose contents may be edited later: a table of commands, a
// list of test cases, a set of default values. Hardcoding the count means
// the next person to add an entry forgets to bump it and the last entry is
// silently ignored (or, with `<=`, one past the end is read).
//
// TASK
// `len` is hardcoded to the wrong number. Compute it with sizeof so the
// program still works if more numbers are added.
//
// EXPECTED OUTPUT
//     The array has 6 elements and their sum is 21

#include <stdio.h>

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, 6};
    size_t len = 4;
    int sum = 0;

    for (size_t i = 0; i < len; i++) {
        sum += numbers[i];
    }
    printf("The array has %zu elements and their sum is %d\n", len, sum);
    return 0;
}
