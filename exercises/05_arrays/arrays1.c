// arrays1.c
//
// CONCEPT
// `int numbers[5]` is five ints stored back to back in memory. Indices
// start at 0, so the valid ones are 0 to 4. There is no bounds checking:
// `numbers[5]` reads whatever int happens to sit after the array. That is
// undefined behavior: it may print garbage, crash, or appear to work,
// depending on what is there, and it can silently corrupt other variables
// when you *write* past the end. Buffer overflows of this kind are the
// root of most security vulnerabilities in C programs.
//
// Clings compiles with AddressSanitizer, which adds the bounds checking C
// lacks and stops the program with a report the moment the loop reads
// past the end. Run this exercise as it is and read that report: it names
// the line, and says how far past the array the access was.
//
// Initialization: `int a[3] = {1, 2, 3};` sets all; `int a[3] = {0};`
// zeroes all (missing initializers are 0); `int a[3];` is garbage.
// `int a[] = {1, 2, 3};` lets the compiler count.
//
// WHEN YOU USE THIS
// Arrays are the fundamental container of C: strings, buffers, tables,
// matrices. Every loop over one is a chance for an off-by-one. The `<`
// form of the loop condition, `i < length`, is the one to write by reflex.
//
// TASK
// Fix the loop bound.
//
// EXPECTED OUTPUT
//     10 20 30 40 50

#include <stdio.h>

int main(void)
{
    int numbers[5] = {10, 20, 30, 40, 50};

    for (int i = 0; i <= 5; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", numbers[i]);
    }
    printf("\n");
    return 0;
}
