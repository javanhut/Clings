// arrays3.c
//
// CONCEPT
// A two-dimensional array is an array of arrays. `int grid[2][3]` is two
// rows, each an array of three ints, laid out in memory as one contiguous
// block of six ints, row after row ("row-major order"). `grid[r][c]`
// picks row r, then element c within it. `grid[r]` alone is the whole row.
//
// Because the rows are contiguous, walking the array with the column
// index in the *inner* loop touches memory in order, which the CPU cache
// rewards. Swapping the loops works but is slower on large arrays.
//
// WHEN YOU USE THIS
// Grids, boards, images, matrices, tables of fixed shape. When the shape is
// not known at compile time you use a dynamically allocated block and
// compute `row * cols + col` yourself; that comes in the memory section.
//
// TASK
// Fill in the two `???` to print the grid row by row.
//
// EXPECTED OUTPUT
//     1 2 3
//     4 5 6

#include <stdio.h>

#define ROWS 2
#define COLS 3

int main(void)
{
    int grid[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
    };

    for (int r = 0; r < ???; r++) {
        for (int c = 0; c < ???; c++) {
            if (c > 0) {
                printf(" ");
            }
            printf("%d", grid[r][c]);
        }
        printf("\n");
    }
    return 0;
}
