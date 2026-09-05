// arrays6.c
//
// CONCEPT
// A 2D array can be passed to a function, but the function must know the
// number of *columns*, because that is what it needs to find row r: the
// address of `m[r][c]` is `start + (r * COLS + c) * sizeof(int)`. So the
// parameter is written with the column count and an open row count:
//
//     void print_matrix(int m[][COLS], int rows);
//
// (`int (*m)[COLS]` means the same: a pointer to rows of COLS ints.) Since
// C99 the column count can also be a runtime value that comes earlier in
// the parameter list, `void f(int rows, int cols, int m[rows][cols])`, a
// "variable length array" parameter; it is handy but not universally
// loved, so most code uses a fixed COLS or a flat 1D array with manual
// indexing.
//
// WHEN YOU USE THIS
// Any grid processing: game boards, image kernels, matrix arithmetic,
// dynamic programming tables.
//
// TASK
// Write `transpose`, which writes the transpose of `in` (ROWS x COLS)
// into `out` (COLS x ROWS): out[c][r] = in[r][c]. Then write `row_sums`,
// which prints "row r: sum" for each row of a ROWS x COLS matrix.
//
// EXPECTED OUTPUT
//     row 0: 6
//     row 1: 15
//     transposed:
//     1 4
//     2 5
//     3 6

#include <stdio.h>

#define ROWS 2
#define COLS 3

void transpose(int in[ROWS][COLS], int out[COLS][ROWS])
{
    // TODO
    (void)in;
    (void)out;
}

void row_sums(int m[ROWS][COLS])
{
    // TODO
    (void)m;
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
