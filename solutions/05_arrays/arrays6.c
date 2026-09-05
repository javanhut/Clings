// arrays6.c - solution

#include <stdio.h>

#define ROWS 2
#define COLS 3

void transpose(int in[ROWS][COLS], int out[COLS][ROWS])
{
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            out[c][r] = in[r][c];
        }
    }
}

void row_sums(int m[ROWS][COLS])
{
    for (int r = 0; r < ROWS; r++) {
        int sum = 0;
        for (int c = 0; c < COLS; c++) {
            sum += m[r][c];
        }
        printf("row %d: %d\n", r, sum);
    }
}

int main(void)
{
    int m[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
    };
    int t[COLS][ROWS] = {{0}};

    row_sums(m);
    transpose(m, t);
    printf("transposed:\n");
    for (int r = 0; r < COLS; r++) {
        for (int c = 0; c < ROWS; c++) {
            if (c > 0) {
                printf(" ");
            }
            printf("%d", t[r][c]);
        }
        printf("\n");
    }
    return 0;
}
