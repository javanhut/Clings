// arrays3.c
//
// A two-dimensional array is an array of arrays. `grid[row][col]` picks a
// row first, then a column within it. Fill in the two `???` so that the
// program prints the grid row by row:
//
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

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (col > 0) {
                printf(" ");
            }
            printf("%d", grid[row][col]);
        }
        printf("\n");
    }
    return 0;
}
