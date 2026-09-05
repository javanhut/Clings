// arrays3.c - solution

#include <stdio.h>

#define ROWS 2
#define COLS 3

int main(void)
{
    int grid[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
    };

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (c > 0) {
                printf(" ");
            }
            printf("%d", grid[r][c]);
        }
        printf("\n");
    }
    return 0;
}
