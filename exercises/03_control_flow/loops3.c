// loops3.c
//
// CONCEPT
// Loops nest: the body of a loop can contain another loop, and the inner
// one runs to completion for every single iteration of the outer one. Two
// nested loops over n items do n*n units of work, which is why nesting
// depth matters for performance.
//
// printf can pad a number to a fixed width: `%3d` prints an int right-
// aligned in 3 columns (" 12"), `%-5s` prints a string left-aligned in 5.
// That is how you print tables that line up.
//
// WHEN YOU USE THIS
// Grids, matrices, images (rows and columns), comparing every pair of
// items, generating combinations. Nested loops are the workhorse of
// numeric code; knowing which index is "outer" decides whether you walk
// memory in order (fast) or jump around (slow).
//
// TASK
// Write the loops that print a 4x4 multiplication table. Each cell is
// `row * col` printed with %3d; each row is one line; rows and columns
// both go from 1 to 4.
//
// EXPECTED OUTPUT
//       1  2  3  4
//       2  4  6  8
//       3  6  9 12
//       4  8 12 16

#include <stdio.h>

int main(void)
{
    // TODO: nested loops.

    return 0;
}
